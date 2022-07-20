#include "PreCompile.h"
#include "Pickaxe.h"

Pickaxe::Pickaxe()
{
}

Pickaxe::~Pickaxe()
{
}

void Pickaxe::SetState(PickaxeState _State)
{
}

PickaxeState Pickaxe::GetState()
{
    return PickaxeState();
}

void Pickaxe::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Pickaxe", FrameAnimation_DESC("Pickaxe", 0.1f));
	Renderer->ChangeFrameAnimation("Pickaxe");
	Renderer->GetTransform().SetLocalScale({ 88,83,100 });
}

void Pickaxe::Update(float _DeltaTime)
{
}

void Pickaxe::Talk()
{
}

void Pickaxe::Idle()
{
}
