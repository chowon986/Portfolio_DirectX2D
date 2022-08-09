#include "PreCompile.h"
#include "ChargerBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "ChargerShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

ChargerBullet::ChargerBullet()
	: Weapon(nullptr)
{
}

ChargerBullet::~ChargerBullet()
{
}

void ChargerBullet::Start()
{
	BulletBase::Start();
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PeashotLoop", FrameAnimation_DESC("PeashotLoop", 0.1f));
	Renderer->CreateFrameAnimationFolder("PeashotIntro", FrameAnimation_DESC("PeashotIntro", 0.05f));
	//Renderer->AnimationBindEnd("PeashotIntro", &PeaBullet::PeashotLoop, this);

	Renderer->ChangeFrameAnimation("PeashotIntro");
	Renderer->ScaleToTexture();

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	SetCollision(Collision);
	Collision->ChangeOrder(ObjectOrder::PC_BULLET);
	Collision->GetTransform().SetLocalScale({ 50.0f,50.0f });
}

void ChargerBullet::Update(float _DeltaTime)
{
	BulletBase::Update(_DeltaTime);
	Renderer->ScaleToTexture();
	GameEngineDebug::DrawBox(GetCollision()->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void ChargerBullet::End()
{
}

void ChargerBullet::ChargershotLoop(const FrameAnimation_DESC& _DESC)
{
	Renderer->ChangeFrameAnimation("ChargershotLoop");
}
