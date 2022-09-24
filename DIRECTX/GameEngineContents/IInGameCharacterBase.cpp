#include "PreCompile.h"
#include "IInGameCharacterBase.h"

IInGameCharacterBase::IInGameCharacterBase()
	: State(InGameCharacterState::Idle)
	, Renderer(nullptr)
	, VerticalDir("Center")
	, HorizontalDir("Center")
	, IsOnGround(false)
	, HP(0)
	, Gauge(0.0f)
	, MaxGauge(5)
{
}

IInGameCharacterBase::~IInGameCharacterBase()
{
}

void IInGameCharacterBase::SetAttackState(InGameCharacterAttackState _State)
{
	if (AttackState != _State)
	{
		AttackState = _State;
		AttackStateChangedDelegate.Invoke(AttackState);
	}
}

void IInGameCharacterBase::SetShooterState(InGameCharacterShooterState _State)
{
	if (ShooterState != _State)
	{
		ShooterState = _State;
		ShooterStateChangedDelegate.Invoke(ShooterState);
	}
}

void IInGameCharacterBase::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("Aim"))
	{
		GameEngineInput::GetInst()->CreateKey("Aim", 'A');
		GameEngineInput::GetInst()->CreateKey("Shoot", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("GaugeShoot", 'X');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_CONTROL);
		GameEngineInput::GetInst()->CreateKey("Dash", 'Z');
		GameEngineInput::GetInst()->CreateKey("ChangeGun", 'Q');
	}
}

void IInGameCharacterBase::Update(float _Delta)
{
}

void IInGameCharacterBase::OnStateChanged()
{
}

void IInGameCharacterBase::SetState(InGameCharacterState _State)
{
	if (State != _State)
	{
		State = _State;
		OnStateChanged();
		StateChangedDelegate.Invoke(State);
	}
}

void IInGameCharacterBase::SetVerticalDirection(std::string _Dir)
{
	if (VerticalDir != _Dir)
	{
		VerticalDir = _Dir;
		VerticalDirectionChangedDelegate.Invoke(VerticalDir);
	}
}

void IInGameCharacterBase::SetHorizontalDirection(std::string _Dir)
{
	if (HorizontalDir != _Dir)
	{
		HorizontalDir = _Dir;
		HorizontalDirectionChangedDelegate.Invoke(HorizontalDir);
	}
}

void IInGameCharacterBase::SetRenderer(GameEngineTextureRenderer* _Renderer)
{
	Renderer = _Renderer;
}

void IInGameCharacterBase::SetMainCollision(GameEngineCollision* _MainCollision)
{
	MainCollision = _MainCollision;
}

void IInGameCharacterBase::SetPhysicsComponent(PhysicsComponent* _Physics)
{
	Physics = _Physics;
}

void IInGameCharacterBase::SetIsOnGround(bool _IsOnGround)
{
	if (IsOnGround != _IsOnGround)
	{
		IsOnGround = _IsOnGround;
		IsOnGroundChangedDelegate.Invoke(IsOnGround);
	}
}

void IInGameCharacterBase::SetGauge(float _Gauge)
{
	if (Gauge != _Gauge)
	{
		Gauge = _Gauge;
		if (Gauge > MaxGauge)
		{
			Gauge = MaxGauge;
		}
	}
}

float IInGameCharacterBase::GetGauge()
{
	return Gauge;
}

int IInGameCharacterBase::GetMaxGauge()
{
	return MaxGauge;
}

