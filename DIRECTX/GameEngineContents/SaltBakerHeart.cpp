#include "PreCompile.h"
#include "SaltBakerHeart.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "SaltBakerHeartPhysicsComponent.h"
#include "InGameCuphead.h"

SaltBakerHeart::SaltBakerHeart()
	: Renderer(nullptr)
	, State(InGameMonsterState::Idle)
	, AttackState(InGameMonsterAttackState::None)
	, Collision(nullptr)
	, CanMove(false)
{
}

SaltBakerHeart::~SaltBakerHeart()
{
}

void SaltBakerHeart::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("SaltBakerHeartIdle", FrameAnimation_DESC("SaltBakerHeartIdle", 0.1f));
	Renderer->CreateFrameAnimationFolder("SaltBakerHeartIdlePink", FrameAnimation_DESC("SaltBakerHeartIdlePink", 0.1f)); // Pink
	Renderer->CreateFrameAnimationFolder("SaltBakerHeartIntro", FrameAnimation_DESC("SaltBakerHeartIntro", 0.1f, false));
	Renderer->CreateFrameAnimationFolder("SaltBakerHeartTurn", FrameAnimation_DESC("SaltBakerHeartTurn", 0.1f)); // Pink
	Renderer->CreateFrameAnimationFolder("SaltBakerHeartTurnPink", FrameAnimation_DESC("SaltBakerHeartTurnPink", 0.1f)); // Pink
	Renderer->CreateFrameAnimationFolder("SaltBakerHeartDeath", FrameAnimation_DESC("SaltBakerHeartDeath", 0.1f)); // Pink
	Renderer->ChangeFrameAnimation("SaltBakerHeartIntro");

	Renderer->AnimationBindFrame("SaltBakerHeartIntro", std::bind(&SaltBakerHeart::OnSaltBakerHeartIntroAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerHeartTurn", std::bind(&SaltBakerHeart::OnSaltBakerHeartTurnAnimationFrameChanged, this, std::placeholders::_1));
	Renderer->AnimationBindFrame("SaltBakerHeartTurnPink", std::bind(&SaltBakerHeart::OnSaltBakerHeartIntroAnimationFrameChanged, this, std::placeholders::_1));

	Renderer->SetScaleModeImage();
	
	InGameMonsterAnimationControllerComponent* Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("SaltBakerHeart");
	SetRenderer(Renderer);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 60.0f, 60.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::NPC);

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);

	StartPosX.insert(std::make_pair<int, float>(0, 400.0f));
	DestPosX.insert(std::make_pair<int, float>(0, 700.0f));

	SetVerticalDirection(float4::DOWN);
	SetHorizontalDirection(float4::RIGHT);
}

void SaltBakerHeart::Update(float _DeltaTime)
{
	GameEngineTextureRenderer* CollisionMap = GetLevel()->GetMainColMapImage();
	if (CollisionMap == nullptr)
	{
		return;
	}

	GameEngineTexture* ColMapTexture = CollisionMap->GetCurTexture();
	if (ColMapTexture == nullptr)
	{
		return;
	}

	if (HorizontalDirection.CompareInt3D(float4::RIGHT))
	{
		if (GetState() == InGameMonsterState::Turn)
		{
			Renderer->GetTransform().PixLocalPositiveX();
		}
		else
		{
			Renderer->GetTransform().PixLocalNegativeX();
		}
	}
	else
	{
		if (GetState() == InGameMonsterState::Turn)
		{
			Renderer->GetTransform().PixLocalNegativeX();
		}
		else
		{
			Renderer->GetTransform().PixLocalPositiveX();
		}
	}

	if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y - 15)).CompareInt4D(float4::MAGENTA))
	{
		SetVerticalDirection(float4::UP);
	}
	else if (true == ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y + 15)).CompareInt4D(float4::MAGENTA))
	{
		SetVerticalDirection(float4::DOWN);
	}

	Collision->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::TRACKING1, CollisionType::CT_AABB2D, std::bind(&SaltBakerHeart::OnDirectionChangeColToRight, this, std::placeholders::_1, std::placeholders::_2));
	Collision->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::TRACKING2, CollisionType::CT_AABB2D, std::bind(&SaltBakerHeart::OnDirectionChangeColToLeft, this, std::placeholders::_1, std::placeholders::_2));
	
	if (Collision->GetOrder() == 1) // CollisionÀÇ Order °¡ NPC°í (white -> pink)
	{
		Collision->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PC_BULLET, CollisionType::CT_AABB2D, std::bind(&SaltBakerHeart::OnChangeParriable, this, std::placeholders::_1, std::placeholders::_2));
	}
	else // pink -> white
	{
		Collision->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::PC, CollisionType::CT_AABB2D, std::bind(&SaltBakerHeart::OnChangeNotParriable, this, std::placeholders::_1, std::placeholders::_2));
	}

	if (GetState() != InGameMonsterState::Prepare && CanMove == true)
	{
		GetTransform().SetLocalMove((VerticalDirection + HorizontalDirection) * _DeltaTime * 200);
	}
}

