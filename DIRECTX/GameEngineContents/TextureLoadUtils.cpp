#include "PreCompile.h"
#include "TextureLoadUtils.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineFolderTexture.h>
#include <GameEngineBase/GameEngineFile.h>

void TextureLoadUtils::LoadTextures(std::string _FolderName)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ConstantResources");
	Dir.Move("ConstantResources");
	Dir.Move("Texture");
	Dir.Move(_FolderName);
	std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();
	for (GameEngineDirectory Dir : RecursiveDir)
	{
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}
	std::vector<GameEngineFile> Textures = Dir.GetAllFile();
	for (size_t i = 0; i < Textures.size(); i++)
	{
		GameEngineTexture::Load(Textures[i].GetFullPath());
	}
}

void TextureLoadUtils::LoadFolderTextures(std::string _FolderName, std::string _ParentFolderName)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ConstantResources");
	Dir.Move("ConstantResources");
	Dir.Move("Texture");
	if (_ParentFolderName != "")
	{
		Dir.Move(_ParentFolderName);
	}
	Dir.Move(_FolderName);
	std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();
	for (GameEngineDirectory Dir : RecursiveDir)
	{
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}
}
