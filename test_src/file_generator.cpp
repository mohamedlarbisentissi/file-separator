#include <filesystem>
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;
int N_lines = 100;

int main(int argc, char** argv) {

    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <directory A> <directory B> <directory Output> <number of files>" << std::endl;
        return 1;
    }
    fs::path pathA = fs::path(argv[1]);
    fs::path pathB = fs::path(argv[2]);
    fs::path pathAssert = fs::path(argv[3]);
    int number_of_files = std::stoi(argv[4]);

    if (!fs::exists(pathA) || !fs::is_directory(pathA)) {
        std::cerr << pathA << std::endl;
        std::cerr << "Directory A does not exist" << std::endl;
        return 1;
    }
    if (!fs::exists(pathB) || !fs::is_directory(pathB)) {
        std::cerr << "Directory B does not exist" << std::endl;
        return 1;
    }
    if (!fs::exists(pathAssert) || !fs::is_directory(pathAssert)) {
        std::cerr << "Directory Output does not exist" << std::endl;
        return 1;
    }
    if (number_of_files <= 0) {
        std::cerr << "Number of files must be greater than 0" << std::endl;
        return 1;
    }

    // Create files in directory A alone
    fs::path file_path_assertA = pathAssert / ("a_only");
    std::ofstream file_assertA(file_path_assertA);
    for (int i = 0; i < number_of_files; ++i) {
        // Create filename and add it to the assert directory
        std::string filename = "file" + std::to_string(i);
        fs::path file_path = pathA / filename;
        file_assertA << filename << std::endl;
        // Create file in directory A
        std::ofstream file(file_path);
        for (int j = 0; j < N_lines; ++j) {
            file << "This is file " << i << " in directory A" << std::endl;
        }
        file.close();
    }
    file_assertA.close();
    // Create files in directory B alone
    fs::path file_path_assertB = pathAssert / ("b_only");
    std::ofstream file_assertB(file_path_assertB);
    for (int i = 0; i < number_of_files; ++i) {
        // Create filename and add it to the assert directory
        std::string filename = "file" + std::to_string(i);
        fs::path file_path = pathB / filename;
        file_assertB << filename << std::endl;
        // Create file in directory B
        std::ofstream file(file_path);
        for (int j = 0; j < N_lines; ++j) {
            file << "This is file " << i << " in directory B" << std::endl;
        }
        file.close();
    }
    file_assertB.close();
    // Create files with the same content in both directories
    fs::path file_path_common = pathAssert / ("common");
    std::ofstream file_common(file_path_common);
    for (int i = 0; i < number_of_files; ++i) {
        // Create filenames and add them to the assert directory
        std::string filename = "file" + std::to_string(i+number_of_files);
        file_common << filename << " " << filename << std::endl;
        fs::path file_pathA = pathA / filename;
        fs::path file_pathB = pathB / filename;
        std::ofstream fileA(file_pathA);
        std::ofstream fileB(file_pathB);
        for (int j = 0; j < N_lines; ++j) {
            fileA << "This is file " << i << " in both directories" << std::endl;
            fileB << "This is file " << i << " in both directories" << std::endl;
        }
        fileA.close();
        fileB.close();
    }
    file_common.close();

    return 0;
}