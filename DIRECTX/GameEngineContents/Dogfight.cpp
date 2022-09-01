#include "PreCompile.h"
#include "Dogfight.h"

Dogfight::Dogfight()
{
}

Dogfight::~Dogfight()
{
}

void Dogfight::Start()
{
	PortalBase::Start();

	Renderer->CreateFrameAnimationFolder("Dogfight", FrameAnimation_DESC("Dogfight", 0.1f));
	Renderer->ChangeFrameAnimation("Dogfight");
	Renderer->GetTransform().SetLocalScale({ 189,163,1 });
	Renderer->SetPivot(PIVOTMODE::CENTER);

	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });

}

void Dogfight::Update(float _DeltaTime)
{
	if (Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D, std::bind(&Dogfight::OnPortalCollision, this, std::placeholders::_1, std::placeholders::_2)))
	{
		if (true == GameEngineInput::GetInst()->IsDown("EnterMap"))
		{
			GEngine::ChangeLevel("DogFight");
		}
	}
}

void Dogfight::End()
{
}
