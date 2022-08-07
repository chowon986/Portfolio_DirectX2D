#include "PreCompile.h"
#include "BackgroundObject.h"

BackgroundObject::BackgroundObject()
	: Renderer(nullptr)
	, Direction(float4::ZERO)
	, StartPosition(float4::ZERO)
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

void BackgroundObject::SetStartPosition(float4 _StartPosition)
{
	StartPosition = _StartPosition;
}

void BackgroundObject::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	GetTransform().SetLocalPosition(GetStartPosition());
	SetRenderer(Renderer);
}

void BackgroundObject::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	GetTransform().SetWorldMove(Direction * MoveSpeed * _DeltaTime);
}

void BackgroundObject::End()
{
}
