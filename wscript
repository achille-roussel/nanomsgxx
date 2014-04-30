#!/usr/bin/env python
# encoding: utf-8
from copy import copy
import os
import sys

APPNAME = 'nanomsgxx'
VERSION = '0.1'

# ==============================================================================
# Utilities
# ==============================================================================

def all_files(waf):
    return h_files(waf) + cpp_files(waf) + test_files(waf)

def h_files(waf):
    return waf.path.ant_glob('**/src/nnxx.h **/src/nnxx/*.h')

def cpp_files(waf):
    return waf.path.ant_glob('**/src/nnxx/*.cpp')

def test_files(waf):
    return waf.path.ant_glob('**/tests/*.cpp')

def install_files(waf):
    waf.install_files('${PREFIX}/include', h_files(waf))

# ==============================================================================
# Waf commands
# ==============================================================================

DEFAULT_CONF = {
    'cxxflags': ['-W',  '-Wall',  '-Wextra',  '-std=c++11',  '-stdlib=libc++'],
    'defines' : [],
    'includes': ['src'],
}

def build_nanomsgxx(waf):
    conf = copy(DEFAULT_CONF)
    conf.update({
        'lib'   : ['nanomsg'],
        'source': cpp_files(waf),
        'target': 'nanomsgxx',
    })
    if waf.options.debug:
        conf['cxxflags'] += ['-g3']
    else:
        conf['cxxflags'] += ['-O3']
        conf['defines']  += ['NDEBUG=1']

    if waf.options.static:
        libnanomsgxx = waf.stlib(**conf)
    else:
        libnanomsgxx = waf.shlib(**conf)
    return libnanomsgxx

def build_tests(waf, libnanomsgxx):
    conf = copy(DEFAULT_CONF)
    conf.update({
        'features' : ['cxx', 'cxxprogram', 'test'],
        'linkflags': ['-L.', '-lnanomsgxx'],
        'install_path': None,
    })

    tests = []
    for test_file in test_files(waf):
        conf['source'] = test_file, 
        conf['target'] = str(test_file)[:-4]
        tests.append(waf(**conf))

    libnanomsgxx.post()
    for test in tests:
        test.post()
        for t1 in test.tasks:
            for t2 in libnanomsgxx.tasks:
                t1.set_run_after(t2)

    from waflib.Tools import waf_unit_test
    waf.add_post_fun(waf_unit_test.summary)

def build(waf):
    libnanomsgxx = build_nanomsgxx(waf)
    if not waf.options.no_tests:
        build_tests(waf, libnanomsgxx)
    install_files(waf)

def configure(waf):
    waf.load('compiler_cxx waf_unit_test')
    waf.check_cxx(
        lib = 'nanomsg'
    )

def dist(waf):
    waf.algo  = 'tar.gz'
    waf.files = all_files(waf)

def options(waf):
    def add_bool(name, help):
        waf.add_option(name, action='store_true', help=help)
    waf.load('compiler_cxx waf_unit_test')
    add_bool('--debug', 'build in debug mode')
    add_bool('--static', 'build static library')
    add_bool('--shared', 'build shared library (default)')
    add_bool('--no-tests', 'turn off tests')
