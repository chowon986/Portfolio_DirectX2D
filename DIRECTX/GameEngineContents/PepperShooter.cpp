#include "PreCompile.h"
#include "PepperShooter.h"
#include "IInGameMonsterBase.h"
#include "PepperBullet.h"
#include "Pepper.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "InGameCuphead.h"
#include "SaltBaker.h"
#include "SaltBakerLevel.h"

PepperShooter::PepperShooter()
	: MonsterAttackState(InGameMonsterAttackState::None)
	, Player(nullptr)
	, Renderer(nullptr)
	, Collision(nullptr)
	, CanTakeDamageInterval(1.0f)
	, DeathNum(0)
	, StartBodyAttack(false)
	, ElapsedTimeMove(0.0f)
{
}

PepperShooter::~PepperShooter()
{
}

void PepperShooter::UpdateDirection()
{
}


void PepperShooter::UpdatePivot()
{
}

void PepperShooter::OnMonsterStateChanged(InGameMonsterState _State)
{
}

void PepperShooter::OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState)
{
}

void PepperShooter::UpdateAnimation()
{
	switch (State)
	{
	case PepperState::Prepare:
		Renderer->ChangeFrameAnimation("PepperShooterIntro");
		break;
	case PepperState::Idle:
		Renderer->ChangeFrameAnimation("PepperShooterIdle");
		break;
	case PepperState::Attack1:		
		Renderer->ChangeFrameAnimation("PepperShooterAttack");
		break;
	case PepperState::Attack2:
		Renderer->ChangeFrameAnimation("PepperShooterDeath" + std::to_string(DeathNum));
		break;
	case PepperState::Death:
		Renderer->ChangeFrameAnimation("PepperShooterReturn");
		break;
	}
}

void PepperShooter::SetPepperState(PepperState _State)
{
	if (State != _State)
	{
		State = _State;
		UpdateAnimation();
	}
}

void PepperShooter::OnPepperShooterIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 16)
	{
		SetPepperState(PepperState::Idle);
	}
}

void PepperShooter::OnPepperShooterAttackAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 22)
	{
		if (SaltBakerLevel* Level = dynamic_cast<SaltBakerLevel*>(GetLevel()))
		{
			if (InGameCuphead* Player = dynamic_cast<InGameCuphead*>(Level->GetPlayer()))
			{
				float4 PlayerPos = Player->GetTransform().GetWorldPosition();
				float4 MoveDirection = PlayerPos - GetTransform().GetWorldPosition();
				MoveDirection.Normalize();
				Direction = float4({ MoveDirection });

				float4 MyPos = GetTransform().GetWorldPosition();

				int RandomAttackNum = GameEngineRandom::MainRandom.RandomInt(0, 2);
				PepperBullet* Bullet = GetLevel()->CreateActor<PepperBullet>();
				Bullet->GetRenderer()->ChangeFrameAnimation("Pepper" + std::to_string(RandomAttackNum));
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition({ MyPos.x, MyPos.y, MyPos.z - 1 });
				Bullet->SetDirection(Direction);
			}
		}
	}

	if (_Info.CurFrame == 43)
	{
		SetPepperState(PepperState::Idle);
	}
}

void PepperShooter::OnPepperShooterDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (DeathNum == 0)
	{
		if (_Info.CurFrame == 11)
		{
			SetHP(10);
		}
		else if (_Info.CurFrame == 5)
		{
			StartBodyAttack = true;
		}
	}

	else if (DeathNum == 1)
	{
		if (_Info.CurFrame == 16)
		{
			SetHP(10);
		}
		else if (_Info.CurFrame == 5)
		{
			StartBodyAttack = true;
		}
	}

	else if (DeathNum == 2)
	{
		if (_Info.CurFrame == 20)
		{
			SetHP(10);
		}
		else if (_Info.CurFrame == 5)
		{
			StartBodyAttack = true;
		}
	}

	else if (DeathNum == 3)
	{
		if (_Info.CurFrame == 10)
		{
			SetHP(10);
		}
		else if (_Info.CurFrame == 5)
		{
			StartBodyAttack = true;
		}
	}
}

void PepperShooter::OnPepperShooterReturnAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}

void PepperShooter::SetDeathNum(int _Num)
{
	DeathNum = _Num;
	StartPos = GetTransform().GetWorldPosition();
}

