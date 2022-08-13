#include "PreCompile.h"
#include "BowWowBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BowWowShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

BowWowBullet::BowWowBullet()
	: Weapon(nullptr)
	, Collision(nullptr)
{
}

BowWowBullet::~BowWowBullet()
{
}

void BowWowBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("BowWow1", FrameAnimation_DESC("BowWow1", 0.1f));
	Renderer->CreateFrameAnimationFolder("BowWow2", FrameAnimation_DESC("BowWow2", 0.1f));
	Renderer->CreateFrameAnimationFolder("BowWow3", FrameAnimation_DESC("BowWow3", 0.1f));
	Renderer->ChangeFrameAnimation("BowWow1");
	Renderer->ScaleToTexture();
	SetRenderer(Renderer);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(5.0f);
}

void BowWowBullet::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void BowWowBullet::End()
{
}
