#include <functional>
#include "PreCompile.h"
#include "TitleLevel.h"
#include "Background.h"
#include <GameEngineCore/GameEngineBlur.h>
#include <GameEngineContents/TextureLoadUtils.h>
#include "OldFilm.h"
#include "Darkness.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineBlur.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineContents/TextureLoadUtils.h>
#include <GameEngineContents/SuperBeamItem.h>
#include <GameEngineContents/SuperGhostItem.h>
#include <GameEngineContents/SuperInvincibleItem.h>
#include <GameEngineContents/AstalCookieItem.h>
#include <GameEngineContents/WeaponItemBase.h>
#include <GameEngineContents/PeaShooterItem.h>
#include <GameEngineContents/CharacterState.h>
#include <GameEngineContents/PeaShooter.h>
#include <GameEngineContents/CharacterScore.h>
#include <GameEngineContents/TitleBGMPlayer.h>

TitleLevel::TitleLevel()
	: IrisRenderer(nullptr)
	, MDHRLogoRenderer(nullptr)
	, FadeInActorRenderer(nullptr)
	, ElapsedTime(0.0f)
	, FadeInElapsedTime(0.0f)
	, BlackScreenToAnimationIntervalTime(3.5f)
	, Phase(0)
	, SoundOnceCheckA(false)
	, SoundOnceCheckB(false)
	, SoundOnceCheckC(false)
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	GameEngineActor* FadeInActor = CreateActor<GameEngineActor>();
	FadeInActorRenderer = FadeInActor->CreateComponent<GameEngineTextureRenderer>();
	FadeInActorRenderer->SetTexture("Loading_background.png");
	FadeInActorRenderer->GetTransform().SetWorldScale({ 1280.0f, 720, 1.0 });
	FadeInActorRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f, -50.0f });
}

