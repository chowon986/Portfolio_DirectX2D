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

void SuperPeaBullet::OnAttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other)
{
}

void SuperPeaBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PeashotLoop", FrameAnimation_DESC("PeashotLoop", 0.05f));
	Renderer->CreateFrameAnimationFolder("PeashotIntro", FrameAnimation_DESC("PeashotIntro", 0.05f));
	Renderer->CreateFrameAnimationFolder("PeashotDeath", FrameAnimation_DESC("PeashotDeath", 0.05f, false));

	Renderer->ChangeFrameAnimation("PeashotIntro");
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
	BulletBase::Update(_DeltaTime); //¸ðµç ÃÑ

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

void SuperPeaBullet::SuperPeashotLoop(const FrameAnimation_DESC& _DESC)
{
	//Renderer->ChangeFrameAnimation("SuperPeashotLoop");
}
