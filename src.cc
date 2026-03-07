#include "libFK.hh"
#include "src.hh"
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

bool src::fileExists(const std::string& filename) {
    return fs::exists(filename);
}

// Segregates to two files, one to list already installed libraries and another that lists libraries to install
void src::outputNeededLibraries(const std::string file, std::string librariesOutput) {
    std::vector lines = fk::readFileLines(file);
    std::string query = "#include <";   // Match value to know what libraries to look for
    std::string queryEnd = ">";
    std::string library, searchLibraryPath;
    std::string foundLibrariesList = "out/libFound.txt";        // Output found libraries
    std::string notFoundLibrariesList = "out/libNotFound.txt";  // Output missing libraries
    for (size_t i = 0; i < lines.size(); ++i) {
        std::string line = lines[i];
        size_t result = -1;
        while ((result = line.find(query, result + 1)) != std::string::npos) {  // Query for needed libraries
            size_t startPosition = result + query.length();
            size_t endPosition = line.find(queryEnd, startPosition);
            if (endPosition == std::string::npos) { std::cout << "Error: no \"endPosition! \"" << std::endl; break; }
            library = line.substr(startPosition, endPosition - query.length());
            fk::writeDataToFile(librariesOutput,library, true); // Output needed libraries
            fk::writeDataToFile(notFoundLibrariesList, library ,true);
            searchLibraryPath = "/usr/local/include/" + library;
            if (fileExists(searchLibraryPath)) {
                fk::writeDataToFile(foundLibrariesList, library,true);
            } else {
                fk::writeDataToFile(notFoundLibrariesList, library,true);
            }
        }
    }
}

void src::generateBuildCommand(std::string buildFlagsPath) {
    std::string allBuildFlags = fk::readDataFromFile(buildFlagsPath);
    std::string inputFile = "example.cc";
    std::string outputFileName = "a.out";
    std::string buildCommand = "clang " + inputFile + " -lstdc++ " + allBuildFlags + " -o " + outputFileName;
    fk::msg(1, "Compiling the program!");
    system(buildCommand.c_str());
}

void src::runCompiledProgram() {
    fk::msg(1, "Running the compiled program!");
    system("./a.out");
}

void src::handleBuildingAndRunningTheProgram(std::string runLibraryInstallScripts, std::string buildFlagsPath) {
    if (fileExists(runLibraryInstallScripts)) {
        std::string cmd = "sudo -S chmod +x " + runLibraryInstallScripts + " && sudo -S bash " + runLibraryInstallScripts + " > /dev/null 2>&1";
        system(cmd.c_str());
        generateBuildCommand(buildFlagsPath);
    }
    runCompiledProgram();
}

void src::generateInstallScript(std::string foundLibraries) {
    std::vector<std::string> library = fk::readFileLines(foundLibraries);
    std::vector<std::string> availableLibrariesToBeInstalled = fk::readFileLines("../availableLibs.txt");
    std::string availableLibraryBuildFlags = "../libraryBuildFlags";
    std::string buildScriptsDir = "../libraryBuildScripts/";
    std::string buildFlagsPath = "out/buildFlags.txt";
    std::string buildScriptPath = buildScriptsDir + "0" + ".sh";
    std::string runLibraryInstallScripts = "out/runLibraryInstallScripts.sh";
    for (size_t i = 0; i < library.size(); ++i) {
        for (size_t j = 0; j < availableLibrariesToBeInstalled.size(); ++j) {
            if (library[i] == availableLibrariesToBeInstalled[j]) {
                buildScriptPath = buildScriptsDir + std::to_string(j+1) + ".sh";
                fk::writeDataToFile(runLibraryInstallScripts, buildScriptPath, true);
                std::string buildFlagsFile = availableLibraryBuildFlags + "/" + std::to_string(j+1) + ".txt";
                std::string buildFlagsFileData = " " + fk::readDataFromFile(buildFlagsFile);
                fk::writeDataToFile(buildFlagsPath, buildFlagsFileData, true);
            }
        }
    }
}