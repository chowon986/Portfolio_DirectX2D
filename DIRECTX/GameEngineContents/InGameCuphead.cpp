#include "PreCompile.h"
#include "InGameCuphead.h"
#include "InGameCharacterAnimationControllerComponent.h"
#include "InGameCharacterMovementCompmonent.h"
#include "PhysicsComponent.h"
#include "PeaShooter.h"
#include "SpreadShooter.h"
#include "ConvergeShooter.h"
#include "BoomerangShooter.h"
#include "CharacterState.h"
#include "CharacterScore.h"
#include "WeaponItemBase.h"
#include "CharmItemBase.h"
#include "SaltBakerLevel.h"
#include <GameEngineContents/TutorialLevel.h>
#include <GameEngineContents/DogFightLevel.h>

InGameCuphead::InGameCuphead()
	: IsInputEnabled(false)
	, Animation(nullptr)
	, Movement(nullptr)
	, IsOpenScoreBoard(false)
	, Collision(nullptr)
	, Renderer(nullptr)
	, AlphaOn(true)
	, CanTakeDamageElapsedTime(0.0f)
	, CanTakeDamageIntervalTime(1.0f)
	, ToggleWeapon(false)
	, IsInvisible(false)
	, CountInvisibleTime(false)
{
}

InGameCuphead::~InGameCuphead()
{
}


