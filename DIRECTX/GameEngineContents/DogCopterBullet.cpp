#include "PreCompile.h"
#include "DogCopterBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "DogCopterShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

DogCopterBullet::DogCopterBullet()
	: Collision(nullptr)
{
}

DogCopterBullet::~DogCopterBullet()
{
}

void DogCopterBullet::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("BulldogDogCopterA", FrameAnimation_DESC("BulldogDogCopterA", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogDogCopterB", FrameAnimation_DESC("BulldogDogCopterB", 0.1f));
	Renderer->CreateFrameAnimationFolder("BulldogDogCopterPink", FrameAnimation_DESC("BulldogDogCopterPink", 0.1f));
	Renderer->ChangeFrameAnimation("BulldogDogCopterA");
	Renderer->ScaleToTexture();
	SetRenderer(Renderer);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);
}

void DogCopterBullet::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void DogCopterBullet::End()
{
}
