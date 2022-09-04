#include "PreCompile.h"
#include "SpreadBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "SpreadShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

SpreadBullet::SpreadBullet()
	: Weapon(nullptr)
{
}

SpreadBullet::~SpreadBullet()
{
}

void SpreadBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("SpreadExIntro", FrameAnimation_DESC("SpreadExIntro", 0.1f));
	Renderer->ChangeFrameAnimation("SpreadExIntro");
	Renderer->ScaleToTexture();

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);

	Renderer->ChangeCamera(CAMERAORDER::IRISCAMERA);

}

void SpreadBullet::Update(float _DeltaTime)
{

}

void SpreadBullet::End()
{
}
