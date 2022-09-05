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

void BulletBase::Start()
{

}

void BulletBase::Update(float _DeltaTime)
{
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

	if (true == ColMapTexture->GetPixelToFloat4(Renderer->GetTransform().GetWorldPosition().ix(), -Renderer->GetTransform().GetWorldPosition().iy()).CompareInt3D(float4::BLACK))
	{
		Death();
	} 
}

void BulletBase::End()
{
}

