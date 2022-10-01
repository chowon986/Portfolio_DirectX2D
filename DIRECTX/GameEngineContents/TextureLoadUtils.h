#pragma once
#include <string>

static class TextureLoadUtils
{
public:
	static void LoadTextures(std::string _FolderName);
	static void LoadFolderTextures(std::string _FolderName, std::string _ParentFolderName = "");

	static bool LoadTexturesAsync(std::string _FolderName);
	static bool LoadFolderTexturesAsync(std::string _FolderName, std::string _ParentFolderName = "");
};
