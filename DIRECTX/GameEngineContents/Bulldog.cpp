#include "PreCompile.h"
#include "Bulldog.h"
#include "BulldogPlane.h"
#include "TattooShooter.h"
#include "InGameLevelBase.h"
#include "DogCopterPhase1.h"
#include "YarnballShooter.h"
#include "IInGameCharacterBase.h"
#include "Ph1Dog.h"
#include "InGameMovementComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

Bulldog::Bulldog()
	: Plane(nullptr)
	, Collision(nullptr)
	, Movement(nullptr)
	, Renderer(nullptr)
	, Animation(nullptr)
	, DogCopter(nullptr)
	, BeforePosition(float4::ZERO)
	, Attack1On(true)
	, MoveWithPlaneOn(false)
	, DirecitonChangeOn(true)
	, OnceAttack1FrameChanged(-1)
	, OnceAttack2FrameChanged(-1)
	, PlayerPosX(0)
	, CanTakeDamageTime(0.0f)
	, EndPos(float4::ZERO)
	, MoveSpeed(0.0f)
	, SetEndPosOk(false)
{
}

Bulldog::~Bulldog()
{
}

bool Bulldog::DirectionChangeOnOffSwitch()
{
	int RandomDirection = (rand() % 3);
	++RandomDirection;
	if (RandomDirection == 1)
	{
		DirecitonChangeOn = true;
	}
	else
	{
		DirecitonChangeOn = false;
	}
	return DirecitonChangeOn;
}

bool Bulldog::AttackChangeOnOffSwitch()
{
	Attack1On = !Attack1On;
	return Attack1On;
}

void Bulldog::LookRight()
{
	SetState(InGameMonsterState::LookRight);
}

void Bulldog::LookLeft()
{
	SetState(InGameMonsterState::LookLeft);
}

