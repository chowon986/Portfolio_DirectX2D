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
}

void Darkness::Update(float _DeltaTime)
{
	GetLevel()->GetUICamera2()->GetTransform().SetLocalPosition(float4{ 640.0f,-360.0f,0.0f });
	GameEngineTextureRenderer* Renderer =CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetTexture("Darkness.png");
	Renderer->GetTransform().SetLocalScale({ 1300, 750, 1.0 });
	Renderer->GetPipeLine()->SetOutputMergerBlend("Darkness");
	Renderer->ChangeCamera(CAMERAORDER::UICAMERA2);
}

void Darkness::End()
{
}
