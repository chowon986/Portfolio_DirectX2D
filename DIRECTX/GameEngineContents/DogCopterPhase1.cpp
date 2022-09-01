#include "PreCompile.h"
#include "Bulldog.h"
#include "HydrantBullet.h"
#include "DogCopterPhase1.h"
#include "InGameMovementComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

DogCopterPhase1::DogCopterPhase1()
	: Renderer(nullptr)
	, HydrantXPos(0.0f)
	, CreateTimeInterval(3.0f)
{
}

DogCopterPhase1::~DogCopterPhase1()
{
}

void DogCopterPhase1::Start()
{
	GetTransform().SetWorldPosition({ 0.0f, -360.0f, (int)ZOrder::NPC });

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("DogCopterPhase1Prepare", FrameAnimation_DESC("DogCopterHydrant", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("DogCopterPhase1Attack1", FrameAnimation_DESC("Nothing", 0.1f, true));
	Renderer->ChangeFrameAnimation("DogCopterPhase1Prepare");
	Renderer->AnimationBindEnd("DogCopterPhase1Prepare", std::bind(&DogCopterPhase1::PrepareAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();

	for (int i = 0; i < 4; i++)
	{
		HydrantStartPosition.insert(std::pair<int, float4>(i, { HydrantXPos, 0.0f,(int)ZOrder::Player + 1 }));
		HydrantXPos += 300.0f;
	}

	InGameMovementComponent* Movement = CreateComponent<InGameMovementComponent>();
	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("DogCopterPhase1");
}

void DogCopterPhase1::Update(float _DeltaTime)
{
	ElapsedTime += _DeltaTime;

	if (GetState() == InGameMonsterState::Attack1)
	{
		if (nullptr != dynamic_cast<Bulldog*>(GetParent()))
		{
			ParentBullDog = dynamic_cast<Bulldog*>(GetParent());
		}

		if (ParentBullDog->GetHP() != 0)
		{
			if (CreateTimeInterval < ElapsedTime)
			{
				ElapsedTime -= CreateTimeInterval;
				Bullet = GetLevel()->CreateActor<HydrantBullet>();
				Bullet->SetParent(this);
			}
		}
	}
}

void DogCopterPhase1::End()
{
}

void DogCopterPhase1::Prepare()
{
	if (GetState() != InGameMonsterState::Attack1)
	{
	SetState(InGameMonsterState::Prepare);
	}
	else
	{
		return;
	}
}

void DogCopterPhase1::Idle()
{
}

void DogCopterPhase1::TakeDamage()
{
}

void DogCopterPhase1::Shoot()
{
}

void DogCopterPhase1::Die()
{
}

void DogCopterPhase1::Attack1()
{
	SetState(InGameMonsterState::Attack1);
}

void DogCopterPhase1::PrepareAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Attack1();
}
