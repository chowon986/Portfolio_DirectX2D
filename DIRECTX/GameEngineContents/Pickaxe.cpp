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
	Renderer->CreateFrameAnimationFolder("Pickaxe", FrameAnimation_DESC("NPCPickaxe", 0.1f));
	Renderer->ChangeFrameAnimation("Pickaxe");
	Renderer->GetTransform().SetLocalScale({ 88,83,1 });
	Renderer->SetPivot(PIVOTMODE::CENTER);
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
