#include "PreCompile.h"
#include "InGamePh2DogAnimationControllerComponent.h"
#include "IInGameMonsterBase.h"

InGamePh2DogAnimationControllerComponent::InGamePh2DogAnimationControllerComponent()
{
}

InGamePh2DogAnimationControllerComponent::~InGamePh2DogAnimationControllerComponent()
{
}

void InGamePh2DogAnimationControllerComponent::UpdateAnimation()
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
	InGamePh2DogState State = InGameMonster->GetPh2DogState();
	InGameMonsterAttackState AttackState = InGameMonster->GetAttackState();
	Name = GetMonsterName();

	if (State == InGamePh2DogState::Prepare1)
	{
		Renderer->ChangeFrameAnimation(Name + "IntroTop");
	}

	else if (State == InGamePh2DogState::Prepare2)
	{
		Renderer->ChangeFrameAnimation(Name + "IntroRight");
	}

	else if (State == InGamePh2DogState::Prepare3)
	{
		Renderer->ChangeFrameAnimation(Name + "IntroBottom");
	}

	else if (State == InGamePh2DogState::Prepare4)
	{
		Renderer->ChangeFrameAnimation(Name + "IntroLeft");
	}

	else if (State == InGamePh2DogState::Idle)
	{
		Renderer->ChangeFrameAnimation(Name + "Idle" + AnimationNumber);
		if (true == InGameMonster->GetIsAnimatedOrderPositive())
		{
			Renderer->GetTransform().PixLocalPositiveX();
		}
		else
		{
			Renderer->GetTransform().PixLocalNegativeX();
		}
	}

	else if (State == InGamePh2DogState::Attack)
	{
		Renderer->ChangeFrameAnimation(Name + "Attack" + AnimationNumber);
		if (true == InGameMonster->GetIsAnimatedOrderPositive())
		{
			Renderer->GetTransform().PixLocalPositiveX();
		}
		else
		{
			Renderer->GetTransform().PixLocalNegativeX();
		}
	}

	else if (State == InGamePh2DogState::TakeDamage)
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

void InGamePh2DogAnimationControllerComponent::Start()
{
	IInGameMonsterBase* InGameMonster = GetParent<IInGameMonsterBase>();
	if (InGameMonster != nullptr)
	{
		InGameMonster->GetPh2DogStateChangedDelegate().Add(std::bind(&InGamePh2DogAnimationControllerComponent::OnPh2DogStateChanged, this, std::placeholders::_1));
		InGameMonster->GetAttackStateChangedDelegate().Add(std::bind(&InGamePh2DogAnimationControllerComponent::OnAttackStateChanged, this, std::placeholders::_1));
	}
}

void InGamePh2DogAnimationControllerComponent::Update(float _DeltaTime)
{
	InGameMonsterAnimationControllerComponent::Update(_DeltaTime);
}

void InGamePh2DogAnimationControllerComponent::End()
{
}

void InGamePh2DogAnimationControllerComponent::OnPh2DogStateChanged(InGamePh2DogState _State)
{
	UpdateAnimation();
}

void InGamePh2DogAnimationControllerComponent::OnAttackStateChanged(InGameMonsterAttackState _AttackState)
{
	UpdateAnimation();
}

void InGamePh2DogAnimationControllerComponent::SetMonsterName(std::string _MonsterName)
{
	Name = _MonsterName;
}
