#include "PreCompile.h"
#include "Bulldog.h"
#include "BulldogPlane.h"
#include "TattooShooter.h"
#include "DogCopterPhase1.h"
#include "YarnballShooter.h"
#include "IInGameCharacterBase.h"
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

		Renderer->AnimationBindEnd("BulldogUnmount", std::bind(&Bulldog::OnUnmountAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogPrepareAttack1", std::bind(&Bulldog::OnPrepareAttackAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogPrepareAttack2", std::bind(&Bulldog::OnPrepareAttackAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogAttack1", std::bind(&Bulldog::OnAttackAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogAttack2", std::bind(&Bulldog::OnAttackAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogAttackFinish1", std::bind(&Bulldog::OnAttackFinishAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogAttackFinish2", std::bind(&Bulldog::OnAttackFinishAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogMount", std::bind(&Bulldog::OnBulldogMountAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogIdle", std::bind(&Bulldog::OnBulldogIdleAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogLookRight", std::bind(&Bulldog::OnBulldogLookAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogLookLeft", std::bind(&Bulldog::OnBulldogLookAnimationFinished, this, std::placeholders::_1));

		Renderer->AnimationBindFrame("BulldogMount", std::bind(&Bulldog::OnMountAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogIdle", std::bind(&Bulldog::OnIdleAnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogAttack1", std::bind(&Bulldog::OnAttack1AnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogAttack2", std::bind(&Bulldog::OnAttack2AnimationFrameChanged, this, std::placeholders::_1));


		Renderer->CreateFrameAnimationFolder("BulldogDie", FrameAnimation_DESC("BulldogDie", 0.05f));
		Renderer->AnimationBindEnd("BulldogDie", std::bind(&Bulldog::BulldogDieCheck, this, std::placeholders::_1));
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

	srand(time(NULL));

	SetHP(5);

	// 총 생성
	{
		YarnballShooter* YarnballGun = GetLevel()->CreateActor<YarnballShooter>();
		YarnballGun->SetParent(this);

		TattooShooter* TattooGun = GetLevel()->CreateActor<TattooShooter>();
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

	GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
	Renderer->ScaleToTexture();
	UpdateState();

	/*if (false == MoveDirection.CompareInt2D(float4::ZERO))
	{
		if (false == IsEndPosArrived())
		{
			if (Plane == nullptr)
			{
				GetTransform().SetWorldMove(MoveDirection * MoveSpeed * GameEngineTime::GetDeltaTime());
			}
			else
			{
				Plane->GetTransform().SetWorldMove(MoveDirection * MoveSpeed * GameEngineTime::GetDeltaTime());
			}
		}
	}*/

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
	if (true == Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D,
		std::bind(&Bulldog::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2)))
	{
		if (CanTakeDamageTime > 1.0f)
		{
			CanTakeDamageTime = 0.0f;
			SetHP(GetHP() - 1);
			TakeDamage();
			if (GetHP() == 2)
			{
				if (DogCopter == nullptr)
				{
					DogCopter = GetLevel()->CreateActor<DogCopterPhase1>();
					DogCopter->SetState(InGameMonsterState::Prepare);
					DogCopter->SetParent(this);
					DogCopter->SetPlayer(Plane->GetPlayer());
				}
			}
		}
	}

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
}

void Bulldog::PrepareAttack1()
{
	DirectionChangeOnOffSwitch();
	Collision->GetTransform().SetLocalScale({ 200.0f, 300.0f });
	SetState(InGameMonsterState::PrepareAttack1);
	if (DirecitonChangeOn == true)
	{
		Renderer->GetTransform().PixLocalNegativeX();
		GetTransform().SetWorldPosition(float4{ 640, -820 });
		Collision->GetTransform().SetLocalPosition({ -500.0f, 350.0f });
	}
	else
	{
		Renderer->GetTransform().PixLocalPositiveX();
		GetTransform().SetWorldPosition(float4{ 640, -820 });
		Collision->GetTransform().SetLocalPosition({ 500.0f, 350.0f });
	}
}

void Bulldog::PrepareAttack2()
{
	DirectionChangeOnOffSwitch();
	Collision->GetTransform().SetLocalScale({ 200.0f, 300.0f });
	if (DirecitonChangeOn == false)
	{
		Renderer->GetTransform().PixLocalNegativeX();
		GetTransform().SetWorldPosition(float4{ 640, -750 });
		Collision->GetTransform().SetLocalPosition({ 500.0f, 350.0f });
		SetState(InGameMonsterState::PrepareAttack2);
	}
	else
	{
		Renderer->GetTransform().PixLocalPositiveX();
		GetTransform().SetWorldPosition(float4{ 640, -750 });
		Collision->GetTransform().SetLocalPosition({ -500.0f, 350.0f });
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

bool Bulldog::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void Bulldog::BulldogDieCheck(const FrameAnimation_DESC& _Info)
{
	Death();
}

void Bulldog::OnUnmountAnimationFinished(const FrameAnimation_DESC& _Info)
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

void Bulldog::OnBulldogLookAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Unmount();
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
	if (_Info.CurFrame == 2)
	{
		int RandomTattoo = (rand() % 2);
		++RandomTattoo;
		if (RandomTattoo == 1)
		{
			SetAttackState(InGameMonsterAttackState::Tattoo1);
		}
		else
		{
			SetAttackState(InGameMonsterAttackState::Tattoo3);
		}
	}
	else if (_Info.CurFrame == 11)
	{
		SetAttackState(InGameMonsterAttackState::Tattoo2);
	}
	else if (_Info.CurFrame == 29)
	{
		int RandomTattoo = (rand() % 2);
		++RandomTattoo;
		if (RandomTattoo == 1)
		{
			SetAttackState(InGameMonsterAttackState::Tattoo1);
		}
		else
		{
			SetAttackState(InGameMonsterAttackState::Tattoo3);
		}
	}
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}

void Bulldog::OnMountAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (Plane == nullptr)
	{
		Plane = GetParent<BulldogPlane>();
	}

	if (_Info.CurFrame == 3)
	{
		StartPos = Plane->GetTransform().GetLocalPosition();
		if (Plane->GetTransform().GetLocalPosition().y > 0)
		{
			EndPos = float4(Plane->GetTransform().GetLocalPosition().x, Plane->GetTransform().GetLocalPosition().y - 400);
		}
		else
		{
			EndPos = float4(Plane->GetTransform().GetLocalPosition().x, Plane->GetTransform().GetLocalPosition().y - 50);
		}
		MoveSpeed = 150.0f;
		MoveToEndPos(StartPos, EndPos, Plane);
	}
}

void Bulldog::OnIdleAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 4)
	{
		if (-345 > EndPos.y)
		{
			StartPos = Plane->GetTransform().GetLocalPosition();
			EndPos = float4(Plane->GetTransform().GetLocalPosition().x, Plane->GetTransform().GetLocalPosition().y + 50);
			MoveSpeed = 100.0f;
			MoveToEndPos(StartPos, EndPos, Plane);
			PlayerPosX = Plane->GetPlayer()->GetTransform().GetLocalPosition().x;
		}
	}
}

void Bulldog::OnBulldogIdleAnimationFinished(const FrameAnimation_DESC& _Info)
{
	if (GetHP() <= 0)
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

void Bulldog::OnBulldogMountAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Idle();
}
