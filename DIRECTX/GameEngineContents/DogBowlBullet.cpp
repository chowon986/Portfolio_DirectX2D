#include "PreCompile.h"
#include "DogBowlBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "DogCopterShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameMonsterBase.h"
#include "MonsterPhysicsComponent.h"

DogBowlBullet::DogBowlBullet()
	: Weapon(nullptr)
	, Renderer(nullptr)
{
}

DogBowlBullet::~DogBowlBullet()
{
}

void DogBowlBullet::SetDirection(float4 _Direction)
{

}

void DogBowlBullet::SetMonsterPhysicsComponent(MonsterPhysicsComponent* _Physics)
{
	Physics = _Physics;
}

void DogBowlBullet::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("RedDogBowlDrop", FrameAnimation_DESC("RedDogBowlDrop", 0.1f, false));
	Renderer->CreateFrameAnimationFolder("RedDogBowlShoot", FrameAnimation_DESC("RedDogBowlShoot", 0.1f, false));
	Renderer->CreateFrameAnimationFolder("YellowDogBowlDrop", FrameAnimation_DESC("YellowDogBowlDrop", 0.1f, false));
	Renderer->CreateFrameAnimationFolder("YellowDogBowlShoot", FrameAnimation_DESC("YellowDogBowlShoot", 0.1f, false));
	Renderer->ChangeFrameAnimation("RedDogBowlDrop");
	Renderer->SetScaleModeImage();
	Renderer->GetTransform().SetLocalPosition({ 100.0f, -500.0f,(int)ZOrder::Player + 1 });

	TopDogBowl.insert(std::pair<int, float4>(0, { 100.0f, -500.0f,(int)ZOrder::Player + 1 }));
	BottomDogBowl.insert(std::pair<int, float4>(1, { 100.0f, -700.0f,(int)ZOrder::Player + 1 }));

	//MovementComponent = CreateComponent<BulletMovementComponent>();
	//MovementComponent->SetSpeed(10.0f);
	SetMonsterPhysicsComponent(CreateComponent<MonsterPhysicsComponent>());
}

void DogBowlBullet::Update(float _DeltaTime)
{
	RotateAngle += _DeltaTime;

	if (false == Direction.CompareInt2D(float4::UP) ||
		false == Direction.CompareInt2D(float4::DOWN))
	{
		Renderer->GetTransform().SetLocalRotate({ 0,0, RotateAngle });
	}
}

void DogBowlBullet::End()
{
}
