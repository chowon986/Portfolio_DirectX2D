#include "PreCompile.h"
#include "Ph2DogZetPuff.h"
#include "Ph2Dog.h"

Ph2DogZetPuff::Ph2DogZetPuff()
{
}

Ph2DogZetPuff::~Ph2DogZetPuff()
{
}

void Ph2DogZetPuff::OnZetPuffAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}

void Ph2DogZetPuff::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Ph2DogPuffWhite", FrameAnimation_DESC("Ph2DogPuffWhite", 0.05f, true));
	Renderer->CreateFrameAnimationFolder("Ph2DogPuffGrey", FrameAnimation_DESC("Ph2DogPuffGrey", 0.05f, true));
	Renderer->AnimationBindEnd("Ph2DogPuffWhite", std::bind(&Ph2DogZetPuff::OnZetPuffAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("Ph2DogPuffGrey", std::bind(&Ph2DogZetPuff::OnZetPuffAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->ChangeFrameAnimation("Ph2DogPuffWhite");
	Renderer->SetScaleModeImage();
}

void Ph2DogZetPuff::Update(float _DeltaTime)
{
}

void Ph2DogZetPuff::End()
{
}
