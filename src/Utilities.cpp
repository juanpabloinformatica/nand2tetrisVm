#include "Utilities.hpp"
string Utility::getFilepath(string file) {
  std::filesystem::path cwd = std::filesystem::current_path();
  std::string filepath =
      cwd.string() + std::string("/") + "testFiles" + std::string("/") + file;
  return filepath;
}
