#include "PreCompile.h"
#include "YarnballBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "YarnballShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

YarnballBullet::YarnballBullet()
	: Weapon(nullptr)
	, Collision(nullptr)
{
}

YarnballBullet::~YarnballBullet()
{
}

void YarnballBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Yarnball1", FrameAnimation_DESC("Yarnball1", 0.1f));
	Renderer->CreateFrameAnimationFolder("Yarnball2", FrameAnimation_DESC("Yarnball2", 0.1f));
	Renderer->CreateFrameAnimationFolder("Yarnball3", FrameAnimation_DESC("Yarnball3", 0.1f));
	Renderer->ChangeFrameAnimation("Yarnball1");
	Renderer->ScaleToTexture();
	SetRenderer(Renderer);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(20.0f);
}

void YarnballBullet::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	//GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void YarnballBullet::End()
{
}
