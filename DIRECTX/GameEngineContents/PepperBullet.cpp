#include "PreCompile.h"
#include "PepperBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

PepperBullet::PepperBullet()
	: Collision(nullptr)
	, DirectionElapsedTime(0.0f)
{
}

PepperBullet::~PepperBullet()
{
}

void PepperBullet::Start()
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
	MovementComponent->SetSpeed(400.0f);

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);
}

void PepperBullet::Update(float _DeltaTime)
{

	GameEngineTextureRenderer* CollisionMap = GetLevel()->GetMainColMapImage();
	if (CollisionMap == nullptr)
	{
		return;
	}

	GameEngineTexture* ColMapTexture = CollisionMap->GetCurTexture();
	if (ColMapTexture == nullptr)
	{
		return;
	}
}

void PepperBullet::End()
{
}
