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

bool TextureLoadUtils::LoadTexturesAsync(std::string _FolderName)
{
	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ConstantResources");
	Dir.Move("ConstantResources");
	Dir.Move("Texture");
	Dir.Move(_FolderName);
	std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();

	for (GameEngineDirectory Dir : RecursiveDir)
	{
		std::string FullPath = Dir.GetFullPath();
		std::string FileName = GameEnginePath::GetFileName(FullPath);
		if (GameEngineRes<GameEngineFolderTexture>::Find(FileName) == nullptr)
		{
			GameEngineFolderTexture::Load(FullPath);

			// 한개씩 로드 한다
			return false;
		}
	}
	std::vector<GameEngineFile> Textures = Dir.GetAllFile();
	for (size_t i = 0; i < Textures.size(); i++)
	{
		std::string FullPath = Textures[i].GetFullPath();
		std::string FileName = GameEnginePath::GetFileName(FullPath);
		if (GameEngineRes<GameEngineTexture>::Find(FileName) == nullptr)
		{
			GameEngineTexture::Load(FullPath);

			// 한개씩 로드 한다
			return false;
		}
	}
	return true;
}

bool TextureLoadUtils::LoadFolderTexturesAsync(std::string _FolderName, std::string _ParentFolderName)
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
		std::string FullPath = Dir.GetFullPath();
		std::string FileName = GameEnginePath::GetFileName(FullPath);
		if (GameEngineRes<GameEngineFolderTexture>::Find(FileName) == nullptr)
		{
			GameEngineFolderTexture::Load(Dir.GetFullPath());

			// 한개씩 로드 한다
			return false;
		}
	}

	return true;
}