void TitleLevel::LevelStartEvent()
{
	if (false == TextureLoadUtils::LoadTextures("10BeforeTitleLevel"))
	{
		return;
	}

	if (false == TextureLoadUtils::LoadTextures("11TitleLevel"))
	{
		return;
	}

	//Start
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetBackgroundCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetRotateCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetRotateCamera2()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();

	GetUICameraActorTransform().SetLocalPosition({ 0, 0 });
	GetDarknessCameraActorTransform().SetLocalPosition({ 0, 0 });

	Background* MDHRLogo = CreateActor<Background>(GameObjectGroup::UI);
	MDHRLogoRenderer = MDHRLogo->CreateComponent<GameEngineTextureRenderer>();
	MDHRLogoRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
	MDHRLogoRenderer->CreateFrameAnimationFolder("BeforeTitle", FrameAnimation_DESC("Logo", 0.04f, false));
	MDHRLogoRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f, -10 });
	MDHRLogoRenderer->ChangeFrameAnimation("BeforeTitle");
	MDHRLogoRenderer->CurAnimationPauseOn();
	MDHRLogoRenderer->AnimationBindEnd("BeforeTitle", std::bind(&TitleLevel::OnHDMRAnimationFrameEnd, this, std::placeholders::_1));

	OldFilm* PostEffect = CreateActor<OldFilm>(GameObjectGroup::UI);
	PostEffect->SetLevelOverOn();

	CharacterState* State = CreateActor<CharacterState>(GameObjectGroup::CharacterState);
	State->SetLevelOverOn();
	std::shared_ptr<PeaShooterItem> PeaShot = std::make_shared<PeaShooterItem>();
	State->EquippedItems[InventoryType::ShotA] = PeaShot;
	State->Items[ItemType::Shoot].push_back(PeaShot);
	if (WeaponItemBase* Item = dynamic_cast<WeaponItemBase*>(State->EquippedItems[InventoryType::ShotA].get()))
	{
		Item->Weapon = CreateActor<PeaShooter>();
		Item->Weapon->SetLevelOverOn();
	}

	CharacterScore* Score = CreateActor<CharacterScore>(GameObjectGroup::CharacterScore);
	Score->SetLevelOverOn();

	std::shared_ptr<SuperBeamItem> SuperBeamItemIcon = std::make_shared<SuperBeamItem>();
	std::shared_ptr<SuperGhostItem> SuperGhostItemIcon = std::make_shared<SuperGhostItem>();
	std::shared_ptr<SuperInvincibleItem> SuperInvincibleItemIcon = std::make_shared<SuperInvincibleItem>();
	State->Items[ItemType::Super].push_back(SuperBeamItemIcon);
	State->Items[ItemType::Super].push_back(SuperInvincibleItemIcon);
	State->Items[ItemType::Super].push_back(SuperGhostItemIcon);

	std::shared_ptr<AstalCookieItem> AstalCookieItemIcon = std::make_shared<AstalCookieItem>();
	State->Items[ItemType::Charm].push_back(AstalCookieItemIcon);

	{
		GameEngineActor* DarknessActor = CreateActor<GameEngineActor>();
		GameEngineTextureRenderer* DarknessRenderer = DarknessActor->CreateComponent<GameEngineTextureRenderer>();
		DarknessRenderer->CreateFrameAnimationFolder("Darkness", FrameAnimation_DESC("Darkness", 0.05f, true));
		DarknessRenderer->ChangeFrameAnimation("Darkness");
		DarknessRenderer->GetTransform().SetWorldScale({ 1300.0f, 750, 1.0 });
		DarknessRenderer->GetTransform().SetWorldPosition({ 0.0f, 0.0f, -100.0f });
		DarknessRenderer->GetPipeLine()->SetOutputMergerBlend("Darkness");

		Background* Title = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* TitleRenderer = Title->CreateComponent<GameEngineTextureRenderer>();
		TitleRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
		TitleRenderer->SetTexture("TitleScreenBackground.png");
		TitleRenderer->GetTransform().SetLocalPosition({ 0.0f, 0.0f, (int)ZOrder::Background });

		Background* Bottom = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* BottomRenderer = Bottom->CreateComponent<GameEngineTextureRenderer>();
		BottomRenderer->GetTransform().SetLocalScale({ 1328.0f, 176.0f, 1.0f });
		BottomRenderer->GetTransform().SetLocalPosition({ 18.0f, -300.0f, (int)ZOrder::Player - 2 });
		BottomRenderer->SetTexture("TitleChipsLeft.png");

		Background* Button = CreateActor<Background>(GameObjectGroup::UI);
		GameEngineTextureRenderer* ButtonRenderer = Button->CreateComponent<GameEngineTextureRenderer>();
		ButtonRenderer->CreateFrameAnimationFolder("Press", FrameAnimation_DESC("PressAnyKey", 0.5f));
		ButtonRenderer->ChangeFrameAnimation("Press");
		ButtonRenderer->GetTransform().SetLocalScale({ 363.0f, 49.0f, 1.0f });
		ButtonRenderer->GetTransform().SetLocalPosition({ 0.0f, -293.0f,  (int)ZOrder::Player - 3 });

		Background* Iris = CreateActor<Background>(GameObjectGroup::UI);
		IrisRenderer = Iris->CreateComponent<GameEngineTextureRenderer>();
		IrisRenderer->GetTransform().SetLocalScale({ 1280.0f, 720.0f, 1.0f });
		IrisRenderer->CreateFrameAnimationFolder("IrisBStart", FrameAnimation_DESC("IrisB", 0.05f, false));
		IrisRenderer->CreateFrameAnimationFolder("IrisB", FrameAnimation_DESC("IrisB", 0, 0, 0.05f, true));
		IrisRenderer->AnimationBindEnd("IrisBStart", std::bind(&TitleLevel::OnIrisAnimationFrameEnd, this, std::placeholders::_1));
		IrisRenderer->ChangeFrameAnimation("IrisB");
	}

	{
		Background* Chalice = CreateActor<Background>(GameObjectGroup::Player);
		GameEngineTextureRenderer* ChaliceRenderer = Chalice->CreateComponent<GameEngineTextureRenderer>();
		ChaliceRenderer->CreateFrameAnimationFolder("Chalice", FrameAnimation_DESC("Chalice", 0.055f));
		ChaliceRenderer->ChangeFrameAnimation("Chalice");
		ChaliceRenderer->SetScaleModeImage();
		ChaliceRenderer->GetTransform().SetLocalPosition({ -25.0f, -50.0f, (int)ZOrder::Player });

		Background* Cuphead = CreateActor<Background>(GameObjectGroup::Player);
		GameEngineTextureRenderer* CupheadRenderer = Cuphead->CreateComponent<GameEngineTextureRenderer>();
		CupheadRenderer->CreateFrameAnimationFolder("Cuphead", FrameAnimation_DESC("Cuphead", 0.055f));
		CupheadRenderer->ChangeFrameAnimation("Cuphead");
		CupheadRenderer->SetScaleModeImage();
		CupheadRenderer->GetTransform().SetLocalPosition({ -320.0f, -20.0f, (int)ZOrder::Player - 1 });

		Background* Mugman = CreateActor<Background>(GameObjectGroup::Player);
		GameEngineTextureRenderer* MugmanRenderer = Mugman->CreateComponent<GameEngineTextureRenderer>();
		MugmanRenderer->CreateFrameAnimationFolder("MugmanA", FrameAnimation_DESC("Mugman", 0.055f));
		MugmanRenderer->ChangeFrameAnimation("MugmanA");
		MugmanRenderer->SetScaleModeImage();
		MugmanRenderer->GetTransform().SetLocalPosition({ 305.0f, -24.0f, (int)ZOrder::Player - 1 });
	}
}

