#include "PreCompile.h"
#include "PeaBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "PeaShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"
#include "PepperShooter.h"

PeaBullet::PeaBullet()
	: Weapon(nullptr)
{
}

PeaBullet::~PeaBullet()
{
}

void PeaBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("PeashotLoop", FrameAnimation_DESC("PeashotLoop", 0.05f));
	Renderer->CreateFrameAnimationFolder("PeashotIntro", FrameAnimation_DESC("PeashotIntro", 0.05f));
	Renderer->CreateFrameAnimationFolder("PeashotDeath", FrameAnimation_DESC("PeashotDeath", 0.05f, false));
	Renderer->AnimationBindEnd("PeashotIntro", std::bind(&PeaBullet::PeashotLoop, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("PeashotDeath", std::bind(&PeaBullet::OnPeashotDeathAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("PeashotDeath", std::bind(&PeaBullet::Test, this, std::placeholders::_1));

	Renderer->ChangeFrameAnimation("PeashotIntro");
	Renderer->SetScaleModeImage();

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(1500.0f);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	Collision->GetTransform().SetLocalScale({ 50.0f,50.0f });
	Collision->ChangeOrder(ObjectOrder::PC_BULLET);
	SetCollision(Collision);
	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);
}

void PeaBullet::Update(float _DeltaTime)
{
	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER, CollisionType::CT_AABB2D, std::bind(&PeaBullet::AttackSuccess, this, std::placeholders::_1, std::placeholders::_2));
	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER_DAMAGEABLE_BULLET, CollisionType::CT_AABB2D, std::bind(&PeaBullet::AttackSuccess, this, std::placeholders::_1, std::placeholders::_2));

	if (nullptr == ColMapImage)
	{
		SetColMapImage(GetLevel()->GetMainColMapImage());
	}
	else
	{
		BulletBase::Update(_DeltaTime);
	}
}

void PeaBullet::End()
{
}

void PeaBullet::OnPeashotDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}

void PeaBullet::Test(const FrameAnimation_DESC& _Info)
{
	int a = 0;
}

CollisionReturn PeaBullet::AttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (PepperShooter* Pepper = dynamic_cast<PepperShooter*>(_Other))
	{
	}
	else
	{
		MovementComponent->SetSpeed(0.0f);
	}
	Renderer->ChangeFrameAnimation("PeashotDeath");
	return CollisionReturn::ContinueCheck;
}

void PeaBullet::PeashotLoop(const FrameAnimation_DESC& _DESC)
{
	Renderer->ChangeFrameAnimation("PeashotLoop");
}
