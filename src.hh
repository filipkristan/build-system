#ifndef SORCERER_SRC_HH
#define SORCERER_SRC_HH


class src {
public:
    static bool fileExists(const std::string &filename);
    static void outputNeededLibraries(std::string file, std::string librariesOutput);
    static void generateBuildCommand(std::string buildFlagsPath);
    static void runCompiledProgram();
    static void handleBuildingAndRunningTheProgram(std::string runLibraryInstallScripts, std::string buildFlagsPath);
    static void generateInstallScript(std::string foundLibraries);
};


#endif