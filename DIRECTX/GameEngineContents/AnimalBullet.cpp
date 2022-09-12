#include "PreCompile.h"
#include "AnimalBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"
#include "AnimalBulletPhysicsComponent.h"

AnimalBullet::AnimalBullet()
	: Collision(nullptr)
{
}

AnimalBullet::~AnimalBullet()
{
}

void AnimalBullet::SetAnimalBulletPhysicsComponent(AnimalBulletPhysicsComponent* _Physics)
{
	Physics = _Physics;
}

void AnimalBullet::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();	
	Renderer->CreateFrameAnimationFolder("RedDogBowlDrop", FrameAnimation_DESC("RedDogBowlDrop", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("RedDogBowlShoot", FrameAnimation_DESC("RedDogBowlShoot", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("YellowDogBowlDrop", FrameAnimation_DESC("YellowDogBowlDrop", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("YellowDogBowlShoot", FrameAnimation_DESC("YellowDogBowlShoot", 0.1f, true));
	Renderer->ChangeFrameAnimation("RedDogBowlDrop");
	Renderer->SetScaleModeImage();

	SetAnimalBulletPhysicsComponent(CreateComponent<AnimalBulletPhysicsComponent>());

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);
}

void AnimalBullet::Update(float _DeltaTime)
{
	GetTransform().SetWorldMove(float4::RIGHT * _DeltaTime * 200);

	if (Physics->IsOnGround == true)
	{
		if (GetAnimal() == "Camel")
		{
			Physics->Reset();
			Physics->AddForce(50);
			Physics->IsOnGround = false;
		}
		else if (GetAnimal() == "Elephant")
		{
			Physics->Reset();
			Physics->AddForce(40);
			Physics->IsOnGround = false;
		}
		else
		{
			Physics->Reset();
			Physics->AddForce(30);
			Physics->IsOnGround = false;
		}
	}
}

void AnimalBullet::End()
{
}
