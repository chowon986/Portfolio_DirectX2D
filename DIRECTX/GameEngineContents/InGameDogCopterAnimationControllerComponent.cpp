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
	InGameDogCopterState State = InGameMonster->GetDogCopterState();
	InGameMonsterAttackState AttackState = InGameMonster->GetAttackState();
	Name = GetMonsterName();

	if (State == InGameDogCopterState::Prepare)
	{
		Renderer->ChangeFrameAnimation(Name + "Intro");
	}

	else if (State == InGameDogCopterState::Idle)
	{
		Renderer->ChangeFrameAnimation(Name + "Idle");
	}

	else if (State == InGameDogCopterState::Attack)
	{
		Renderer->ChangeFrameAnimation(Name + "Attack");
	}

	else if (State == InGameDogCopterState::TakeDamage)
	{
		Renderer->ChangeFrameAnimation(Name + "Pain" + AnimationNumber);
		if (true == InGameMonster->GetIsAnimatedOrderPositive())
		{
			Renderer->GetTransform().PixLocalPositiveX();
		}
		else
		{
			Renderer->GetTransform().PixLocalNegativeX();
		}
	}
}

void InGameDogCopterAnimationControllerComponent::Start()
{
	IInGameMonsterBase* InGameMonster = GetParent<IInGameMonsterBase>();
	if (InGameMonster != nullptr)
	{
		InGameMonster->GetDogCopterStateChangedDelegate().Add(std::bind(&InGameDogCopterAnimationControllerComponent::OnDogCopterStateChanged, this, std::placeholders::_1));
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

void InGameDogCopterAnimationControllerComponent::OnDogCopterStateChanged(InGameDogCopterState _State)
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
