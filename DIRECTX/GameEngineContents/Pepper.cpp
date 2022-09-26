#include "PreCompile.h"
#include "Pepper.h"
#include "PepperShooter.h"
#include "InGameMovementComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

Pepper::Pepper()
	: Renderer(nullptr)
	, State(InGameMonsterState::Idle)
	, AttackState(InGameMonsterAttackState::None)
	, Collision(nullptr)
{
}

Pepper::~Pepper()
{
}

void Pepper::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PepperIntro", FrameAnimation_DESC("BulldogIdle", 0.1f));
	Renderer->CreateFrameAnimationFolder("PepperIdle", FrameAnimation_DESC("BulldogIdle", 0.1f));
	Renderer->CreateFrameAnimationFolder("PepperAttack2", FrameAnimation_DESC("BulldogAttack1", 0.1f));
	Renderer->AnimationBindFrame("PepperAttack2", std::bind(&Pepper::Test, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("PepperAttack2");

	SetRenderer(Renderer);

	InGameMovementComponent* Movement = CreateComponent<InGameMovementComponent>();
	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("Pepper");

	// �� ����
	{
		PepperShooter* PepperGun = GetLevel()->CreateActor<PepperShooter>();
		PepperGun->SetParent(this);
	}

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 300.0f, 500.0f, 1.0f });
	Collision->GetTransform().SetLocalPosition({ 0.0f, 300.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER);

	SetHP(5);
}

void Pepper::Update(float _DeltaTime)
{
	float4 MoveDirection = Monster->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
	if (abs(MoveDirection.x) <= 0.1 && abs(MoveDirection.y) <= 0.1)
	{
		AttackDirection = float4::ZERO;
		// ���ư��� ���·� �ٲ۴�
	}
	GetTransform().SetWorldMove(AttackDirection);

	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D,
	std::bind(&Pepper::OnTakeDamage, this, std::placeholders::_1, std::placeholders::_2));
}

CollisionReturn Pepper::OnTakeDamage(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	SetHP(GetHP() - 1);

	return CollisionReturn::Break;
}

void Pepper::TakeDamage()
{
	SetState(InGameMonsterState::TakeDamage);
}

void Pepper::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void Pepper::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void Pepper::Shoot()
{
	//SetState(InGameMonsterState::Attack5);
	//SetAttackState(InGameMonsterAttackState::Attack5);
	SetState(InGameMonsterState::Attack2);
	SetAttackState(InGameMonsterAttackState::Attack2);
}

void Pepper::Die()
{
	SetState(InGameMonsterState::Die);
}

void Pepper::Test(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 3)
	{
		Shoot();
		if (Monster != nullptr)
		{
			float4 MoveDirection = Monster->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
			MoveDirection.Normalize();
			AttackDirection = MoveDirection;
			// �ݸ����� �΋H���� movedirection = 0;
		}
	}
}
