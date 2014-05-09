#!/usr/bin/env python
# encoding: utf-8

APPNAME = 'nanomsgxx'
VERSION = '0.1'

def build(waf):
    cflags   = ['-W', '-Wall', '-Wextra']
    cxxflags = ['-W', '-Wall', '-Wextra', '-std=c++11']
    defines  = []
    includes = ['src']
    libpath  = ['src/ext', 'src/nnxx']

    if waf.options.debug:
        cflags   += ['-g3']
        cxxflags += ['-g3']
    else:
        cflags   += ['-O3']
        cxxflags += ['-O3']
        defines  += ['NDEBUG=1']

    waf.env.DEFINES  += defines
    waf.env.INCLUDES += includes
    waf.env.CFLAGS   += cflags
    waf.env.CXXFLAGS += cxxflags

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

    waf.recurse('src/ext')
    waf.recurse('src/nnxx')
    if not waf.options.notests:
        waf.recurse('tests')

def configure(waf):
    waf.load('compiler_c compiler_cxx c_config waf_unit_test')
    waf.recurse('src/ext')
    waf.recurse('src/nnxx')
    if not waf.options.notests:
        waf.recurse('tests')

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
