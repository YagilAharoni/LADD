#include <iostream>
#include <fstream>
#include <string>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>

// This function reads the source filename from config.txt
std::string getSourceFilename() {
    std::string configFilename = "config.env";
    std::ifstream configFile(configFilename);

    if (!configFile.is_open()) {
        std::cerr << "Error: Could not open config file '" << configFilename << "'" << std::endl;
        return "";
    }

    std::string sourceFilename;
    if (std::getline(configFile, sourceFilename)) {
        configFile.close();
        if (sourceFilename.empty()) {
             std::cerr << "Error: Config file is empty." << std::endl;
             return "";
        }
        return sourceFilename; 
    } else {
        std::cerr << "Error: Config file '" << configFilename << "' is empty." << std::endl;
        configFile.close();
        return "";
    }
}


int main() {
    std::string outputFilename = "output.txt";

    std::string inputFilename = getSourceFilename();
    if (inputFilename.empty()) {
        std::cerr << "Could not determine source filename from config." << std::endl;
        return 1; // Exit
    }

    // Open the source file (from config)
    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open source file '" << inputFilename << "'" << std::endl;
        return 1;
    }

    // Open the hard-coded destination file
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open destination file '" << outputFilename << "'" << std::endl;
        inputFile.close();
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        outputFile << line << std::endl;
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Successfully copied '" << inputFilename << "' (from config) to '" << outputFilename << std::endl;
    return 0;
}