void Bulldog::Start()
{
	IInGameMonsterBase::Start();
	// 애니메이션 생성
	{
		Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("BulldogIdle", FrameAnimation_DESC("BulldogIdle", 0.08f));
		Renderer->CreateFrameAnimationFolder("BulldogUnmount", FrameAnimation_DESC("BulldogUnmount", 0.05f));
		Renderer->CreateFrameAnimationFolder("BulldogPrepareAttack1", FrameAnimation_DESC("BulldogPrepareAttack1", 0.05f)); 
		Renderer->CreateFrameAnimationFolder("BulldogAttack1", FrameAnimation_DESC("BulldogAttack1", 0.05f)); 
		Renderer->CreateFrameAnimationFolder("BulldogAttackFinish1", FrameAnimation_DESC("BulldogAttackFinish1", 0.05f)); 
		Renderer->CreateFrameAnimationFolder("BulldogPrepareAttack2", FrameAnimation_DESC("BulldogPrepareAttack2", 0.05f)); 
		Renderer->CreateFrameAnimationFolder("BulldogAttack2", FrameAnimation_DESC("BulldogAttack2", 0.06f)); 
		Renderer->CreateFrameAnimationFolder("BulldogAttackFinish2", FrameAnimation_DESC("BulldogAttackFinish2", 0.05f)); 
		Renderer->CreateFrameAnimationFolder("BulldogMount", FrameAnimation_DESC("BulldogMount", 0.05f));
		Renderer->CreateFrameAnimationFolder("BulldogLookLeft", FrameAnimation_DESC("BulldogLookLeft", 0.05f));
		Renderer->CreateFrameAnimationFolder("BulldogLookRight", FrameAnimation_DESC("BulldogLookRight", 0.05f));

		Renderer->AnimationBindEnd("BulldogPrepareAttack1", std::bind(&Bulldog::OnPrepareAttackAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogPrepareAttack2", std::bind(&Bulldog::OnPrepareAttackAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogAttack1", std::bind(&Bulldog::OnAttackAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogAttack2", std::bind(&Bulldog::OnAttackAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogIdle", std::bind(&Bulldog::OnBulldogIdleAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogLookRight", std::bind(&Bulldog::OnBulldogLookAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogLookLeft", std::bind(&Bulldog::OnBulldogLookAnimationFinished, this, std::placeholders::_1));

		Renderer->AnimationBindFrame("BulldogUnmount", std::bind(&Bulldog::OnUnmountAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogPrepareAttack1", std::bind(&Bulldog::OnPrepareAttack1AnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogPrepareAttack2", std::bind(&Bulldog::OnPrepareAttack2AnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogMount", std::bind(&Bulldog::OnMountAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogIdle", std::bind(&Bulldog::OnIdleAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogAttack1", std::bind(&Bulldog::OnAttack1AnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogAttack2", std::bind(&Bulldog::OnAttack2AnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogAttackFinish1", std::bind(&Bulldog::OnAttackFinish1AnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogAttackFinish2", std::bind(&Bulldog::OnAttackFinish2AnimationFrameChanged, this, std::placeholders::_1));


		Renderer->CreateFrameAnimationFolder("BulldogDie", FrameAnimation_DESC("BulldogDie", 0.05f));
		Renderer->AnimationBindEnd("BulldogDie", std::bind(&Bulldog::BulldogDieCheck, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogDie", std::bind(&Bulldog::Test, this, std::placeholders::_1));
		Renderer->SetScaleModeImage();
		Renderer->SetPivot(PIVOTMODE::BOT);
		SetRenderer(Renderer);
	}

	// 컴포넌트 생성
	{
		Movement = CreateComponent<InGameMovementComponent>();
		Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
		Animation->SetMonsterName("Bulldog");

		// Collision
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetParent(this);
		Collision->GetTransform().SetLocalScale({ 300.0f, 300.0f, 1.0f });
		Collision->ChangeOrder(ObjectOrder::MONSTER);
	}

	srand(static_cast<int>(time(NULL)));

	SetHP(3);

	// 총 생성
	{
		YarnballShooter* YarnballGun = GetLevel()->CreateActor<YarnballShooter>();
		YarnballGun->SetParent(this);

		TattooGun = GetLevel()->CreateActor<TattooShooter>();
		TattooGun->SetParent(this);
	}

	// 비행기 생성

	// 시작 위치 세팅
	SetBeforePosition({ 640, 100});
	SetState(InGameMonsterState::Mount);
	SetAttackState(InGameMonsterAttackState::None);
}

void Bulldog::Update(float _DeltaTime)
{
	if (MoveWithPlaneOn == false)
	{
		if (nullptr != GetParent<BulldogPlane>())
		{
			Plane = GetParent<BulldogPlane>();
			MoveWithPlaneOn = true;
		}
	}
	CanTakeDamageTime += _DeltaTime;

	MoveElapsedTime += _DeltaTime;

	Renderer->ScaleToTexture();
	UpdateState();

	float MovePosY = GameEngineMath::LerpLimit(Plane->GetTransform().GetWorldPosition().y, EndPos.y, MoveElapsedTime * MoveSpeed);
	float4 CurPos = Plane->GetTransform().GetWorldPosition();

	if (GetState() != InGameMonsterState::Mount || GetState() != InGameMonsterState::Unmount)
	{
		SetEndPosOk = false;
		float4 BulldogCurPos = GetTransform().GetLocalPosition();
		GetTransform().SetLocalPosition(float4{ BulldogCurPos.x, BulldogCurPos.y, (int)ZOrder::NPC - 2 });
	}
	
	Plane->GetTransform().SetWorldPosition(float4{ CurPos.x, MovePosY, CurPos.z });

	if (SetEndPosOk == true && abs(Plane->GetTransform().GetWorldPosition().y - EndPos.y) <= 0.1) // Endpos가 -250으로 설정되어있고 그 위치가 맞으면
	{
		Plane->CanMoveLeftRight = true;
	}

	if (GetState() == InGameMonsterState::Mount ||
		GetState() == InGameMonsterState::Unmount ||
		GetState() == InGameMonsterState::Idle)
	{
		Collision->GetTransform().SetLocalScale({ 250.0f, 200.0f, 1.0f });
		Collision->GetTransform().SetLocalPosition({ 0.0f, 100.0f, 1.0f });
	}
}

void Bulldog::UpdateState()
{
	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D,
		std::bind(&Bulldog::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
	
	GetState();
}

void Bulldog::TakeDamage()
{
	SetState(InGameMonsterState::TakeDamage);
}

void Bulldog::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void Bulldog::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void Bulldog::Shoot()
{
	if (Attack1On == true)
	{	
		SetState(InGameMonsterState::Attack1);
	}
	else
	{
		SetState(InGameMonsterState::Attack2);
	}
}

void Bulldog::Die()
{
	SetState(InGameMonsterState::Die);
	GetTransform().SetWorldPosition({640.0f,-760.0f,(int)ZOrder::NPC - 100});
}

void Bulldog::PrepareAttack1()
{
	DirectionChangeOnOffSwitch();
	Collision->GetTransform().SetLocalScale({ 200.0f, 300.0f });
	SetState(InGameMonsterState::PrepareAttack1);
	if (DirecitonChangeOn == true)
	{
		Renderer->GetTransform().PixLocalNegativeX();
	}
	else
	{
		Renderer->GetTransform().PixLocalPositiveX();
	}
}

void Bulldog::PrepareAttack2()
{
	DirectionChangeOnOffSwitch();
	Collision->GetTransform().SetLocalScale({ 200.0f, 300.0f });
	if (DirecitonChangeOn == false)
	{
		Renderer->GetTransform().PixLocalNegativeX();
		SetState(InGameMonsterState::PrepareAttack2);
	}
	else
	{
		Renderer->GetTransform().PixLocalPositiveX();
		SetState(InGameMonsterState::PrepareAttack2);
	}
}

void Bulldog::Unmount()
{
	SetBeforePosition({ GetTransform().GetLocalPosition().x, 50 });
	SetState(InGameMonsterState::Unmount);
}

void Bulldog::Mount()
{
	GetTransform().SetLocalPosition({ GetBeforePosition().x, 100 }); // 탈때는 위로
	SetState(InGameMonsterState::Mount);
}

void Bulldog::FinishAttack()
{
	SetAttackState(InGameMonsterAttackState::None);
	if (Attack1On == true)
	{
		SetState(InGameMonsterState::AttackFinish1);
	}
	else
	{
		SetState(InGameMonsterState::AttackFinish2);
	}
}

void Bulldog::OnPrepareAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Mount();
}

CollisionReturn Bulldog::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (CanTakeDamageTime > 1.0f)
	{
		CanTakeDamageTime = 0.0f;
		SetHP(GetHP() - 1);
		if (GetHP() <= 0)
		{
			Die();
		}
		else
		{
			TakeDamage();
		}
		if (GetHP() == 2)
		{
			if (DogCopter == nullptr)
			{
				DogCopter = GetLevel()->CreateActor<DogCopterPhase1>();
				DogCopter->SetState(InGameMonsterState::Prepare);
			}
		}
	}
	return CollisionReturn::Break;
}

void Bulldog::BulldogDieCheck(const FrameAnimation_DESC& _Info)
{
	Death();

	if (InGameLevelBase* Level = dynamic_cast<InGameLevelBase*>(GetLevel()))
	{
		Level->SetPhase(Phase::Phase2);
	}
}


void Bulldog::OnUnmountAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 1)
	{
		float4 BulldogCurPos = GetTransform().GetLocalPosition();
		GetTransform().SetLocalPosition(float4{ BulldogCurPos.x, BulldogCurPos.y, (int)ZOrder::NPC + 1 });
	}
	if (_Info.CurFrame == 7)
	{
		AttackChangeOnOffSwitch();
		if (Attack1On == true)
		{
			PrepareAttack1();
		}
		else if (Attack1On == false)
		{
			PrepareAttack2();
		}
	}
}

void Bulldog::OnBulldogLookAnimationFinished(const FrameAnimation_DESC& _Info)
{
	if (GetHP() <= 0)
	{
		Idle();
	}
	else
	{
		Unmount();
	}
}

void Bulldog::OnPrepareAttackAnimationFinished(const FrameAnimation_DESC& _Info)
{
	if (GetHP() <= 0)
	{
		FinishAttack();
	}
	else
	{
		Shoot();
	}
}

void Bulldog::OnPrepareAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 1)
	{
		float scaleX = Renderer->GetTransform().GetLocalScale().x > 0 ? 1 : -1;

		GetTransform().SetWorldPosition(float4{ 640, -820 });
		Collision->GetTransform().SetLocalPosition({ 500.0f * scaleX, 350.0f });
	}
}

void Bulldog::OnPrepareAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	float posX = Renderer->GetTransform().GetLocalScale().x > 0 ? -500 : 500;
	switch (_Info.CurFrame)
	{
	case 0: Collision->GetTransform().SetLocalPosition({ posX, 700.0f }); break;
	case 1: Collision->GetTransform().SetLocalPosition({ posX, 690.0f }); break;
	case 2: Collision->GetTransform().SetLocalPosition({ posX, 680.0f }); break;
	case 3: Collision->GetTransform().SetLocalPosition({ posX, 670.0f }); break;
	case 4: Collision->GetTransform().SetLocalPosition({ posX, 660.0f }); break;
	case 5: Collision->GetTransform().SetLocalPosition({ posX, 650.0f }); break;
	case 6: Collision->GetTransform().SetLocalPosition({ posX, 640.0f }); break;
	case 7: Collision->GetTransform().SetLocalPosition({ posX, 630.0f }); break;
	case 8: Collision->GetTransform().SetLocalPosition({ posX, 620.0f }); break;
	case 9: Collision->GetTransform().SetLocalPosition({ posX, 600.0f }); break;
	case 10: Collision->GetTransform().SetLocalPosition({ posX, 600.0f }); break;
	case 11: Collision->GetTransform().SetLocalPosition({ posX, 520.0f }); break;
	case 12: Collision->GetTransform().SetLocalPosition({ posX, 510.0f }); break;
	case 13: Collision->GetTransform().SetLocalPosition({ posX, 500.0f }); break;
	case 14: Collision->GetTransform().SetLocalPosition({ posX, 490.0f }); break;
	case 15: Collision->GetTransform().SetLocalPosition({ posX, 480.0f }); break;
	}

	if (_Info.CurFrame == 1)
	{
		GetTransform().SetWorldPosition(float4{ 640, -750 });
	}
}


void Bulldog::OnAttackAnimationFinished(const FrameAnimation_DESC& _Info)
{
	FinishAttack();
}

void Bulldog::OnAttackFinishAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Mount();
}

void Bulldog::OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (OnceAttack1FrameChanged != _Info.CurFrame)
	{
		OnceAttack1FrameChanged = _Info.CurFrame;

		if (OnceAttack1FrameChanged == 2)
		{
			SetAttackState(InGameMonsterAttackState::YarnBall1);
		}
		else if (OnceAttack1FrameChanged == 8)
		{
			SetAttackState(InGameMonsterAttackState::YarnBall2);
		}
		else if (OnceAttack1FrameChanged == 14)
		{
			SetAttackState(InGameMonsterAttackState::YarnBall3);
		}
		else
		{
			SetAttackState(InGameMonsterAttackState::None);
		}
	}
}

void Bulldog::OnAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	float scaleX = Renderer->GetTransform().GetLocalScale().x > 0 ? -1 : 1;
	switch (_Info.CurFrame)
	{
	case 0: Collision->GetTransform().SetLocalPosition({ 500.0f * scaleX, 450.0f }); break;
	case 5: Collision->GetTransform().SetLocalPosition({ 500.0f * scaleX, 380.0f }); break;
	case 16: Collision->GetTransform().SetLocalPosition({ 500.0f * scaleX, 370.0f }); break;
	case 17: Collision->GetTransform().SetLocalPosition({ 500.0f * scaleX, 360.0f }); break;
	case 18: Collision->GetTransform().SetLocalPosition({ 500.0f * scaleX, 350.0f }); break;
	case 19: Collision->GetTransform().SetLocalPosition({ 500.0f * scaleX, 340.0f }); break;
	case 20: Collision->GetTransform().SetLocalPosition({ 500.0f * scaleX, 330.0f }); break;
	case 21: Collision->GetTransform().SetLocalPosition({ 500.0f * scaleX, 320.0f }); break;
	}

	if (_Info.CurFrame == 2)
	{
		int RandomTattoo = (rand() % 2);
		++RandomTattoo;
		if (RandomTattoo == 1)
		{
			SetAttackState(InGameMonsterAttackState::Tattoo1);
			TattooGun->Shoot(InGameMonsterAttackState::Tattoo1);
		}
		else
		{
			SetAttackState(InGameMonsterAttackState::Tattoo3);
			TattooGun->Shoot(InGameMonsterAttackState::Tattoo3);
		}
	}
	else if (_Info.CurFrame == 11)
	{
		SetAttackState(InGameMonsterAttackState::Tattoo2);
		TattooGun->Shoot(InGameMonsterAttackState::Tattoo2);
	}
	else if (_Info.CurFrame == 29)
	{
		int RandomTattoo = (rand() % 2);
		++RandomTattoo;
		if (RandomTattoo == 1)
		{
			SetAttackState(InGameMonsterAttackState::Tattoo1);
			TattooGun->Shoot(InGameMonsterAttackState::Tattoo1);
		}
		else
		{
			SetAttackState(InGameMonsterAttackState::Tattoo3);
			TattooGun->Shoot(InGameMonsterAttackState::Tattoo3);
		}
	}
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}