void SaltBakerHeart::TakeDamage()
{
	SetState(InGameMonsterState::TakeDamage);
}

void SaltBakerHeart::Prepare()
{
}

void SaltBakerHeart::Turn()
{
	if (GetState() == InGameMonsterState::Idle)
	{
		SetState(InGameMonsterState::Turn);
	}
	else if (GetState() == InGameMonsterState::IdlePink) 
	{
		SetState(InGameMonsterState::TurnPink);
	}
}

void SaltBakerHeart::TurnPink()
{
	SetState(InGameMonsterState::TurnPink);
}

void SaltBakerHeart::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void SaltBakerHeart::Shoot()
{
	//SetState(InGameMonsterState::Attack5);
	//SetAttackState(InGameMonsterAttackState::Attack5);
	SetState(InGameMonsterState::Attack1);
	SetAttackState(InGameMonsterAttackState::Attack1);
}

void SaltBakerHeart::Die()
{
	SetState(InGameMonsterState::Die);
}

CollisionReturn SaltBakerHeart::OnDirectionChangeColToLeft(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Turn();
	SetHorizontalDirection(float4::LEFT);
	return CollisionReturn::ContinueCheck;
}

CollisionReturn SaltBakerHeart::OnDirectionChangeColToRight(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Turn();
	SetHorizontalDirection(float4::RIGHT);
	return CollisionReturn::ContinueCheck;
}

CollisionReturn SaltBakerHeart::OnChangeParriable(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Collision->ChangeOrder(ObjectOrder::PARRIABLEOBJECT);
	if (GetState() == InGameMonsterState::Idle)
	{
		SetState(InGameMonsterState::IdlePink);
	}
	else if (GetState() == InGameMonsterState::Turn)
	{
		SetState(InGameMonsterState::TurnPink);
	}
	return CollisionReturn();
}

CollisionReturn SaltBakerHeart::OnChangeNotParriable(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (InGameCuphead* Cuphead = dynamic_cast<InGameCuphead*>(_Other))
	{
		if(Cuphead->GetState() == InGameCharacterState::Parry)
		{
			SetHP(GetHP() - 1);
			Collision->ChangeOrder(ObjectOrder::NPC);
			if (GetState() == InGameMonsterState::IdlePink)
			{
			SetState(InGameMonsterState::Idle);
			}
			else if (GetState() == InGameMonsterState::TurnPink)
			{
				SetState(InGameMonsterState::Turn);
			}
		}
	}
	return CollisionReturn();
}

void SaltBakerHeart::OnSaltBakerHeartIntroAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 35)
	{
		SetState(InGameMonsterState::Idle);
		CanMove = true;
	}
}

void SaltBakerHeart::OnSaltBakerHeartTurnAnimationFrameChanged(const FrameAnimation_DESC& _Info)
{
	if (_Info.CurFrame == 8)
	{
		if (GetState() == InGameMonsterState::Turn)
		{
			SetState(InGameMonsterState::Idle);
		}
		else
		{
			SetState(InGameMonsterState::IdlePink);
		}
	}
}
