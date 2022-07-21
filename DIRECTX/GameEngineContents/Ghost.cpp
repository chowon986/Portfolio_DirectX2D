#include "PreCompile.h"
#include "Ghost.h"

Ghost::Ghost()
{
}

Ghost::~Ghost()
{
}

void Ghost::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Ghost", FrameAnimation_DESC("Ghost", 0.1f));
	Renderer->ChangeFrameAnimation("Ghost");
	Renderer->GetTransform().SetLocalScale({ 114,98,100 });
	HandRenderer = CreateComponent<GameEngineTextureRenderer>();
	HandRenderer->CreateFrameAnimationFolder("GhostHand", FrameAnimation_DESC("GhostHand", 0.1f));
	HandRenderer->ChangeFrameAnimation("GhostHand");
	HandRenderer->GetTransform().SetLocalScale({ 32, 40, 100 });
	HandRenderer->GetTransform().SetLocalPosition({-30, 20, 100});
}

void Ghost::Update(float _DeltaTime)
{
}

void Ghost::Talk()
{
}

void Ghost::Idle()
{
}
