#include "FileLoader.h"
#include <iostream>
#include <filesystem>
#include <typeinfo>


namespace fs = std::filesystem;
std::string GetPath(const std::string& name)
{
	/*fs::path resourceFolder;
	for(auto& p : fs::recursive_directory_iterator("../../../3DGameEngine"))
	{
		std::cout << p.path() << std::endl;
		if(fs::is_directory(p.status()))
			if(p.path().string().find("res") != std::string::npos)
			{
				resourceFolder = p.path();
				break;
			}
	}*/
	fs::path resourceFolder = "../../../3DGameEngine/res";
	fs::path filePath = fs::absolute(resourceFolder / fs::path(name));
	return filePath.string();
}


void LoadResource(const std::string& name)
{
	
}
