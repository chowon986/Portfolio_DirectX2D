#include "PreCompile.h"
#include "ShellWeDance.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "ShellWeDancePhysicsComponent.h"
#include "SaltBakerLevel.h"
#include "CogWheel.h"

ShellWeDance::ShellWeDance()
	: Renderer(nullptr)
	, State(InGameMonsterState::Idle)
	, AttackState(InGameMonsterAttackState::None)
	, Collision(nullptr)
	, Wheel(nullptr)
	, Physics(nullptr)
	, CurAnimationName("")
	, BeforeMoveDirection(float4::ZERO)
{
}

ShellWeDance::~ShellWeDance()
{
}

void ShellWeDance::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("ShellWeDanceIntro", FrameAnimation_DESC("ShellWeDanceIntro", 0.05f));
	Renderer->CreateFrameAnimationFolder("ShellWeDanceDie", FrameAnimation_DESC("ShellWeDanceDeath", 0.05f));
	Renderer->CreateFrameAnimationFolder("ShellWeDanceIdle", FrameAnimation_DESC("ShellWeDanceIdle", 0.05f));
	Renderer->CreateFrameAnimationFolder("ShellWeDanceAttack1", FrameAnimation_DESC("ShellWeDanceLand", 0.05f));

	Renderer->AnimationBindFrame("ShellWeDanceIntro", std::bind(&ShellWeDance::OnShellWeDanceIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ShellWeDanceDie", std::bind(&ShellWeDance::OnShellWeDanceDeathAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("ShellWeDanceAttack1", std::bind(&ShellWeDance::OnShellWeDanceAttack1AnimationFrameChanged, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->SetPivot(PIVOTMODE::BOT);

	Renderer->ChangeFrameAnimation("ShellWeDanceIntro");

	SetRenderer(Renderer);

	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("ShellWeDance");
	MoveDirection = float4::ZERO;

	SetState(InGameMonsterState::Prepare);
}

void ShellWeDance::Update(float _DeltaTime)
{
	if (GetHP() <= 0)
	{
		//SetState(InGameMonsterState::Die);
		//if (nullptr != Wheel)
		//{
		//	Wheel->SetState(InGameMonsterState::Die); //ph3 완성되면 주석 풀기
		//}
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

	if (GetState() == InGameMonsterState::Prepare)
	{
		MoveDirection = float4::ZERO;
	}

	if (GetState() == InGameMonsterState::Idle)
	{
		if (nullptr != Physics)
		{
			if (Physics->IsOnGround == true)
			{
				if (MoveDirection.CompareInt3D(float4::ZERO))
				{
					MoveDirection = float4::RIGHT * 2.5;
				}

				BeforeMoveDirection = MoveDirection;
				MoveDirection = float4::ZERO;
				Shoot();
			}

		}
	}

	if (true == ColMapTexture->GetPixelToFloat4(static_cast<int>(GetTransform().GetWorldPosition().x - 65.0f), static_cast<int>(-GetTransform().GetWorldPosition().y)).CompareInt4D(float4::BLUE))
	{
		MoveDirection = float4::RIGHT * 2.5;
	}
	else if (true == ColMapTexture->GetPixelToFloat4(static_cast<int>(GetTransform().GetWorldPosition().x + 65.0f), static_cast<int>( - GetTransform().GetWorldPosition().y)).CompareInt4D(float4::BLUE))
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
	SetCurAnimationName("ShellWeDanceIdle");
}

void ShellWeDance::Shoot()
{
	SetState(InGameMonsterState::Attack1);
	SetCurAnimationName("ShellWeDanceAttack1");
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

void ShellWeDance::OnShellWeDanceIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 65)
	{
		GetTransform().SetWorldPosition({ 640.0f, 50.0f });
		SetState(InGameMonsterState::Idle);
		if (nullptr == Physics)
		{
			Physics = CreateComponent<ShellWeDancePhysicsComponent>();
		}
	}
}

void ShellWeDance::OnShellWeDanceAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 2)
	{
		if (nullptr != Physics)
		{
			Idle();
			MoveDirection = BeforeMoveDirection;
			Physics->Reset();
			Physics->AddForce(60);
			Physics->IsOnGround = false;
		}
	}
}

