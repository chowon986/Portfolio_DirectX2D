#include "PreCompile.h"
#include "Bulldog.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "YarnballShooter.h"
#include "TattooShooter.h"

Bulldog::Bulldog()
	: Collision(nullptr)
	, Renderer(nullptr)
	, Movement(nullptr)
	, Animation(nullptr)
	, ElapsedTime(3.0f)
	, AttackIntervalTime(10.0f)
	, BeforePosition(float4::ZERO)
	, CountTimeOnOff(true)
	, DirecitonChangeOn(true)
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
	int RandomAttack = (rand() % 3);
	++RandomAttack;
	if (RandomAttack == 1)
	{
		Attack1On = true;
	}
	else
	{
		Attack1On = false;
	}
	return Attack1On;
}

void Bulldog::Start()
{
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

		Renderer->AnimationBindEnd("BulldogIntro", std::bind(&Bulldog::OnPrepareAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogUnmount", std::bind(&Bulldog::OnUnmountAnimationFinished, this, std::placeholders::_1));

		Renderer->AnimationBindEnd("BulldogPrepareAttack1", std::bind(&Bulldog::OnPrepareAttackAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogPrepareAttack2", std::bind(&Bulldog::OnPrepareAttackAnimationFinished, this, std::placeholders::_1));

		Renderer->AnimationBindEnd("BulldogAttack1", std::bind(&Bulldog::OnAttackAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogAttack2", std::bind(&Bulldog::OnAttackAnimationFinished, this, std::placeholders::_1));

		Renderer->AnimationBindEnd("BulldogAttackFinish1", std::bind(&Bulldog::OnAttackFinishAnimationFinished, this, std::placeholders::_1));
		Renderer->AnimationBindEnd("BulldogAttackFinish2", std::bind(&Bulldog::OnAttackFinishAnimationFinished, this, std::placeholders::_1));

		Renderer->AnimationBindEnd("BulldogMount", std::bind(&Bulldog::OnBulldogMountAnimationFinished, this, std::placeholders::_1));

		Renderer->AnimationBindFrame("BulldogAttack1", std::bind(&Bulldog::OnAttack1AnimationFrameChanged, this, std::placeholders::_1));
		Renderer->AnimationBindFrame("BulldogAttack2", std::bind(&Bulldog::OnAttack2AnimationFrameChanged, this, std::placeholders::_1));

		Renderer->CreateFrameAnimationFolder("BulldogDie", FrameAnimation_DESC("BulldogDie", 0.1f));
		Renderer->AnimationBindEnd("BulldogDie", std::bind(&Bulldog::BulldogDieCheck, this, std::placeholders::_1));
		Renderer->ChangeFrameAnimation("BulldogIntro");
		Renderer->ScaleToTexture();
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

	// 시작 위치 세팅
	SetBeforePosition({ 640, 50, (int)ZOrder::NPC });
	SetAttackState(InGameMonsterAttackState::None);
}

void Bulldog::Update(float _DeltaTime)
{
	if (CountTimeOnOff == true)
	{
		ElapsedTime += _DeltaTime;
	}

	GameEngineDebug::DrawBox(Collision->GetTransform(), {1.0f, 0.0f,0.0f, 0.5f});
	Renderer->ScaleToTexture();
	UpdateState();
}

void Bulldog::UpdateState()
{
	if (GetHP() <= 0)
	{
		Die();
	}

	if (true == Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D,
		std::bind(&Bulldog::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2)))
	{
		SetHP(GetHP() - 1);
		TakeDamage();
	}

	if (ElapsedTime >= AttackIntervalTime)
	{
		ElapsedTime = 0.0f;
		CountTimeOnOff = false;
		Unmount();
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
	CountTimeOnOff = true;

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
		Renderer->SetPivot(PIVOTMODE::LEFTCENTER);
		Renderer->GetTransform().PixLocalNegativeX();
		GetTransform().SetLocalPosition(float4{ 80,-500 });
		SetState(InGameMonsterState::PrepareAttack1);
	}
	else
	{
		Renderer->SetPivot(PIVOTMODE::LEFTCENTER);
		Renderer->GetTransform().PixLocalPositiveX();
		GetTransform().SetLocalPosition(float4{ 1200,-500 });
		SetState(InGameMonsterState::PrepareAttack1);
	}

}

void Bulldog::PrepareAttack2()
{
	DirectionChangeOnOffSwitch();
	if (DirecitonChangeOn == false)
	{
		Renderer->GetTransform().PixLocalNegativeX();
		GetTransform().SetLocalPosition(float4{ 1180, 0 });
		SetState(InGameMonsterState::PrepareAttack2);
	}
	else
	{
		Renderer->GetTransform().PixLocalPositiveX();
		GetTransform().SetLocalPosition(float4{ 100, 0});
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
	GetTransform().SetLocalPosition({GetBeforePosition().x, 50});
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
		PrepareAttack1();
	}
	else
	{
		Renderer->SetPivot(PIVOTMODE::BOT);
		PrepareAttack2();
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


void Bulldog::OnAttackAnimationFinished(const FrameAnimation_DESC& _Info)
{
	FinishAttack();
}

void Bulldog::OnAttackFinishAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->SetPivot(PIVOTMODE::BOT);
	Mount();
	ElapsedTime = 0.0f;
}

void Bulldog::OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 2)
	{
		SetAttackState(InGameMonsterAttackState::YarnBall1);
	}
	else if (_Info.CurFrame == 8)
	{
		SetAttackState(InGameMonsterAttackState::YarnBall2);
	}
	else if (_Info.CurFrame == 14)
	{
		SetAttackState(InGameMonsterAttackState::YarnBall3);
	}
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}

void Bulldog::OnAttack2AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 2)
	{
		SetAttackState(InGameMonsterAttackState::Tatto1);
	}
	else if (_Info.CurFrame == 11)
	{
		SetAttackState(InGameMonsterAttackState::Tatto1);
	}
	else if (_Info.CurFrame == 29)
	{
		SetAttackState(InGameMonsterAttackState::Tatto1);
	}
	else
	{
		SetAttackState(InGameMonsterAttackState::None);
	}
}

void Bulldog::OnBulldogMountAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Idle();
}
