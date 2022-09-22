#include "PreCompile.h"
#include "ShellWeDance.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "ShellWeDancePhysicsComponent.h"
#include "SaltBakerLevel.h"

ShellWeDance::ShellWeDance()
	: Renderer(nullptr)
	, State(InGameMonsterState::Idle)
	, AttackState(InGameMonsterAttackState::None)
	, Collision(nullptr)
{
}

ShellWeDance::~ShellWeDance()
{
}

void ShellWeDance::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("ShellWeDanceIntro", FrameAnimation_DESC("ShellWeDance", 0.05f));
	Renderer->CreateFrameAnimationFolder("ShellWeDanceAttack1", FrameAnimation_DESC("ShellWeDance", 0.05f));
	Renderer->CreateFrameAnimationFolder("ShellWeDanceDie", FrameAnimation_DESC("ShellWeDance", 0.05f));
	Renderer->AnimationBindFrame("ShellWeDanceDie", std::bind(&ShellWeDance::OnShellWeDanceDeathAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("ShellWeDanceAttack1");

	SetRenderer(Renderer);

	SetPhysicsComponent(CreateComponent<ShellWeDancePhysicsComponent>());

	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("ShellWeDance");
	MoveDirection = float4::RIGHT;
}

void ShellWeDance::Update(float _DeltaTime)
{
	if (GetHP() <= 0)
	{
		SetState(InGameMonsterState::Die);
	}

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

	if (Physics->IsOnGround == true)
	{
		Physics->Reset();
		Physics->AddForce(68);
		Physics->IsOnGround = false;
	}

	if (true == ColMapTexture->GetPixelToFloat4(static_cast<int>(GetTransform().GetWorldPosition().x - 65.0f), static_cast<int>(-GetTransform().GetWorldPosition().y)).CompareInt4D(float4::BLACK))
	{
		MoveDirection = float4::RIGHT * 2.5;
	}
	else if (true == ColMapTexture->GetPixelToFloat4(static_cast<int>(GetTransform().GetWorldPosition().x + 65.0f), static_cast<int>( - GetTransform().GetWorldPosition().y)).CompareInt4D(float4::BLACK))
	{
		MoveDirection = float4::LEFT * 2.5;
	}

	GetTransform().SetLocalMove(MoveDirection * _DeltaTime * 200);
}

void ShellWeDance::TakeDamage()
{
	SetState(InGameMonsterState::TakeDamage);
}

void ShellWeDance::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void ShellWeDance::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void ShellWeDance::Shoot()
{
	//SetState(InGameMonsterState::Attack5);
	//SetAttackState(InGameMonsterAttackState::Attack5);
	SetState(InGameMonsterState::Attack1);
	SetAttackState(InGameMonsterAttackState::Attack1);
}

void ShellWeDance::Die()
{
	SetState(InGameMonsterState::Die);
}

void ShellWeDance::OnShellWeDanceDeathAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 5)
	{
		Death();
		if (SaltBakerLevel* Level = dynamic_cast<SaltBakerLevel*>(GetLevel()))
		{
			Level->SetPhase(Phase::Phase4);
		}
	}
}