void InGameCuphead::Start()
{
	IInGameCharacterBase::Start();

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	SetRenderer(Renderer);

	// Aim
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadAimDiagDown", FrameAnimation_DESC("Cup.png", 180, 184, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadAimDiagUp", FrameAnimation_DESC("Cup.png", 186, 190, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadAimDown", FrameAnimation_DESC("Cup.png", 192, 196, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadAimStraight", FrameAnimation_DESC("Cup.png", 200, 204, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadAimUp", FrameAnimation_DESC("Cup.png", 206, 210, 0.1f, true));

	// Dash
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadDash", FrameAnimation_DESC("Cup_Dash.png", 0, 7, 0.06f, true));
	Renderer->AnimationBindEnd("IngameCupheadDash", std::bind(&InGameCuphead::OnDashAnimationEnded, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadDash", std::bind(&InGameCuphead::OnDashAnimationFrameChanged, this, std::placeholders::_1));

	// Intro
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIntro", FrameAnimation_DESC("Cup.png", 220, 247, 0.1f, true));
	Renderer->AnimationBindEnd("IngameCupheadIntro", std::bind(&InGameCuphead::OnPrepareAnimationEnded, this, std::placeholders::_1));

	// Jump
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadJump", FrameAnimation_DESC("Cup.png", 20, 27, 0.05f, true));

	// Parry
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadParry", FrameAnimation_DESC("Cup.png", 120, 127, 0.05f, true));
	Renderer->AnimationBindEnd("IngameCupheadParry", std::bind(&InGameCuphead::OnParryAnimationFrameEnd, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadParry", std::bind(&InGameCuphead::OnParryAnimationFrameStarted, this, std::placeholders::_1));

	// Run
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadRun", FrameAnimation_DESC("Cup.png", 40, 55, 0.1f, true));

	// Shoot
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadRunShootStraight", FrameAnimation_DESC("Cup.png", 60, 75, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadRunShootDiagUp", FrameAnimation_DESC("Cup.png", 80, 95, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadShootStraight", FrameAnimation_DESC("Cup.png", 100, 102, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadShootDiagDown", FrameAnimation_DESC("Cup.png", 104, 106, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadShootDiagUp", FrameAnimation_DESC("Cup.png", 108, 110, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadShootDown", FrameAnimation_DESC("Cup.png", 112, 114, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadShootUp", FrameAnimation_DESC("Cup.png", 116, 118, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadDuckShoot", FrameAnimation_DESC("Cup.png", 174, 176, 0.1f, true));

	Renderer->CreateFrameAnimationFolder("IngameCupheadExShootStraight", FrameAnimation_DESC("IngameCupheadExShootStraight", 0.05f, true));
	Renderer->AnimationBindEnd("IngameCupheadExShootStraight", std::bind(&InGameCuphead::OnExShootAnimationEnded, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadExShootStraight", std::bind(&InGameCuphead::OnExShootAnimationChanged, this, std::placeholders::_1));

	// TakeDamage
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadTakeDamage", FrameAnimation_DESC("Cup.png", 28, 33, 0.05f, true));
	Renderer->AnimationBindEnd("IngameCupheadTakeDamage", std::bind(&InGameCuphead::OnTakeDamageAnimationEnded, this, std::placeholders::_1));

	// Die
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadGhost", FrameAnimation_DESC("Cup.png", 140, 155, 0.1f, true));
	Renderer->AnimationBindEnd("IngameCupheadGhost", std::bind(&InGameCuphead::OnGhostAnimationEnded, this, std::placeholders::_1));

	// Idle
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdle", FrameAnimation_DESC("Cup.png", 0, 7, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdleDownStart", FrameAnimation_DESC("Cup.png", 160, 166, 0.1f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdleDown", FrameAnimation_DESC("Cup.png", 168, 172, 0.05f, true));
	Renderer->CreateFrameAnimationCutTexture("IngameCupheadIdleDownTurn", FrameAnimation_DESC("Cup.png", 159, 159, 0.1f, true));

	Renderer->AnimationBindStart("IngameCupheadRunShootStraight", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadRunShootDiagUp", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadShootStraight", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadShootDiagDown", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadShootDiagUp", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadShootDown", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadShootUp", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameCupheadDuckShoot", std::bind(&InGameCuphead::OnShootAnimationFrameStarted, this, std::placeholders::_1));

	Renderer->AnimationBindFrame("IngameCupheadRunShootStraight", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadRunShootDiagUp", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadShootStraight", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadShootDiagDown", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadShootDiagUp", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadShootDown", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadShootUp", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadDuckShoot", std::bind(&InGameCuphead::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameCupheadJump", std::bind(&InGameCuphead::OnJumpAnimationFrameChanged, this, std::placeholders::_1));

	{
		// Collision
		MainCollision = CreateComponent<GameEngineCollision>();
		MainCollision->ChangeOrder(ObjectOrder::PC);
		MainCollision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		MainCollision->GetTransform().SetLocalPosition({ 0.0f, 60.0f });
	}

	SetState(InGameCharacterState::Prepare);
	Renderer->ChangeFrameAnimation("IngameCupheadIntro");
	Renderer->ScaleToCutTexture(0);
	Renderer->SetPivot(PIVOTMODE::BOT);

	Movement = CreateComponent<InGameCharacterMovementCompmonent>();
	SetPhysicsComponent(CreateComponent<PhysicsComponent>());
	Animation = CreateComponent<InGameCharacterAnimationControllerComponent>();
	Animation->SetCharacterName("Cuphead");

	SetHP(3);

	{
		std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
		EquippedWeapon = nullptr;
		for (GameEngineActor* Actor : Actors)
		{
			if (State = dynamic_cast<CharacterState*>(Actor))
			{
				if (WeaponItemBase* ShotAItem = dynamic_cast<WeaponItemBase*>(State->EquippedItems[InventoryType::ShotA].get()))
				{
					EquippedWeapon = ShotAItem->Weapon;
					EquippedWeapon->SetParent(this);
					EquippedWeapon->SetIsEquipped(true);
				}

				SetHP(State->MaxHP);
			}
		}

		if (EquippedWeapon == nullptr)
		{
			PeaShooter* Shooter = GetLevel()->CreateActor<PeaShooter>();
			Shooter->SetParent(this);
			EquippedWeapon = Shooter;
			EquippedWeapon->SetIsEquipped(true);
		}
	}

	{
		std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterScore);
		for (GameEngineActor* Actor : Actors)
		{
			if (CharacterScore* _Score = dynamic_cast<CharacterScore*>(Actor))
			{
				Score = _Score;
			}
		}
	}
}

void InGameCuphead::Update(float _DeltaTime)
{
	IInGameCharacterBase::Update(_DeltaTime);
	OnCollisionDebug();
	CheckCollision();

	if (true == CountInvisibleTime)
	{
		InvisibleElapsedTime += _DeltaTime;
	}

	if (false == Renderer->IsUpdate())
	{
		if (InvisibleElapsedTime > 0.3)
		{
			if (false == Renderer->IsUpdate())
			{
				Renderer->On();
				MainCollision->On();
			}

			IsInputEnabled = true;
			if (GetIsOnGround() == false)
			{
				Renderer->ChangeFrameAnimation("InGameCupheadJump");
			}
			GetPhysicsComponent()->On();
			InvisibleElapsedTime = 0.0f;
			CountInvisibleTime = false;
		}
	}

	CanTakeDamageElapsedTime += _DeltaTime;

	if (true == GameEngineInput::GetInst()->IsDown("ChangeGun"))
	{
		ToggleWeapon = !ToggleWeapon;
		
		WeaponItemBase* Item = ToggleWeapon ? dynamic_cast<WeaponItemBase*>(State->EquippedItems[InventoryType::ShotB].get()) :dynamic_cast<WeaponItemBase*>(State->EquippedItems[InventoryType::ShotA].get());
		if (nullptr != Item)
		{
			if (nullptr != EquippedWeapon)
			{
				EquippedWeapon->SetIsEquipped(false);
			}

			EquippedWeapon = Item->Weapon;
			EquippedWeapon->SetIsEquipped(true);
			if (nullptr != EquippedWeapon && nullptr == EquippedWeapon->GetParent())
			{
				EquippedWeapon->SetParent(this);
			}
		}
	}

	if (true == GetLevel()->GetMainCameraActor()->IsFreeCameraMode())
	{
		return;
	}


	if (GetState() == InGameCharacterState::Duck)
	{
		MainCollision->GetTransform().SetLocalScale({ 100.0f, 50.0f, 1.0f });
	}
	else if(GetState() == InGameCharacterState::Die)
	{
		MainCollision->GetTransform().SetLocalScale({ 0.0f, 0.0f, 1.0f });
	}
	else
	{
		MainCollision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
	}

	if (IsInputEnabled == false)
	{
		return;
	}

	UpdateDirection();
	UpdateState();

	if (GetState() != InGameCharacterState::Dash)
	{
		if (true == GameEngineInput::GetInst()->IsPress("Shoot"))
		{
			if (TutorialLevel* Level = dynamic_cast<TutorialLevel*>(GetLevel()))
			{
				return;
			}
			Shoot();
		}
		else if (true == GameEngineInput::GetInst()->IsDown("GaugeShoot"))
		{
			if (GetGauge() == GetMaxGauge())
			{
				SetAttackState(InGameCharacterAttackState::SpecialAttack);
				SetShooterState(InGameCharacterShooterState::SpecialShot);
				SetGauge(0);
				Score->UseCard += 1;

			}
			else
			{
				if (GetGauge() > 1.0f)
				{
					SetAttackState(InGameCharacterAttackState::SuperAttack);
					GetPhysicsComponent()->Reset();
					GetPhysicsComponent()->Off();
					SetGauge(GetGauge()-1);
					Score->UseCard += 1;
				}
			}
		}
		else
		{
			if (GetAttackState() == InGameCharacterAttackState::Shoot)
			{
				SetAttackState(InGameCharacterAttackState::None);
			}
		}
	}
	else
	{
		SetAttackState(InGameCharacterAttackState::None);
	}
}

void InGameCuphead::Walk()
{
	SetState(InGameCharacterState::Walk);
}

void InGameCuphead::Idle()
{
	SetState(InGameCharacterState::Idle);
}

void InGameCuphead::OnStateChanged()
{
	if (GetState() == InGameCharacterState::Jump)
	{
		GetPhysicsComponent()->Reset();
		GetPhysicsComponent()->AddForce(50);
	}
	else if (GetState() == InGameCharacterState::Parry)
	{
		GetPhysicsComponent()->Reset();
		GetPhysicsComponent()->AddForce(45);
		SetGauge(GetGauge() + 1);
		if (Score != nullptr)
		{
			Score->Parry += 1;
		}
	}
	if (GetState() == InGameCharacterState::Dash)
	{
		GetPhysicsComponent()->Reset();
		GetPhysicsComponent()->Off();
	}
	if (GetState() == InGameCharacterState::TakeDamage)
	{
		IsTakeDamageInProgess = true;
	}
}

void InGameCuphead::OnIsOnGroundChanged()
{
	if (GetIsOnGround())
	{
		if (DogFightLevel* Level = dynamic_cast<DogFightLevel*>(GetLevel()))
		{
			GameEngineTextureRenderer* CollisionMap = GetColMapImage();
			if (CollisionMap == nullptr)
			{
				return;
			}

			GameEngineTexture* ColMapTexture = CollisionMap->GetCurTexture();
			if (ColMapTexture == nullptr)
			{
				return;
			}
			if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -GetTransform().GetWorldPosition().y + 10).CompareInt4D(float4::RED))
			{
				GetPhysicsComponent()->AddForce(50);
				TakeDamage();
			}
		}
	}
}

void InGameCuphead::OnPrepareAnimationEnded(const FrameAnimation_DESC& _Info)
{
	IsInputEnabled = true;
}

void InGameCuphead::OnDashAnimationEnded(const FrameAnimation_DESC& _Info)
{
	IsInputEnabled = true;
	if (GetIsOnGround() == false)
	{
		Renderer->ChangeFrameAnimation("InGameCupheadJump");
	}
	GetPhysicsComponent()->On();
}

void InGameCuphead::OnDashAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 2)
	{
		if (true == IsInvisible)
		{
			Renderer->Off();
			MainCollision->Off();
			CountInvisibleTime = true;
		}
	}
}

void InGameCuphead::OnTakeDamageAnimationEnded(const FrameAnimation_DESC& _Info)
{
	IsTakeDamageInProgess = false;
	UpdateState();
}

void InGameCuphead::OnExShootAnimationEnded(const FrameAnimation_DESC& _Info)
{
	GetPhysicsComponent()->On();
	SetAttackState(InGameCharacterAttackState::None);
	UpdateState();
}

void InGameCuphead::OnExShootAnimationChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 6)
	{
		SetShooterState(InGameCharacterShooterState::SuperShot);
	}
	else
	{
		SetShooterState(InGameCharacterShooterState::None);
	}
}

void InGameCuphead::OnGhostAnimationEnded(const FrameAnimation_DESC& _Info)
{
	if (IsInputEnabled == false)
	{
		IsInputEnabled = true;
	}

	OpenScoreBoard();
}

void InGameCuphead::OnShootAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	FrameAnimation_DESC* Info = const_cast<FrameAnimation_DESC*>(&_Info);
	Info->Inter = 0.05f;
	if (Info->CurFrame % 2 == 0)
	{
		SetShooterState(InGameCharacterShooterState::BasicShot);
	}
	else
	{
		SetShooterState(InGameCharacterShooterState::None);
	}
}

void InGameCuphead::OnShootAnimationFrameStarted(const FrameAnimation_DESC& _Info)
{

}

void InGameCuphead::OnJumpAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	FrameAnimation_DESC* Info = const_cast<FrameAnimation_DESC*>(&_Info);
	if (Info->CurFrame % 2 == 0)
	{
		//SetShooterState(InGameCharacterShooterState::BasicShot);
	}
	else
	{
		SetShooterState(InGameCharacterShooterState::None);
	}
}


void InGameCuphead::Aim()
{
	SetState(InGameCharacterState::Aim);
}

void InGameCuphead::TakeDamage()
{
	SetHP(GetHP() - 1);
	if (GetHP() > 0)
	{
		SetState(InGameCharacterState::TakeDamage);
		GetPhysicsComponent()->On();
	}
	else
	{
		Die();
		GetPhysicsComponent()->Off();
	}
}

void InGameCuphead::Dash()
{
	SetState(InGameCharacterState::Dash);
}

void InGameCuphead::Die()
{
	if (GetHP() <= 0)
	{
		SetState(InGameCharacterState::Die);
	}
}

void InGameCuphead::Duck()
{
	SetState(InGameCharacterState::Duck);
}

void InGameCuphead::Jump()
{
	SetState(InGameCharacterState::Jump);

}

void InGameCuphead::Parry()
{
	SetState(InGameCharacterState::Parry);
}

void InGameCuphead::Prepare()
{
	SetState(InGameCharacterState::Prepare);
}

void InGameCuphead::Run()
{
}

void InGameCuphead::Shoot()
{
	SetAttackState(InGameCharacterAttackState::Shoot);
}

void InGameCuphead::SuperAttack()
{
	SetAttackState(InGameCharacterAttackState::SuperAttack);

}
void InGameCuphead::SpecialAttack()
{
}
void InGameCuphead::UpdateState()
{
	if (GetState() == InGameCharacterState::TakeDamage &&
		IsTakeDamageInProgess == true)
	{
		return;
	}
	else if (GetState() == InGameCharacterState::Die)
	{
		return;
	}
	else
	{
		IsTakeDamageInProgess = false;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Dash"))
	{
		IsInputEnabled = false;
		Dash();
	}

	else if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		if (GetIsOnGround() == true)
		{
			Jump();
		}
		else
		{
			//IsInputEnabled = false;
			MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D,
				std::bind(&InGameCuphead::OnParry, this, std::placeholders::_1, std::placeholders::_2));
			MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::ONLYPARRIABLEOBJECT, CollisionType::CT_AABB2D,
				std::bind(&InGameCuphead::OnParry, this, std::placeholders::_1, std::placeholders::_2));
		}
	}

	else if (true == GameEngineInput::GetInst()->IsPress("Aim"))
	{
		Aim();
	}

	else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		Duck();
	}

	else if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") ||
		true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		Walk();
	}

	else
	{
		if (GetIsOnGround() == true)
		{
			IsInputEnabled = true;
			Idle();
		}
	}
}

