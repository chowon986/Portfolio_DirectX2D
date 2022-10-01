#include "PreCompile.h"
#include "SugarBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"
#include "InGameCuphead.h"

SugarBullet::SugarBullet()
	: DirectionElapsedTime(0.0f)
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

	if (Collision->GetOrder() == (int)ObjectOrder::PARRIABLEOBJECT)
	{
		Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D,
			std::bind(&SugarBullet::OnParryCollision, this, std::placeholders::_1, std::placeholders::_2));
	}
}

void SugarBullet::End()
{
}

CollisionReturn SugarBullet::OnParryCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	/*if (InGameCuphead* Player = dynamic_cast<InGameCuphead*>(_Other->GetParent()))
	{
		if (true == Player->OnParriable)
		{
			Death();
		}
	}*/
	return CollisionReturn::Break;
}
