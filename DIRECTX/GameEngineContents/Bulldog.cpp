#include "PreCompile.h"
#include "Bulldog.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMovementComponent.h"
#include "BulldogShooter.h"

Bulldog::Bulldog()
	: Collision(nullptr)
	, Renderer(nullptr)
	, Movement(nullptr)
	, Animation(nullptr)
	, ElapsedTime(5.0f)
	, AttackIntervalTime(10.0f)
	, AttackInProgress(false)
	, BeforePosition(float4::ZERO)
	, OnCountTime(true)
{
}

Bulldog::~Bulldog()
{
}

void Bulldog::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("BulldogIntro", FrameAnimation_DESC("BulldogIntro", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogIdle", FrameAnimation_DESC("BulldogIdle", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogUnmount", FrameAnimation_DESC("BulldogUnmount", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogPrepareAttack1", FrameAnimation_DESC("BulldogPrepareAttack1", 0.1f)); // Catgun
	//Renderer->CreateFrameAnimationFolder("BulldogPrepareAttack2", FrameAnimation_DESC("BulldogPrepareAttack2", 0.1f)); // Tattoo
	Renderer->CreateFrameAnimationFolder("BulldogAttack1", FrameAnimation_DESC("BulldogAttack1", 0.1f)); // Catgun
	Renderer->CreateFrameAnimationFolder("BulldogAttackFinish1", FrameAnimation_DESC("BulldogAttackFinish1", 0.1f)); // Catgun
	//Renderer->CreateFrameAnimationFolder("BulldogAttack2", FrameAnimation_DESC("BulldogAttack2", 0.1f)); // Tattoo
	Renderer->CreateFrameAnimationFolder("BulldogMount", FrameAnimation_DESC("BulldogMount", 0.1f));

	Renderer->AnimationBindEnd("BulldogIntro", std::bind(&Bulldog::OnPrepareAnimationFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("BulldogUnmount", std::bind(&Bulldog::OnUnmountAnimationFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("BulldogPrepareAttack1", std::bind(&Bulldog::OnPrepareAttack1AnimationFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("BulldogAttack1", std::bind(&Bulldog::OnAttack1AnimationFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("BulldogAttackFinish1", std::bind(&Bulldog::OnAttackFinish1AnimationFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("BulldogMount", std::bind(&Bulldog::OnBulldogMountAnimationFinished, this, std::placeholders::_1));

	Renderer->AnimationBindFrame("BulldogAttack1", std::bind(&Bulldog::OnAttack1AnimationFrameChanged, this, std::placeholders::_1));
	
	Renderer->CreateFrameAnimationFolder("BulldogDie", FrameAnimation_DESC("BulldogDie", 0.1f));
	Renderer->AnimationBindEnd("BulldogDie", std::bind(&Bulldog::BulldogDieCheck, this, std::placeholders::_1));
	Renderer->ChangeFrameAnimation("BulldogIntro");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::BOT);
	SetRenderer(Renderer);
	Prepare();

	Movement = CreateComponent<InGameMovementComponent>();
	Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("Bulldog");

	// Collision
	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER);

	SetHP(5);

	BulldogShooter* Shooter = GetLevel()->CreateActor<BulldogShooter>();
	Shooter->SetParent(this);

	SetBeforePosition({ 640, 100, (int)ZOrder::NPC });
}

void Bulldog::Update(float _DeltaTime)
{
	GameEngineDebug::DrawBox(Collision->GetTransform(), {1.0f, 0.0f,0.0f, 0.5f});

	Renderer->ScaleToTexture();
	UpdateState();
	if (OnCountTime == true)
	{
		ElapsedTime += _DeltaTime;
	}

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
		OnCountTime = false;
		Unmount();
	}

	if (GetState() != InGameMonsterState::TakeDamage &&
		GetState() != InGameMonsterState::Die &&
		GetState() != InGameMonsterState::Prepare &&
		AttackInProgress == false)
	{
		OnCountTime = true;
		Idle();
	}
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
	SetState(InGameMonsterState::Attack1);
}

void Bulldog::Die()
{
	SetState(InGameMonsterState::Die);
}

void Bulldog::PrepareAttack()
{
	// 좌우 위치 번갈아가며 변경
	SetBeforePosition({ GetTransform().GetLocalPosition().x, GetTransform().GetLocalPosition().y + 100 });
	GetTransform().SetLocalPosition(float4{ 1200,-500 });
	SetState(InGameMonsterState::PrepareAttack1);
}

void Bulldog::Unmount()
{
	AttackInProgress = true;
	SetState(InGameMonsterState::Unmount);
}

void Bulldog::Mount()
{
	SetState(InGameMonsterState::Mount);
}

void Bulldog::FinishAttack()
{
	// Movementcomponent로 위로 이동 시키기
	SetAttackState(InGameMonsterAttackState::None);
	SetState(InGameMonsterState::AttackFinish1);
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
	Renderer->SetPivot(PIVOTMODE::LEFTCENTER);
	PrepareAttack();
}

void Bulldog::OnPrepareAttack1AnimationFinished(const FrameAnimation_DESC& _Info)
{
	Shoot();
}

void Bulldog::OnAttack1AnimationFinished(const FrameAnimation_DESC& _Info)
{
	FinishAttack();
}

void Bulldog::OnAttackFinish1AnimationFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->SetPivot(PIVOTMODE::BOT);
	Mount();
	ElapsedTime = 0.0f;

}

void Bulldog::OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 3)
	{
		SetAttackState(InGameMonsterAttackState::Shoot1);
		// 몬스터의 이미지 x값에따라 좌 우로 이동하는 총, 총알, 총알이동컴포넌트
	}

}

void Bulldog::OnBulldogMountAnimationFinished(const FrameAnimation_DESC& _Info)
{
	AttackInProgress = false;
}
