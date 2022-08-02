#include "PreCompile.h"
#include "PortalBase.h"

PortalBase::PortalBase()
	: Renderer(nullptr)
	, Collision(nullptr)
{
}

PortalBase::~PortalBase()
{
}

void PortalBase::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	PortalRenderer = CreateComponent<GameEngineTextureRenderer>();
	PortalRenderer->CreateFrameAnimationFolder("Ladder", FrameAnimation_DESC("Ladder", 0.1f));
	PortalRenderer->ChangeFrameAnimation("Ladder");
	PortalRenderer->ScaleToTexture();
	PortalRenderer->SetPivot(PIVOTMODE::CENTER);
	PortalRenderer->Off();

	Collision = CreateComponent<GameEngineCollision>();
	Collision->ChangeOrder(ObjectOrder::NPC);
	Collision->SetParent(this);

}

void PortalBase::Update(float _DeltaTime)
{
	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D,
		std::bind(&PortalBase::OnPortalCollision, this, std::placeholders::_1, std::placeholders::_2));
}

void PortalBase::End()
{
}

bool PortalBase::OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}
