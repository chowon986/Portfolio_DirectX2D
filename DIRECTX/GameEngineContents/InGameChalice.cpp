#include "PreCompile.h"
#include "InGameChalice.h"
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
#include "InGameCharacterDust.h"
#include "InGameCharacterJumpDust.h"
#include <GameEngineContents/TutorialLevel.h>
#include <GameEngineContents/DogFightLevel.h>

InGameChalice::InGameChalice()
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
	, CountInvisibleTime(false)
	, DustElapsedTime(0.0f)
{
}

InGameChalice::~InGameChalice()
{
}


void InGameChalice::Start()
{
	IInGameCharacterBase::Start();

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	SetRenderer(Renderer);

	// Aim
	Renderer->CreateFrameAnimationFolder("IngameChaliceAimDiagDown", FrameAnimation_DESC("IngameChaliceAimDiagDown", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceAimDiagUp", FrameAnimation_DESC("IngameChaliceAimDiagUp", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceAimDown", FrameAnimation_DESC("IngameChaliceAimDown", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceAimStraight", FrameAnimation_DESC("IngameChaliceAimStraight", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceAimUp", FrameAnimation_DESC("IngameChaliceAimUp", 0.1f, true));

	// Dash
	Renderer->CreateFrameAnimationFolder("IngameChaliceDash", FrameAnimation_DESC("IngameChaliceDash", 0.06f, true));
	Renderer->AnimationBindEnd("IngameChaliceDash", std::bind(&InGameChalice::OnDashAnimationEnded, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameChaliceDash", std::bind(&InGameChalice::OnDashAnimationFrameChanged, this, std::placeholders::_1));

	// Intro
	Renderer->CreateFrameAnimationFolder("IngameChaliceIntro", FrameAnimation_DESC("IngameChaliceIntro", 0.1f, true));
	Renderer->AnimationBindEnd("IngameChaliceIntro", std::bind(&InGameChalice::OnPrepareAnimationEnded, this, std::placeholders::_1));

	// Jump
	Renderer->CreateFrameAnimationFolder("IngameChaliceJump", FrameAnimation_DESC("IngameChaliceJump", 0.05f, true));

	// Parry
	//Renderer->CreateFrameAnimationFolder("IngameChaliceParry", FrameAnimation_DESC("IngameChaliceParry", 0.05f, true));
	//Renderer->AnimationBindEnd("IngameChaliceParry", std::bind(&InGameChalice::OnParryAnimationFrameEnd, this, std::placeholders::_1));
	//Renderer->AnimationBindStart("IngameChaliceParry", std::bind(&InGameChalice::OnParryAnimationFrameStarted, this, std::placeholders::_1));

	// Run
	Renderer->CreateFrameAnimationFolder("IngameChaliceRun", FrameAnimation_DESC("IngameChaliceRun", 0.1f, true));

	// Shoot
	Renderer->CreateFrameAnimationFolder("IngameChaliceRunShootStraight", FrameAnimation_DESC("IngameChaliceRunShootStraight",  0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceRunShootDiagUp", FrameAnimation_DESC("IngameChaliceRunShootDiagUp",  0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceShootStraight", FrameAnimation_DESC("IngameChaliceShootStraight",  0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceShootDiagDown", FrameAnimation_DESC("IngameChaliceShootDiagDown", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceShootDiagUp", FrameAnimation_DESC("IngameChaliceShootDiagUp", 0.1f,true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceShootDown", FrameAnimation_DESC("IngameChaliceShootDown", 0.1f,true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceShootUp", FrameAnimation_DESC("IngameChaliceShootUp", 0.1f,true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceDuckShoot", FrameAnimation_DESC("IngameChaliceDuckShoot", 0.1f,true));

	//Renderer->CreateFrameAnimationFolder("IngameChaliceExShootStraight", FrameAnimation_DESC("IngameChaliceExShootStraight", 0.05f, true));
	//Renderer->AnimationBindEnd("IngameChaliceExShootStraight", std::bind(&InGameChalice::OnExShootAnimationEnded, this, std::placeholders::_1));
	//Renderer->AnimationBindFrame("IngameChaliceExShootStraight", std::bind(&InGameChalice::OnExShootAnimationChanged, this, std::placeholders::_1));

	// TakeDamage
	Renderer->CreateFrameAnimationFolder("IngameChaliceTakeDamage", FrameAnimation_DESC("IngameChaliceTakeDamage", 0.05f, true));
	Renderer->AnimationBindEnd("IngameChaliceTakeDamage", std::bind(&InGameChalice::OnTakeDamageAnimationEnded, this, std::placeholders::_1));

	// Die
	Renderer->CreateFrameAnimationFolder("IngameChaliceGhost", FrameAnimation_DESC("IngameChaliceGhost", 0.1f, true));
	Renderer->AnimationBindEnd("IngameChaliceGhost", std::bind(&InGameChalice::OnGhostAnimationEnded, this, std::placeholders::_1));

	// Idle
	Renderer->CreateFrameAnimationFolder("IngameChaliceIdle", FrameAnimation_DESC("IngameChaliceIdle", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceIdleDownStart", FrameAnimation_DESC("IngameChaliceIdleDownStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceIdleDown", FrameAnimation_DESC("IngameChaliceIdleDown", 0.05f, true));
	Renderer->CreateFrameAnimationFolder("IngameChaliceIdleDownTurn", FrameAnimation_DESC("IngameChaliceIdleDownTurn", 0.1f, true));

	Renderer->AnimationBindStart("IngameChaliceRunShootStraight", std::bind(&InGameChalice::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameChaliceRunShootDiagUp", std::bind(&InGameChalice::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameChaliceShootStraight", std::bind(&InGameChalice::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameChaliceShootDiagDown", std::bind(&InGameChalice::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameChaliceShootDiagUp", std::bind(&InGameChalice::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameChaliceShootDown", std::bind(&InGameChalice::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameChaliceShootUp", std::bind(&InGameChalice::OnShootAnimationFrameStarted, this, std::placeholders::_1));
	Renderer->AnimationBindStart("IngameChaliceDuckShoot", std::bind(&InGameChalice::OnShootAnimationFrameStarted, this, std::placeholders::_1));

	Renderer->AnimationBindFrame("IngameChaliceRunShootStraight", std::bind(&InGameChalice::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameChaliceRunShootDiagUp", std::bind(&InGameChalice::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameChaliceShootStraight", std::bind(&InGameChalice::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameChaliceShootDiagDown", std::bind(&InGameChalice::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameChaliceShootDiagUp", std::bind(&InGameChalice::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameChaliceShootDown", std::bind(&InGameChalice::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameChaliceShootUp", std::bind(&InGameChalice::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameChaliceDuckShoot", std::bind(&InGameChalice::OnShootAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("IngameChaliceJump", std::bind(&InGameChalice::OnJumpAnimationFrameChanged, this, std::placeholders::_1));

	{
		// Collision
		MainCollision = CreateComponent<GameEngineCollision>();
		MainCollision->ChangeOrder(ObjectOrder::PC);
		MainCollision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		MainCollision->GetTransform().SetLocalPosition({ 0.0f, 60.0f });
	}

	SetState(InGameCharacterState::Prepare);
	Renderer->ChangeFrameAnimation("IngameChaliceIntro");
	Renderer->SetScaleModeImage();
	Renderer->SetPivot(PIVOTMODE::BOT);

	Movement = CreateComponent<InGameCharacterMovementCompmonent>();
	SetPhysicsComponent(CreateComponent<PhysicsComponent>());
	Animation = CreateComponent<InGameCharacterAnimationControllerComponent>();
	Animation->SetCharacterName("Chalice");

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

void InGameChalice::Update(float _DeltaTime)
{
	IInGameCharacterBase::Update(_DeltaTime);
	OnCollisionDebug();
	CheckCollision();

	DustElapsedTime += _DeltaTime;

	if (DustElapsedTime > 0.5 && GetState() == InGameCharacterState::Walk)
	{
		InGameCharacterDust* Dust = GetLevel()->CreateActor<InGameCharacterDust>();
		Dust->SetBoss(this);
		Dust->GetRenderer()->ChangeFrameAnimation("IngameCupheadWalk");
		float4 MyPos = GetTransform().GetWorldPosition();
		if (GetLevel()->GetNameCopy() == "DOGFIGHT")
		{
			Dust->GetTransform().SetWorldPosition({ MyPos.x, MyPos.y + 50, MyPos.z + 0.1f });
		}
		else if (GetLevel()->GetNameCopy() == "TUTORIAL")
		{
			Dust->GetTransform().SetWorldPosition({ MyPos.x - 640.0f, (MyPos.y + 50) + 360.0f, MyPos.z + 0.1f });
		}
		DustElapsedTime = 0.0f;
	}

	if (BeforeState != GetState())
	{
		BeforeState = GetState();

		if (GetState() == InGameCharacterState::Jump)
		{
			InGameCharacterJumpDust* Dust = GetLevel()->CreateActor<InGameCharacterJumpDust>();
			Dust->SetBoss(this);
			Dust->GetRenderer()->ChangeFrameAnimation("IngameCupheadJump");
			float4 MyPos = GetTransform().GetWorldPosition();
			if (GetLevel()->GetNameCopy() == "DOGFIGHT")
			{
				Dust->GetTransform().SetWorldPosition({ MyPos.x, MyPos.y + 50, MyPos.z + 0.1f });
			}
			else if (GetLevel()->GetNameCopy() == "TUTORIAL")
			{
				Dust->GetTransform().SetWorldPosition({ MyPos.x - 640.0f, (MyPos.y + 50) + 360.0f, MyPos.z + 0.1f });
			}
		}
	}

	CanTakeDamageElapsedTime += _DeltaTime;

	if (true == GameEngineInput::GetInst()->IsDown("ChangeGun"))
	{
		ToggleWeapon = !ToggleWeapon;

		WeaponItemBase* Item = ToggleWeapon ? dynamic_cast<WeaponItemBase*>(State->EquippedItems[InventoryType::ShotB].get()) : dynamic_cast<WeaponItemBase*>(State->EquippedItems[InventoryType::ShotA].get());
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
		MainCollision->GetTransform().SetLocalPosition({ 0.0f, 35.0f });
	}
	else if (GetState() == InGameCharacterState::Die)
	{
		MainCollision->GetTransform().SetLocalScale({ 0.0f, 0.0f, 1.0f });
		MainCollision->GetTransform().SetLocalPosition({ 0.0f, 60.0f });
	}
	else
	{
		MainCollision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
		MainCollision->GetTransform().SetLocalPosition({ 0.0f, 60.0f });
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
					SetGauge(GetGauge() - 1);
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

void InGameChalice::LevelEndEvent()
{
	std::list<GameEngineActor*> Actors = GetLevel()->GetGroup(GameObjectGroup::CharacterState);
	for (GameEngineActor* Actor : Actors)
	{
		if (State = dynamic_cast<CharacterState*>(Actor))
		{
			if (WeaponItemBase* ShotAItem = dynamic_cast<WeaponItemBase*>(State->EquippedItems[InventoryType::ShotA].get()))
			{
				ShotAItem->Weapon->SetParent(nullptr);
			}
		}
	}
}

void InGameChalice::Walk()
{
	SetState(InGameCharacterState::Walk);
}

void InGameChalice::Idle()
{
	SetState(InGameCharacterState::Idle);
}

void InGameChalice::OnStateChanged()
{
	if (GetState() == InGameCharacterState::Jump)
	{
		GetPhysicsComponent()->Reset();
		GetPhysicsComponent()->AddForce(50);
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
	JumpOnParry = false;
}

void InGameChalice::OnIsOnGroundChanged()
{
	JumpTwice = false;
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

void InGameChalice::OnPrepareAnimationEnded(const FrameAnimation_DESC& _Info)
{
	IsInputEnabled = true;
}

void InGameChalice::OnDashAnimationEnded(const FrameAnimation_DESC& _Info)
{
	IsInputEnabled = true;
	if (GetIsOnGround() == false)
	{
		Renderer->ChangeFrameAnimation("InGameChaliceJump");
	}
	GetPhysicsComponent()->On();
}

void InGameChalice::OnDashAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{

	if (_Info.CurFrame == 1)
	{
		GameEngineSound::SoundPlayOneShot("sfx_player_dash_01.wav");
	}


	if (_Info.CurFrame == 2)
	{
		if (true == GetOnDashInvisible())
		{
			Renderer->Off();
			MainCollision->Off();
			CountInvisibleTime = true;
		}
	}
}

void InGameChalice::OnTakeDamageAnimationEnded(const FrameAnimation_DESC& _Info)
{
	IsTakeDamageInProgess = false;
	UpdateState();
}

void InGameChalice::OnExShootAnimationEnded(const FrameAnimation_DESC& _Info)
{
	GetPhysicsComponent()->On();
	SetAttackState(InGameCharacterAttackState::None);
	UpdateState();
}

void InGameChalice::OnExShootAnimationChanged(const FrameAnimation_DESC& _Info)
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

void InGameChalice::OnGhostAnimationEnded(const FrameAnimation_DESC& _Info)
{
	if (IsInputEnabled == false)
	{
		IsInputEnabled = true;
	}

	OpenScoreBoard();
}

void InGameChalice::OnShootAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	FrameAnimation_DESC* Info = const_cast<FrameAnimation_DESC*>(&_Info);

	if (nullptr != dynamic_cast<ConvergeShooter*>(EquippedWeapon))
	{
		Info->Inter = 0.1f;
	}
	else
	{
		Info->Inter = 0.05f;
	}
	if (Info->CurFrame % 2 == 0)
	{
		SetShooterState(InGameCharacterShooterState::BasicShot);
	}
	else
	{
		SetShooterState(InGameCharacterShooterState::None);
	}
}

void InGameChalice::OnShootAnimationFrameStarted(const FrameAnimation_DESC& _Info)
{

}

void InGameChalice::OnJumpAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 1)
	{
		GameEngineSound::SoundPlayOneShot("sfx_player_jump_01.wav");
	}

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

void InGameChalice::Aim()
{
	SetState(InGameCharacterState::Aim);
}

void InGameChalice::TakeDamage()
{
	SetHP(GetHP() - 1);
	if (GetHP() > 0)
	{
		SetState(InGameCharacterState::TakeDamage);
		if (false == GetPhysicsComponent()->IsUpdate())
		{
			GetPhysicsComponent()->On();
		}
	}
	else
	{
		SetState(InGameCharacterState::TakeDamage);
		if (false == GetPhysicsComponent()->IsUpdate())
		{
			GetPhysicsComponent()->On();
		}
		//Die();
		//GetPhysicsComponent()->Off();
	}
}

void InGameChalice::Dash()
{
	SetState(InGameCharacterState::Dash);
}

void InGameChalice::Die()
{
	if (GetHP() <= 0)
	{
		SetState(InGameCharacterState::Die);
	}
}

void InGameChalice::Duck()
{
	SetState(InGameCharacterState::Duck);
}

void InGameChalice::Jump()
{
	SetState(InGameCharacterState::Jump);

}

void InGameChalice::Parry()
{
	//SetState(InGameCharacterState::Parry);
}

void InGameChalice::Prepare()
{
	SetState(InGameCharacterState::Prepare);
}

void InGameChalice::Run()
{
}

void InGameChalice::Shoot()
{
	SetAttackState(InGameCharacterAttackState::Shoot);
}

void InGameChalice::SuperAttack()
{
	SetAttackState(InGameCharacterAttackState::SuperAttack);

}
void InGameChalice::SpecialAttack()
{
}
void InGameChalice::UpdateState()
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
		if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
		{
			SetState(InGameCharacterState::Evade);
		}
		else
		{
			IsInputEnabled = false;
			Dash();
		}
	}

	else if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		if (GetIsOnGround() == true)
		{
			Jump();
		}
		else
		{
			if (JumpTwice == false)
			{
				GetPhysicsComponent()->Reset();
				GetPhysicsComponent()->AddForce(45);
				JumpTwice = true;
			}
		}
	}

	else if (true == GameEngineInput::GetInst()->IsPress("Aim"))
	{
		Aim();
	}

	else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		if (true == GetIsOnGround() &&
			GetState() != InGameCharacterState::Evade)
		{
			Duck();
		}
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

	if (GetState() == InGameCharacterState::Dash)
	{
		MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D,
			std::bind(&InGameChalice::OnParry, this, std::placeholders::_1, std::placeholders::_2));
		MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::ONLYPARRIABLEOBJECT, CollisionType::CT_AABB2D,
			std::bind(&InGameChalice::OnParry, this, std::placeholders::_1, std::placeholders::_2));
	}
}

void InGameChalice::UpdateDirection()
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

void InGameChalice::CheckCollision()
{
	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PARRIABLEOBJECT, CollisionType::CT_AABB2D,
		std::bind(&InGameChalice::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));

	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER_BULLET, CollisionType::CT_AABB2D,
		std::bind(&InGameChalice::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER_DAMAGEABLE_BULLET, CollisionType::CT_AABB2D,
		std::bind(&InGameChalice::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER, CollisionType::CT_AABB2D,
		std::bind(&InGameChalice::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER_BULLET2, CollisionType::CT_AABB2D,
		std::bind(&InGameChalice::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));

	if (SaltBakerLevel* Level = dynamic_cast<SaltBakerLevel*>(GetLevel()))
	{
		MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::TRACKING1, CollisionType::CT_AABB2D,
			std::bind(&InGameChalice::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
		MainCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::TRACKING1, CollisionType::CT_AABB2D,
			std::bind(&InGameChalice::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	}
}

bool InGameChalice::GetIsOpenScoreBoard()
{
	return IsOpenScoreBoard;
}

CollisionReturn InGameChalice::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (CanTakeDamageIntervalTime < CanTakeDamageElapsedTime)
	{
		CanTakeDamageElapsedTime = 0.0f;
		TakeDamage();
	}

	return CollisionReturn::ContinueCheck;
}

CollisionReturn InGameChalice::OnParry(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (_Other != nullptr)
	{
		if (GameEngineActor* Actor = _Other->GetActor())
		{
			// 다른 총알이면 죽여야 한다.
			//Actor->Death();
		}
	}
	Jump();

	return CollisionReturn::Break;
}

void InGameChalice::OnParryAnimationFrameEnd(const FrameAnimation_DESC& _Info)
{
	IsInputEnabled = true;
	Idle();
}

void InGameChalice::OnParryAnimationFrameStarted(const FrameAnimation_DESC& _Info)
{
}

void InGameChalice::OnCollisionDebug()
{
	//GameEngineDebug::DrawBox(MainCollision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void InGameChalice::OpenScoreBoard()
{
	IsOpenScoreBoard = true;
}
