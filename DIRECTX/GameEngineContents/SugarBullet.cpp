#include "PreCompile.h"
#include "SugarBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

SugarBullet::SugarBullet()
	: Collision(nullptr)
	, DirectionElapsedTime(0.0f)
{
}

SugarBullet::~SugarBullet()
{
}

void SugarBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Sugar0", FrameAnimation_DESC("Sugar0", 0.1f));
	Renderer->CreateFrameAnimationFolder("Sugar1", FrameAnimation_DESC("Sugar1", 0.1f)); // Pink
	Renderer->CreateFrameAnimationFolder("Sugar2", FrameAnimation_DESC("Sugar2", 0.1f));
	Renderer->CreateFrameAnimationFolder("Sugar3", FrameAnimation_DESC("Sugar3", 0.1f)); // Pink
	Renderer->ChangeFrameAnimation("Sugar0");
	Renderer->SetScaleModeImage();
	SetRenderer(Renderer);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 60.0f, 60.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);
}

void SugarBullet::Update(float _DeltaTime)
{
	DirectionElapsedTime += _DeltaTime;
	Direction.x += _DeltaTime * 400;
	Direction.y = sin(DirectionElapsedTime * 3) * 150 - 500;
	GetTransform().SetWorldPosition({ Direction.x, Direction.y, GetTransform().GetWorldPosition().z});
}

void SugarBullet::End()
{
}
