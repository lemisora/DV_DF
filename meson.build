project('DV-DF', 'c', version: '0.1')
#cpp_std = 'c++20'
bibliotecas_adicionales = ['-lm']
executable(
  'traductor',
  'src/main.c',
  'src/tabla_paginas.h',
  'src/tabla_paginas.c',
  'src/file_entries.h',
  'src/file_entries.c',
  link_args: bibliotecas_adicionales,
  install: true,
)
