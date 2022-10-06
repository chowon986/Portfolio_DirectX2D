#include "PreCompile.h"
#include "InGameCharacterAnimationControllerComponent.h"
#include "InGameCuphead.h"

InGameCharacterAnimationControllerComponent::InGameCharacterAnimationControllerComponent()
	:IsIdleDownStartAnimationChanged(false)
{
}

InGameCharacterAnimationControllerComponent::~InGameCharacterAnimationControllerComponent()
{
}

void InGameCharacterAnimationControllerComponent::OnStateChanged(InGameCharacterState _State)
{
	UpdateAnimation();
}

void InGameCharacterAnimationControllerComponent::OnAttackStateChanged(InGameCharacterAttackState _AttackState)
{
	UpdateAnimation();
}


void InGameCharacterAnimationControllerComponent::OnVerticalDirectionChanged(std::string _Dir)
{
	UpdateAnimation();
}

void InGameCharacterAnimationControllerComponent::OnHorizontalDirectionChanged(std::string _Dir)
{
	if (_Dir != "Center")
	{
		BeforeDir = _Dir;
	}
	UpdateAnimation();
}

void InGameCharacterAnimationControllerComponent::OnIdleDownStartAnimationEnded(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 6)
	{
		IsIdleDownStartAnimationChanged = true;
		UpdateAnimation();
	}
}

void InGameCharacterAnimationControllerComponent::OnIsOnGroundChanged(bool _IsOnGround)
{
	UpdateAnimation();
}

void InGameCharacterAnimationControllerComponent::SetCharacterName(std::string _CharacterName)
{
	CharacterName = _CharacterName;

	IInGameCharacterBase* InGameCharacter = GetParent<IInGameCharacterBase>();
	if (InGameCharacter != nullptr)
	{
		GameEngineTextureRenderer* Renderer = InGameCharacter->GetRenderer();
		if (Renderer != nullptr)
		{
			std::string Name = GetCharacterName();
			Renderer->AnimationBindFrame("Ingame" + Name + "IdleDownStart", std::bind(&InGameCharacterAnimationControllerComponent::OnIdleDownStartAnimationEnded, this, std::placeholders::_1));
		}
	}
}

