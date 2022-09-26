#include "PreCompile.h"
#include "SuperPeaBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "PeaShooter.h"
#include "IInGameCharacterBase.h"
#include "InGameLevelBase.h"
#include "BulletMovementComponent.h"

SuperPeaBullet::SuperPeaBullet()
{
}

SuperPeaBullet::~SuperPeaBullet()
{
}

void SuperPeaBullet::OnPeashotExIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->ChangeFrameAnimation("PeashotExLoop");
}

void SuperPeaBullet::OnAttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Renderer->ChangeFrameAnimation("PeashotExDeath");
}

void SuperPeaBullet::OnPeashotExDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}

void SuperPeaBullet::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PeashotExIntro", FrameAnimation_DESC("PeashotExIntro", 0.05f));
	Renderer->CreateFrameAnimationFolder("PeashotExLoop", FrameAnimation_DESC("PeashotExLoop", 0.05f));
	Renderer->CreateFrameAnimationFolder("PeashotExDeath", FrameAnimation_DESC("PeashotExDeath", 0.05f, false));

	Renderer->AnimationBindEnd("PeashotExIntro", std::bind(&SuperPeaBullet::OnPeashotExIntroAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PeashotExDeath", std::bind(&SuperPeaBullet::OnPeashotExDeathAnimationFrameFinished, this, std::placeholders::_1));

	Renderer->ChangeFrameAnimation("PeashotExIntro");
	Renderer->SetScaleModeImage();

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(1500.0f);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	Collision->GetTransform().SetLocalScale({ 50.0f,50.0f });
	Collision->ChangeOrder(ObjectOrder::PC_BULLET);
	SetCollision(Collision);
	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);
}

void SuperPeaBullet::Update(float _DeltaTime)
{
	if (nullptr == ColMapImage)
	{
		SetColMapImage(GetLevel()->GetMainColMapImage());
	}
	else
	{
		BulletBase::Update(_DeltaTime);
	}
}

void SuperPeaBullet::End()
{
}