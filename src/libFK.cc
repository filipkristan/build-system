/////////////////////////////////////////
// Created by Filip Kristan. v20260301 //
/////////////////////////////////////////

#include "libFK.hh"

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

void fk::msg(int level, std::string message)
{
    std::string prefix = "";
    if (level == 0)
    {
        prefix = "[ INFO ] ";
    }
    else if (level == 1)
    {
        prefix = "[" + std::string("\033[32m") + " !OK! " + "\033[0m" + "] ";
    }
    else if (level == 2)
    {
        prefix = "[" + std::string("\033[33m") + " ???? " + "\033[0m" + "] ";
    }
    else
    {
        prefix = "[" + std::string("\033[31m") + " !!!! " + "\033[0m" + "] ";
    }
    std::cout << prefix << message << std::endl;
};

// Function definition with std::string return type
std::string fk::setStringValueFromFunction() {
    return std::string("Hello from a C++ function!");
}

// Writes text to a file (Replaces all data with set text)
void fk::writeDataToFile(std::string location, std::string data, bool appendMode) {
    std::ofstream file;
    if (appendMode)
    {
        file.open(location, std::ios::app);
    }
    else
    {
        file.open(location, std::ios::out);
    }

    if (file.is_open())
    {
        file << data << "\n";
        file.close();
    }
    else
        std::cout << "File was closed!" << "\n";
}

// Returns the data read from a file
std::string fk::readDataFromFile(std::string location) {
    std::ifstream stream(location);
    std::string data;
    if (stream) {
        std::ostringstream ss;
        ss << stream.rdbuf();
        data = ss.str();
        std::erase(data, '\n');
    } else {
        std::cout << "Unable to read data from the file!" <<'\n';
        std::cout << "File location: " << location <<'\n';
    }
    return data;
}

// Converts decimal number to hex
std::string fk::decimalToHex(int decimalValue) {
    std::stringstream ss;
    ss << std::hex << decimalValue;
    std::string hexValue ( ss.str() );
    return hexValue;
}

// Converts hex number to decimal
int fk::hexToDecimal(std::string hexValue) {
    int decimalValue = *"0";
    std::stringstream ss;
    ss << hexValue;
    ss >> std::hex >> decimalValue;
    return decimalValue;
}

// Adds zeroes to number
std::string fk::addZeroes(int zeroNumberLength, int number) {
    std::string padding = "";
    std::string numberString = std::to_string(number);
    int numberLength = numberString.length();
    for (int i = 0; i < zeroNumberLength - numberLength; ++i) {
        padding.append("0");
    }
    std::string result = padding + std::to_string(number);
    return result;
}

// Returns the output of a terminal command
std::string fk::returnCommandResult(const char* cmd) {
    std::array<char, 128> buffer;
    std::string output;

    auto pipe = popen(cmd, "r");

    if (!pipe) throw std::runtime_error("popen() failed!");

    while (!feof(pipe)) {
        if (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
            output += buffer.data();
    }

    auto rc = pclose(pipe);

    if (rc == EXIT_SUCCESS) { } else if (rc == EXIT_FAILURE) { }

    output.erase(std::remove(output.begin(), output.end(), '\n'), output.cend());

    return output;
}

std::vector<std::string> fk::readFileLines(const std::string& location) {
    std::ifstream stream(location);
    std::vector<std::string> lines;

    if (stream) {
        std::string line;
        while (std::getline(stream, line)) {
            lines.push_back(line);
        }
    } else {
        std::cout << "Unable to read data from the file!" << '\n';
        std::cout << "File location: " << location << '\n';
    }

    return lines;
}