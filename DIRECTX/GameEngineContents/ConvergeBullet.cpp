#include "PreCompile.h"
#include "ConvergeBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "ConvergeShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"
#include "GameEngineBase/GameEngineMath.h"

ConvergeBullet::ConvergeBullet()
	: Weapon(nullptr)
{
}

ConvergeBullet::~ConvergeBullet()
{
}

void ConvergeBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("ConvergeA", FrameAnimation_DESC("ConvergeA", 0.1f));
	Renderer->CreateFrameAnimationFolder("ConvergeB", FrameAnimation_DESC("ConvergeB", 0.1f));
	Renderer->CreateFrameAnimationFolder("ConvergeC", FrameAnimation_DESC("ConvergeC", 0.1f));
	Renderer->ChangeFrameAnimation("ConvergeA");
	Renderer->ScaleToTexture();

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(1500.0f);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->SetParent(this);
	Collision->GetTransform().SetLocalScale({ 50.0f,50.0f });
	Collision->ChangeOrder(ObjectOrder::PC_BULLET);
	SetCollision(Collision);

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);
}

void ConvergeBullet::Update(float _DeltaTime)
{
	if ((Renderer->GetTransform().GetWorldPosition().ix() < -50 || Renderer->GetTransform().GetWorldPosition().ix() > 1330) ||
		(Renderer->GetTransform().GetWorldPosition().iy() < -800 || Renderer->GetTransform().GetWorldPosition().iy() > 100))
	{
		Death();
	}

}

void ConvergeBullet::End()
{
}

void ConvergeBullet::SetDirection(float4 _Direction)
{
	Direction = _Direction;
	if (nullptr != MovementComponent)
	{
		MovementComponent->SetDirection(Direction);
	}

	if (nullptr != Renderer)
	{
		float Radian = atan2(Direction.y, Direction.x);
		float Degree = Radian * GameEngineMath::RadianToDegree;
		Renderer->GetTransform().SetLocalRotate({ 0,0, Degree });
	}
}

void ConvergeBullet::OnAttackSuccess(GameEngineCollision* _This, GameEngineCollision* _Other)
{
}
