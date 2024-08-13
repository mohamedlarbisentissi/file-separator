#include <filesystem>
#include <fstream>
#include <vector>
#include <openssl/evp.h>
#include <string>
#include "file_utils.h"

using std::string;
namespace fs = std::filesystem;


string compute_md5(const fs::path& path) {
    // Open file
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    auto size = fs::file_size(path);
    if (size == 0) {
        throw std::runtime_error("File is empty");
    }
    std::vector<unsigned char> buffer(size);
    file.read(reinterpret_cast<char*>(buffer.data()), size);
    file.close();
    unsigned char md5[16];
    size_t md5_size = 0;
    int success = EVP_Q_digest(NULL, "MD5", NULL, buffer.data(), size, md5, &md5_size);
    if (success != 1 || md5_size != 16) {
        throw std::runtime_error("MD5 computation failed");
    }
    string result(reinterpret_cast<char*>(md5), 16);
    return result;
}