#include "PreCompile.h"
#include "AnimalBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"
#include "AnimalBulletPhysicsComponent.h"

AnimalBullet::AnimalBullet()
	: Collision(nullptr)
	, CurAnimationName("")
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
	Renderer->CreateFrameAnimationFolder("LionJumpUpStart", FrameAnimation_DESC("LionJumpUpStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("LionJumpUp", FrameAnimation_DESC("LionJumpUp", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("LionJumpDownStart", FrameAnimation_DESC("LionJumpDownStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("LionJumpDown", FrameAnimation_DESC("LionJumpDown", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("ElephantJumpUpStart", FrameAnimation_DESC("ElephantJumpUpStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("ElephantJumpUp", FrameAnimation_DESC("ElephantJumpUp", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("ElephantJumpDownStart", FrameAnimation_DESC("ElephantJumpDownStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("ElephantJumpDown", FrameAnimation_DESC("ElephantJumpDown", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("CamelJumpUpStart", FrameAnimation_DESC("CamelJumpUpStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("CamelJumpUp", FrameAnimation_DESC("CamelJumpUp", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("CamelJumpDownStart", FrameAnimation_DESC("CamelJumpDownStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("CamelJumpDown", FrameAnimation_DESC("CamelJumpDown", 0.1f, true));

	Renderer->AnimationBindEnd("LionJumpDownStart", std::bind(&AnimalBullet::OnJumpDownStartAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("LionJumpUpStart", std::bind(&AnimalBullet::OnJumpUpStartAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("ElephantJumpDownStart", std::bind(&AnimalBullet::OnJumpDownStartAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("ElephantJumpUpStart", std::bind(&AnimalBullet::OnJumpUpStartAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("CamelJumpDownStart", std::bind(&AnimalBullet::OnJumpDownStartAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("CamelJumpUpStart", std::bind(&AnimalBullet::OnJumpUpStartAnimationFrameFinished, this, std::placeholders::_1));

	Renderer->ChangeFrameAnimation("LionJumpUpStart");
	Renderer->SetScaleModeImage();

	SetAnimalBulletPhysicsComponent(CreateComponent<AnimalBulletPhysicsComponent>());

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);
}

void AnimalBullet::Update(float _DeltaTime)
{
	GetTransform().SetWorldMove(float4::RIGHT * _DeltaTime * 200);

	if (Physics->GetAcceleration() > 0)
	{
		if (GetCurAnimationName() != GetAnimal() + "JumpDownStart")
		{
			Renderer->ChangeFrameAnimation(GetAnimal() + "JumpDownStart");
			SetCurAnimationName(GetAnimal() + "JumpDownStart");
		}
	}
	else if (Physics->IsOnGround == true)
	{
		if (GetCurAnimationName() != GetAnimal() + "JumpUpStart")
		{
			Renderer->ChangeFrameAnimation(GetAnimal() + "JumpUpStart");
			SetCurAnimationName(GetAnimal() + "JumpUpStart");
		}

		if (GetAnimal() == "Camel")
		{
			Physics->Reset();
			Physics->AddForce(60);
			Physics->IsOnGround = false;
		}
		else if (GetAnimal() == "Elephant")
		{
			Physics->Reset();
			Physics->AddForce(55);
			Physics->IsOnGround = false;
		}
		else if(GetAnimal() == "Lion")
		{
			Physics->Reset();
			Physics->AddForce(50);
			Physics->IsOnGround = false;
		}
	}

	if (GetTransform().GetWorldPosition().y < -750)
	{
		Death();
	}
}

void AnimalBullet::End()
{
}

void AnimalBullet::OnJumpDownStartAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (GetAnimal() != "")
	{
	Renderer->ChangeFrameAnimation(GetAnimal() + "JumpDown");
	}
}

void AnimalBullet::OnJumpUpStartAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	if (GetAnimal() != "")
	{
		Renderer->ChangeFrameAnimation(GetAnimal() + "JumpUp");
	}
}
