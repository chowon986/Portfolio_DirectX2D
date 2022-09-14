#include "PreCompile.h"
#include "SaltBakerShooter.h"
#include "IInGameMonsterBase.h"
#include "StrawberryBullet.h"
#include "LimeBullet.h"
#include "SugarBullet.h"
#include "AnimalBullet.h"
#include "MonsterPhysicsComponent.h"
#include "AnimalBulletPhysicsComponent.h"
#include "LeafBullet.h"

SaltBakerShooter::SaltBakerShooter()
	: MonsterAttackState(InGameMonsterAttackState::None)
	, StartPosSwitch(false)
	, SugarBulletStartPosX(0.0f)
{
}

SaltBakerShooter::~SaltBakerShooter()
{
}

void SaltBakerShooter::UpdateDirection()
{
	Character = dynamic_cast<IInGameMonsterBase*>(GetParent());
	if (Character == nullptr)
	{
		return;
	}
	State = Character->GetState();
	AttackState = Character->GetAttackState();

	if (State == InGameMonsterState::Attack1)
	{
		Direction = float4::LEFT + float4::DOWN;
	}

	else if (State == InGameMonsterState::Attack4)
	{
		Direction = LimeBulletStartPosX == 50.0f ? float4::RIGHT : float4::LEFT;
	}

	UpdatePivot();
}


