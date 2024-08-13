#include <map>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include "file_utils.h"

using std::map;
using std::string;
namespace fs = std::filesystem;

void populateMap(const fs::path& path, map<string, fs::path>& dir) {
    for (const auto& entry : fs::directory_iterator(path)) {
        fs::path file_path = entry.path();
        if(fs::is_regular_file(file_path)) {
            // Compute md5sum of file
            string md5 = compute_md5(file_path);
            // Store md5sum in map
            dir[md5] = file_path;
        }
    }
}

int main(int argc, char** argv) {

    // Check if the number of arguments is correct
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <directory A> <directory B> <directory Output>" << std::endl;
        return 1;
    }
    // Check if the directories exist and are directories
    fs::path pathA = fs::path(argv[1]);
    fs::path pathB = fs::path(argv[2]);
    fs::path pathOut = fs::path(argv[3]);
    if (!fs::exists(pathA) || !fs::is_directory(pathA)) {
        std::cerr << "Directory A does not exist" << std::endl;
        return 1;
    }
    if (!fs::exists(pathB) || !fs::is_directory(pathB)) {
        std::cerr << "Directory B does not exist" << std::endl;
        return 1;
    }
    if (!fs::exists(pathOut) || !fs::is_directory(pathOut)) {
        std::cerr << "Directory Output does not exist" << std::endl;
        return 1;
    }
    // Check if the directories are not the same
    if (argv[1] == argv[2] || argv[1] == argv[3] || argv[2] == argv[3]) {
        std::cerr << "Directories A and B and Output must be different" << std::endl;
        return 1;
    }

    // Generate and store md5sums of all files in directory A and B
    map<string, fs::path> dirA;
    map<string, fs::path> dirB;

    populateMap(pathA, dirA);
    populateMap(pathB, dirB);

    // Write all files that are in A but not in B to file Output/a_only and all files that are in both A and B to file Output/common
    std::ofstream aOnly = std::ofstream(pathOut / "a_only");
    std::ofstream common = std::ofstream(pathOut / "common");
    for (const auto& [md5A, pathFileA] : dirA) {
        if (dirB.find(md5A) == dirB.end()) {
            aOnly << pathFileA.filename().string() << std::endl;
        } else {
            common << pathFileA.filename().string() << " " << dirB[md5A].filename().string() << std::endl;
            dirB.erase(md5A);
        }
    }
    aOnly.close();
    common.close();

    // Write all files that are in B but not in A to file Output/b_only
    std::ofstream bOnly = std::ofstream(pathOut / "b_only");
    for (const auto& [md5B, pathFileB] : dirB) {
        bOnly << pathFileB.filename().string() << std::endl;
    }
    bOnly.close();

    return 0;
}