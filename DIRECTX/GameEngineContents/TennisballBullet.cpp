#include "PreCompile.h"
#include "TennisballBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "TennisballShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

TennisballBullet::TennisballBullet()
	: Weapon(nullptr)
	, Collision(nullptr)
{
}

TennisballBullet::~TennisballBullet()
{
}

void TennisballBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("TennisBall", FrameAnimation_DESC("TennisBall", 0.1f));

	Renderer->ChangeFrameAnimation("TennisBall");
	Renderer->ScaleToTexture();
	SetRenderer(Renderer);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 50.0f, 50.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(5.0f);
}

void TennisballBullet::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void TennisballBullet::End()
{
}
