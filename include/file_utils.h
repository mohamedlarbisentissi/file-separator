#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <filesystem>
#include <fstream>
#include <string>

std::string compute_md5(const std::filesystem::path& path);

#endif