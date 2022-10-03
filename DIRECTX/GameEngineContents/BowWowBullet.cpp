#include "PreCompile.h"
#include "BowWowBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BowWowShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

BowWowBullet::BowWowBullet()
	: Weapon(nullptr)
	, Collision(nullptr)
{
}

BowWowBullet::~BowWowBullet()
{
}

void BowWowBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Bow1", FrameAnimation_DESC("Bow1", 0.1f));
	Renderer->CreateFrameAnimationFolder("Bow2", FrameAnimation_DESC("Bow2", 0.1f)); // Pink
	Renderer->CreateFrameAnimationFolder("Wow1", FrameAnimation_DESC("Wow1", 0.1f));
	Renderer->CreateFrameAnimationFolder("Wow2", FrameAnimation_DESC("Wow2", 0.1f)); // Pink
	Renderer->ChangeFrameAnimation("Bow1");
	Renderer->SetScaleModeImage();
	SetRenderer(Renderer);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 60.0f, 60.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(600.0f);

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);

}

void BowWowBullet::Update(float _DeltaTime)
{
	BulletBase::Update(_DeltaTime);
	//GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void BowWowBullet::End()
{
}
