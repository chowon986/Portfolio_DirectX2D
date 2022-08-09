#include "PreCompile.h"
#include "TattooBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulldogShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

TattooBullet::TattooBullet()
	: Weapon(nullptr)
{
}

TattooBullet::~TattooBullet()
{
}

void TattooBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("TattooshotLoop", FrameAnimation_DESC("TattooshotLoop", 0.1f));
	Renderer->CreateFrameAnimationFolder("TattooshotIntro", FrameAnimation_DESC("TattooshotIntro", 0.05f));
	Renderer->AnimationBindEnd("TattooshotIntro", std::bind(&TattooBullet::TattooshotLoop, this, std::placeholders::_1));

	Renderer->ChangeFrameAnimation("TattooshotIntro");
	Renderer->ScaleToTexture();

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);
}

void TattooBullet::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
}

void TattooBullet::End()
{
}

void TattooBullet::TattooshotLoop(const FrameAnimation_DESC& _DESC)
{
	Renderer->ChangeFrameAnimation("TattooshotLoop");
}
