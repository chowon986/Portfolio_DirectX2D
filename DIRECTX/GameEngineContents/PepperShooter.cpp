#include "PreCompile.h"
#include "PepperShooter.h"
#include "IInGameMonsterBase.h"
#include "PepperBullet.h"
#include "Pepper.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "InGameCuphead.h"
#include "SaltBaker.h"

PepperShooter::PepperShooter()
	: MonsterAttackState(InGameMonsterAttackState::None)
	, Player(nullptr)
	, Renderer(nullptr)
	, Collision(nullptr)
	, CanTakeDamageInterval(1.0f)
	, DeathNum(0)
{
}

PepperShooter::~PepperShooter()
{
}

void PepperShooter::UpdateDirection()
{
	UpdatePivot();
}


void PepperShooter::UpdatePivot()
{
	if (State != InGameMonsterState::Attack1)
	{
		return;
	}

	if (State == InGameMonsterState::Attack1)
	{
		GetTransform().SetLocalPosition({ 0.0f, 0.0f });
	}
}

void PepperShooter::OnMonsterStateChanged(InGameMonsterState _State)
{
	UpdateDirection();
}

void PepperShooter::OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState)
{
	switch (_AttackState)
	{
	case InGameMonsterAttackState::Attack1:
		ElapsedTime = 0.0f;
		break;
	}

	UpdateDirection();
}

CollisionReturn PepperShooter::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (ElapsedTime > 1.0f)
	{
		SetHP(GetHP() - 1);
		ElapsedTime = 0.0f;
	}
	return CollisionReturn::ContinueCheck;

}

void PepperShooter::OnPepperShooterIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 16)
	{
		Renderer->ChangeFrameAnimation("PepperShooterIdle");
	}
}

void PepperShooter::OnPepperShooterAttackAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 22)
	{
		if (nullptr != dynamic_cast<InGameCuphead*>(GetParent()))
		{
			Player = dynamic_cast<InGameCuphead*>(GetParent());
		}

		if (Player != nullptr)
		{
			float4 PlayerPos = Player->GetTransform().GetWorldPosition();
			float4 MoveDirection = PlayerPos - GetTransform().GetWorldPosition();
			MoveDirection.Normalize();
			Direction = float4({ MoveDirection });
		}

		float4 MyPos = GetTransform().GetWorldPosition();

		int RandomAttackNum = GameEngineRandom::MainRandom.RandomInt(0, 2);
		PepperBullet* Bullet = GetLevel()->CreateActor<PepperBullet>();
		Bullet->GetRenderer()->ChangeFrameAnimation("Pepper" + std::to_string(RandomAttackNum));
		Bullet->SetColMapImage(GetColMapImage());
		Bullet->GetTransform().SetWorldPosition({ MyPos.x, MyPos.y, MyPos.z - 1 });
		Bullet->SetDirection(GetDirection());
	}

	if (_Info.CurFrame == 43)
	{
		Renderer->ChangeFrameAnimation("PepperShooterIdle");
	}
}

void PepperShooter::OnPepperShooterDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (DeathNum == 0 && _Info.CurFrame == 4)
	{
		// 몬스터한테 이동해야해Death();
	}


	//if (DeathNum == 0 && _Info.CurFrame == 11)
	//{
	//	Death();
	//}

	//else if (DeathNum == 1 && _Info.CurFrame == 16)
	//{
	//	Death();
	//}

	//else if (DeathNum == 2 && _Info.CurFrame == 20)
	//{
	//	Death();
	//}

	//else if (DeathNum == 3 && _Info.CurFrame == 10)
	//{
	//	Death();
	//}
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
	Renderer->AnimationBindFrame("PepperShooterIntro", std::bind(&PepperShooter::OnPepperShooterIntroAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PepperShooterAttack", std::bind(&PepperShooter::OnPepperShooterAttackAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PepperShooterDeath0", std::bind(&PepperShooter::OnPepperShooterDeathAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PepperShooterDeath1", std::bind(&PepperShooter::OnPepperShooterDeathAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PepperShooterDeath2", std::bind(&PepperShooter::OnPepperShooterDeathAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PepperShooterDeath3", std::bind(&PepperShooter::OnPepperShooterDeathAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("PepperShooterIntro");

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	Collision->ChangeOrder(ObjectOrder::MONSTER_DAMAGEABLE_BULLET);
	Collision->GetTransform().SetWorldScale({ 100.0f, 150.0f, 1.0f });
	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D, std::bind(&PepperShooter::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));

	HP = 10;
}

void PepperShooter::Update(float _DeltaTime)
{
	MonsterWeaponBase::Update(_DeltaTime);

	ElapsedTime += _DeltaTime;

	if (ElapsedTime > 1.0f)
	{
		SetHP(GetHP() - 1);
		ElapsedTime = 0.0f;
	}

	if (GetHP() <= 2)
	{
		if (SaltBaker* Boss = dynamic_cast<SaltBaker*>(GetParent()))
		{
			if (Boss->GetHP() <= 0)
			{
				Renderer->ChangeFrameAnimation("PepperShooterDeath" + std::to_string(DeathNum));
				SetHP(10);
			}
		}
		else
		{
			SetHP(10);
			Renderer->ChangeFrameAnimation("PepperShooterAttack");
		}

	}
}

void PepperShooter::End()
{
}