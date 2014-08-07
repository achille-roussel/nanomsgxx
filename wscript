#!/usr/bin/env python
# encoding: utf-8
import os
import sys

APPNAME = 'nanomsgxx'
VERSION = '0.1'

def build(waf):
    cflags   = ['-W', '-Wall', '-Wextra', '-fvisibility=hidden']
    cxxflags = ['-W', '-Wall', '-Wextra', '-std=c++11']
    defines  = []
    includes = [os.path.join(waf.path.abspath(), 'src')]
    libpath  = ['src/nanomsg/ext', 'src/nnxx']

    if waf.options.debug:
        cflags   += ['-g3']
        cxxflags += ['-g3']
    else:
        cflags   += ['-O3']
        cxxflags += ['-O3']
        defines  += ['NDEBUG=1']

    waf.env.C_CONF_KWARGS = {
        'includes': includes,
        'libpath' : libpath,
        'defines' : defines,
        'cflags'  : cflags,
    }

    waf.env.CXX_CONF_KWARGS = {
        'includes': includes,
        'libpath' : libpath,
        'defines' : defines,
        'cflags'  : cflags,
        'cxxflags': cxxflags,
    }

    waf.recurse('src/nanomsg/ext')
    waf.recurse('src/nnxx')
    if not waf.options.notests:
        waf.recurse('tests')
    if waf.env.with_doc:
        waf.recurse('doc')
    if waf.env.with_pkgconfig:
        waf(source='libnnxx.pc.in', install_path='${LIBDIR}/pkgconfig/')

def configure(waf):
    waf.load('compiler_c compiler_cxx c_config waf_unit_test')
    waf.recurse('src/nanomsg/ext')
    waf.recurse('src/nnxx')

    if waf.options.nodoc:
        waf.env.with_doc = False
    else:
        waf.env.with_doc = True
        try:
            waf.recurse('doc')
        except Exception:
            sys.stderr.write('Disabling documentation build...\n')
            waf.env.with_doc = False

    waf.env.with_pkgconfig = not waf.options.nopkgconfig
    waf.env.with_strip = waf.options.strip
    waf.env.install_html_path = waf.options.install_html_path

def dist(waf):
    waf.algo  = 'tar.gz'
    waf.files = all_files(waf)

def options(waf):
    def add_bool(name, help):
        waf.add_option(name, action='store_true', help=help)
    waf.load('compiler_c compiler_cxx waf_unit_test')
    add_bool('--debug', 'build in debug mode')
    add_bool('--static', 'build static library')
    add_bool('--shared', 'build shared library (default)')
    add_bool('--notests', 'turn off tests')
    add_bool('--nodoc', 'turn off documentation')
    add_bool('--nopkgconfig', 'turn off pkg-config support')
    add_bool('--strip', 'runs the \'strip\' utility on the build')
    waf.recurse('doc')
