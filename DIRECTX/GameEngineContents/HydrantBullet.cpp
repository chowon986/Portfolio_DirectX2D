#include "PreCompile.h"
#include "HydrantBullet.h"
#include "DogCopterPhase1.h"
#include "IInGameCharacterBase.h"
#include "DogFightLevel.h"
#include <GameEngineBase/GameEngineMath.h>

HydrantBullet::HydrantBullet()
	: Collision(nullptr)
	, Parent(nullptr)
	, ElapsedTime(0.0f)
	, UpdateDirectionInterval(1.f)
	, CurDirection(0.0f)
{
}

HydrantBullet::~HydrantBullet()
{
}

bool HydrantBullet::AttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Death();
	// 수정하기 성공, 실패 나눠서 작업
	//Renderer->ChangeFrameAnimation("")
	return true;
}

void HydrantBullet::Start()
{
	srand(time(NULL));

	std::vector<float> RandomPosX = { 0.0f, 640.0f, 1280.0f };
	int RandomPosXIndex = rand() % RandomPosX.size();
	GetTransform().SetWorldPosition({ RandomPosX[RandomPosXIndex], 30, (int)ZOrder::UI });

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Hydrant", FrameAnimation_DESC("Hydrant", 0.1f, true));
	Renderer->ChangeFrameAnimation("Hydrant");
	Renderer->SetScaleModeImage();

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);
	Renderer->ChangeCamera(CAMERAORDER::IRISCAMERA);
}

void HydrantBullet::Update(float _DeltaTime)
{
	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D,
		std::bind(&HydrantBullet::AttackSuccess, this, std::placeholders::_1, std::placeholders::_2));
	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D,
		std::bind(&HydrantBullet::AttackSuccess, this, std::placeholders::_1, std::placeholders::_2));

	if (DogFightLevel* Level = dynamic_cast<DogFightLevel*>(GetLevel()))
	{
		if (IInGameCharacterBase* Player = Level->GetPlayer())
		{
			ElapsedTime += _DeltaTime;
			if (ElapsedTime > UpdateDirectionInterval)
			{
				ElapsedTime -= UpdateDirectionInterval;
				float4 PlayerPos = Player->GetTransform().GetWorldPosition();
				DestPosition = PlayerPos - GetTransform().GetWorldPosition();
				DestPosition.Normalize();
				DestPosition.z = 0;
			}

			CurDirection.x = GameEngineMath::LerpLimit(CurDirection.x, DestPosition.x, ElapsedTime / 20);
			CurDirection.y = GameEngineMath::LerpLimit(CurDirection.y, DestPosition.y, ElapsedTime / 20);

			float AngleZ = std::atan2(CurDirection.y, CurDirection.x);
			
			GetTransform().SetLocalRotation({ 0.0f, 0.0f, GameEngineMath::RadianToDegree * AngleZ - 90 });
			GetTransform().SetWorldMove(CurDirection * _DeltaTime * 400);
		}
	}
}

void HydrantBullet::End()
{
}
