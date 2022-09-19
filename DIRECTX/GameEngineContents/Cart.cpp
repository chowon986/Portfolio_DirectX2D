#include "PreCompile.h"
#include "Cart.h"

Cart::Cart()
{
}

Cart::~Cart()
{
}

void Cart::Start()
{
	PortalBase::Start();

	Renderer->GetTransform().SetLocalScale({ 176,179,1 });
	Renderer->CreateFrameAnimationFolder("Cart", FrameAnimation_DESC("Cart", 0.1f));
	Renderer->ChangeFrameAnimation("Cart");
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
}

void Cart::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);
}

void Cart::End()
{
}

CollisionReturn Cart::OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst()->IsDown("EnterMap"))
	{
		GEngine::ChangeLevel("Tutorial");
	}
	return CollisionReturn::ContinueCheck;
}