#include "PreCompile.h"
#include "Tornado.h"
#include "SaltBakerHeart.h"

Tornado::Tornado()
{
}

Tornado::~Tornado()
{
}

void Tornado::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("TornadoIdle", FrameAnimation_DESC("TornadoIdle", 0.05f, true));

	Renderer->ChangeFrameAnimation("TornadoIdle");
	Renderer->SetScaleModeImage();
	Renderer->SetPivot(PIVOTMODE::TOP);
	Renderer->GetTransform().SetWorldPosition({ 0.0, 720.0f });

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetWorldScale({ 100.0f,720.0f,1.0f });
	Collision->GetTransform().SetLocalPosition({ 0.0f, 360.0f });

	SetState(TornadoState::Intro);
}

void Tornado::Update(float _DeltaTime)
{
	if (GetState() == TornadoState::Intro)
	{
		if (Renderer->GetTransform().GetWorldPosition().y <= 10)
		{
			SetState(TornadoState::Move);
			SaltBakerHeart* Ph4Boss = GetLevel()->CreateActor<SaltBakerHeart>();
			Ph4Boss->GetTransform().SetWorldPosition({ 640.0f,-400.0f });
			return;
		}
		GetTransform().SetWorldMove(float4::DOWN * _DeltaTime * 400);
	}

	else if (GetState() == TornadoState::Move)
	{
		float4 DirectionToCenter = (GetTransform().GetWorldPosition().x - 720.0f) > 0 ? float4::LEFT : float4::RIGHT;
		GetTransform().SetWorldMove(DirectionToCenter * _DeltaTime * 3);
	}
}

void Tornado::End()
{
}