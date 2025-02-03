project('chip8', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])
cc = meson.get_compiler('c')
lib_sdl = cc.find_library('SDL3-static',
             dirs: ['C:/Program Files (x86)/SDL3/lib'])
winmm = cc.find_library('winmm', required: true)
setupapi = cc.find_library('Setupapi', required: true)
imm = cc.find_library('imm32', required: true)
ole = cc.find_library('ole32', required: true)
oleaut = cc.find_library('oleaut32', required: true)
version = cc.find_library('Version', required: true)
inc_sdl = include_directories('C:/Program Files (x86)/SDL3/include')
inc_source = include_directories('include')
exe = executable('chip8', 'main.c', 'chip8.c', 'instructions.c', 'graphics.c',
  dependencies : [lib_sdl, winmm, setupapi, imm, ole, oleaut, version],
  include_directories : [inc_sdl, inc_source],
  install : true, c_args: '-std=c23', link_args: '-Wl,/NODEFAULTLIB:msvcrt') 

test('basic', exe)
