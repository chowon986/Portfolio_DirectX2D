#include "PreCompile.h"
#include "AnimalBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"
#include "AnimalBulletPhysicsComponent.h"

AnimalBullet::AnimalBullet()
	: Collision(nullptr)
	, CurAnimationName("")
	, CanMove(true)
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
	Renderer->CreateFrameAnimationFolder("LionJumpUpStart", FrameAnimation_DESC("LionJumpUpStart", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("LionJumpUp", FrameAnimation_DESC("LionJumpUp", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("LionJumpDownStart", FrameAnimation_DESC("LionJumpDownStart", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("LionJumpDown", FrameAnimation_DESC("LionJumpDown", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("ElephantJumpUpStart", FrameAnimation_DESC("ElephantJumpUpStart", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("ElephantJumpUp", FrameAnimation_DESC("ElephantJumpUp", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("ElephantJumpDownStart", FrameAnimation_DESC("ElephantJumpDownStart", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("ElephantJumpDown", FrameAnimation_DESC("ElephantJumpDown", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("CamelJumpUpStart", FrameAnimation_DESC("CamelJumpUpStart", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("CamelJumpUp", FrameAnimation_DESC("CamelJumpUp", 0.07f, true));
	Renderer->CreateFrameAnimationFolder("CamelJumpDownStart", FrameAnimation_DESC("CamelJumpDownStart", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("CamelJumpDown", FrameAnimation_DESC("CamelJumpDown", 0.07f, true));

	Renderer->CreateFrameAnimationFolder("LionDeath", FrameAnimation_DESC("LionDeath", 0.07f, false));
	Renderer->CreateFrameAnimationFolder("ElephantDeath", FrameAnimation_DESC("ElephantDeath", 0.07f, false));
	Renderer->CreateFrameAnimationFolder("CamelDeath", FrameAnimation_DESC("CamelDeath", 0.07f, false));

	Renderer->AnimationBindEnd("LionJumpDownStart", std::bind(&AnimalBullet::OnJumpDownStartAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("LionJumpUpStart", std::bind(&AnimalBullet::OnJumpUpStartAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("ElephantJumpDownStart", std::bind(&AnimalBullet::OnJumpDownStartAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("ElephantJumpUpStart", std::bind(&AnimalBullet::OnJumpUpStartAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("CamelJumpDownStart", std::bind(&AnimalBullet::OnJumpDownStartAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("CamelJumpUpStart", std::bind(&AnimalBullet::OnJumpUpStartAnimationFrameFinished, this, std::placeholders::_1));

	Renderer->AnimationBindEnd("LionDeath", std::bind(&AnimalBullet::OnDeathAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("ElephantDeath", std::bind(&AnimalBullet::OnDeathAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("CamelDeath", std::bind(&AnimalBullet::OnDeathAnimationFrameFinished, this, std::placeholders::_1));

	Renderer->ChangeFrameAnimation("LionJumpUpStart");
	Renderer->SetScaleModeImage();

	SetAnimalBulletPhysicsComponent(CreateComponent<AnimalBulletPhysicsComponent>());

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 100.0f, 100.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_DAMAGEABLE_BULLET);
}

void AnimalBullet::Update(float _DeltaTime)
{
	if (CanMove == true)
	{
		GetTransform().SetWorldMove(float4::RIGHT * _DeltaTime * 200);
	}
	else
	{
		GetTransform().SetWorldMove(float4::DOWN * _DeltaTime * 250);

	}

	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D,
		std::bind(&AnimalBullet::Attack, this, std::placeholders::_1, std::placeholders::_2));
	Collision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D,
		std::bind(&AnimalBullet::Attack, this, std::placeholders::_1, std::placeholders::_2));

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
			Physics->AddForce(65);
			Physics->IsOnGround = false;
		}
		else if(GetAnimal() == "Lion")
		{
			Physics->Reset();
			Physics->AddForce(55);
			Physics->IsOnGround = false;
		}
	}

	if (GetTransform().GetWorldPosition().y < -750)
	{
		Death();
	}
}

CollisionReturn AnimalBullet::Attack(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (nullptr != Renderer)
	{
		Physics->Off();
		CanMove = false;
		Renderer->ChangeFrameAnimation(GetAnimal() + "Death");
	}
	return CollisionReturn::Break;
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

void AnimalBullet::OnDeathAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}
