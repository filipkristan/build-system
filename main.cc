#include "libFK.hh"
#include "src.hh"
#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    fs::create_directory("out");
    src::outputNeededLibraries(&*argv[1], "out/neededLibraries.txt");
    src::generateInstallScript("out/libNotFound.txt");
    src::handleBuildingAndRunningTheProgram("out/runLibraryInstallScripts.sh", "out/buildFlags.txt", argc, argv[1]);
    system("rm -rf out");
    return system("rm -rf a.out");;
}