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
