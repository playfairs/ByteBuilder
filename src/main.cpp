#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <cmath>
#include <filesystem>

constexpr size_t BUFFER_SIZE = 1024 * 1024;

uint64_t parseSize(const std::string& sizeStr) {
    if (sizeStr.empty()) return 0;

    size_t endPos = 0;
    double value = std::stod(sizeStr, &endPos);

    while (endPos < sizeStr.length() && std::isspace(sizeStr[endPos])) {
        endPos++;
    }

    std::string unit;
    while (endPos < sizeStr.length()) {
        unit += std::toupper(sizeStr[endPos]);
        endPos++;
    }

    if (unit.empty() || unit == "B") {
        return static_cast<uint64_t>(value);
    } else if (unit == "KB") {
        return static_cast<uint64_t>(value * 1024);
    } else if (unit == "KIB") {
        return static_cast<uint64_t>(value * 1024);
    } else if (unit == "MB") {
        return static_cast<uint64_t>(value * 1024 * 1024);
    } else if (unit == "MIB") {
        return static_cast<uint64_t>(value * 1024 * 1024);
    } else if (unit == "GB") {
        return static_cast<uint64_t>(value * 1024 * 1024 * 1024);
    } else if (unit == "GIB") {
        return static_cast<uint64_t>(value * 1024 * 1024 * 1024);
    } else if (unit == "TB") {
        return static_cast<uint64_t>(value * 1024.0 * 1024 * 1024 * 1024);
    } else if (unit == "TIB") {
        return static_cast<uint64_t>(value * 1024.0 * 1024 * 1024 * 1024);
    } else if (unit == "PB") {
        return static_cast<uint64_t>(value * 1024.0 * 1024 * 1024 * 1024 * 1024);
    } else if (unit == "PIB") {
        return static_cast<uint64_t>(value * 1024.0 * 1024 * 1024 * 1024 * 1024);
    } else if (unit == "EB") {
        return static_cast<uint64_t>(value * 1024.0 * 1024 * 1024 * 1024 * 1024 * 1024);
    } else if (unit == "EIB") {
        return static_cast<uint64_t>(value * 1024.0 * 1024 * 1024 * 1024 * 1024 * 1024);
    } else if (unit == "ZB") {
        return static_cast<uint64_t>(value * 1024.0 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024);
    } else if (unit == "ZIB") {
        return static_cast<uint64_t>(value * 1024.0 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024);
    } else if (unit == "YB") {
        return static_cast<uint64_t>(value * 1024.0 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024);
    } else if (unit == "YIB") {
        return static_cast<uint64_t>(value * 1024.0 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024 * 1024);
    }

    throw std::invalid_argument("Invalid size unit. Use B, KB, KiB, MB, MiB, GB, GiB, TB, TiB, PB, PiB, EB, EiB, ZB, ZiB, YB, YiB");
}

std::string formatSize(uint64_t bytes) {
    const char* units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
    int unit = 0;
    double size = static_cast<double>(bytes);

    while (size >= 1024 && unit < 9) {
        size /= 1024;
        unit++;
    }

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << size << " " << units[unit];
    return oss.str();
}

  uint64_t getFreeSpace(const std::string& path) {
    try {
        std::filesystem::path fsPath = path;
        return std::filesystem::space(fsPath).available;
    } catch (...) {
        return 0;
    }
}

void printProgress(double percentage, const std::string& sizeInfo) {
    const int barWidth = 50;
    std::cout << "[";
    int pos = barWidth * percentage;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << (percentage * 100.0) << "% - " << sizeInfo << "\r";
    std::cout.flush();
}

int main() {
    std::string filename;
    std::string folderPath;
    std::string sizeInput;
    
    std::string customDataInput;
    bool useCustomData = false;

    std::cout << "Enter the folder path where the file should be saved (e.g., /path/to/folder): ";
    std::getline(std::cin, folderPath);

    if (!folderPath.empty() && (folderPath.back() == '/' || folderPath.back() == '\\')) {
        folderPath.pop_back();
    }

    std::cout << "Enter the name for the output file (e.g., bigfile.txt): ";
    std::getline(std::cin, filename);

    std::string fullPath = folderPath + "/" + filename;

    std::cout << "Enter the size (e.g., 1GB, 500MB, 1.5TB): ";
    std::getline(std::cin, sizeInput);
    std::cout << "Would you like to use custom data instead of the default string? (y/n): ";
    std::string choice;
    std::getline(std::cin, choice);
    if (!choice.empty() && (choice[0] == 'y' || choice[0] == 'Y')) {
        useCustomData = true;
    }

    uint64_t targetSize;
    try {
        targetSize = parseSize(sizeInput);
        if (targetSize == 0) {
            throw std::invalid_argument("Size must be greater than 0");
        }
        
        uint64_t freeSpace = getFreeSpace(folderPath);
        std::cout << "Estimated file size: " << formatSize(targetSize) << std::endl;
        std::cout << "Free disk space in target folder: " << formatSize(freeSpace) << std::endl;

        if (targetSize > freeSpace) {
            std::cerr << "Error: Not enough free space to create file.\n";
            std::cerr << "Required: " << formatSize(targetSize) << ", Available: " << formatSize(freeSpace) << "\n";
            std::cerr << "Aborting.\n";
            return 1;
        }
    
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    if (useCustomData) {
        std::cout << "Enter the custom data to repeat in the file: \n> ";
        std::getline(std::cin, customDataInput);
        if (customDataInput.empty()) {
            std::cerr << "Custom data cannot be empty. Exiting. \n";
            return 1;
        }
        customDataInput += '\n'; // Adds newline at end
    }

    std::string data = useCustomData ? customDataInput
        : "This is a sample text line that will be repeated to fill the file. The quick brown fox jumps over the lazy dog. 123456789!@#$%^&*()_+\n";

    while (data.size() < BUFFER_SIZE) {
        data += data;
    }
    data = data.substr(0, BUFFER_SIZE);

    std::cout << "Creating file: " << fullPath << " with size " << formatSize(targetSize) << std::endl;
    std::cout << "This may take a while..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    try {
        std::filesystem::path dirPath = folderPath;
        if (!std::filesystem::exists(dirPath)) {
            if (!std::filesystem::create_directories(dirPath)) {
                throw std::runtime_error("Failed to create directory: " + folderPath);
            }
        }

        std::ofstream outFile(fullPath, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Failed to create file: " + fullPath);
        }

        uint64_t bytesWritten = 0;
        const uint64_t totalChunks = (targetSize + BUFFER_SIZE - 1) / BUFFER_SIZE;
        uint64_t chunksWritten = 0;

        while (bytesWritten < targetSize) {
            uint64_t remaining = targetSize - bytesWritten;
            uint64_t toWrite = std::min(static_cast<uint64_t>(data.size()), remaining);

            outFile.write(data.c_str(), static_cast<std::streamsize>(toWrite));
            if (outFile.fail()) {
                throw std::runtime_error("Error writing to file");
            }

            bytesWritten += toWrite;
            chunksWritten++;

            if (chunksWritten % 100 == 0 || bytesWritten >= targetSize) {
                double progress = static_cast<double>(bytesWritten) / targetSize;
                std::string progressInfo = formatSize(bytesWritten) + " / " + formatSize(targetSize);
                printProgress(progress, progressInfo);
            }
        }

        outFile.close();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

        std::cout << "\nFile created successfully at: " << fullPath << std::endl;
        std::cout << "Total size: " << formatSize(bytesWritten) << std::endl;
        std::cout << "Time taken: " << (duration / 60) << " minutes and " << (duration % 60) << " seconds" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
