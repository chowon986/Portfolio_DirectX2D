#include "PreCompile.h"
#include "ContentsCore.h"

#include "PlayLevel.h"
#include "ShopLevel.h"
#include "TitleLevel.h"
#include "SelectLevel.h"
#include "DogFightLevel.h"
#include "TutorialLevel.h"
#include "WorldMapLevel.h"
#include "HourglassLevel.h"
#include "BeforeTitleLevel.h"

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

	std::vector<GameEngineDirectory> RecursiveDir = Dir.GetRecursiveAllDirectory();
	for (GameEngineDirectory Dir : RecursiveDir)
	{
		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	Dir.Move("01ShopLevel");
	std::vector<GameEngineFile> Textures = Dir.GetAllFile();

	for (size_t i = 0; i < Textures.size(); i++)
	{
		GameEngineTexture::Load(Textures[i].GetFullPath());
	}

	Dir.MoveParent();
	Dir.Move("11TitleLevel");
	std::vector<GameEngineFile> Textures1 = Dir.GetAllFile();

	for (size_t i = 0; i < Textures1.size(); i++)
	{
		GameEngineTexture::Load(Textures1[i].GetFullPath());
	}

	Dir.MoveParent();
	Dir.Move("12SelectLevel");
	std::vector<GameEngineFile> Textures2 = Dir.GetAllFile();

	for (size_t i = 0; i < Textures2.size(); i++)
	{
		GameEngineTexture::Load(Textures2[i].GetFullPath());
	}

	Dir.MoveParent();
	Dir.Move("14WorldMapLevel");
	std::vector<GameEngineFile> Textures3 = Dir.GetAllFile();

	for (size_t i = 0; i < Textures3.size(); i++)
	{
		GameEngineTexture::Load(Textures3[i].GetFullPath());
	}

	Dir.MoveParent();
	Dir.Move("15DogFightLevel");
	std::vector<GameEngineFile> Textures4 = Dir.GetAllFile();

	for (size_t i = 0; i < Textures4.size(); i++)
	{
		GameEngineTexture::Load(Textures4[i].GetFullPath());
	}

	GameEngineTexture::Cut("Cup.png", 20, 20);
	GameEngineTexture::Cut("Cup_Dash.png", 8, 1);

	CreateLevel<BeforeTitleLevel>("BeforeTitle");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<SelectLevel>("Select");
	CreateLevel<HourglassLevel>("Hourglass");
	CreateLevel<WorldMapLevel>("WorldMap");
	CreateLevel<ShopLevel>("Shop");
	CreateLevel<TutorialLevel>("Tutorial");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<DogFightLevel>("DogFight");
	ChangeLevel("DogFight");

	GameEngineFont::Load("±Ã¼­");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);

}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
	int a = 0;
}