void InGameCuphead::UpdateDirection()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetHorizontalDirection("Left");
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetHorizontalDirection("Right");
	}
	else
	{
		SetHorizontalDirection("Center");
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetVerticalDirection("Up");
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetVerticalDirection("Down");
	}
	else
	{
		SetVerticalDirection("Center");
	}
}

void InGameCuphead::CheckCollision()
{
	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D,
		std::bind(&InGameCuphead::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));

	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER_BULLET, CollisionType::CT_AABB2D,
		std::bind(&InGameCuphead::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER_DAMAGEABLE_BULLET, CollisionType::CT_AABB2D,
		std::bind(&InGameCuphead::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER, CollisionType::CT_AABB2D,
		std::bind(&InGameCuphead::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER_BULLET2, CollisionType::CT_AABB2D,
		std::bind(&InGameCuphead::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));

	if (SaltBakerLevel* Level = dynamic_cast<SaltBakerLevel*>(GetLevel()))
	{
		MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::TRACKING1, CollisionType::CT_AABB2D,
			std::bind(&InGameCuphead::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
		MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::TRACKING1, CollisionType::CT_AABB2D,
			std::bind(&InGameCuphead::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	}
}

bool InGameCuphead::GetIsOpenScoreBoard()
{
	return IsOpenScoreBoard;
}

CollisionReturn InGameCuphead::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (CanTakeDamageIntervalTime < CanTakeDamageElapsedTime)
	{
		CanTakeDamageElapsedTime = 0.0f;
		TakeDamage();
	}

	return CollisionReturn::ContinueCheck;
}

CollisionReturn InGameCuphead::OnParry(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Parry();

	if (_Other != nullptr)
	{
		if (GameEngineActor* Actor = _Other->GetActor())
		{
			// 다른 총알이면 죽여야 한다.
			//Actor->Death();
		}
	}
	
	return CollisionReturn::Break;
}

void InGameCuphead::OnParryAnimationFrameEnd(const FrameAnimation_DESC& _Info)
{
	IsInputEnabled = true;
	Idle();
}

void InGameCuphead::OnParryAnimationFrameStarted(const FrameAnimation_DESC& _Info)
{
}

void InGameCuphead::OnCollisionDebug()
{
	//GameEngineDebug::DrawBox(MainCollision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void InGameCuphead::OpenScoreBoard()
{
	IsOpenScoreBoard = true;
}
