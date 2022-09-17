#include "PreCompile.h"
#include "PlayerHP.h"

PlayerHP::PlayerHP()
{
}

PlayerHP::~PlayerHP()
{
}

void PlayerHP::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
}

void PlayerHP::Update(float _DeltaTime)
{
}

void PlayerHP::End()
{
}
