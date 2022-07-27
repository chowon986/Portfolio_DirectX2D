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
	Renderer->GetTransform().SetLocalScale({ 114,98,1 });
	Renderer->SetPivot(PIVOTMODE::CENTER);
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
