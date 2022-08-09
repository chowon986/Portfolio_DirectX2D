#include "PreCompile.h"
#include "YarnballBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulldogShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

YarnballBullet::YarnballBullet()
	: Weapon(nullptr)
{
}

YarnballBullet::~YarnballBullet()
{
}

void YarnballBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("YarnballA", FrameAnimation_DESC("YarnballA", 0.1f));
	Renderer->ChangeFrameAnimation("YarnballA");
	Renderer->ScaleToTexture();

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(20.0f);
}

void YarnballBullet::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void YarnballBullet::End()
{
}
