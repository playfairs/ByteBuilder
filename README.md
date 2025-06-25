# ByteBuilder v1.0.0

A simple C++ tool for generating files of any size with custom content. Perfect for testing storage, benchmarking, or creating dummy data.

## Features

- Generate files from 1 byte to multiple yottabytes (theoretical limit, not sure how you could even have that much storage but whatever.)
- Supports various units: B, KB/KiB, MB/MiB, GB/GiB, TB/TiB, PB/PiB, EB/EiB, ZB/ZiB, YB/YiB (I get petabytes MAYBE, but if you have storage beyond that, what the fuck could you possibly need that for??)
- Choose exact folder location for file generation
- Progress bar with real-time statistics
- Cross-platform compatibility (Linux/macOS/Windows with WSL)
- Optimized for performance with large file operations

## Prerequisites

- C++17 compatible compiler (g++, clang++, or MSVC)
- CMake (optional, for alternative build method)
- Linux/macOS (or Windows with WSL)

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/playfairs/ByteBuilder.git
   cd bytebuilder
   ```

2. Make the start script executable:
   ```bash
   chmod +x start.sh
   ```

## Usage

### Basic Usage

1. Run the start script:
   ```bash
   ./start.sh
   ```

2. Follow the interactive prompts:
   - Enter the folder path where the file should be saved
   - Enter the desired filename
   - Enter the target size (e.g., 1GB, 500MB, 1.5TB)

### Command Line Arguments (Advanced)

For non-interactive use, you can compile and run directly:

```bash
g++ -std=c++17 -O3 -o ByteBuilder src/main.cpp
./ByteBuilder
```

## Examples

- Create a 1GB file:
  ```
  Size: 1GB
  ```

- Create a 2.5TB file:
  ```
  Size: 2.5TB
  ```

- Create a 500MB file using binary prefix:
  ```
  Size: 500MiB
  ```

## How It Works

1. The program allocates a 1MB buffer with sample content
2. It writes this buffer repeatedly to the target file
3. Progress is tracked and displayed in real-time
4. The file is precisely sized to the requested dimensions
5. All operations include error checking and validation

## Performance

- Uses buffered I/O for efficient writing
- Minimal memory footprint (1MB buffer)
- Progress updates every 100MB to reduce overhead
- Optimized for large file operations


## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Support

For issues or feature requests, please open an issue on the GitHub repository.# ByteBuilder
