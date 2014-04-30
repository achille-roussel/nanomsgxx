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

def c_files(waf):
    return waf.path.ant_glob('**/src/*.c')

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
    'cflags'  : ['-W',  '-Wall',  '-Wextra'],
    'cxxflags': ['-W',  '-Wall',  '-Wextra', '-std=c++11',  '-stdlib=libc++'],
    'defines' : [],
    'includes': ['src'],
}

def build_nanomsgext(waf):
    conf = copy(DEFAULT_CONF)
    conf.update({
        'lib'   : ['nanomsg'],
        'source': c_files(waf),
        'target': 'nanomsgext',
    })
    del conf['cxxflags']
    if waf.options.debug:
        conf['cflags'] += ['-g3']
    else:
        conf['cflags'] += ['-O3']
        conf['defines'] += ['NDEBUG=1']
    return waf.stlib(**conf)

def build_nanomsgxx(waf):
    conf = copy(DEFAULT_CONF)
    conf.update({
        'lib'      : ['nanomsg', 'nanomsgext'],
        'linkflags': ['-L.'],
        'source'   : cpp_files(waf),
        'target'   : 'nanomsgxx',
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

def build_tests(waf):
    if waf.options.no_tests:
        return []
    conf = copy(DEFAULT_CONF)
    conf.update({
        'features' : ['cxx', 'cxxprogram', 'test'],
        'lib'      : ['nanomsg', 'nanomsgxx', 'nanomsgext'],
        'linkflags': ['-L.'],
        'install_path': None,
    })

    tests = []
    for test_file in test_files(waf):
        conf['source'] = test_file, 
        conf['target'] = str(test_file)[:-4]
        tests.append(waf(**conf))

    from waflib.Tools import waf_unit_test
    waf.add_post_fun(waf_unit_test.summary)
    return tests

def setup_dependencies(libnanomsgext, libnanomsgxx, tests):
    libnanomsgext.post()
    libnanomsgxx.post()

    for t1 in libnanomsgxx.tasks:
        for t2 in libnanomsgext.tasks:
            t1.set_run_after(t2)

    for test in tests:
        test.post()
        for t1 in test.tasks:
            for t2 in libnanomsgxx.tasks:
                t1.set_run_after(t2)

def build(waf):
    libnanomsgext = build_nanomsgext(waf)
    libnanomsgxx  = build_nanomsgxx(waf)
    tests         = build_tests(waf)
    setup_dependencies(libnanomsgext, libnanomsgxx, tests)
    install_files(waf)

def configure(waf):
    waf.load('compiler_c compiler_cxx waf_unit_test')
    waf.check_cxx(
        lib = 'nanomsg'
    )

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
    add_bool('--no-tests', 'turn off tests')
