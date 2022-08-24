#include "PreCompile.h"
#include "BackgroundObject.h"

BackgroundObject::BackgroundObject()
	: Renderer(nullptr)
	, Direction(float4::ZERO)
	, MoveSpeed(0.0f)
{
}

BackgroundObject::~BackgroundObject()
{
}

void BackgroundObject::SetRenderer(GameEngineTextureRenderer* _Renderer)
{
	Renderer = _Renderer;
}

void BackgroundObject::SetDirection(float4 _Direction)
{
	Direction = _Direction;
}

void BackgroundObject::SetMoveSpeed(float _MoveSpeed)
{
	MoveSpeed = _MoveSpeed;
}

void BackgroundObject::Start()
{
	GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
	SetRenderer(Renderer);
	//Renderer->ChangeCamera(CAMERAORDER::BACKGROUND);
}

void BackgroundObject::Update(float _DeltaTime)
{
	if (Renderer == nullptr)
	{
		return;
	}
	Renderer->ScaleToTexture();
	GetTransform().SetWorldMove(Direction * MoveSpeed * _DeltaTime);
}

void BackgroundObject::End()
{
}
