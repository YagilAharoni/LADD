#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <algorithm>

void copyFileWithHeader(const std::string& sourceFilename, std::ofstream& outputFile) {
    std::ifstream inputFile(sourceFilename);
    if (!inputFile.is_open()) {
        std::cerr << "  -> Error: Could not open source file '" << sourceFilename << "'" << std::endl;
        return; 
    }

    outputFile << "========================================\n";
    outputFile << "=== Content from file: " << sourceFilename << " ===\n";
    outputFile << "========================================\n";

    std::string line;
    while (std::getline(inputFile, line)) {
        outputFile << line << std::endl;
    }

    outputFile << "\n";
    
    inputFile.close();
    std::cout << "  -> Successfully copied: " << sourceFilename << std::endl;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}


int main(int argc, char* argv[]) {
    std::string configFilename = "config.env";
    std::string outputFilename = "";
    std::ios_base::openmode openMode = std::ios::app;
    std::vector<std::string> sourceFiles;
    bool setFromCmd = false;

    sleep(1);

    if (argc == 2) {
        std::string arg1 = argv[1];
        if (arg1 != "-o") {
            outputFilename = arg1;
            setFromCmd = true;
        }
    } else if (argc == 3) {
        std::string flag = argv[1];
        if (flag == "-o") {
            outputFilename = argv[2];
            openMode = std::ios::trunc;
            setFromCmd = true;
        } else {
            std::cerr << "Error: Unknown flag '" << flag << "'" << std::endl;
            std::cerr << "Usage: " << argv[0] << " [-o] <output_filename>" << std::endl;
            return 1;
        }
    } else if (argc > 3) {
         std::cerr << "Error: Too many arguments." << std::endl;
         std::cerr << "Usage: " << argv[0] << " [-o] <output_filename>" << std::endl;
         return 1;
    }

    std::ifstream configFile(configFilename);
    if (!configFile.is_open()) {
        std::cerr << "Error: Could not open config file '" << configFilename << "'" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(configFile, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::stringstream ss(line);
        std::string key, value;
        
        if (std::getline(ss, key, '=') && std::getline(ss, value)) {
            key = trim(key);
            value = trim(value);

            if (key == "Source") {
                sourceFiles.push_back(value);
            }
            
            if (!setFromCmd) {
                if (key == "OutputFile") {
                    outputFilename = value;
                } else if (key == "Mode") {
                    if (value == "overwrite") {
                        openMode = std::ios::trunc;
                    } else {
                        openMode = std::ios::app;
                    }
                }
            }
        }
    }
    configFile.close();

    if (outputFilename.empty()) {
        std::cerr << "Error: Output filename not specified." << std::endl;
        std::cerr << "Please specify it in 'config.env' (OutputFile=...) or as an argument." << std::endl;
        std::cerr << "Usage: " << argv[0] << " [-o] <output_filename>" << std::endl;
        return 1;
    }

    std::ofstream outputFile(outputFilename, openMode); 
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open destination file '" << outputFilename << "'" << std::endl;
        return 1;
    }

    std::cout << "Starting to process files..." << std::endl;
    std::cout << "Output Target: '" << outputFilename << "' (Mode: " 
              << (openMode == std::ios::app ? "Append" : "Overwrite") << ")" << std::endl;
    
    int filesProcessed = 0;
    
    for (const std::string& sourceFile : sourceFiles) {
        if (sourceFile.empty()) continue;

        std::cout << "Processing: " << sourceFile << std::endl;
        copyFileWithHeader(sourceFile, outputFile);
        filesProcessed++;
    } 

    outputFile.close();

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Finished. Processed " << filesProcessed << " source files." << std::endl;
    std::cout << "All content written to '" << outputFilename << "'." << std::endl;

    return 0;
}