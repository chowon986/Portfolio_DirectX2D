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
#include <GameEngineBase/GameEngineRandom.h>

SaltBakerShooter::SaltBakerShooter()
	: MonsterAttackState(InGameMonsterAttackState::None)
	, StartPosSwitch(false)
	, SugarBulletStartPosX(0.0f)
	, DoughAttackCount(0)
	, SugarAttackCount(0)
	, LimeAttackCount(0)
	, CanDoughAttackWithBerry(false)
	, Switch(true)
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
		Direction = (float4::LEFT + float4::DOWN);
	}

	else if (State == InGameMonsterState::Attack4)
	{
		Direction = float4::LEFT;
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
			case InGameMonsterAttackState::Attack5:
			{
				{
					LeafBullet* Bullet = GetLevel()->CreateActor<LeafBullet>();
					if (nullptr != GetColMapImage())
					{
						Bullet->SetColMapImage(GetColMapImage());
					}

					Bullet->GetRenderer()->ChangeFrameAnimation("Leaf0");
					Bullet->SetIndexNum(0);
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition({ 200.0f, 0.0f });
				}
				{
					LeafBullet* Bullet = GetLevel()->CreateActor<LeafBullet>();
					if (nullptr != GetColMapImage())
					{
						Bullet->SetColMapImage(GetColMapImage());
					}

					Bullet->GetRenderer()->ChangeFrameAnimation("Leaf1");
					Bullet->SetIndexNum(1);
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition({ 500.0f,0.0f });
				}
				{
					LeafBullet* Bullet = GetLevel()->CreateActor<LeafBullet>();
					if (nullptr != GetColMapImage())
					{
						Bullet->SetColMapImage(GetColMapImage());
					}

					Bullet->GetRenderer()->ChangeFrameAnimation("Leaf2");
					Bullet->SetIndexNum(2);
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition({ 800.0f, 0.0f });
				}
				{
					LeafBullet* Bullet = GetLevel()->CreateActor<LeafBullet>();
					if (nullptr != GetColMapImage())
					{
						Bullet->SetColMapImage(GetColMapImage());
					}

					Bullet->GetRenderer()->ChangeFrameAnimation("Leaf3");
					Bullet->SetIndexNum(3);
					Bullet->SetColMapImage(GetColMapImage());
					Bullet->GetTransform().SetWorldPosition({ 1100.0f, 0.0f });
				}
			}
			break;
			}
		}

		switch (MonsterAttackState)
		{
		case InGameMonsterAttackState::Attack1:
		{
			if (StrawberryBulletStartPosX.size() < 4)
			{
				StrawberryBulletStartPosX = { std::make_pair(0, 300.0f), std::make_pair(1, 500.0f), std::make_pair(2,700.0f), std::make_pair(3,900.0f), std::make_pair(4,1100.0f), std::make_pair(5,1300.0f), std::make_pair(6,1500.0f), std::make_pair(7,1700.0f) };
			}

			int RandomStartPosX = GameEngineRandom::MainRandom.RandomInt(0, 7);
			float StartPositionX = StrawberryBulletStartPosX[RandomStartPosX];

			StrawberryBullet* Bullet = GetLevel()->CreateActor<StrawberryBullet>();
			if (RandomStartPosX < 2)
			{
				Bullet->GetRenderer()->ChangeFrameAnimation("BerryA");
			}
			else if (2 <= RandomStartPosX && RandomStartPosX < 4)
			{
				Bullet->GetRenderer()->ChangeFrameAnimation("BerryB");
			}
			else if (4 <= RandomStartPosX && RandomStartPosX < 5)
			{
				Bullet->GetRenderer()->ChangeFrameAnimation("BerryC");
			}
			else if (5 <= RandomStartPosX)
			{
				Bullet->GetRenderer()->ChangeFrameAnimation("BerryD");
			}
			Bullet->SetColMapImage(GetColMapImage());


			std::map<int, float>::iterator It = StrawberryBulletStartPosX.find(RandomStartPosX);
			if (It != StrawberryBulletStartPosX.end())
			{
				StrawberryBulletStartPosX.erase(It);
			}

			Bullet->GetTransform().SetWorldPosition({ StartPositionX, 10.0f });
			Bullet->SetDirection(float4::LEFT + float4::DOWN);


			if (DoughAttackCount < 5 && CanDoughAttackWithBerry == true)
			{
				Switch = !Switch;

				if (Switch)
				{
					int RandomKey = GameEngineRandom::MainRandom.RandomInt(0, 2);

					AnimalBullet* Bullet = GetLevel()->CreateActor<AnimalBullet>();
					if (nullptr != GetColMapImage())
					{
						Bullet->SetColMapImage(GetColMapImage());
					}
					if (RandomKey == 0)
					{
						Bullet->GetRenderer()->ChangeFrameAnimation("CamelJumpUp");
						Bullet->GetMonsterPhysicsComponent()->Reset();
						Bullet->GetMonsterPhysicsComponent()->AddForce(60);
						Bullet->GetTransform().SetWorldPosition({ 0, -500.0f });
						Bullet->SetAnimal("Camel");
					}
					else if (RandomKey == 1)
					{
						Bullet->GetRenderer()->ChangeFrameAnimation("ElephantJumpUp");
						Bullet->GetMonsterPhysicsComponent()->Reset();
						Bullet->GetMonsterPhysicsComponent()->AddForce(55);
						Bullet->GetTransform().SetWorldPosition({ 0, -500.0f });
						Bullet->SetAnimal("Elephant");
					}
					else
					{
						Bullet->GetRenderer()->ChangeFrameAnimation("LionJumpUp");
						Bullet->GetMonsterPhysicsComponent()->Reset();
						Bullet->GetMonsterPhysicsComponent()->AddForce(50);
						Bullet->GetTransform().SetWorldPosition({ 0, -500.0f });
						Bullet->SetAnimal("Lion");
					}
					++DoughAttackCount;

					if (DoughAttackCount == 5)
					{
						CanDoughAttackWithBerry = false;
						DoughAttackCount = 0;
					}
				}
			}
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

			int RandomSugarNum = GameEngineRandom::MainRandom.RandomInt(0, 3);

			SugarBullet* Bullet = GetLevel()->CreateActor<SugarBullet>();
			Bullet->GetRenderer()->ChangeFrameAnimation("Sugar" + std::to_string(RandomSugarNum));
			if (RandomSugarNum == 3)
			{
				if (nullptr != Bullet->GetCollision())
				{
					Bullet->GetCollision()->ChangeOrder(ObjectOrder::PARRIABLEOBJECT);
				}
			}
			Bullet->SetColMapImage(GetColMapImage());
			Bullet->GetTransform().SetWorldPosition({ SugarBulletStartPosX, -500.0f });
			++SugarAttackCount;
			if (SugarAttackCount >= 5)
			{
				if (Character != nullptr)
				{
					Character->SetAttackState(InGameMonsterAttackState::None);
					SugarAttackCount = 0;
				}
			}
		}
		break;
		case InGameMonsterAttackState::Attack3:
		{

			int RandomKey = GameEngineRandom::MainRandom.RandomInt(0, 2);

			AnimalBullet* Bullet = GetLevel()->CreateActor<AnimalBullet>();
			if (nullptr != GetColMapImage())
			{
				Bullet->SetColMapImage(GetColMapImage());
			}
			if (RandomKey == 0)
			{
				Bullet->GetRenderer()->ChangeFrameAnimation("CamelJumpUp");
				Bullet->GetMonsterPhysicsComponent()->Reset();
				Bullet->GetMonsterPhysicsComponent()->AddForce(60);
				Bullet->GetTransform().SetWorldPosition({ 0, -500.0f });
				Bullet->SetAnimal("Camel");
			}
			else if (RandomKey == 1)
			{
				Bullet->GetRenderer()->ChangeFrameAnimation("ElephantJumpUp");
				Bullet->GetMonsterPhysicsComponent()->Reset();
				Bullet->GetMonsterPhysicsComponent()->AddForce(65);
				Bullet->GetTransform().SetWorldPosition({ 0, -500.0f });
				Bullet->SetAnimal("Elephant");
			}
			else
			{
				Bullet->GetRenderer()->ChangeFrameAnimation("LionJumpUp");
				Bullet->GetMonsterPhysicsComponent()->Reset();
				Bullet->GetMonsterPhysicsComponent()->AddForce(55);
				Bullet->GetTransform().SetWorldPosition({ 0, -500.0f });
				Bullet->SetAnimal("Lion");
			}

			if (DoughAttackCount < 5)
			{
				CanDoughAttackWithBerry = true;
			}
			++DoughAttackCount;
			if (DoughAttackCount >= 5)
			{
				if (Character != nullptr)
				{
					Character->SetAttackState(InGameMonsterAttackState::None);
					DoughAttackCount = 0;
				}
			}

		}
		break;
		case InGameMonsterAttackState::Attack4:
		{
			int RandomLimeNum = GameEngineRandom::MainRandom.RandomInt(0, 3);

			LimeBullet* Bullet = GetLevel()->CreateActor<LimeBullet>();
			++LimeAttackCount;
			if (nullptr != GetColMapImage())
			{
				Bullet->SetColMapImage(GetColMapImage());
			}

			Bullet->GetRenderer()->ChangeFrameAnimation("Lime" + std::to_string(RandomLimeNum));
			Bullet->SetColMapImage(GetColMapImage());

			if (RandomLimeNum == 0 || RandomLimeNum == 1)
			{
				LimeBulletStartPosY = -450.0f;
				LimeBulletStartPosX = 1250.0f;
				Bullet->SetStartPosName("LeftUp");
			}
			else
			{
				LimeBulletStartPosY = -600;
				LimeBulletStartPosX = 1250.0f;
				Bullet->SetStartPosName("LeftDown");
			}
			Bullet->GetTransform().SetWorldPosition({ LimeBulletStartPosX, LimeBulletStartPosY });
			Bullet->SetDirection(float4::LEFT);
			if (LimeAttackCount >= 6)
			{
				if (Character != nullptr)
				{
					Character->SetAttackState(InGameMonsterAttackState::None);
					LimeAttackCount = 0;
				}
			}
		}
		break;
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
		IntervalTime = 1.0f;
		break;
	case InGameMonsterAttackState::Attack2:
		IntervalTime = 1.0f;
		break;
	case InGameMonsterAttackState::Attack3:
		IntervalTime = 2.0f;
		break;
	case InGameMonsterAttackState::Attack4:
		IntervalTime = 1.0f;
		break;
	case InGameMonsterAttackState::Attack5:
		IntervalTime = 1.0f;
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