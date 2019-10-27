#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <iostream>

std::vector<std::filesystem::path> getFileNames(std::string dir_path);