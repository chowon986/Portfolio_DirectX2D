#include "PreCompile.h"
#include "MonsterWeaponBase.h"
#include "IInGameMonsterBase.h"
#include "Ph2Dog.h"
#include "DogCopter.h"

MonsterWeaponBase::MonsterWeaponBase()
	: IntervalTime(0.01f)
	, ElapsedTime(0.0f)
	, Character(nullptr)
	, State(InGameMonsterState::Prepare)
	, AttackState(InGameMonsterAttackState::None)
	, ColMapImage(nullptr)
{
}

MonsterWeaponBase::~MonsterWeaponBase()
{
}

void MonsterWeaponBase::UpdateDirection()
{
	Character = dynamic_cast<IInGameMonsterBase*>(GetParent());
	if (Character == nullptr)
	{
		return;
	}
	Ph2DogState = Character->GetPh2DogState();
	State = Character->GetState();
	AttackState = Character->GetAttackState();

	if (State == InGameMonsterState::Attack1)
	{
		Direction = Character->GetRenderer()->GetTransform().GetLocalScale().x > 0 ? float4::LEFT : float4::RIGHT;
	}

	if (State == InGameMonsterState::Attack2)
	{
		Direction = Character->GetRenderer()->GetTransform().GetLocalScale().x > 0 ? float4::RIGHT : float4::LEFT;
	}

	if (State == InGameMonsterState::Attack3 || State == InGameMonsterState::Attack4)
	{
		Direction = float4::DOWN;
	}

	if (Ph2DogState == InGamePh2DogState::Attack)
	{
		Ph2Dog* BowWowDog = dynamic_cast<Ph2Dog*>(GetParent());
		if (BowWowDog != nullptr)
		{
			Direction = BowWowDog->GetBowWowDirection();
		}
	}

	UpdatePivot();
}


void MonsterWeaponBase::Update(float _DeltaTime)
{
	Character = dynamic_cast<IInGameMonsterBase*>(GetParent());

	if (Character == nullptr)
	{
		return;
	}

	State = Character->GetState();
	AttackState = Character->GetAttackState();
	if (AttackState == InGameMonsterAttackState::None)
	{
		return;
	}

	if (ElapsedTime == -1)
	{
		return;
	}
}

void MonsterWeaponBase::UpdatePivot()
{

	if (State != InGameMonsterState::Attack1 &&
		State != InGameMonsterState::Attack2 &&
		State != InGameMonsterState::Attack3 &&
		State != InGameMonsterState::Attack4)
	{
		return;
	}

	if (State == InGameMonsterState::Attack1)
	{
		if (Character->GetRenderer()->GetTransform().GetLocalScale().x > 0)
		{
			GetTransform().SetLocalPosition({ -80.0f, 50.0f });
		}
		else
		{
			GetTransform().SetLocalPosition({ 80.0f, 50.0f });
		}
	}

	else if (State == InGameMonsterState::Attack2)
	{
		if (Character->GetRenderer()->GetTransform().GetLocalScale().x > 0)
		{
			GetTransform().SetLocalPosition({ 80.0f, 220.0f });
		}
		else
		{
			GetTransform().SetLocalPosition({ -80.0f, 220.0f });
		}
	}

	else if (State == InGameMonsterState::Attack3 || State == InGameMonsterState::Attack4)
	{
		GetTransform().SetLocalPosition({ 0.0f, 10.0f });
	}
}

void MonsterWeaponBase::OnMonsterStateChanged(InGameMonsterState _State)
{
	UpdateDirection();
}

void MonsterWeaponBase::OnPh2DogStateChanged(InGamePh2DogState _State)
{
	UpdateDirection();
}

void MonsterWeaponBase::OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState)
{
	switch (_AttackState)
	{
	case InGameMonsterAttackState::None:
		ElapsedTime = -1;
		break;
	case InGameMonsterAttackState::YarnBall1:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::YarnBall2:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::YarnBall3:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::Tattoo1:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::Tattoo2:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::Tattoo3:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::TennisBall:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::BowWow:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::LaserPattern1:
		ElapsedTime = 0.0f;
		break;
	}
	UpdateDirection();
}


void MonsterWeaponBase::SetParent(GameEngineUpdateObject* _Parent)
{
	GameEngineActor::SetParent(_Parent);

	IInGameMonsterBase* Monster = dynamic_cast<IInGameMonsterBase*>(GetParent());
	if (Monster != nullptr)
	{
		Monster->GetAttackStateChangedDelegate().Add(std::bind(&MonsterWeaponBase::OnMonsterAttackStateChanged, this, std::placeholders::_1));
		Monster->GetStateChangedDelegate().Add(std::bind(&MonsterWeaponBase::OnMonsterStateChanged, this, std::placeholders::_1));
		Monster->GetPh2DogStateChangedDelegate().Add(std::bind(&MonsterWeaponBase::OnPh2DogStateChanged, this, std::placeholders::_1));
		UpdateDirection();
		SetColMapImage(Monster->GetColMapImage());
	}
}