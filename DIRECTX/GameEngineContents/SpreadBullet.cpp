#include "PreCompile.h"
#include "SpreadBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "SpreadShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

SpreadBullet::SpreadBullet()
	: Weapon(nullptr)
{
}

SpreadBullet::~SpreadBullet()
{
}

void SpreadBullet::SetParent(GameEngineUpdateObject* _Parent)
{
	BulletBase::SetParent(_Parent);

	Weapon = dynamic_cast<SpreadShooter*>(GetParent());
	if (Weapon != nullptr)
	{
		MovementComponent->SetHorizontalDirection(Weapon->GetHorizontalDirection());
		MovementComponent->SetVerticalDirection(Weapon->GetVerticalDirection());
	}
}

void SpreadBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("SpreadshotLoop", FrameAnimation_DESC("SpreadshotLoop", 0.1f));
	Renderer->ChangeFrameAnimation("SpreadshotLoop");
	Renderer->ScaleToTexture();

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);
}

void SpreadBullet::Update(float _DeltaTime)
{

}

void SpreadBullet::End()
{
}
