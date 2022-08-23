#include "PreCompile.h"
#include "IInGameCharacterBase.h"

IInGameCharacterBase::IInGameCharacterBase()
	: State(InGameCharacterState::Idle)
	, Renderer(nullptr)
	, VerticalDir("Center")
	, HorizontalDir("Center")
	, IsOnGround(false)
	, HP(0)
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

void IInGameCharacterBase::Start()
{
	RedDogBowlCollsion = CreateComponent<GameEngineCollision>();
	RedDogBowlCollsion->GetTransform().SetLocalScale({ 7200.0f, 100.0f, 1.0f });
	RedDogBowlCollsion->ChangeOrder((int)ObjectOrder::TRACKING1);

	YellowDogBowlCollsion = CreateComponent<GameEngineCollision>();
	YellowDogBowlCollsion ->GetTransform().SetLocalScale({ 7200.0f, 100.0f, 1.0f });
	YellowDogBowlCollsion ->ChangeOrder((int)ObjectOrder::TRACKING2);
}

void IInGameCharacterBase::Update(float _Delta)
{
	GameEngineDebug::DrawBox(RedDogBowlCollsion->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
	GameEngineDebug::DrawBox(YellowDogBowlCollsion->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void IInGameCharacterBase::SetState(InGameCharacterState _State)
{
	if (State != _State)
	{
		State = _State;
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

