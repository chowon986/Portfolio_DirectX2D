#include "PreCompile.h"
#include "TattooBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "TattooShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

TattooBullet::TattooBullet()
	: Weapon(nullptr)
	, Collision(nullptr)
{
}

TattooBullet::~TattooBullet()
{
}

void TattooBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("BulldogTattooA", FrameAnimation_DESC("BulldogTattooA", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogTattooB", FrameAnimation_DESC("BulldogTattooB", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogTattooPink", FrameAnimation_DESC("BulldogTattooPink", 0.1f));
	Renderer->ChangeFrameAnimation("BulldogTattooA");
	Renderer->ScaleToTexture();
	SetRenderer(Renderer);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);
}

void TattooBullet::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void TattooBullet::End()
{
}
