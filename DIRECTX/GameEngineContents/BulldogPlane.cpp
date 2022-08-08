#include "PreCompile.h"
#include "BulldogPlane.h"

BulldogPlane::BulldogPlane()
	:Renderer(nullptr)
{
}

BulldogPlane::~BulldogPlane()
{
}

void BulldogPlane::SetRenderer(GameEngineTextureRenderer* _Renderer)
{
	Renderer = _Renderer;
}

void BulldogPlane::Start()
{
	GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
	SetRenderer(Renderer);
}

void BulldogPlane::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
}

void BulldogPlane::End()
{
}
