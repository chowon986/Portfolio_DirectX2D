#include "PreCompile.h"
#include "Pig.h"
#include "Enums.h"

Pig::Pig()
{
}

Pig::~Pig()
{
}

void Pig::SetState(PigState _State)
{
	State = _State;
}

PigState Pig::GetState()
{
	return PigState();
}

void Pig::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Welcome", FrameAnimation_DESC("PigWelcome", 0.05f, false));
	Renderer->CreateFrameAnimationFolder("Start", FrameAnimation_DESC("PigWelcome",0,0, 0.05f, false));
	Renderer->GetTransform().SetLocalScale({ 424,389,1 });
	Renderer->GetTransform().SetLocalPosition({ 0,155,(int)ZOrder::UI + 2 });
	Renderer->ChangeFrameAnimation("Start");
	
	//Renderer->AnimationBindEnd 바이하면
}

void Pig::Update(float _DeltaTime)
{
	//GEngine::ChangeLevel("WorldMap");
}

void Pig::Talk()
{
}

void Pig::Idle()
{
}
