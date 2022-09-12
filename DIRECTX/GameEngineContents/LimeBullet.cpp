#include "PreCompile.h"
#include "LimeBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

LimeBullet::LimeBullet()
	: Collision(nullptr)
	, DirectionElapsedTime(0.0f)
{
}

LimeBullet::~LimeBullet()
{
}

void LimeBullet::Start()
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

void LimeBullet::Update(float _DeltaTime)
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

	if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -GetTransform().GetWorldPosition().y).CompareInt4D(float4::BLACK))
	{
		SetDirection(float4::ZERO);
		if (GetStartPosName() == "LeftUp")
		{
			DirectionElapsedTime += _DeltaTime;
			float Time = DirectionElapsedTime / 30;
			float4 CurPos = GetTransform().GetWorldPosition();

			float DestPosY = GameEngineMath::LerpLimit(CurPos.y, -700, Time);

			if (abs(CurPos.y - (-700)) <= 1)
			{
				SetDirection(float4::LEFT);
			}
			else
			{
				GetTransform().SetLocalPosition(float4({ CurPos.x, DestPosY, CurPos.z }));
			}
		}
		else if (GetStartPosName() == "LeftDown")
		{
			DirectionElapsedTime += _DeltaTime;
			float Time = DirectionElapsedTime / 30;
			float4 CurPos = GetTransform().GetWorldPosition();

			float DestPosY = GameEngineMath::LerpLimit(CurPos.y, -350, Time);

			if (abs(CurPos.y - (-350)) <= 1)
			{
				SetDirection(float4::LEFT);
			}
			else
			{
				GetTransform().SetLocalPosition(float4({ CurPos.x, DestPosY, CurPos.z }));
			}
		}

	}
}

void LimeBullet::End()
{
}
