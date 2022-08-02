#include "PreCompile.h"
#include "PeaBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "PeaShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

PeaBullet::PeaBullet()
	: Weapon(nullptr)
{
}

PeaBullet::~PeaBullet()
{
}

void PeaBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PeashotLoop", FrameAnimation_DESC("PeashotLoop", 0.1f));
	Renderer->CreateFrameAnimationFolder("PeashotIntro", FrameAnimation_DESC("PeashotIntro", 0.05f));
	Renderer->AnimationBindEnd("PeashotIntro", &PeaBullet::PeashotLoop, this);

	Renderer->ChangeFrameAnimation("PeashotIntro");
	Renderer->ScaleToTexture();

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);
}

void PeaBullet::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
}

void PeaBullet::End()
{
}

void PeaBullet::PeashotLoop(const FrameAnimation_DESC& _DESC)
{
	Renderer->ChangeFrameAnimation("PeashotLoop");
}
