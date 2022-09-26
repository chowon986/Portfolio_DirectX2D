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
	Renderer->CreateFrameAnimationFolder("Lime0", FrameAnimation_DESC("Lime0", 0.07f));
	Renderer->CreateFrameAnimationFolder("Lime1", FrameAnimation_DESC("Lime1", 0.07f)); // Pink
	Renderer->CreateFrameAnimationFolder("Lime2", FrameAnimation_DESC("Lime2", 0.07f));
	Renderer->CreateFrameAnimationFolder("Lime3", FrameAnimation_DESC("Lime3", 0.07f)); // Pink
	Renderer->ChangeFrameAnimation("Lime0");
	Renderer->SetScaleModeImage();
	SetRenderer(Renderer);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 60.0f, 60.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(500.0f);

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

	if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x - 10, -GetTransform().GetWorldPosition().y).CompareInt4D(float4::BLACK))
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
				SetDirection(float4::RIGHT);
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
				SetDirection(float4::RIGHT);
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
