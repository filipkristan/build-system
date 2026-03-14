#include "libFK.hh"
#include "src.hh"
#include "progressBar.hh"
#include <filesystem>
#include <string>
#include <chrono>
#include <thread>

namespace fs = std::filesystem;


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fk::msg(1, "No input file specified.");
    } else if (argc > 2) {
        fk::msg(1, "Too many inputs specified.");
    }
    else {
        fs::create_directory("out");
        printProgressBar(0,5,0);
        src::outputNeededLibraries(&*argv[1], "out/neededLibraries.txt");
        src::generateInstallScript("out/libNotFound.txt");
        src::handleBuildingAndRunningTheProgram("out/runLibraryInstallScripts.sh", "out/buildFlags.txt", argc, argv[1]);
        system("rm -rf out");
        system("rm -rf a.out");
    }

    return 0;
}