#include "PreCompile.h"
#include "GameEngineFolderTexture.h"
#include <GameEngineBase/GameEnginePath.h>

GameEngineFolderTexture::GameEngineFolderTexture() 
{
}

GameEngineFolderTexture::~GameEngineFolderTexture() 
{
	for (size_t i = 0; i < Textures.size(); i++)
	{
		delete Textures[i];
	}
}


GameEngineFolderTexture* GameEngineFolderTexture::Load(const std::string& _Path)
{
	return Load(_Path, GameEnginePath::GetFileName(_Path));
}

GameEngineFolderTexture* GameEngineFolderTexture::Load(const std::string& _Path, const std::string& _Name)
{
	GameEngineFolderTexture* NewTex = CreateResName(_Name);
	NewTex->LoadFolder(_Path);
	return NewTex;
}

GameEngineFolderTexture* GameEngineFolderTexture::LoadAsync(const std::string& _Path)
{
	return LoadAsync(_Path, GameEnginePath::GetFileName(_Path));
}

GameEngineFolderTexture* GameEngineFolderTexture::LoadAsync(const std::string& _Path, const std::string& _Name)
{
	GameEngineFolderTexture* NewTex = CreateResName(_Name);
	NewTex->LoadFolderAsync(_Path);
	return NewTex;
}

void GameEngineFolderTexture::LoadFolder(const std::string& _Path)
{
	GameEngineDirectory Dir = GameEngineDirectory(_Path);

	//GameEngineDirectory Dir = _Path;

	//GameEngineDirectory Dir = { _Path };

	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

	for (size_t i = 0; i < AllFile.size(); i++)
	{
		GameEngineTexture* NewTexture = new GameEngineTexture();
		NewTexture->TextureLoad(AllFile[i].GetFullPath());
		Textures.push_back(NewTexture);
	}
}

bool GameEngineFolderTexture::LoadFolderAsync(const std::string& _Path)
{
	GameEngineDirectory Dir = GameEngineDirectory(_Path);

	std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

	for (size_t i = 0; i < AllFile.size(); i++)
	{
		std::string FullPath = AllFile[i].GetFullPath();

		if (TextureMap.find(FullPath) == TextureMap.end())
		{
			GameEngineTexture* NewTexture = new GameEngineTexture();
			NewTexture->TextureLoad(FullPath);
			Textures.push_back(NewTexture);
			TextureMap.insert({ FullPath, NewTexture });

			// �Ѱ��� �ε�
			return false;
		}
	}

	return true;
}