void Bulldog::OnAttackFinish1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	float posX = Renderer->GetTransform().GetLocalScale().x > 0 ? 500 : -500;
	switch (_Info.CurFrame)
	{
	case 0: Collision->GetTransform().SetLocalPosition({ posX, 320.0f }); break;
	case 1: Collision->GetTransform().SetLocalPosition({ posX, 320.0f }); break;
	case 2:
	{
		if (posX > 0)
		{
			Collision->GetTransform().SetLocalPosition({ posX + 50, 320.0f });
		}
		else
		{
			Collision->GetTransform().SetLocalPosition({ posX - 50, 320.0f });
		}
	}
	break;

	case 3:
	{
		if (posX > 0)
		{
			Collision->GetTransform().SetLocalPosition({ posX + 50, 350.0f });
		}
		else
		{
			Collision->GetTransform().SetLocalPosition({ posX - 50, 350.0f });
		}
	}
	break;
	case 4:
	{
		if (posX > 0)
		{
			Collision->GetTransform().SetLocalPosition({ posX + 70, 350.0f });
		}
		else
		{
			Collision->GetTransform().SetLocalPosition({ posX - 70, 350.0f });
		}
	}
	break;
	case 5:
	{
		if (posX > 0)
		{
			Collision->GetTransform().SetLocalPosition({ posX + 90, 350.0f });
		}
		else
		{
			Collision->GetTransform().SetLocalPosition({ posX - 90, 350.0f });
		}
	}
	break;
	case 6:
	{
		if (posX > 0)
		{
			Collision->GetTransform().SetLocalPosition({ posX + 120, 350.0f });
		}
		else
		{
			Collision->GetTransform().SetLocalPosition({ posX - 120, 350.0f });
		}
	}
	break;
	case 7:
	{
		if (posX > 0)
		{
			Collision->GetTransform().SetLocalPosition({ posX + 150, 350.0f });
		}
		else
		{
			Collision->GetTransform().SetLocalPosition({ posX - 150, 350.0f });
		}
	}
	break;
	case 8:
	{
		if (posX > 0)
		{
			Collision->GetTransform().SetLocalPosition({ posX + 500, 350.0f });
		}
		else
		{
			Collision->GetTransform().SetLocalPosition({ posX - 500, 350.0f });
		}
	}
	break;
	case 14:
	{
		Mount();
		break;
	}
	}
}

