#include <cassert>

#include "bytebuilder/args.h"

int main() {
  char program[] = "bytebuilder";
  char help[] = "--help";
  char* argv[] = {program, help};

  bytebuilder::Options options;
  const bytebuilder::Status status = bytebuilder::parse_args(2, argv, options);
  assert(status.ok);
  assert(options.help_requested);

  char create[] = "create";
  char create_help[] = "--help";
  char* create_argv[] = {program, create, create_help};
  bytebuilder::Options create_options;
  const bytebuilder::Status create_status = bytebuilder::parse_args(3, create_argv, create_options);
  assert(create_status.ok);
  assert(create_options.help_requested);
  return 0;
}
