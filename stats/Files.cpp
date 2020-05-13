#include "Files.h"

//return all the file paths
std::vector<std::filesystem::path> getFileNames(std::string dir_path) {
	std::vector<std::filesystem::path> file_names;
	for (const auto& file : std::filesystem::directory_iterator(dir_path)) {
		//std::cout << file.path() << "\n";
		file_names.push_back(file.path());
	}
	return file_names;
}