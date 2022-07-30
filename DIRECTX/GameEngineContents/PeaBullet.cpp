#include "PreCompile.h"
#include "PeaBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulletMovementComponent.h"
#include "PeaShooter.h"

PeaBullet::PeaBullet()
{
}

PeaBullet::~PeaBullet()
{
}

void PeaBullet::SetParent(GameEngineUpdateObject* _Parent)
{
	BulletBase::SetParent(_Parent);
	PeaShooter* Weapon = dynamic_cast<PeaShooter*>(GetParent());
	if (Weapon != nullptr)
	{
		MovementComponent->SetHorizontalDirection(Weapon->GetHorizontalDirection());
		MovementComponent->SetVerticalDirection(Weapon->GetVerticalDirection());
	}
}

void PeaBullet::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->SetTexture("PeaBullet.png");
	Renderer->ScaleToTexture();

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);
}

void PeaBullet::Update(float _DeltaTime)
{

}

void PeaBullet::End()
{
}
