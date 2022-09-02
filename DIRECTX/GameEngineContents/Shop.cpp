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
	PortalBase::Start();

	Renderer->CreateFrameAnimationFolder("Shop", FrameAnimation_DESC("Shop", 0.1f));
	Renderer->ChangeFrameAnimation("Shop");
	Renderer->GetTransform().SetLocalScale({ 222,259,100 });
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });

}

void Shop::Update(float _DeltaTime)
{
	PortalBase::Update(_DeltaTime);
	if (Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D, std::bind(&Shop::OnPortalCollision, this, std::placeholders::_1, std::placeholders::_2)))
	{
		if (true == GameEngineInput::GetInst()->IsDown("EnterMap"))
		{
			GEngine::ChangeLevel("Shop");
		}
	}
}

void Shop::End()
{
}
