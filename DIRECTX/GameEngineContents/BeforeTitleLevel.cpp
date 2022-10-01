#include "PreCompile.h"
#include "BeforeTitleLevel.h"
#include "Background.h"
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

BeforeTitleLevel::BeforeTitleLevel()
	: BlackScreenToAnimationIntervalTime(3.5f)
	, ElapsedTime(0.0f)
	, MDHRLogoRenderer(nullptr)
{
}

BeforeTitleLevel::~BeforeTitleLevel()
{
}

void BeforeTitleLevel::LevelStartEvent()
{
	TextureLoadUtils::LoadTextures("10BeforeTitleLevel");

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<GameEngineBlur>();
	GetUICameraActorTransform().SetLocalPosition({ 0, 0 });
	GetDarknessCameraActorTransform().SetLocalPosition({ 0, 0 });

	Background* MDHRLogo = CreateActor<Background>(GameObjectGroup::UI);
	MDHRLogoRenderer = MDHRLogo->CreateComponent<GameEngineTextureRenderer>();
	MDHRLogoRenderer->GetTransform().SetLocalScale({ 1280,720,100 });
	MDHRLogoRenderer->CreateFrameAnimationFolder("BeforeTitle", FrameAnimation_DESC("Logo", 0.05f));
	MDHRLogoRenderer->SetTexture("Loading_background.png");
	MDHRLogoRenderer->AnimationBindEnd("BeforeTitle", std::bind(&BeforeTitleLevel::OnHDMRAnimationFrameEnd, this, std::placeholders::_1));

	//Darkness* DarknessActor = CreateActor<Darkness>();
	//DarknessActor->GetTransform().SetWorldPosition({ 0.0f, 0.0f });
	//DarknessActor->SetLevelOverOn();

	OldFilm* PostEffect = CreateActor<OldFilm>(GameObjectGroup::UI);
	PostEffect->SetLevelOverOn();

	//GameEngineSound::SoundPlayOneShot("MDHR.mp3");

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

	std::shared_ptr<SuperBeamItem> SuperBeamItemIcon = std::make_shared<SuperBeamItem>();
	std::shared_ptr<SuperGhostItem> SuperGhostItemIcon = std::make_shared<SuperGhostItem>();
	std::shared_ptr<SuperInvincibleItem> SuperInvincibleItemIcon = std::make_shared<SuperInvincibleItem>();
	State->Items[ItemType::Super].push_back(SuperBeamItemIcon);
	State->Items[ItemType::Super].push_back(SuperInvincibleItemIcon);
	State->Items[ItemType::Super].push_back(SuperGhostItemIcon);

	std::shared_ptr<AstalCookieItem> AstalCookieItemIcon = std::make_shared<AstalCookieItem>();
	State->Items[ItemType::Charm].push_back(AstalCookieItemIcon);
}

void BeforeTitleLevel::Update(float _DeltaTime)
{
	ElapsedTime += _DeltaTime;
	if (ElapsedTime > BlackScreenToAnimationIntervalTime)
	{
		MDHRLogoRenderer->ChangeFrameAnimation("BeforeTitle");
	}

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Title");
	}
}

void BeforeTitleLevel::End()
{
}

void BeforeTitleLevel::OnHDMRAnimationFrameEnd(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("Title");
}