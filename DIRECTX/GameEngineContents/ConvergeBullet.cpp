#include "PreCompile.h"
#include "ConvergeBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "ConvergeShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

ConvergeBullet::ConvergeBullet()
	: Weapon(nullptr)
{
}

ConvergeBullet::~ConvergeBullet()
{
}

void ConvergeBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("ConvergeA", FrameAnimation_DESC("ConvergeA", 0.1f));
	Renderer->CreateFrameAnimationFolder("ConvergeB", FrameAnimation_DESC("ConvergeB", 0.1f));
	Renderer->CreateFrameAnimationFolder("ConvergeC", FrameAnimation_DESC("ConvergeC", 0.1f));
	Renderer->ChangeFrameAnimation("ConvergeA");
	Renderer->ScaleToTexture();

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);
}

void ConvergeBullet::Update(float _DeltaTime)
{

}

void ConvergeBullet::End()
{
}
