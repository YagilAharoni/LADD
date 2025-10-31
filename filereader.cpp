#include <iostream>
#include <fstream>
#include <string>

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


int main(int argc, char* argv[]) {
    std::string configFilename = "config.env";
    std::string outputFilename;
    std::ios_base::openmode openMode = std::ios::app; 

    if (argc == 2) {
        outputFilename = argv[1];
    } else if (argc == 3) {
        std::string flag = argv[1];
        if (flag == "-o") {
            outputFilename = argv[2];
            openMode = std::ios::trunc;
        } else {
            std::cerr << "Error: Unknown flag '" << flag << "'" << std::endl;
            std::cerr << "Usage: " << argv[0] << " [-o] <output_filename>" << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Error: Invalid arguments." << std::endl;
        std::cerr << "Usage: " << argv[0] << " [-o] <output_filename>" << std::endl;
        return 1;
    }

    std::ifstream configFile(configFilename);
    if (!configFile.is_open()) {
        std::cerr << "Error: Could not open config file '" << configFilename << "'" << std::endl;
        return 1;
    }

    std::ofstream outputFile(outputFilename, openMode); 
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open destination file '" << outputFilename << "'" << std::endl;
        configFile.close();
        return 1;
    }

    std::cout << "Starting to process files listed in '" << configFilename << "'..." << std::endl;

    std::string sourceFileFromConfig;
    int filesProcessed = 0;

    while (std::getline(configFile, sourceFileFromConfig)) {
        
        if (sourceFileFromConfig.empty()) {
            continue;
        }
        
        if (sourceFileFromConfig[0] == '#') {
            continue;
        }

        std::cout << "Processing: " << sourceFileFromConfig << std::endl;
        
        copyFileWithHeader(sourceFileFromConfig, outputFile);
        filesProcessed++;
    } 

    configFile.close();
    outputFile.close();

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Finished. Processed " << filesProcessed << " files." << std::endl;
    std::cout << "All content written to '" << outputFilename << "'." << std::endl;

    return 0;
}