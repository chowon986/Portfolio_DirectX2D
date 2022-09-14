#include "PreCompile.h"
#include "StrawberryBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

StrawberryBullet::StrawberryBullet()
	: Collision(nullptr)
{
}

StrawberryBullet::~StrawberryBullet()
{
}

void StrawberryBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("BerryA", FrameAnimation_DESC("BerryA", 0.1f));
	Renderer->CreateFrameAnimationFolder("BerryB", FrameAnimation_DESC("BerryB", 0.1f)); // Pink
	Renderer->CreateFrameAnimationFolder("BerryC", FrameAnimation_DESC("BerryC", 0.1f));
	Renderer->CreateFrameAnimationFolder("BerryD", FrameAnimation_DESC("BerryD", 0.1f)); // Pink
	Renderer->ChangeFrameAnimation("BerryA");
	Renderer->SetScaleModeImage();
	Renderer->GetTransform().SetLocalRotate({ 0.0f,0.0f,90.0f });
	SetRenderer(Renderer);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 60.0f, 60.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(400.0f);

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);

}

void StrawberryBullet::Update(float _DeltaTime)
{
	
}

void StrawberryBullet::End()
{
}
