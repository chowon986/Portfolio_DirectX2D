#pragma once
#include <string>

static class TextureLoadUtils
{
public:
	static void LoadTextures(std::string _FolderName);
	static void LoadFolderTextures(std::string _FolderName, std::string _ParentFolderName = "");
};
