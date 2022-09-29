#include "PreCompile.h"
#include "Darkness.h"

Darkness::Darkness()
{
}

Darkness::~Darkness()
{
}

void Darkness::Start()
{
	GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetTexture("Darkness.png");
	Renderer->GetTransform().SetWorldScale({ 1300.0f, 750, 1.0 });
	Renderer->GetPipeLine()->SetOutputMergerBlend("Darkness");
}

void Darkness::Update(float _DeltaTime)
{
}

void Darkness::End()
{
}
