#include "PreCompile.h"
#include "BoomerangBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BoomerangShooter.h"
#include "BoomerangBulletMovementComponent.h"
#include "IInGameCharacterBase.h"

BoomerangBullet::BoomerangBullet()
	: Weapon(nullptr)
{
}

BoomerangBullet::~BoomerangBullet()
{
}

void BoomerangBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("ConvergeA", FrameAnimation_DESC("ConvergeA", 0.1f));

	Renderer->ChangeFrameAnimation("ConvergeA");
	Renderer->ScaleToTexture();

	MovementComponent = CreateComponent<BoomerangBulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);

	Renderer->ChangeCamera(CAMERAORDER::IRISCAMERA);

}

void BoomerangBullet::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
}

void BoomerangBullet::End()
{
}

void BoomerangBullet::BoomerangshotLoop(const FrameAnimation_DESC& _DESC)
{
	Renderer->ChangeFrameAnimation("BoomerangshotLoop");
}
