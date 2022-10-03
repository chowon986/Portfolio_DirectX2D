#pragma once
#include <string>

static class TextureLoadUtils
{
public:
	static bool LoadTextures(std::string _FolderName);
	static bool LoadFolderTextures(std::string _FolderName, std::string _ParentFolderName = "");

	static bool LoadTexturesAsync(std::string _FolderName);
	static bool LoadFolderTexturesAsync(std::string _FolderName, std::string _ParentFolderName = "");
};
