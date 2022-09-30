#include "PreCompile.h"
#include "GlassPlatform.h"
#include <GameEngineBase/GameEngineRandom.h>

GlassPlatform::GlassPlatform()
	: Renderer(nullptr)
	, StartPos()
	, IsOnGround(false)
{
}

GlassPlatform::~GlassPlatform()
{
}

void GlassPlatform::Start()
{
	StartPos.push_back({ 640.0f, 30.0f, (int)ZOrder::Background - 3 });
	StartPos.push_back({ 300.0f, 30.0f, (int)ZOrder::Background - 3 });
	StartPos.push_back({ 940.0f, 30.0f, (int)ZOrder::Background - 3 });

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("GlassPlatform0", FrameAnimation_DESC("GlassPlatformA", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("GlassPlatform1", FrameAnimation_DESC("GlassPlatformB", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("GlassPlatform2", FrameAnimation_DESC("GlassPlatformC", 0.07f, false));

	Renderer->SetScaleModeImage();

	Collision = CreateComponent<GameEngineCollision>();
	Collision->ChangeOrder(ObjectOrder::GROUND);
	float4 RendererWorldScale = Renderer->GetTransform().GetWorldScale();
	Collision->GetTransform().SetWorldScale({ RendererWorldScale.x, RendererWorldScale.y, 1.0f });
	Collision->GetTransform().SetLocalPosition(float4::ZERO);
}

void GlassPlatform::Update(float _DeltaTime)
{
	if (GetTransform().GetWorldPosition().y < -800 && IsOnGround == false)
	{
		IsOnGround = true;
		int RandomNum = GameEngineRandom::MainRandom.RandomInt(0, 2);
		GetTransform().SetWorldPosition(StartPos[GetPositionNum()]);
		Renderer->ChangeFrameAnimation("GlassPlatform" + std::to_string(RandomNum));
		IsOnGround = false;
	}

	if (false == IsOnGround)
	{
		GetTransform().SetWorldMove(float4::DOWN * _DeltaTime * 300);
	}
}

void GlassPlatform::End()
{
}