void SaltBakerShooter::Update(float _DeltaTime)
{
	MonsterWeaponBase::Update(_DeltaTime);

	ElapsedTime += _DeltaTime;
	if (ElapsedTime > IntervalTime)
	{
		ElapsedTime -= IntervalTime;

		if (MonsterAttackState != AttackState)
		{
			MonsterAttackState = AttackState;

			switch (MonsterAttackState)
			{
			case InGameMonsterAttackState::Attack1:
			{
				if (StrawberryBulletStartPosX.size() < 4)
				{
					StrawberryBulletStartPosX = { std::make_pair(0, 300.0f), std::make_pair(1, 500.0f), std::make_pair(2,700.0f), std::make_pair(3,900.0f), std::make_pair(4,1100.0f), std::make_pair(5,1300.0f), std::make_pair(6,1500.0f), std::make_pair(7,1700.0f) };
				}

				StrawberryBullet* Bullet = GetLevel()->CreateActor<StrawberryBullet>();
				Bullet->GetRenderer()->ChangeFrameAnimation("Bow1");
				Bullet->SetColMapImage(GetColMapImage());

				int RandomStartPosX = rand() % StrawberryBulletStartPosX.size();
				float StartPositionX = StrawberryBulletStartPosX[RandomStartPosX];

				std::map<int, float>::iterator It = StrawberryBulletStartPosX.find(RandomStartPosX);
				if (It != StrawberryBulletStartPosX.end())
				{
					StrawberryBulletStartPosX.erase(It);
				}

				Bullet->GetTransform().SetWorldPosition({ StartPositionX, 10.0f });
				Bullet->SetDirection(GetDirection());
			}
			break;
			case InGameMonsterAttackState::Attack2:
			{
				StartPosSwitch = !StartPosSwitch;
				if (StartPosSwitch == true)
				{
					SugarBulletStartPosX = -20;
				}
				else
				{
					SugarBulletStartPosX = -100;
				}

				SugarBullet* Bullet = GetLevel()->CreateActor<SugarBullet>();
				Bullet->GetRenderer()->ChangeFrameAnimation("Bow1");
				Bullet->SetColMapImage(GetColMapImage());
				Bullet->GetTransform().SetWorldPosition({ SugarBulletStartPosX, -500.0f });
			}
			break;
			case InGameMonsterAttackState::Attack3:
			{
				int RandomKey = rand() % 3;

				AnimalBullet* Bullet = GetLevel()->CreateActor<AnimalBullet>();
				if (nullptr != GetColMapImage())
				{
					Bullet->SetColMapImage(GetColMapImage());
				}
				if (RandomKey == 0)
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("CamelJumpUp");
					Bullet->GetMonsterPhysicsComponent()->Reset();
					Bullet->GetMonsterPhysicsComponent()->AddForce(50);
					Bullet->GetTransform().SetWorldPosition({ 50, -500.0f });
					Bullet->SetAnimal("Camel");
				}
				else if (RandomKey == 1)
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("ElephantJumpUp");
					Bullet->GetMonsterPhysicsComponent()->Reset();
					Bullet->GetMonsterPhysicsComponent()->AddForce(40);
					Bullet->GetTransform().SetWorldPosition({ 50, -500.0f });
					Bullet->SetAnimal("Elephant");
				}
				else
				{
					Bullet->GetRenderer()->ChangeFrameAnimation("LionJumpUp");
					Bullet->GetMonsterPhysicsComponent()->Reset();
					Bullet->GetMonsterPhysicsComponent()->AddForce(30);
					Bullet->GetTransform().SetWorldPosition({ 50, -500.0f });
					Bullet->SetAnimal("Lion");
				}
			}
			break;
			case InGameMonsterAttackState::Attack4:
			{
				LimeBullet* Bullet = GetLevel()->CreateActor<LimeBullet>();
				if (nullptr != GetColMapImage())
				{
					Bullet->SetColMapImage(GetColMapImage());
				}

				Bullet->GetRenderer()->ChangeFrameAnimation("Bow1");
				Bullet->SetColMapImage(GetColMapImage());

				StartPosSwitch = !StartPosSwitch;
				if (StartPosSwitch == true)
				{
					LimeBulletStartPosY = -400.0f;
					LimeBulletStartPosX = 50.0f;
					Bullet->SetStartPosName("LeftUp");
				}
				else
				{
					LimeBulletStartPosY = -650;
					LimeBulletStartPosX = 50.0f;
					Bullet->SetStartPosName("LeftDown");
				}
				Bullet->GetTransform().SetWorldPosition({ LimeBulletStartPosX, LimeBulletStartPosY });
				Bullet->SetDirection(GetDirection());
			}
			break;
			case InGameMonsterAttackState::Attack5:
			{
				{
					LeafBullet* Bullet = GetLevel()->CreateActor<LeafBullet>();
					if (nullptr != GetColMapImage())
					{
						Bullet->SetColMapImage(GetColMapImage());
					}

					Bullet->GetRenderer()->ChangeFrameAnimation("Bow1");
					Bullet->SetIndexNum(0);
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition({ 200.0f, 0.0f });
					Bullet->SetDirection(GetDirection());
				}
				{
					LeafBullet* Bullet = GetLevel()->CreateActor<LeafBullet>();
					if (nullptr != GetColMapImage())
					{
						Bullet->SetColMapImage(GetColMapImage());
					}

					Bullet->GetRenderer()->ChangeFrameAnimation("Bow1");
					Bullet->SetIndexNum(1);
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition({ 500.0f,0.0f });
					Bullet->SetDirection(GetDirection());
				}
				{
					LeafBullet* Bullet = GetLevel()->CreateActor<LeafBullet>();
					if (nullptr != GetColMapImage())
					{
						Bullet->SetColMapImage(GetColMapImage());
					}

					Bullet->GetRenderer()->ChangeFrameAnimation("Bow1");
					Bullet->SetIndexNum(2);
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition({ 800.0f, 0.0f });
					Bullet->SetDirection(GetDirection());
				}
				{
					LeafBullet* Bullet = GetLevel()->CreateActor<LeafBullet>();
					if (nullptr != GetColMapImage())
					{
						Bullet->SetColMapImage(GetColMapImage());
					}

					Bullet->GetRenderer()->ChangeFrameAnimation("Bow1");
					Bullet->SetIndexNum(3);
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition({ 1100.0f, 0.0f });
					Bullet->SetDirection(GetDirection());
				}
			}
			break;
			}
		}
	}
}

void SaltBakerShooter::UpdatePivot()
{
	if (State != InGameMonsterState::Attack1 &&
		State != InGameMonsterState::Attack2 &&
		State != InGameMonsterState::Attack4 &&
		State != InGameMonsterState::Attack5)
	{
		return;
	}

	if (State == InGameMonsterState::Attack1 ||
		State == InGameMonsterState::Attack2 ||
		State == InGameMonsterState::Attack4 ||
		State == InGameMonsterState::Attack5)
	{

		GetTransform().SetLocalPosition({ 0.0f, 0.0f });
	}
}

void SaltBakerShooter::OnMonsterStateChanged(InGameMonsterState _State)
{
	UpdateDirection();
}

void SaltBakerShooter::OnMonsterAttackStateChanged(InGameMonsterAttackState _AttackState)
{
	switch (_AttackState)
	{
	case InGameMonsterAttackState::Attack1:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::Attack2:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::Attack3:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::Attack4:
		ElapsedTime = 0.0f;
		break;
	case InGameMonsterAttackState::Attack5:
		ElapsedTime = 0.0f;
		break;
	}

	UpdateDirection();
}

void SaltBakerShooter::Start()
{
}

void SaltBakerShooter::End()
{
}