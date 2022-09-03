#include "PreCompile.h"
#include "PeaBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "PeaShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

PeaBullet::PeaBullet()
	: Weapon(nullptr)
{
}

PeaBullet::~PeaBullet()
{
}

void PeaBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PeashotLoop", FrameAnimation_DESC("PeashotLoop", 0.1f));
	Renderer->CreateFrameAnimationFolder("PeashotIntro", FrameAnimation_DESC("PeashotIntro", 0.05f));
	Renderer->AnimationBindEnd("PeashotIntro", std::bind(&PeaBullet::PeashotLoop, this, std::placeholders::_1));

	Renderer->ChangeFrameAnimation("PeashotIntro");
	Renderer->SetScaleModeImage();

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	Collision->GetTransform().SetLocalScale({ 50.0f,50.0f });
	Collision->ChangeOrder(ObjectOrder::PC_BULLET);
	SetCollision(Collision);
}

void PeaBullet::Update(float _DeltaTime)
{
	if (nullptr == ColMapImage)
	{
		SetColMapImage(GetLevel()->GetMainColMapImage());
	}
	else
	{
		BulletBase::Update(_DeltaTime);
	}
}

void PeaBullet::End()
{
}

void PeaBullet::PeashotLoop(const FrameAnimation_DESC& _DESC)
{
	Renderer->ChangeFrameAnimation("PeashotLoop");
}