void InGameCharacterAnimationControllerComponent::UpdateAnimation()
{
	IInGameCharacterBase* InGameCharacter = GetParent<IInGameCharacterBase>();
	if (InGameCharacter == nullptr)
	{
		return;
	}
	GameEngineTextureRenderer* Renderer = InGameCharacter->GetRenderer();
	InGameCharacterState State = InGameCharacter->GetState();
	InGameCharacterAttackState AttackState = InGameCharacter->GetAttackState();
	std::string VerticalDir = InGameCharacter->GetVerticalDirection();
	std::string HorizontalDir = InGameCharacter->GetHorizontalDirection();
	std::string Name = GetCharacterName();

	bool IsOnGround = InGameCharacter->GetIsOnGround();

	// 키를 떼는 순간 idle이 되는데 애니메이션은 jump가 나온다.
	// 현재 애니메이션이 parry고, 애니메이션이 안 끝났으면 jump가 되면 안된다.
	if (IsOnGround != true &&
		State != InGameCharacterState::Dash &&
		State != InGameCharacterState::TakeDamage &&
		State != InGameCharacterState::Die &&
		State != InGameCharacterState::Parry &&
		State != InGameCharacterState::Duck &&
		AttackState != InGameCharacterAttackState::SuperAttack)
	{
		Renderer->ChangeFrameAnimation("Ingame" + Name + "Jump");
	}

	else
	{
		if (State == InGameCharacterState::Die)
		{
			Renderer->ChangeFrameAnimation("Ingame" + Name + "Ghost");
		}

		else if (AttackState == InGameCharacterAttackState::SuperAttack)
		{
			Renderer->ChangeFrameAnimation("Ingame" + Name + "ExShootStraight");
		}

		else if (State == InGameCharacterState::TakeDamage)
		{
			Renderer->ChangeFrameAnimation("Ingame" + Name + "TakeDamage");
		}

		else if (State == InGameCharacterState::Prepare)
		{
			Renderer->ChangeFrameAnimation("Ingame" + Name + "Intro");
		}

		else if (State == InGameCharacterState::Parry)
		{
			Renderer->ChangeFrameAnimation("Ingame" + Name + "Parry");
		}

		else if (State == InGameCharacterState::Evade)
		{
			Renderer->ChangeFrameAnimation("Ingame" + Name + "Dash");
		}

		else if (State == InGameCharacterState::Dash)
		{
			Renderer->ChangeFrameAnimation("Ingame" + Name + "Dash");
		}

		else if (State == InGameCharacterState::Idle)
		{
			if (AttackState == InGameCharacterAttackState::SuperAttack)
			{
				Renderer->ChangeFrameAnimation("Ingame" + Name + "ExShootStraight");
			}
			else if (AttackState == InGameCharacterAttackState::Shoot)
			{
				if (VerticalDir == "Up")
				{
					Renderer->ChangeFrameAnimation("Ingame" + Name + "ShootUp");
				}
				else
				{
					Renderer->ChangeFrameAnimation("Ingame" + Name + "ShootStraight");
				}
			}
			else
			{
				if (VerticalDir == "Up")
				{
					Renderer->ChangeFrameAnimation("Ingame" + Name + "AimUp");
				}
				else
				{
					Renderer->ChangeFrameAnimation("Ingame" + Name + "Idle");
				}
			}
		}

		else if (State == InGameCharacterState::Aim)
		{
			if (AttackState == InGameCharacterAttackState::Shoot)
			{
				if (VerticalDir == "Up")
				{
					if (true == GameEngineInput::GetInst()->IsPress("MoveRight") ||
						true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
					{
						Renderer->ChangeFrameAnimation("Ingame" + Name + "ShootDiagUp");
					}
					else
					{
						Renderer->ChangeFrameAnimation("Ingame" + Name + "ShootUp");
					}
				}
				else  if (VerticalDir == "Down")
				{
					if (true == GameEngineInput::GetInst()->IsPress("MoveRight") ||
						true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
					{
						Renderer->ChangeFrameAnimation("Ingame" + Name + "ShootDiagDown");
					}
					else
					{
						Renderer->ChangeFrameAnimation("Ingame" + Name + "ShootDown");
					}
				}
				else
				{
					Renderer->ChangeFrameAnimation("Ingame" + Name + "ShootStraight");
				}
			}

			else
			{
				if (VerticalDir == "Up")
				{
					if (true == GameEngineInput::GetInst()->IsPress("MoveRight") ||
						true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
					{
						Renderer->ChangeFrameAnimation("Ingame" + Name + "AimDiagUp");
					}
					else
					{
						Renderer->ChangeFrameAnimation("Ingame" + Name + "AimUp");
					}
				}
				else if (VerticalDir == "Down")
				{
					if (true == GameEngineInput::GetInst()->IsPress("MoveRight") ||
						true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
					{
						Renderer->ChangeFrameAnimation("Ingame" + Name + "AimDiagDown");
					}
					else
					{
						Renderer->ChangeFrameAnimation("Ingame" + Name + "AimDown");
					}
				}
				else
				{
					Renderer->ChangeFrameAnimation("Ingame" + Name + "AimStraight");
				}
			}
		}

		else if (State == InGameCharacterState::Duck)
		{
			if (AttackState == InGameCharacterAttackState::Shoot)
			{
				Renderer->ChangeFrameAnimation("Ingame" + Name + "DuckShoot");
			}

			else
			{
				if (IsIdleDownStartAnimationChanged == false)
				{
					Renderer->ChangeFrameAnimation("Ingame" + Name + "IdleDownStart");
				}
				else
				{
					Renderer->ChangeFrameAnimation("Ingame" + Name + "IdleDown");
				}
			}
		}

		else if (State == InGameCharacterState::Walk)
		{
			if (AttackState == InGameCharacterAttackState::Shoot)
			{
				if (VerticalDir == "Up")
				{
					Renderer->ChangeFrameAnimation("Ingame" + Name + "RunShootDiagUp");
				}
				else
				{
					Renderer->ChangeFrameAnimation("Ingame" + Name + "RunShootStraight");
				}
			}
			else
			{
				Renderer->ChangeFrameAnimation("Ingame" + Name + "Run");
			}

		}
	}

	if (HorizontalDir == "Center")
	{
		HorizontalDir = BeforeDir;
	}


	if (HorizontalDir == "Left")
	{
		if (Renderer->GetTransform().GetLocalScale().x > 0)
		{
			float x = Renderer->GetTransform().GetLocalScale().x * -1;
			Renderer->GetTransform().SetLocalScale({ x,Renderer->GetTransform().GetLocalScale().y, Renderer->GetTransform().GetLocalScale().z });
		}
	}

	else if (HorizontalDir == "Right")
	{
		if (Renderer->GetTransform().GetLocalScale().x < 0)
		{
			float x = Renderer->GetTransform().GetLocalScale().x * -1;
			Renderer->GetTransform().SetLocalScale({ x,Renderer->GetTransform().GetLocalScale().y, Renderer->GetTransform().GetLocalScale().z });
		}
	}

	if (State != InGameCharacterState::Duck)
	{
		IsIdleDownStartAnimationChanged = false;
	}
}

void InGameCharacterAnimationControllerComponent::Start()
{
	IInGameCharacterBase* InGameCharacter = GetParent<IInGameCharacterBase>();
	if (InGameCharacter != nullptr)
	{
		InGameCharacter->GetStateChangedDelegate().Add(std::bind(&InGameCharacterAnimationControllerComponent::OnStateChanged, this, std::placeholders::_1));
		InGameCharacter->GetAttackStateChangedDelegate().Add(std::bind(&InGameCharacterAnimationControllerComponent::OnAttackStateChanged, this, std::placeholders::_1));
		InGameCharacter->GetVerticalDirectionChangedDelegate().Add(std::bind(&InGameCharacterAnimationControllerComponent::OnVerticalDirectionChanged, this, std::placeholders::_1));
		InGameCharacter->GetHorizontalDirectionChangedDelegate().Add(std::bind(&InGameCharacterAnimationControllerComponent::OnHorizontalDirectionChanged, this, std::placeholders::_1));
		InGameCharacter->GetIsOnGroundChangedDelegate().Add(std::bind(&InGameCharacterAnimationControllerComponent::OnIsOnGroundChanged, this, std::placeholders::_1));

		GameEngineTextureRenderer* Renderer = InGameCharacter->GetRenderer();
	}
}

void InGameCharacterAnimationControllerComponent::Update(float _DeltaTime)
{
	GameEngineActor* Actor = GetParent<GameEngineActor>();
	if (Actor == nullptr)
	{
		return;
	}
}

void InGameCharacterAnimationControllerComponent::End()
{
}
