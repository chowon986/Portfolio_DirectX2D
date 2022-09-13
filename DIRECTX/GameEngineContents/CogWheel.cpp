#include "PreCompile.h"
#include "CogWheel.h"
#include "InGameMovementComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

CogWheel::CogWheel()
	: Renderer(nullptr)
	, State(InGameMonsterState::Idle)
	, AttackState(InGameMonsterAttackState::None)
	, Collision(nullptr)
{
}

CogWheel::~CogWheel()
{
}

void CogWheel::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("CogWheelIntro", FrameAnimation_DESC("BulldogIdle", 0.1f));
	Renderer->CreateFrameAnimationFolder("CogWheelAttack1", FrameAnimation_DESC("BulldogIdle", 0.1f));
	Renderer->AnimationBindFrame("CogWheelAttack1", std::bind(&CogWheel::Test, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("CogWheelAttack1");

	SetRenderer(Renderer);

	InGameMovementComponent* Movement = CreateComponent<InGameMovementComponent>();
	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("CogWheel");
	MoveDirection = float4::RIGHT;
}

void CogWheel::Update(float _DeltaTime)
{
	GameEngineTextureRenderer* CollisionMap = GetLevel()->GetMainColMapImage();
	if (CollisionMap == nullptr)
	{
		return;
	}

	GameEngineTexture* ColMapTexture = CollisionMap->GetCurTexture();
	if (ColMapTexture == nullptr)
	{
		return;
	}

	if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x - 10, -GetTransform().GetWorldPosition().y).CompareInt4D(float4::BLACK))
	{
		MoveDirection = float4::RIGHT;
	}
	else if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x + 10, -GetTransform().GetWorldPosition().y).CompareInt4D(float4::BLACK))
	{
		MoveDirection = float4::LEFT;
	}

	GetTransform().SetLocalMove(MoveDirection);
}

void CogWheel::TakeDamage()
{
	SetState(InGameMonsterState::TakeDamage);
}

void CogWheel::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void CogWheel::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void CogWheel::Shoot()
{
	//SetState(InGameMonsterState::Attack5);
	//SetAttackState(InGameMonsterAttackState::Attack5);
	SetState(InGameMonsterState::Attack1);
	SetAttackState(InGameMonsterAttackState::Attack1);
}

void CogWheel::Die()
{
	SetState(InGameMonsterState::Die);
}

void CogWheel::Test(const FrameAnimation_DESC& _Info)
{
}
