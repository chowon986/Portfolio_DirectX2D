#include "PreCompile.h"
#include "SuperConvergeBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "ConvergeShooter.h"
#include "IInGameCharacterBase.h"
#include "InGameLevelBase.h"
#include "BulletMovementComponent.h"

SuperConvergeBullet::SuperConvergeBullet()
{
}

SuperConvergeBullet::~SuperConvergeBullet()
{
}

void SuperConvergeBullet::OnAttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other)
{
}

void SuperConvergeBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("ConvergeshotLoop", FrameAnimation_DESC("ConvergeshotLoop", 0.05f));
	Renderer->CreateFrameAnimationFolder("ConvergeshotIntro", FrameAnimation_DESC("ConvergeshotIntro", 0.05f));
	Renderer->CreateFrameAnimationFolder("ConvergeshotDeath", FrameAnimation_DESC("ConvergeshotDeath", 0.05f, false));

	Renderer->ChangeFrameAnimation("ConvergeshotIntro");
	Renderer->SetScaleModeImage();

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	Collision->GetTransform().SetLocalScale({ 50.0f,50.0f });
	Collision->ChangeOrder(ObjectOrder::PC_BULLET);
	SetCollision(Collision);
	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);

}

void SuperConvergeBullet::Update(float _DeltaTime)
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

void SuperConvergeBullet::End()
{
}

void SuperConvergeBullet::SuperConvergeshotLoop(const FrameAnimation_DESC& _DESC)
{
	//Renderer->ChangeFrameAnimation("SuperConvergeshotLoop");
}
