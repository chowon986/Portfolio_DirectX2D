#include "PreCompile.h"
#include "Bakery.h"

Bakery::Bakery()
{
}

Bakery::~Bakery()
{
}

void Bakery::Start()
{
	PortalBase::Start();

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Bakery", FrameAnimation_DESC("Bakery", 0.1f));
	Renderer->ChangeFrameAnimation("Bakery");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 200.0f, 350.0f, 1.0f });
}

void Bakery::Update(float _DeltaTime)
{
	Collision->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PC, CollisionType::CT_AABB2D, std::bind(&Bakery::OnPortalCollision, this, std::placeholders::_1, std::placeholders::_2));
}

void Bakery::End()
{
}

CollisionReturn Bakery::OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (true == GameEngineInput::GetInst()->IsDown("EnterMap"))
	{
		GEngine::ChangeLevel("Bakery");
	}

	return CollisionReturn::ContinueCheck;
}