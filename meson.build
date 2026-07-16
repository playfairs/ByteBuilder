project('bytebuilder', 'cpp', version: '2.0.0', default_options: ['cpp_std=c++20'])

cpp_args = ['-Wall', '-Wextra', '-Wpedantic']

inc = include_directories('include')

bytebuilder_lib = static_library(
  'bytebuilder',
  [
    'src/args.cpp',
    'src/filesize.cpp',
    'src/pattern.cpp',
    'src/progress.cpp',
    'src/random.cpp',
    'src/sparse.cpp',
    'src/util.cpp',
    'src/verify.cpp',
    'src/writer.cpp',
  ],
  include_directories: inc,
  cpp_args: cpp_args,
)

executable(
  'bytebuilder',
  'src/main.cpp',
  include_directories: inc,
  link_with: bytebuilder_lib,
  cpp_args: cpp_args,
  install: true,
  install_dir: get_option('bindir'),
)

subdir('tests')
