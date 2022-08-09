#include "PreCompile.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "Bulldog.h"

InGameMonsterAnimationControllerComponent::InGameMonsterAnimationControllerComponent()
{
}

InGameMonsterAnimationControllerComponent::~InGameMonsterAnimationControllerComponent()
{
}

void InGameMonsterAnimationControllerComponent::OnStateChanged(InGameMonsterState _State)
{
	UpdateAnimation();
}

void InGameMonsterAnimationControllerComponent::OnAttackStateChanged(InGameMonsterAttackState _AttackState)
{
	UpdateAnimation();
}

void InGameMonsterAnimationControllerComponent::SetMonsterName(std::string _MonsterName)
{
	Name = _MonsterName;
}

void InGameMonsterAnimationControllerComponent::UpdateAnimation()
{
	IInGameMonsterBase* InGameMonster = GetParent<IInGameMonsterBase>();
	if (InGameMonster == nullptr)
	{
		return;
	}

	GameEngineTextureRenderer* Renderer = InGameMonster->GetRenderer();
	if (Renderer == nullptr)
	{
		return;
	}
	InGameMonsterState State = InGameMonster->GetState();
	InGameMonsterAttackState AttackState = InGameMonster->GetAttackState();

	if (State == InGameMonsterState::Prepare)
	{
		Renderer->ChangeFrameAnimation(Name + "Intro");
	}

	else if (AttackState== InGameMonsterAttackState::Attack)
	{
		Renderer->ChangeFrameAnimation(Name + "Attack");
	}

	else if (State == InGameMonsterState::Idle)
	{

		Renderer->ChangeFrameAnimation(Name + "Idle");
	}

	else if (State == InGameMonsterState::TakeDamage)
	{
		
	}

	else if (State == InGameMonsterState::Die)
	{
		Renderer->ChangeFrameAnimation(Name + "Die");
	}

}

void InGameMonsterAnimationControllerComponent::Start()
{
	IInGameMonsterBase* InGameMonster = GetParent<IInGameMonsterBase>();
	if (InGameMonster != nullptr)
	{
		InGameMonster->GetStateChangedDelegate().Add(std::bind(&InGameMonsterAnimationControllerComponent::OnStateChanged, this, std::placeholders::_1));
		InGameMonster->GetAttackStateChangedDelegate().Add(std::bind(&InGameMonsterAnimationControllerComponent::OnAttackStateChanged, this, std::placeholders::_1));
	}
}

void InGameMonsterAnimationControllerComponent::Update(float _DeltaTime)
{
	GameEngineActor* Actor = GetParent<GameEngineActor>();
	if (Actor == nullptr)
	{
		return;
	}
}

void InGameMonsterAnimationControllerComponent::End()
{
}
