#include "PreCompile.h"
#include "CogWheel.h"
#include "CogWheelDust.h"
#include "InGameMovementComponent.h"
#include "InGameMonsterAnimationControllerComponent.h"

CogWheel::CogWheel()
	: Renderer(nullptr)
	, State(InGameMonsterState::None)
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
	Renderer->CreateFrameAnimationFolder("CogWheelIntro", FrameAnimation_DESC("CogWheelIntro", 0.05f));
	Renderer->CreateFrameAnimationFolder("CogWheelAlternate", FrameAnimation_DESC("CogWheelAlternate", 0.05f));
	Renderer->CreateFrameAnimationFolder("CogWheelIdle", FrameAnimation_DESC("CogWheelIdle", 0.05f));
	Renderer->CreateFrameAnimationFolder("CogWheelTurn", FrameAnimation_DESC("CogWheelTurn", 0.05f));
	Renderer->CreateFrameAnimationFolder("CogWheelDie", FrameAnimation_DESC("CogWheelTurn", 0.05f));

	Renderer->AnimationBindFrame("CogWheelIntro", std::bind(&CogWheel::OnCogWheelIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("CogWheelAlternate", std::bind(&CogWheel::OnCogWheelAlternateAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("CogWheelTurn", std::bind(&CogWheel::OnCogWheelTurnAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("CogWheelDie", std::bind(&CogWheel::OnCogWheelDeathAnimationFrameChanged, this, std::placeholders::_1));

	Renderer->SetScaleModeImage();
	Renderer->ChangeFrameAnimation("CogWheelIntro");
	Renderer->SetPivot(PIVOTMODE::BOT);

	SetRenderer(Renderer);

	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("CogWheel");
	MoveDirection = float4::RIGHT;
	SetState(InGameMonsterState::Prepare);

	Dust = GetLevel()->CreateActor<CogWheelDust>();
	Dust->SetBoss(this);
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

	if (GetState() == InGameMonsterState::Prepare)
	{
		MoveDirection = float4::ZERO;
		return;
	}
	if (GetState() == InGameMonsterState::Alternate)
	{
		if (MoveDirection.CompareInt3D(float4::ZERO))
		{
			MoveDirection = float4::RIGHT;
		}
	}

	if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x - 50, -GetTransform().GetWorldPosition().y).CompareInt4D(float4::BLACK))
	{
		SetState(InGameMonsterState::Turn);
		MoveDirection = float4::RIGHT;
	}
	else if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x + 50, -GetTransform().GetWorldPosition().y).CompareInt4D(float4::BLACK))
	{
		SetState(InGameMonsterState::Turn);
		MoveDirection = float4::LEFT;
	}

	if (GetState() == InGameMonsterState::Alternate || GetState() == InGameMonsterState::Idle)
	{
		if (MoveDirection.CompareInt3D(float4::RIGHT))
		{
			Renderer->GetTransform().PixLocalPositiveX();
		}
		else if (MoveDirection.CompareInt3D(float4::LEFT))
		{
			Renderer->GetTransform().PixLocalNegativeX();
		}
	}

	GetTransform().SetLocalMove(MoveDirection * _DeltaTime * 200);
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
}

void CogWheel::Die()
{
	SetState(InGameMonsterState::Die);
}

void CogWheel::OnCogWheelIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 20)
	{
		if (nullptr != Dust)
		{
			Dust->SetState(CogWheelDustState::Intro);
		}
	}

	if (_Info.CurFrame == 25)
	{
		SetState(InGameMonsterState::Alternate);
	}
}

void CogWheel::OnCogWheelAlternateAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 15)
	{
		SetState(InGameMonsterState::Idle);
	}
}

void CogWheel::OnCogWheelTurnAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 8)
	{
		SetState(InGameMonsterState::Alternate);
	}
}

void CogWheel::OnCogWheelDeathAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 19)
	{
		SetState(InGameMonsterState::Die);
	}
}