void PepperShooter::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PepperShooterIntro", FrameAnimation_DESC("PepperShooterIntro", 0.05f, false));
	Renderer->CreateFrameAnimationFolder("PepperShooterDeath0", FrameAnimation_DESC("PepperShooterDeathA", 0.05f, false));
	Renderer->CreateFrameAnimationFolder("PepperShooterDeath1", FrameAnimation_DESC("PepperShooterDeathB", 0.05f, false));
	Renderer->CreateFrameAnimationFolder("PepperShooterDeath2", FrameAnimation_DESC("PepperShooterDeathC", 0.05f, false));
	Renderer->CreateFrameAnimationFolder("PepperShooterDeath3", FrameAnimation_DESC("PepperShooterDeathD", 0.05f, false));
	Renderer->CreateFrameAnimationFolder("PepperShooterAttack", FrameAnimation_DESC("PepperShooterAttack", 0.05f, false));
	Renderer->CreateFrameAnimationFolder("PepperShooterIdle", FrameAnimation_DESC("PepperShooterIdle", 0.05f, true));
	Renderer->CreateFrameAnimationFolder("PepperShooterReturn", FrameAnimation_DESC("PepperShooterReturn", 0.05f, true));
	Renderer->AnimationBindFrame("PepperShooterIntro", std::bind(&PepperShooter::OnPepperShooterIntroAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PepperShooterAttack", std::bind(&PepperShooter::OnPepperShooterAttackAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PepperShooterDeath0", std::bind(&PepperShooter::OnPepperShooterDeathAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PepperShooterDeath1", std::bind(&PepperShooter::OnPepperShooterDeathAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PepperShooterDeath2", std::bind(&PepperShooter::OnPepperShooterDeathAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PepperShooterDeath3", std::bind(&PepperShooter::OnPepperShooterDeathAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("PepperShooterReturn", std::bind(&PepperShooter::OnPepperShooterReturnAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("PepperShooterIntro");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	Collision->GetTransform().SetWorldScale({ 100.0f, 180.0f, 1.0f });
	Collision->GetTransform().SetLocalPosition({ 0.0f, -30.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER);

	HP = 10;
	DestPos = float4({ 800.0f,-250.0f, GetTransform().GetWorldPosition().z });

	SetPepperState(PepperState::Prepare);
}

void PepperShooter::Update(float _DeltaTime)
{
	MonsterWeaponBase::Update(_DeltaTime);

	if (GetPepperState() == PepperState::Idle)
	{
		Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D, std::bind(&PepperShooter::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	}


	if (Boss = dynamic_cast<SaltBaker*>(GetParent()))
	{
		if (Boss->GetHP() <= 0)
		{
			SetPepperState(PepperState::Death);
			return;
		}
	}

	if (State == PepperState::Idle)
	{
		ElapsedTimeMove = 0.0f;
		StartBodyAttack = false;
		ElapsedTime += _DeltaTime;
		if (ElapsedTime > 3.0f)
		{
			SetPepperState(PepperState::Attack1);
		}
		else if (GetHP() <= 0)
		{
			//if (Boss->GetState() == InGameMonsterState::TakeDamage)
			//{
			//	return;
			//}
			SetPepperState(PepperState::Attack2);
		}
	}
	else if (State == PepperState::Attack2)
	{
		ElapsedTime = 0.0f;
		if (nullptr != Boss)
		{
			if (StartBodyAttack == true)

			{
				ElapsedTimeMove += _DeltaTime;
				float4 WorldPos = GetTransform().GetWorldPosition();
				float DestX = GameEngineMath::LerpLimit(WorldPos.x, DestPos.x, ElapsedTimeMove / 30);
				float DestY = GameEngineMath::LerpLimit(WorldPos.y, DestPos.y, ElapsedTimeMove / 30);

				if (abs(DestX - DestPos.x) < 1 &&
					abs(DestY - DestPos.y) < 1)
				{
					if (nullptr != Boss)
					{
						Boss->SetTakeDamageNum(DeathNum);
						Boss->SetState(InGameMonsterState::TakeDamage);
						Boss->SetHP(Boss->GetHP() - 1);
					}
					GetTransform().SetWorldPosition(StartPos);
					SetPepperState(PepperState::Prepare);
				}
				else
				{
					GetTransform().SetWorldPosition(float4(DestX, DestY, WorldPos.z));
				}
			}
		}
	}
	else
	{
		ElapsedTimeMove = 0.f;
		StartBodyAttack = false;
		ElapsedTime = 0.0f;
	}

	// Idle -> Attack1 ? Attack2는 아니고 3초에 한번씩
	// Idle -> Death ? Attack1이 아니고 HP가 5 이하
}

CollisionReturn PepperShooter::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	SetHP(GetHP() - 1);
	return CollisionReturn::Break;
}

void PepperShooter::End()
{
}