#include "PreCompile.h"
#include "InGamePh2DogAnimationControllerComponent.h"
#include "IInGameMonsterBase.h"

InGamePh2DogAnimationControllerComponent::InGamePh2DogAnimationControllerComponent()
	:Angle(0.0f)
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
		Renderer->GetTransform().PixLocalNegativeX();
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


	Angle = InGameMonster->GetAngle() + InGameMonster->GetStartAngle();
	Angle = Angle * GameEngineMath::RadianToDegree;

	if ((0 <= Angle && Angle <= 22.5) ||
		(360.0 < Angle && Angle <= 382.5))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle5");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack5");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((22.5 < Angle && Angle <= 45) ||
		(382.5f < Angle && Angle <= 405.0f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle4");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack4");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((45 < Angle && Angle <= 67.5) ||
		(405.0f < Angle && Angle <= 427.5f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle3");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack3");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((67.5 < Angle && Angle <= 90) ||
		(427.5 < Angle && Angle <= 450.0f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle2");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack2");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((90.0f < Angle && Angle <= 112.5f) ||
		(450.0f < Angle && Angle <= 472.5f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle1");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack1");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((112.5 < Angle && Angle <= 135) ||
		(472.5f < Angle && Angle <= 495.0f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle2");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack2");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((135 < Angle && Angle <= 157.5f) ||
		(495.0f < Angle && Angle <= 517.5))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle3");
			Renderer->GetTransform().PixLocalPositiveX();

			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack3");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((157.5 < Angle && Angle <= 180.0) ||
		(517.5 < Angle && Angle <= 540.0f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle4");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack4");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((180.0 < Angle && Angle <= 202.5) ||
		(540.0f < Angle && Angle <= 562.5f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle5");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack5");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((202.5 < Angle && Angle <= 225) ||
		(562.5f < Angle && Angle <= 585.0f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle6");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack6");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((225 < Angle && Angle <= 247.5) ||
		(585.0f < Angle && Angle <= 607.5f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle7");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack7");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((247.5 < Angle && Angle <= 270.0) ||
		(607.5f < Angle && Angle <= 630.0f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle8");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack8");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((270.0 < Angle && Angle <= 292.5) ||
		(630.0f < Angle && Angle <= 652.5f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle9");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack9");
			Renderer->GetTransform().PixLocalPositiveX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((292.5 < Angle && Angle <= 315) ||
		(652.5f < Angle && Angle <= 675.0f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle8");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack8");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((315.0 < Angle && Angle <= 337.5) ||
		(675.0f < Angle && Angle <= 697.5f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle7");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack7");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
		}
	}

	else if ((337.5 < Angle && Angle <= 360) ||
	(697.5f < Angle && Angle <= 720.0f))
	{
		switch (State)
		{
		case InGamePh2DogState::Idle:
			Renderer->ChangeFrameAnimation("Ph2DogIdle6");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::Attack:
			Renderer->ChangeFrameAnimation("Ph2DogAttack6");
			Renderer->GetTransform().PixLocalNegativeX();
			break;
		case InGamePh2DogState::TakeDamage:
			break;
		case InGamePh2DogState::Die:
			break;
		case InGamePh2DogState::None:
			break;
		default:
			break;
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
