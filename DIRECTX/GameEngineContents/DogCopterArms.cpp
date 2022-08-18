#include "PreCompile.h"
#include "DogCopterArms.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "IInGameCharacterBase.h"
#include "DogCopter.h"

DogCopterArms::DogCopterArms()
	: Collision(nullptr)
	, Renderer(nullptr)
	, ElapsedTime(-7.0f)
	, AttackIntervalTime(3.0f)
	, CountTimeOnOff(true)
	, WristRenderer(nullptr)
	, State(InGameMonsterState::Idle)
	, AttackState(InGameMonsterAttackState::None)
	, LeaderState(InGameMonsterState::Idle)
	, LeaderAttackState(InGameMonsterAttackState::None)
	, Animation(nullptr)
{
}

DogCopterArms::~DogCopterArms()
{
}

void DogCopterArms::Start()
{


	// 컴포넌트 생성
	{
		Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
		Animation->SetMonsterName("DogCopterArms");
	}

	srand(static_cast<unsigned int>(time(NULL)));
	SetHP(5);
	//SetState(InGameMonsterState::Idle);
	//SetAttackState(InGameMonsterAttackState::None);
}

void DogCopterArms::Update(float _DeltaTime)
{
}

void DogCopterArms::TakeDamage()
{
}

void DogCopterArms::Prepare()
{
}

void DogCopterArms::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void DogCopterArms::Shoot()
{
}

void DogCopterArms::Die()
{
	SetState(InGameMonsterState::Die);
}
