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
	Renderer->CreateFrameAnimationFolder("Pepper0", FrameAnimation_DESC("Pepper0", 0.1f));
	Renderer->CreateFrameAnimationFolder("Pepper1", FrameAnimation_DESC("Pepper1", 0.1f)); // Pink
	Renderer->CreateFrameAnimationFolder("Pepper2", FrameAnimation_DESC("Pepper2", 0.1f));
	Renderer->ChangeFrameAnimation("Pepper0");
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
