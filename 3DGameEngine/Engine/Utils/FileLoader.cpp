#include "FileLoader.h"
#include <iostream>
#include <filesystem>
#include <typeinfo>


namespace fs = std::filesystem;
std::string GetPath(const std::string& name)
{
	fs::path resourceFolder;
	for(auto& p : fs::recursive_directory_iterator("."))
	{
		if(p.is_directory())
			if(p.path().string().find("res") != std::string::npos)
			{
				resourceFolder = p.path();
				break;
			}
	}
	fs::path filePath = resourceFolder / fs::path(name);
	return filePath;
}


void LoadResource(const std::string& name)
{
	
}
