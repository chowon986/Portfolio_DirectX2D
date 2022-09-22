#include "PreCompile.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "Bulldog.h"
#include "SaltBaker.h"

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
	Name = GetMonsterName();

	if (State == InGameMonsterState::Prepare)
	{
		Renderer->ChangeFrameAnimation(Name + "Intro");
	}

	if (State == InGameMonsterState::Alternate)
	{
		Renderer->ChangeFrameAnimation(Name + "Alternate");
	}

	if (State == InGameMonsterState::Turn)
	{
		Renderer->ChangeFrameAnimation(Name + "Turn");
	}

	if (State == InGameMonsterState::MoveToPhase2)
	{
		Renderer->ChangeFrameAnimation(Name + "Phase2Intro");
	}

	if (State == InGameMonsterState::Phase2)
	{
		Renderer->ChangeFrameAnimation(Name + "Phase2");
	}

	else if (State == InGameMonsterState::Unmount)
	{
		Renderer->ChangeFrameAnimation(Name + "Unmount");
	}

	else if (State == InGameMonsterState::Mount)
	{
		Renderer->ChangeFrameAnimation(Name + "Mount");
	}

	else if (State == InGameMonsterState::PrepareAttack1)
	{
		Renderer->ChangeFrameAnimation(Name + "PrepareAttack1");
	}

	else if (State == InGameMonsterState::PrepareAttack2)
	{
		Renderer->ChangeFrameAnimation(Name + "PrepareAttack2");
	}

	else if (State == InGameMonsterState::Run)
	{
		Renderer->ChangeFrameAnimation(Name + "Run");
	}

	else if (State == InGameMonsterState::Land)
	{
		Renderer->ChangeFrameAnimation(Name + "Land");
	}

	else if (State == InGameMonsterState::Attack1)
	{
		Renderer->ChangeFrameAnimation(Name + "Attack1");
	}

	else if (State == InGameMonsterState::Attack2)
	{
		Renderer->ChangeFrameAnimation(Name + "Attack2");
	}

	else if (State == InGameMonsterState::Attack3)
	{
		Renderer->ChangeFrameAnimation(Name + "Attack3");
	}

	else if (State == InGameMonsterState::Blink)
	{
		Renderer->ChangeFrameAnimation(Name + "Blink");
	}

	else if (State == InGameMonsterState::Look)
	{
		int RandomAction = rand() % 14;
		++RandomAction;
		switch (RandomAction)
		{
		case 1:
			Renderer->ChangeFrameAnimation(Name + "LookAround");
			break;
		case 2:
			Renderer->ChangeFrameAnimation(Name + "LookUp");
			break;
		case 3:
			Renderer->ChangeFrameAnimation(Name + "LookUpLeft");
			break;
		case 4:
			Renderer->ChangeFrameAnimation(Name + "LookUpLeftArchUp");
			break;
		case 5:
			Renderer->ChangeFrameAnimation(Name + "LookUpRight");
			break;
		case 6:
			Renderer->ChangeFrameAnimation(Name + "LookUpRightArchUp");
			break;
		case 7:
			Renderer->ChangeFrameAnimation(Name + "LookDown");
			break;
		case 8:
			Renderer->ChangeFrameAnimation(Name + "LookDownLeft");
			break;
		case 9:
			Renderer->ChangeFrameAnimation(Name + "LookDownRight");
			break;
		default: Renderer->ChangeFrameAnimation(Name + "Idle");
		}
	}

	else if (State == InGameMonsterState::Attack4)
	{
		Renderer->ChangeFrameAnimation(Name + "Attack4");
	}

	else if (State == InGameMonsterState::Attack5)
	{
		Renderer->ChangeFrameAnimation(Name + "Attack5");
	}

	else if (State == InGameMonsterState::AttackFinish1)
	{
		Renderer->ChangeFrameAnimation(Name + "AttackFinish1");
	}

	else if (State == InGameMonsterState::AttackFinish2)
	{
		Renderer->ChangeFrameAnimation(Name + "AttackFinish2");
	}

	else if (State == InGameMonsterState::Idle)
	{
		Renderer->ChangeFrameAnimation(Name + "Idle");
	}

	else if (State == InGameMonsterState::TakeDamage)
	{
		if (Name == "SaltBaker")
		{
			if (SaltBaker* Boss = dynamic_cast<SaltBaker*>(GetParent()))
			{
				int Num = Boss->GetTakeDamageNum();
				Renderer->ChangeFrameAnimation(Name + "TakeDamage" + std::to_string(Num));
			}
		}
	}

	else if (State == InGameMonsterState::Die)
	{
		Renderer->ChangeFrameAnimation(Name + "Die");
	}

	else if (State == InGameMonsterState::LookRight)
	{
		Renderer->ChangeFrameAnimation(Name + "LookRight");
	}

	else if (State == InGameMonsterState::LookLeft)
	{
		Renderer->ChangeFrameAnimation(Name + "LookLeft");
	}
	else
	{
		return;
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
