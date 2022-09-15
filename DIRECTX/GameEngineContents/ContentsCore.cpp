#include "PreCompile.h"
#include "ContentsCore.h"

#include "SaltBakerLevel.h"
#include "ShopLevel.h"
#include "TitleLevel.h"
#include "SelectLevel.h"
#include "DogFightLevel.h"
#include "TutorialLevel.h"
#include "WorldMapLevel.h"
#include "HourglassLevel.h"
#include "BeforeTitleLevel.h"
#include "ScoreLevel.h"
#include "BishopLevel.h"
#include <GameEngineCore/GameEngineBlend.h>

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
	{
		D3D11_BLEND_DESC Desc = { 0 };

		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_REV_SUBTRACT;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_COLOR;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_SUBTRACT;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

		GameEngineBlend::Create("OldFilm", Desc);
	}

	{
		D3D11_BLEND_DESC Desc = { 0 };

		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_MIN;

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_COLOR;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_DEST_ALPHA;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_MAX;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;

		GameEngineBlend::Create("Darkness", Desc);
	}

	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	}

	if (false == GameEngineInput::GetInst()->IsKey("ColMapOnOffSwitch"))
	{
		GameEngineInput::GetInst()->CreateKey("ColMapOnOffSwitch", 'O');
	}

	{

		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("ConstantResources");
		Dir.Move("ConstantResources");
		Dir.Move("Sound");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (GameEngineFile& File : Files)
		{
			GameEngineSound::LoadRessource(File);
		}
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

	Dir.MoveParent();
	Dir.Move("16BishopLevel");
	std::vector<GameEngineFile> Textures5 = Dir.GetAllFile();

	for (size_t i = 0; i < Textures5.size(); i++)
	{
		GameEngineTexture::Load(Textures5[i].GetFullPath());
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
	CreateLevel<DogFightLevel>("DogFight");
	CreateLevel<ScoreLevel>("Score");
	CreateLevel<BishopLevel>("Bishop");
	CreateLevel<SaltBakerLevel>("SaltBaker");
	ChangeLevel("BeforeTitle");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
}