#include "PreCompile.h"
#include "ContentsCore.h"
#include "GameEngineContents/PlayLevel.h"
#include "GameEngineContents/TitleLevel.h"
#include "GameEngineContents/BeforeTitleLevel.h"
#include "GameEngineContents/SelectLevel.h"
#include "GameEngineContents/WorldMapLevel.h"
#include "GameEngineContents/HourglassLevel.h"

#pragma comment(lib, "GameEngineBase.lib")

ContentsCore::ContentsCore() 
	: GameEngineCore()
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	}


	GameEngineDirectory Dir;
	Dir.MoveParentToExitsChildDirectory("ConstantResources");
	Dir.Move("ConstantResources");
	Dir.Move("Texture");
	//Dir.Move("Login");

	std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();
	for (GameEngineDirectory Dir : RecursiveDir)
	{
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	Dir.Move("11TitleLevel");
	std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

	for (size_t i = 0; i < Shaders.size(); i++)
	{
		GameEngineTexture::Load(Shaders[i].GetFullPath());
	}

	Dir.MoveParent();
	Dir.Move("12SelectLevel");
	std::vector<GameEngineFile> Shaders2 = Dir.GetAllFile();

	for (size_t i = 0; i < Shaders2.size(); i++)
	{
		GameEngineTexture::Load(Shaders2[i].GetFullPath());
	}

	Dir.MoveParent();
	Dir.Move("14WorldMapLevel");
	std::vector<GameEngineFile> Shaders3 = Dir.GetAllFile();

	for (size_t i = 0; i < Shaders3.size(); i++)
	{
		GameEngineTexture::Load(Shaders3[i].GetFullPath());
	}


	CreateLevel<BeforeTitleLevel>("BeforeTitle");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<SelectLevel>("Select");
	CreateLevel<HourglassLevel>("Hourglass");
	CreateLevel<WorldMapLevel>("WorldMap");
	CreateLevel<PlayLevel>("Play");
	ChangeLevel("WorldMap");

}

void ContentsCore::Update(float _DeltaTime)
{
	// 서버가 종료되었어.
	// 무조건 경고 메세지창을 띄워줘야한다.
	
	
}

void ContentsCore::End()
{
	int a = 0;
}