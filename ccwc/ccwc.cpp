#include <iostream>
#include <fstream>
#include <string>


void countWords(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: File " << filePath << " not found.\n";
        return;
    }
    
    int wordCount = 0;
    std::string word;
    while (file >> word) {
        wordCount++;
    }

    std::cout << "Word count: " << wordCount << std::endl;
    file.close();
}

void countLines(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: File " << filePath << " not found.\n";
        return;
    }
    
    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineCount++;
    }

    std::cout << "Line count: " << lineCount << std::endl;
    file.close();
}

void countBytes(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: File " << filePath << " not found.\n";
        return;
    }

    // Get the position of the file pointer at the end, which is the file size in bytes
    std::streamsize byteCount = file.tellg();
    std::cout << "Byte count: " << byteCount << std::endl;
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ccwc -option <file_path>\nOptions:\n  -o : Count words\n  -l : Count lines\n  -b : Count bytes\n";
        return 1;
    }

    std::string option = argv[1];
    std::string filePath = argv[2];

    if (option == "-o") {
        countWords(filePath);
    } else if (option == "-l") {
        countLines(filePath);
    } else if (option == "-b") {
        countBytes(filePath);
    } else {
        std::cerr << "Invalid option. Use -o for word count, -l for line count, and -b for byte count.\n";
        return 1;
    }

    return 0;
}