void TitleLevel::Update(float _DeltaTime)
{
	TextureLoadUtils::LoadTexturesAsync("23IntroStory", 1);

	if (0 == Phase)
	{
		ElapsedTime += _DeltaTime;
		if (ElapsedTime > 0.8)
		{
			if (false == SoundOnceCheckA)
			{
				GameEngineSound::SoundPlayOneShot("MDHR.mp3");
				SoundOnceCheckA = true;
			}
		}

		if (ElapsedTime > BlackScreenToAnimationIntervalTime)
		{
			FadeInElapsedTime += _DeltaTime;
			FadeInActorRenderer->GetPixelData().PlusColor.a = max(-(FadeInElapsedTime / 1.0f), -1);
			if (FadeInActorRenderer->GetPixelData().PlusColor.a == -1)
			{
				MDHRLogoRenderer->CurAnimationPauseOff();
			}
		}
	}

	if (1 == Phase)
	{
		if (false == SoundOnceCheckB)
		{
			TitleBGMPlayer* BGMPlayer = CreateActor<TitleBGMPlayer>(GameObjectGroup::TitleBGM);
			BGMPlayer->SetLevelOverOn();
			BGMPlayer->BGMPlayer = GameEngineSound::SoundPlayControl("mus_dlc_title.wav");
			SoundOnceCheckB = true;
		}
		ElapsedTime += _DeltaTime;
		MDHRLogoRenderer->GetPixelData().PlusColor.a = max(-(ElapsedTime / 2.0f), -1);

		if (true == GameEngineInput::GetInst()->GetIsAnyKeyPressed() && false == SoundOnceCheckC) // 아무키가 눌리면
		{
			SoundOnceCheckC = true;
			GameEngineSound::SoundPlayOneShot("sfx_WorldMap_LevelSelect_BubbleAppear.wav");
			IrisRenderer->ChangeFrameAnimation("IrisBStart");
		}

	}

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Select");
	}
}

void TitleLevel::End() 
{
}

void TitleLevel::OnIrisAnimationFrameEnd(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("Select");
}

void TitleLevel::OnHDMRAnimationFrameEnd(const FrameAnimation_DESC& _Info)
{
	ElapsedTime = 0.0f;
	FadeInElapsedTime = 0.0f;
	Phase = 1;
}