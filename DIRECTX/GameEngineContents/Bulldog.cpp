#include "PreCompile.h"
#include "Bulldog.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "YarnballShooter.h"
#include "TattooShooter.h"
#include "BulldogPlane.h"
#include "IInGameCharacterBase.h"

Bulldog::Bulldog()
	: Collision(nullptr)
	, Renderer(nullptr)
	, Movement(nullptr)
	, Animation(nullptr)
	, BeforePosition(float4::ZERO)
	, DirecitonChangeOn(true)
	, OnceAttack1FrameChanged(-1)
	, OnceAttack2FrameChanged(-1)
	, MoveWithPlaneOn(false)
	, Plane(nullptr)
	, PlayerPosX(0)
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
		Renderer->CreateFrameAnimationFolder("BulldogIntro", FrameAnimation_DESC("BulldogIntro", 0.1f));
		Renderer->CreateFrameAnimationFolder("BulldogIdle", FrameAnimation_DESC("BulldogIdle", 0.1f));
		Renderer->CreateFrameAnimationFolder("BulldogUnmount", FrameAnimation_DESC("BulldogUnmount", 0.1f));

		Renderer->CreateFrameAnimationFolder("BulldogPrepareAttack1", FrameAnimation_DESC("BulldogPrepareAttack1", 0.1f)); // Catgun
		Renderer->CreateFrameAnimationFolder("BulldogAttack1", FrameAnimation_DESC("BulldogAttack1", 0.1f)); // Catgun
		Renderer->CreateFrameAnimationFolder("BulldogAttackFinish1", FrameAnimation_DESC("BulldogAttackFinish1", 0.1f)); // Catgun

		Renderer->CreateFrameAnimationFolder("BulldogPrepareAttack2", FrameAnimation_DESC("BulldogPrepareAttack2", 0.1f)); // Tattoo
		Renderer->CreateFrameAnimationFolder("BulldogAttack2", FrameAnimation_DESC("BulldogAttack2", 0.1f)); // Tattoo
		Renderer->CreateFrameAnimationFolder("BulldogAttackFinish2", FrameAnimation_DESC("BulldogAttackFinish2", 0.1f)); // Tattoo

		Renderer->CreateFrameAnimationFolder("BulldogMount", FrameAnimation_DESC("BulldogMount", 0.1f));

		Renderer->CreateFrameAnimationFolder("BulldogLookLeft", FrameAnimation_DESC("BulldogLookLeft", 0.1f));
		Renderer->CreateFrameAnimationFolder("BulldogLookRight", FrameAnimation_DESC("BulldogLookRight", 0.1f));

		Renderer->AnimationBindEnd("BulldogIntro", std::bind(&Bulldog::OnPrepareAnimationFinished, this, std::placeholders::_1));
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
		Renderer->AnimationBindFrame("BulldogAttackFinish2", std::bind(&Bulldog::OnAttackFinish2AnimationFrameChanged, this, std::placeholders::_1));

		Renderer->AnimationBindFrame("BulldogPrepareAttack2", std::bind(&Bulldog::OnPrePareAttack2AnimationFrameChanged, this, std::placeholders::_1));

		Renderer->CreateFrameAnimationFolder("BulldogDie", FrameAnimation_DESC("BulldogDie", 0.1f));
		Renderer->AnimationBindEnd("BulldogDie", std::bind(&Bulldog::BulldogDieCheck, this, std::placeholders::_1));
		Renderer->SetScaleModeImage();
		Renderer->SetPivot(PIVOTMODE::BOT);
		SetRenderer(Renderer);
	}

	Prepare();

	// 컴포넌트 생성
	{
		Movement = CreateComponent<InGameMovementComponent>();
		Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
		Animation->SetMonsterName("Bulldog");

		// Collision
		Collision = CreateComponent<GameEngineCollision>();
		Collision->SetParent(this);
		Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
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

	GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
	Renderer->ScaleToTexture();
	UpdateState();
	if (false == MoveDirection.CompareInt2D(float4::ZERO))
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
	}
}

void Bulldog::UpdateState()
{
	if (true == Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D,
		std::bind(&Bulldog::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2)))
	{					
		SetHP(GetHP() - 1);
		TakeDamage();
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
	if (DirecitonChangeOn == true)
	{
		Renderer->GetTransform().PixLocalNegativeX();
		GetTransform().SetLocalPosition(float4{ 50,-500 });
		SetState(InGameMonsterState::PrepareAttack1);
	}
	else
	{
		Renderer->GetTransform().PixLocalPositiveX();
		GetTransform().SetLocalPosition(float4{ 1230,-500 });
		SetState(InGameMonsterState::PrepareAttack1);
	}

}

void Bulldog::PrepareAttack2()
{
	DirectionChangeOnOffSwitch();
	if (DirecitonChangeOn == false)
	{
		Renderer->GetTransform().PixLocalNegativeX();
		GetTransform().SetLocalPosition(float4{ 1180, 250 });
		SetState(InGameMonsterState::PrepareAttack2);
	}
	else
	{
		Renderer->GetTransform().PixLocalPositiveX();
		GetTransform().SetLocalPosition(float4{ 100, 250 });
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
	// Movementcomponent로 위로 이동 시키기
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
		Renderer->SetPivot(PIVOTMODE::LEFT);
		PrepareAttack1();
	}
	else if (Attack1On == false)
	{
		Renderer->SetPivot(PIVOTMODE::BOT);
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
	Renderer->SetPivot(PIVOTMODE::BOT);
	Mount();
}

void Bulldog::OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	//FrameAnimation_DESC& Info = const_cast<FrameAnimation_DESC&>(_Info);
	//Info.Inter = 0.5;



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
		MoveSpeed = 100.0f;
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

void Bulldog::OnPrePareAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 1)
	{
		StartPos = GetTransform().GetLocalPosition();
		EndPos = float4(GetTransform().GetLocalPosition().x, GetTransform().GetLocalPosition().y - 820);
		MoveSpeed = 110.0f;
		Plane = nullptr;
		MoveToEndPos(StartPos, EndPos, Plane);
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

void Bulldog::OnAttackFinish2AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 1)
	{
		StartPos = GetTransform().GetLocalPosition();
		EndPos = float4(GetTransform().GetLocalPosition().x, 100);
		MoveSpeed = 1000.0f;
		Plane = nullptr;
		MoveToEndPos(StartPos, EndPos, Plane);
	}
}
