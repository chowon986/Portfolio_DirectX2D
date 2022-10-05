#include "PreCompile.h"
#include "BulldogPlanePuff.h"

BulldogPlanePuff::BulldogPlanePuff()
	: Boss(nullptr)
	, Renderer(nullptr)
	, Direction(float4::ZERO)
	, Speed(0.0f)
{
}

BulldogPlanePuff::~BulldogPlanePuff()
{
}

void BulldogPlanePuff::OnPuffAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}

void BulldogPlanePuff::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("BulldogPlanePuffA", FrameAnimation_DESC("BulldogPlanePuffA", 0.03f, true));
	Renderer->CreateFrameAnimationFolder("BulldogPlanePuffB", FrameAnimation_DESC("BulldogPlanePuffB", 0.03f, true));
	Renderer->AnimationBindEnd("BulldogPlanePuffA", std::bind(&BulldogPlanePuff::OnPuffAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("BulldogPlanePuffB", std::bind(&BulldogPlanePuff::OnPuffAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->SetPivot(PIVOTMODE::CENTER);
	SetSpeed(200.0f);
}

void BulldogPlanePuff::Update(float _DeltaTime)
{
	GetTransform().SetWorldMove(Direction * Speed * _DeltaTime);
}

void BulldogPlanePuff::End()
{
}