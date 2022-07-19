#include "PreCompile.h"
#include "WorldMapCuphead.h"

WorldMapCuphead::WorldMapCuphead()
{

}

WorldMapCuphead::~WorldMapCuphead()
{
}

void WorldMapCuphead::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
	}

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("DownA", FrameAnimation_DESC("DownA", 0.1f));
	Renderer->ChangeFrameAnimation("DownA");
	Renderer->GetTransform().SetLocalScale({ 53 ,99,100 });
}

void WorldMapCuphead::Update(float _DeltaTime)
{
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition());
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * 50 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * 50 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * 50 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * 50 * _DeltaTime);
	}

	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition());

}
