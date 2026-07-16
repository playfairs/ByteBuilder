#include <iostream>

#include "bytebuilder/args.h"
#include "bytebuilder/verify.h"
#include "bytebuilder/writer.h"

int main(int argc, char** argv) {
  bytebuilder::Options options;
  const bytebuilder::Status parse_status = bytebuilder::parse_args(argc, argv, options);
  if (!parse_status.ok) {
    std::cerr << parse_status.message << '\n';
    return 1;
  }
  if (options.help_requested) {
    return 0;
  }

  if (options.command == bytebuilder::Command::Create) {
    bytebuilder::WriteStatistics statistics;
    const bytebuilder::Status write_status = bytebuilder::write_file(
        options.output_path,
        options.size_bytes,
        options.pattern,
        options.seed,
        options.sparse,
        options.show_progress ? &std::cout : nullptr,
        &statistics);
    if (!write_status.ok) {
      std::cerr << write_status.message << '\n';
      return 1;
    }

    std::cout << "wrote " << bytebuilder::format_size(statistics.bytes_written) << " to "
              << options.output_path.string() << '\n';

    if (options.verify_after_write) {
      const bytebuilder::VerificationResult verification = bytebuilder::verify_file(
          options.output_path,
          options.size_bytes,
          options.pattern,
          options.seed,
          options.show_progress ? &std::cout : nullptr);
      if (!verification.ok) {
        std::cerr << verification.message << '\n';
        return 1;
      }
      std::cout << "verification succeeded" << '\n';
    }
    return 0;
  }

  const bytebuilder::VerificationResult verification = bytebuilder::verify_file(
      options.output_path,
      options.size_bytes,
      options.pattern,
      options.seed,
      options.show_progress ? &std::cout : nullptr);
  if (!verification.ok) {
    std::cerr << verification.message << '\n';
    return 1;
  }

  std::cout << "verified " << bytebuilder::format_size(verification.bytes_checked) << " with checksum "
            << verification.checksum << '\n';
  return 0;
}
