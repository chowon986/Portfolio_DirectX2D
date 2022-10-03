#include "PreCompile.h"
#include "TextureLoadUtils.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineFolderTexture.h>
#include <GameEngineBase/GameEngineFile.h>

bool TextureLoadUtils::LoadTextures(std::string _FolderName)
{
	bool IsInitialLoad = false;
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
		GameEngineFolderTexture* FolderTexture = GameEngineRes<GameEngineFolderTexture>::Find(FileName);
		if (FolderTexture == nullptr)
		{
			GameEngineFolderTexture::Load(FullPath);
			IsInitialLoad = true;
		}
	}
	std::vector<GameEngineFile> Textures = Dir.GetAllFile();
	for (size_t i = 0; i < Textures.size(); i++)
	{
		std::string FullPath = Textures[i].GetFullPath();
		std::string FileName = GameEnginePath::GetFileName(FullPath);
		GameEngineTexture* FolderTexture = GameEngineRes<GameEngineTexture>::Find(FileName);
		if (FolderTexture == nullptr)
		{
			GameEngineTexture::Load(FullPath);
			IsInitialLoad = true;
		}
	}

	return IsInitialLoad;
}

bool TextureLoadUtils::LoadFolderTextures(std::string _FolderName, std::string _ParentFolderName)
{
	bool IsInitialLoad = false;
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
		GameEngineFolderTexture* FolderTexture = GameEngineRes<GameEngineFolderTexture>::Find(FileName);
		if (FolderTexture == nullptr)
		{
			GameEngineFolderTexture::Load(Dir.GetFullPath());
			IsInitialLoad = true;
		}
	}

	return IsInitialLoad;
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
		GameEngineFolderTexture* FolderTexture = GameEngineRes<GameEngineFolderTexture>::Find(FileName);
		if (FolderTexture == nullptr)
		{
			GameEngineFolderTexture::Load(FullPath);

			// 한개씩 로드 한다
			return false;
		}
		/*else if (FolderTexture->LoadFolderAsync(FullPath) == false)
		{
			return false;
		}*/
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
		GameEngineFolderTexture* FolderTexture = GameEngineRes<GameEngineFolderTexture>::Find(FileName);
		if (FolderTexture == nullptr)
		{
			GameEngineFolderTexture::Load(FullPath);

			// 한개씩 로드 한다
			return false;
		}
		/*else if (FolderTexture->LoadFolderAsync(FullPath) == false)
		{
			return false;
		}*/
	}

	return true;
}
