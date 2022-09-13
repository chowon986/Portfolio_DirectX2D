#include "PreCompile.h"
#include "LeafBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

LeafBullet::LeafBullet()
	: Collision(nullptr)
	, LerpTime(0.0f)
	, IsLeafPosRightEnd(false)
	, IndexNum(-1)
{
}

LeafBullet::~LeafBullet()
{
}

void LeafBullet::Start()
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

	StartPosX.insert(std::make_pair<int, float>(0, 100.0f));
	StartPosX.insert(std::make_pair<int, float>(1, 400.0f));
	StartPosX.insert(std::make_pair<int, float>(2, 700.0f));
	StartPosX.insert(std::make_pair<int, float>(3, 1000.0f));

	DestPosX.insert(std::make_pair<int, float>(0, 300.0f));
	DestPosX.insert(std::make_pair<int, float>(1, 600.0f));
	DestPosX.insert(std::make_pair<int, float>(2, 900.0f));
	DestPosX.insert(std::make_pair<int, float>(3, 1200.0f));
}

void LeafBullet::Update(float _DeltaTime)
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

	ElapsedTime += _DeltaTime;
	LerpTime = ElapsedTime / 1.0f;
	float4 CurPos = GetTransform().GetWorldPosition();

	if (IndexNum != -1)
	{
		if (IsLeafPosRightEnd == false)
		{
			if (DestPosX[IndexNum] == CurPos.x)
			{
				IsLeafPosRightEnd = true;
				ElapsedTime = 0.0f;
				return;
			}

			LerpPos = float4::LerpLimit(StartPosX[IndexNum], DestPosX[IndexNum], LerpTime);
		}
		else
		{
			if (StartPosX[IndexNum] == CurPos.x)
			{
				IsLeafPosRightEnd = false;
				ElapsedTime = 0.0f;
				return;
			}
			LerpPos = float4::LerpLimit(DestPosX[IndexNum], StartPosX[IndexNum], LerpTime);
		}
	}

	GetTransform().SetLocalPosition({ LerpPos.x, CurPos.y, (int)ZOrder::Background - 2 });
	GetTransform().SetLocalMove(float4::DOWN * _DeltaTime * 150);
}

void LeafBullet::End()
{
}
