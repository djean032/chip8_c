project('chip8', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

exe = executable('chip8', 'main.c', 'chip8.c', 'instructions.c',
  install : true)

test('basic', exe)