void Bulldog::OnAttackFinish2AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	float posX = Renderer->GetTransform().GetLocalScale().x > 0 ? -500 : 500;
	switch (_Info.CurFrame)
	{
	case 0: Collision->GetTransform().SetLocalPosition({ posX, 320.0f }); break;
	case 1: Collision->GetTransform().SetLocalPosition({ posX, 320.0f }); break;
	case 2: Collision->GetTransform().SetLocalPosition({ posX, 320.0f }); break;
	case 3: Collision->GetTransform().SetLocalPosition({ posX, 320.0f }); break;
	case 4: Collision->GetTransform().SetLocalPosition({ posX, 400.0f }); break;
	case 5: Collision->GetTransform().SetLocalPosition({ posX, 500.0f }); break;
	case 6:
	{
		Collision->GetTransform().SetLocalPosition({ posX, 700.0f });
		Mount();
		break;
	}
	}
}

void Bulldog::Test(const FrameAnimation_DESC& _Info)
{
	int a = 0;
}

void Bulldog::OnMountAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 1)
	{
	float4 BulldogCurPos = GetTransform().GetLocalPosition();
	GetTransform().SetLocalPosition(float4{ BulldogCurPos.x, BulldogCurPos.y, (int)ZOrder::NPC +1 });


	}
	if (Plane == nullptr)
	{
		Plane = GetParent<BulldogPlane>();
	}

	if (_Info.CurFrame == 3)
	{
		EndPos = float4(Plane->GetTransform().GetLocalPosition().x, -300);
		MoveSpeed = 0.01f;
	}
	else if (_Info.CurFrame == 7)
	{
		Idle();
	}
}

void Bulldog::OnIdleAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 4)
	{
		EndPos = float4(Plane->GetTransform().GetLocalPosition().x, -250);
		MoveSpeed = static_cast<float>(0.01);
		PlayerPosX = Plane->GetPlayer()->GetTransform().GetLocalPosition().x;
		SetEndPosOk = true;
	}
}

void Bulldog::OnBulldogIdleAnimationFinished(const FrameAnimation_DESC& _Info)
{
	if (GetHP() <= 0 &&
		Dog->IsUpdate() == false)
	{
		Die();
	}


	else
	{
		if (PlayerPosX > GetTransform().GetLocalPosition().x)
		{
			LookRight();
		}
		else
		{
			LookLeft();
		}
	}
}
