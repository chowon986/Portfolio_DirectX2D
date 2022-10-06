#include "PreCompile.h"
#include "BulletBase.h"
#include "BulletMovementComponent.h"
#include "PepperShooter.h"
#include <GameEngineContents/InGameLevelBase.h>
#include "IInGameCharacterBase.h"

BulletBase::BulletBase()
	: Renderer(nullptr)
	, MovementComponent(nullptr)
	, Collision(nullptr)
	, ColMapImage(nullptr)
	, GaugeElapsedTime(0.0f)
{
}

BulletBase::~BulletBase()
{
}

void BulletBase::SetIsOnGround(bool _IsOnGround)
{
	if (IsOnGround != _IsOnGround)
	{
		IsOnGround = _IsOnGround;
		IsOnGroundChangedDelegate.Invoke(IsOnGround);
	}
}

void BulletBase::SetDirection(float4 _Direction)
{
	Direction = _Direction;
	if (nullptr != MovementComponent)
	{
		MovementComponent->SetDirection(Direction);
	}

	if (nullptr != Renderer)
	{
		if (Direction.CompareInt2D(float4::UP))
		{
			Renderer->GetTransform().SetLocalRotate({ 0,0,90 });
		}

		else if (Direction.CompareInt2D(float4::UP + float4::RIGHT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 45 });
		}

		else if (Direction.CompareInt2D(float4::UP + float4::LEFT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 135 });
		}

		else if (Direction.CompareInt2D(float4::RIGHT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 0 });
		}

		else if (Direction.CompareInt2D(float4::LEFT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 180 });
		}

		else if (Direction.CompareInt2D(float4::DOWN + float4::RIGHT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 315 });
		}

		else if (Direction.CompareInt2D(float4::DOWN + float4::LEFT))
		{
			Renderer->GetTransform().SetLocalRotate({ 0, 0, 225 });
		}

		else if (Direction.CompareInt2D(float4::DOWN))
		{
			Renderer->GetTransform().SetLocalRotate({ 0,0, 270 });
		}
	}
}

void BulletBase::Start()
{

}

void BulletBase::Update(float _DeltaTime)
{
	GaugeElapsedTime += _DeltaTime;

	if (nullptr != Collision)
	{
		Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER, CollisionType::CT_AABB2D, std::bind(&BulletBase::AttackSuccess, this, std::placeholders::_1, std::placeholders::_2));
		Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER_DAMAGEABLE_BULLET, CollisionType::CT_AABB2D, std::bind(&BulletBase::AttackSuccess, this, std::placeholders::_1, std::placeholders::_2));
	}

	if (nullptr == ColMapImage)
	{
		return;
	}

	if (nullptr == ColMapTexture)
	{
		ColMapImage->SetPivot(PIVOTMODE::LEFTTOP);
		ColMapTexture = ColMapImage->GetCurTexture();
	}

	if (nullptr == Collision)
	{
		return;
	}

	if ((true == Renderer->GetTransform().GetWorldPosition().ix() < -500 || true == Renderer->GetTransform().GetWorldPosition().ix() > 1500)||
		(true == Renderer->GetTransform().GetWorldPosition().iy() < -800 || true == Renderer->GetTransform().GetWorldPosition().iy() > 100))
	{
		Death();
	}
}

void BulletBase::End()
{
}

CollisionReturn BulletBase::AttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (PepperShooter* Pepper = dynamic_cast<PepperShooter*>(_Other))
	{

	}
	else
	{
		if (nullptr != MovementComponent)
		{
			MovementComponent->SetSpeed(0.0f);
		}
	}

	if (GaugeElapsedTime > 0.2f)
	{
		if (InGameLevelBase* Level = dynamic_cast<InGameLevelBase*>(GetLevel()))
		{
			if (IInGameCharacterBase* Character = Level->GetPlayer())
			{
				Character->SetGauge(Character->GetGauge() + 0.01f);
				//Character->SetGauge(4);
			}
		}
		GaugeElapsedTime = 0.0f;
	}
	OnAttackSuccess(_This, _Other);
	return CollisionReturn::Break;
}

