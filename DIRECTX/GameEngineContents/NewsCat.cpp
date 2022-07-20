#include "PreCompile.h"
#include "NewsCat.h"

NewsCat::NewsCat()
{
}

NewsCat::~NewsCat()
{
}

void NewsCat::SetState(NewsCatState _State)
{
}

NewsCatState NewsCat::GetState()
{
	return NewsCatState();
}

void NewsCat::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("NewsCat", FrameAnimation_DESC("NewsCat", 0.1f));
	Renderer->ChangeFrameAnimation("NewsCat");
	Renderer->GetTransform().SetLocalScale({ 110,113,100 });
}

void NewsCat::Update(float _DeltaTime)
{
}

void NewsCat::Talk()
{
}

void NewsCat::Idle()
{
}
