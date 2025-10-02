#include "Utilities.hpp"
string Utility::getFilepath(string file)
{
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string filepath = cwd.string() + std::string("/") + "testFiles" +
			       std::string("/") + file;
	return filepath;
}
map<string, int> Utility::memorySegmentMap = {
	{ "stack", 0 },	  { "local", 1 },   { "argument", 2 },
	{ "this", 3 },	  { "that", 4 },    { "constant", 874 },
	{ "static", 16 }, { "pointer", 3 }, { "temp", 5 }
};

int Utility::fileExtensionDotIndex(const string &path)
{
	int i;
	for (i = path.size() - 1; i >= 0 && path.at(i) != '.'; i--) {
	}
	return (i < 0) ? -1 : i;
}
