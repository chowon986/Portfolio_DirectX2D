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
	Renderer->CreateFrameAnimationFolder("Welcome", FrameAnimation_DESC("PigWelcome", 0.07f, false));
	Renderer->CreateFrameAnimationFolder("Bye", FrameAnimation_DESC("PigWelcome", 0.07f, false));
	Renderer->GetTransform().SetLocalScale({ 424,389,1 });
	Renderer->GetTransform().SetLocalPosition({ 0,155,(int)ZOrder::UI + 2 });
	Renderer->ChangeFrameAnimation("Welcome");
	
	Renderer->AnimationBindFrame("Bye", std::bind(&Pig::OnByeAnimationFrameChanged, this, std::placeholders::_1));
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

void Pig::OnByeAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 3) // need to chng
	{
		GEngine::ChangeLevel("WorldMap");
	}
}
