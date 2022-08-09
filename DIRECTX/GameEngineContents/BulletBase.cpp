#include "PreCompile.h"
#include "BulletBase.h"
#include "BulletMovementComponent.h"

BulletBase::BulletBase()
	: Renderer(nullptr)
	, MovementComponent(nullptr)
	, Collision(nullptr)
	, ColMapImage(nullptr)
{
}

BulletBase::~BulletBase()
{
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

		 else if (Direction.CompareInt2D(float4::UP+float4::RIGHT))
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

void BulletBase::Death()
{
}

void BulletBase::Start()
{
}

void BulletBase::Update(float _DeltaTime)
{
	if (ColMapImage == nullptr)
	{
		return;
	}

	GameEngineTexture* ColMapTexture = ColMapImage->GetCurTexture();
	if (ColMapTexture == nullptr)
	{
		return;
	}

	if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy()).CompareInt4D(float4::BLACK) ||
		true == Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::MONSTER, CollisionType::CT_AABB2D,
			std::bind(&BulletBase::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2)))
	{
		Death();
	}
}

void BulletBase::End()
{
}

bool BulletBase::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return false;
}
