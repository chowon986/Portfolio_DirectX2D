#include "PreCompile.h"
#include "Shop.h"
#include "GameEngineCore/GameEngineCollision.h"
#include "WorldMapCuphead.h"


Shop::Shop()
{
}

Shop::~Shop()
{
}

void Shop::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Shop", FrameAnimation_DESC("Shop", 0.1f));
	Renderer->ChangeFrameAnimation("Shop");
	Renderer->GetTransform().SetLocalScale({ 222,259,100 });
	Renderer->SetPivot(PIVOTMODE::CENTER);
}

void Shop::Update(float _DeltaTime)
{
	std::list<WorldMapCuphead*> PlayerList = GetLevel()->GetConvertToGroup<WorldMapCuphead>(GameObjectGroup::Player);
}

void Shop::End()
{
}
