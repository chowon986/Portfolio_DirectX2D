#include "PreCompile.h"
#include "InGameDogCopterAnimationControllerComponent.h"
#include "IInGameMonsterBase.h"

InGameDogCopterAnimationControllerComponent::InGameDogCopterAnimationControllerComponent()
{
}

InGameDogCopterAnimationControllerComponent::~InGameDogCopterAnimationControllerComponent()
{
}

void InGameDogCopterAnimationControllerComponent::UpdateAnimation()
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
	std::string AnimationNumber = InGameMonster->GetStringNumber();
	InGameMonsterState State = InGameMonster->GetState();
	InGameMonsterAttackState AttackState = InGameMonster->GetAttackState();
	Name = GetMonsterName();

	if (State == InGameMonsterState::Prepare)
	{
		Renderer->ChangeFrameAnimation(Name + "Intro");
	}

	else if (State == InGameMonsterState::Idle ||
		State == InGameMonsterState::Attack1)
	{
		Renderer->ChangeFrameAnimation(Name + "Idle");
	}

	else if (State == InGameMonsterState::BeforeRotateCameraIn)
	{
		Renderer->ChangeFrameAnimation(Name + "BeforeRotateCamera");
	}

	else if (State == InGameMonsterState::RotateCameraIn)
	{
		Renderer->ChangeFrameAnimation(Name + "RotateCamera");
	}

	else if (State == InGameMonsterState::RotateCameraIdle ||
		State == InGameMonsterState::Attack2)
	{
		Renderer->ChangeFrameAnimation(Name + "RotatedIdle");
	}

	else if (State == InGameMonsterState::RotateCameraOut)
	{
		Renderer->ChangeFrameAnimation(Name + "RotateCameraOut");
	}

	else if (State == InGameMonsterState::Die)
	{
		Renderer->ChangeFrameAnimation(Name + "Die");
	}

	else if (State == InGameMonsterState::BeforeRoToateCameraOut)
	{
		Renderer->ChangeFrameAnimation(Name + "BeforeRotateCameraOut");
	}

	else if (State == InGameMonsterState::KnockOut)
	{
		Renderer->ChangeFrameAnimation(Name + "KnockOut");
	}

	else if (State == InGameMonsterState::TakeDamage)
	{
	}
}

void InGameDogCopterAnimationControllerComponent::Start()
{
	IInGameMonsterBase* InGameMonster = GetParent<IInGameMonsterBase>();
	if (InGameMonster != nullptr)
	{
		InGameMonster->GetStateChangedDelegate().Add(std::bind(&InGameMonsterAnimationControllerComponent::OnStateChanged, this, std::placeholders::_1));
		InGameMonster->GetAttackStateChangedDelegate().Add(std::bind(&InGameDogCopterAnimationControllerComponent::OnAttackStateChanged, this, std::placeholders::_1));
	}
}

void InGameDogCopterAnimationControllerComponent::Update(float _DeltaTime)
{
	InGameMonsterAnimationControllerComponent::Update(_DeltaTime);
}

void InGameDogCopterAnimationControllerComponent::End()
{
}

void InGameDogCopterAnimationControllerComponent::OnStateChanged(InGameDogCopterState _State)
{
	UpdateAnimation();
}

void InGameDogCopterAnimationControllerComponent::OnAttackStateChanged(InGameMonsterAttackState _AttackState)
{
	UpdateAnimation();
}

void InGameDogCopterAnimationControllerComponent::SetMonsterName(std::string _MonsterName)
{
	Name = _MonsterName;
}
