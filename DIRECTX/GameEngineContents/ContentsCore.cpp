#include "PreCompile.h"
#include "ContentsCore.h"
#include "GameEngineContents/PlayLevel.h"
#include "GameEngineContents/TitleLevel.h"
#include "GameEngineContents/BeforeTitleLevel.h"
#include "GameEngineContents/SelectLevel.h"
#include <GameEngineContents/WorldMapLevel.h>
#include <GameEngineContents/HourglassLevel.h>

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
	Dir.Move("10BeforeTitleLevel");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();
	Dir.Move("11TitleLevel");
	std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

	for (size_t i = 0; i < Shaders.size(); i++)
	{
		GameEngineTexture::Load(Shaders[i].GetFullPath());
	}

	Dir.Move("Cuphead");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();
	Dir.Move("Mugman");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();
	Dir.Move("Chalice");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();
	Dir.MoveParent();
	Dir.Move("00Iris");
	Dir.Move("IrisA");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();
	Dir.Move("IrisB");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();
	Dir.MoveParent();
	Dir.Move("12SelectLevel");
	std::vector<GameEngineFile> Shaders2 = Dir.GetAllFile();

	for (size_t i = 0; i < Shaders2.size(); i++)
	{
		GameEngineTexture::Load(Shaders2[i].GetFullPath());
	}

	Dir.Move("PressAnyKey");
	GameEngineFolderTexture::Load(Dir.GetFullPath());
	
	Dir.MoveParent();
	Dir.Move("Option");
	Dir.Move("Start");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();
	Dir.Move("Option");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();
	Dir.Move("DLC");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();
	Dir.Move("End");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();	
	Dir.MoveParent();	
	Dir.MoveParent();
	Dir.Move("13HourglassLevel");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();
	Dir.Move("14WorldMapLevel");
	std::vector<GameEngineFile> Shaders3 = Dir.GetAllFile();

	for (size_t i = 0; i < Shaders3.size(); i++)
	{
		GameEngineTexture::Load(Shaders3[i].GetFullPath());
	}

	Dir.Move("WaterLine");
	GameEngineFolderTexture::Load(Dir.GetFullPath());

	Dir.MoveParent();
	Dir.Move("WorldMapCharacter");
	Dir.Move("Cuphead");
	Dir.Move("Idle");
	Dir.Move("DownA");
	GameEngineFolderTexture::Load(Dir.GetFullPath());



	CreateLevel<BeforeTitleLevel>("BeforeTitle");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<SelectLevel>("Select");
	CreateLevel<HourglassLevel>("Hourglass");
	CreateLevel<WorldMapLevel>("WorldMap");
	CreateLevel<PlayLevel>("Play");
	ChangeLevel("Hourglass");

}

void ContentsCore::Update(float _DeltaTime)
{
	
}

void ContentsCore::End()
{
	int a = 0;
}