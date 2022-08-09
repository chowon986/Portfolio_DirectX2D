#include "PreCompile.h"
#include "MonsterWeaponBase.h"
#include "IInGameMonsterBase.h"

MonsterWeaponBase::MonsterWeaponBase()
	: IntervalTime(0.1f)
	, ElapsedTime(0.0f)
	, Monster(nullptr)
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
	Monster = dynamic_cast<IInGameMonsterBase*>(GetParent());
	if (Monster == nullptr)
	{
		return;
	}

	State = Monster->GetState();
	AttackState = Monster->GetAttackState();
	if (State == InGameMonsterState::Attack1)
	{
		Direction = Monster->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? float4::RIGHT : float4::LEFT;
	}

	if (State == InGameMonsterState::Attack1)
	{
		Direction = Monster->GetRenderer()->GetTransform().GetLocalScale().x < 0 ? float4::RIGHT : float4::LEFT;
	}

	UpdatePivot();
}


void MonsterWeaponBase::Update(float _DeltaTime)
{
	Monster = dynamic_cast<IInGameMonsterBase*>(GetParent());

	if (Monster == nullptr)
	{
		return;
	}

	AttackState = Monster->GetAttackState();
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

	if (AttackState != InGameMonsterAttackState::Shoot1 ||
		AttackState != InGameMonsterAttackState::Shoot2)
	{
		return;
	}

	if (AttackState == InGameMonsterAttackState::Shoot1)
	{
		if (Monster->GetRenderer()->GetTransform().GetLocalScale().x > 0)
		{
			GetTransform().SetLocalPosition({ 80.0f, 60.0f });
		}
		else
		{
			//GetTransform().SetLocalPosition({ -80.0f, 60.0f });
		}
	}

	else if (AttackState == InGameMonsterAttackState::Shoot2)
	{
		if (Monster->GetRenderer()->GetTransform().GetLocalScale().x > 0)
		{
			//GetTransform().SetLocalPosition({ 80.0f, 60.0f });
		}
		else
		{
			//GetTransform().SetLocalPosition({ -80.0f, 60.0f });
		}
	}
}

void MonsterWeaponBase::OnMonsterStateChanged(InGameMonsterState _State)
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
	case InGameMonsterAttackState::Shoot1:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::Shoot2:
		ElapsedTime = 0.0f;
	}
	UpdateDirection();
}


void MonsterWeaponBase::SetParent(GameEngineUpdateObject* _Parent)
{
	GameEngineActor::SetParent(_Parent);

	IInGameMonsterBase* Monster = dynamic_cast<IInGameMonsterBase*>(GetParent());
	if (Monster != nullptr)
	{
		Monster->GetStateChangedDelegate().Add(std::bind(&MonsterWeaponBase::OnMonsterStateChanged, this, std::placeholders::_1));
		Monster->GetAttackStateChangedDelegate().Add(std::bind(&MonsterWeaponBase::OnMonsterAttackStateChanged, this, std::placeholders::_1));
		UpdateDirection();
		SetColMapImage(Monster->GetColMapImage());
	}
}