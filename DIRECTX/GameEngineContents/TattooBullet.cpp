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
	Renderer->CreateFrameAnimationFolder("TattoBoomerang", FrameAnimation_DESC("TattoBoomerang", 0.1f));
	Renderer->ChangeFrameAnimation("TattoBoomerang");
	Renderer->ScaleToTexture();
	SetRenderer(Renderer);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(20.0f);
}

void TattooBullet::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	//GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void TattooBullet::End()
{
}
