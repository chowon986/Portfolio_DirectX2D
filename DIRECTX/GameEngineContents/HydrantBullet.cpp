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

void HydrantBullet::Start()
{
	srand(time(NULL));

	std::vector<float> RandomPosX = { 0.0f, 640.0f, 1280.0f };
	int RandomPosXIndex = rand() % RandomPosX.size();
	GetTransform().SetWorldPosition({ RandomPosX[RandomPosXIndex],0,(int)ZOrder::UI });

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PeashotIntro", FrameAnimation_DESC("PeashotIntro", 0.1f, true));
	Renderer->ChangeFrameAnimation("PeashotIntro");
	Renderer->SetScaleModeImage();

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);
}

void HydrantBullet::Update(float _DeltaTime)
{
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

			CurDirection.x = GameEngineMath::LerpLimit(CurDirection.x, DestPosition.x, ElapsedTime / 30);
			CurDirection.y = GameEngineMath::LerpLimit(CurDirection.y, DestPosition.y, ElapsedTime / 30);

			float AngleZ = std::atan2(CurDirection.y, CurDirection.x);
			
			GetTransform().SetLocalRotation({ 0.0f, 0.0f, GameEngineMath::RadianToDegree * AngleZ });
			GetTransform().SetWorldMove(CurDirection * _DeltaTime * 500);
		}
	}
}

void HydrantBullet::End()
{
}
