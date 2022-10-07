#include "PreCompile.h"
#include "ContentsCore.h"

#include "SaltBakerLevel.h"
#include "ShopLevel.h"
#include "TitleLevel.h"
#include "StoryLevel.h"
#include "SelectLevel.h"
#include "DogFightLevel.h"
#include "TutorialLevel.h"
#include "WorldMapLevel.h"
#include "ScoreLevel.h"
#include "BishopLevel.h"
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineContents/TextureLoadUtils.h>

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

		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

		GameEngineBlend::Create("Darkness", Desc);
	}

	{
		// 사운드도 나눠서 로드 하기
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

	// 공통 리소스 로드
	TextureLoadUtils::LoadTextures("00Common");
	TextureLoadUtils::LoadTextures("20Player");
	TextureLoadUtils::LoadTextures("21Bullet");

	GameEngineTexture::Cut("Cup.png", 20, 20);
	GameEngineTexture::Cut("Cup_Dash.png", 8, 1);
	GameEngineTexture::Cut("Cup_ExShot.png", 5, 3);
	GameEngineTexture::Cut("PlayerWalkDust.png", 20, 6);
	GameEngineTexture::Cut("PlayerWorldMapDust.png", 20, 6);

	// 키 생성
	GameEngineInput::GetInst()->CreateKey("AddCoin", VK_OEM_PLUS);
	GameEngineInput::GetInst()->CreateKey("MinusCoin", VK_OEM_MINUS);
	GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	GameEngineInput::GetInst()->CreateKey("ColMapOnOffSwitch", 'O');
	GameEngineInput::GetInst()->CreateKey("PhaseChangeKey", 'L');
	GameEngineInput::GetInst()->CreateKey("Aim", 'A');
	GameEngineInput::GetInst()->CreateKey("Shoot", VK_LSHIFT);
	GameEngineInput::GetInst()->CreateKey("GaugeShoot", 'X');
	GameEngineInput::GetInst()->CreateKey("Jump", VK_CONTROL);
	GameEngineInput::GetInst()->CreateKey("Dash", 'Z');
	GameEngineInput::GetInst()->CreateKey("ChangeGun", 'Q');
	GameEngineInput::GetInst()->CreateKey("MoveDown", VK_DOWN);
	GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
	GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
	GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
	GameEngineInput::GetInst()->CreateKey("Select", VK_RETURN);
	GameEngineInput::GetInst()->CreateKey("ESC", VK_ESCAPE);
	GameEngineInput::GetInst()->CreateKey("EnterMap", 'B');
	GameEngineInput::GetInst()->CreateKey("Inventory", 'Y');
	GameEngineInput::GetInst()->CreateKey("AnimationFrameChangeSpeedUp", 'R');
	GameEngineInput::GetInst()->CreateKey("MagicKey", VK_F2);

	CreateLevel<TitleLevel>("Title");
	CreateLevel<SelectLevel>("Select");
	CreateLevel<StoryLevel>("Story");
	CreateLevel<WorldMapLevel>("WorldMap");
	CreateLevel<ShopLevel>("Shop");
	CreateLevel<TutorialLevel>("Tutorial");
	CreateLevel<DogFightLevel>("DogFight");
	CreateLevel<ScoreLevel>("Score");
	CreateLevel<BishopLevel>("Bishop");
	CreateLevel<SaltBakerLevel>("SaltBaker");
	ChangeLevel("Title");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);
}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
}