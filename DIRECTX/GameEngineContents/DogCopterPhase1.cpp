#include "PreCompile.h"
#include "DogFightLevel.h"
#include "HydrantBullet.h"
#include "DogCopterPhase1.h"
#include "InGameMovementComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

DogCopterPhase1::DogCopterPhase1()
	: HydrantXPos(0.0f)
	, CreateTimeInterval(3.0f)
{
}

DogCopterPhase1::~DogCopterPhase1()
{
}

void DogCopterPhase1::Start()
{
	GetTransform().SetWorldPosition({ 640.0f, -360.0f, (int)ZOrder::NPC });

	GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("DogCopterPhase1Intro", FrameAnimation_DESC("DogCopterHydrant", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("DogCopterPhase1Attack1", FrameAnimation_DESC("Nothing", 0.1f, true));
	Renderer->ChangeFrameAnimation("DogCopterPhase1Intro");
	Renderer->AnimationBindFrame("DogCopterPhase1Intro", std::bind(&DogCopterPhase1::PrepareAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	SetRenderer(Renderer);

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
		if (DogFightLevel* Level = dynamic_cast<DogFightLevel*>(GetLevel()))
		{
			if (Level->GetPhase() == Phase::Phase1)
			{

				if (CreateTimeInterval < ElapsedTime)
				{
					ElapsedTime -= CreateTimeInterval;
					Bullet = GetLevel()->CreateActor<HydrantBullet>();
					GameEngineSound::SoundPlayOneShot("sfx_DLC_Dogfight_P1_HydrantMissile_Entrance.wav");
				}
			}
		}
	}
}

void DogCopterPhase1::End()
{
}

void DogCopterPhase1::Prepare()
{
	SetState(InGameMonsterState::Prepare);
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


void DogCopterPhase1::PrepareAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 1)
	{
		SoundPlayer = GameEngineSound::SoundPlayControl("sfx_DLC_Dogfight_P1_Leader_CopterIntroRightScreen.wav");
	}


	if (_Info.CurFrame == 16 || _Info.CurFrame == 22 || _Info.CurFrame == 25)
	{
		GameEngineSound::SoundPlayOneShot("sfx_DLC_Dogfight_P1_Leader_CopterBackground_Canon_01.wav");
	}

	if (_Info.CurFrame == 40)
	{
		SoundPlayer.Stop();
		Attack1();
	}
}
