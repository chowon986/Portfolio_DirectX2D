#include "PreCompile.h"
#include "Bulldog.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMonsterMovementComponent.h"

Bulldog::Bulldog()
	: Collision(nullptr)
	, Renderer(nullptr)
	, Movement(nullptr)
	, Animation(nullptr)
	, HP(5)
	, ElapsedTime(-5.0f)
	, AttackIntervalTime(10.0f)
{
}

Bulldog::~Bulldog()
{
}

void Bulldog::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("BulldogIntro", FrameAnimation_DESC("BulldogIntro", 0.1f));
	Renderer->AnimationBindEnd("BulldogIntro", std::bind(&Bulldog::SetStateIdle, this, std::placeholders::_1));
	Renderer->CreateFrameAnimationFolder("BulldogIdle", FrameAnimation_DESC("BulldogIdle", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogAttack", FrameAnimation_DESC("BulldogAttack", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogCatgunIntro", FrameAnimation_DESC("BulldogCatgunIntro", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogCatgunIdle", FrameAnimation_DESC("BulldogCatgunIdle", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogCatgunShoot", FrameAnimation_DESC("BulldogCatgunShoot", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogCatgunExit", FrameAnimation_DESC("BulldogCatgunExit", 0.1f));
	Renderer->ChangeFrameAnimation("BulldogIntro");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::BOT);
	SetRenderer(Renderer);
	Prepare();

	Movement = CreateComponent<InGameMonsterMovementComponent>();
	Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("Bulldog");

	// Collision
	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER);
}

void Bulldog::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	UpdateState();

	ElapsedTime += _DeltaTime;

	if (GetAttackState() == InGameMonsterAttackState::Attack)
	{
		GetTransform().SetWorldMove(float4::UP * _DeltaTime * 200); 
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
		TakeDamage();
	}

	if (ElapsedTime >= AttackIntervalTime)
	{
		ElapsedTime = 0.0f;
		Shoot();
	}

	if (GetState() != InGameMonsterState::TakeDamage &&
		GetState() != InGameMonsterState::Die &&
		GetAttackState() != InGameMonsterAttackState::Attack &&
		GetState() != InGameMonsterState::Prepare)
	{
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
	SetAttackState(InGameMonsterAttackState::Attack);
	//SetAttackState(InGameMonsterAttackState::None);
}

void Bulldog::Die()
{
	SetState(InGameMonsterState::Die);
}

void Bulldog::SetStateIdle(const FrameAnimation_DESC& _Info)
{
	SetState(InGameMonsterState::Idle);
}

bool Bulldog::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return false;
}
