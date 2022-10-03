#include "PreCompile.h"
#include "CanteenPlane.h"
#include "Canteen.h"
#include "Ph1Dog.h"
#include "DogCopter.h"
#include "InGameLevelBase.h"
#include "IInGameCharacterBase.h"

CanteenPlane::CanteenPlane()
	: Player(nullptr)
	, CaptainCanteen(nullptr)
	, MoveDirection(float4::ZERO)
	, RightCollision(nullptr)
	, LeftCollision(nullptr)
	, GroundCollision(nullptr)
	, ColMapImage(nullptr)
	, ColMapTexture(nullptr)
	, IsPhase2MoveCompleted(false)
	, IsPhase3MoveCompleted(false)
	, DestRotationDegree(0)
{
}

CanteenPlane::~CanteenPlane()
{
}

void CanteenPlane::SetDogCopter(DogCopter* _LeaderCopter)
{
	LeaderCopter = _LeaderCopter;
	LeaderState = LeaderCopter->GetState();
}

CollisionReturn CanteenPlane::CanMoveLeft(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	MoveDirection = float4::LEFT;
	DestRotationDegree = 5;
	IsOnWing = true;
	ElapsedZTime = 0;
	return CollisionReturn();
}

CollisionReturn CanteenPlane::CanMoveRight(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	MoveDirection = float4::RIGHT;
	DestRotationDegree = -5;
	IsOnWing = true;
	ElapsedZTime = 0;
	return CollisionReturn();
}


bool CanteenPlane::RotateLeaderCopter()
{
	//if (LeaderState != LeaderCopter->GetDogCopterState())
	//{
	//	LeaderState = LeaderCopter->GetDogCopterState();

	//	if (LeaderState == InGameDogCopterState::RotateCameraIn || LeaderState == InGameDogCopterState::RotateCameraOut)
	//	{
	//		return true;
	//	}
	//	else
	//	{
	//		return false;
	//	}
	//}
	return false;
}

void CanteenPlane::Start()
{

	RedDogBowlCollsion = CreateComponent<GameEngineCollision>();
	RedDogBowlCollsion->GetTransform().SetLocalScale({ 7200.0f, 200.0f, 1.0f });
	RedDogBowlCollsion->ChangeOrder((int)ObjectOrder::TRACKING1);

	YellowDogBowlCollsion = CreateComponent<GameEngineCollision>();
	YellowDogBowlCollsion->GetTransform().SetLocalScale({ 7200.0f, 500.0f, 1.0f });
	YellowDogBowlCollsion->ChangeOrder((int)ObjectOrder::TRACKING2);

	//GetLevel()->GetUICamera()->SetCameraOrder(this, CAMERAORDER::UICAMERA);

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneBody", FrameAnimation_DESC("CanteenPlaneBody", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneBody");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, 0, (int)ZOrder::NPC });
		Renderers.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlanePropeller", FrameAnimation_DESC("CanteenPlanePropeller", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlanePropeller");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, -40, (int)ZOrder::Player - 1 });
		Renderers.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneTail", FrameAnimation_DESC("CanteenPlaneTail", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneTail");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, +50, (int)ZOrder::NPC + 3 });
		Renderers.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneTopWing", FrameAnimation_DESC("CanteenPlaneTopWing", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneTopWing");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, +40, (int)ZOrder::NPC - 1 });
		Renderers.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneWheels", FrameAnimation_DESC("CanteenPlaneWheels", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneWheels");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, -70, (int)ZOrder::NPC + 2 });
		Renderers.push_back(Renderer);
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneWing", FrameAnimation_DESC("CanteenPlaneWing", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneWing");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, 0, (int)ZOrder::NPC + 2 });
		Renderers.push_back(Renderer);
	}

	{
		LeftCollision = CreateComponent<GameEngineCollision>();
		LeftCollision->GetTransform().SetLocalScale({ 210.0f, 50.0f, 1.0f });
		LeftCollision->GetTransform().SetLocalPosition({ -175.0f, 40.0f});
		LeftCollision->ChangeOrder(ObjectOrder::MOVEPLANELEFT);

		RightCollision = CreateComponent<GameEngineCollision>();
		RightCollision->GetTransform().SetLocalScale({ 210.0f, 50.0f, 1.0f });
		RightCollision->GetTransform().SetLocalPosition({ 175.0f, 40.0f });
		RightCollision->ChangeOrder(ObjectOrder::MOVEPLANERIGHT);

		GroundCollision = CreateComponent<GameEngineCollision>();
		GroundCollision->GetTransform().SetLocalScale({ 500.0f, 30.0f, 1.0f });
		GroundCollision->GetTransform().SetLocalPosition({ 0.0f, 40.0f });
		GroundCollision->ChangeOrder(ObjectOrder::GROUND);
	}

	{
		CaptainCanteen = GetLevel()->CreateActor<Canteen>();
		CaptainCanteen->SetParent(this);
		CaptainCanteen->GetTransform().SetLocalPosition({ 5, 110, (int)ZOrder::NPC });
	}
}

void CanteenPlane::Update(float _DeltaTime)
{
	if (InGameLevelBase* Level = dynamic_cast<InGameLevelBase*>(GetLevel()))
	{
		if (Phase::Phase2 == Level->GetPhase() || 
			Phase::Phase3 == Level->GetPhase())
		{
			ElapsedXTime += _DeltaTime;
			float Time = ElapsedXTime / 30;
			float4 CurPos = GetTransform().GetWorldPosition();

			float DestPosX = CurPos.x;
			if (CurPos.x > 0 &&
				CurPos.x < 500)
			{
				DestPosX = 500.0f;
			}

			else if (CurPos.x > 780 &&
				CurPos.x < 1280)
			{
				DestPosX = 780.0f;
			}

			DestPosX = GameEngineMath::LerpLimit(CurPos.x, DestPosX, Time);
			GetTransform().SetLocalPosition(float4({ DestPosX, CurPos.y, CurPos.z }));
		}

		if (Phase::Phase2 == Level->GetPhase())
		{
			if (false == IsPhase2MoveCompleted)
			{
				ElapsedYTime += _DeltaTime;
				float Time = ElapsedYTime / 30;
				float4 CurPos = GetTransform().GetWorldPosition();

				float DestPosY = GameEngineMath::LerpLimit(CurPos.y, -530.0f, Time);

				if (abs(CurPos.y - (-530.0f)) <= 1)
				{
					IsPhase2MoveCompleted = true;
					ElapsedYTime = 0.0f;
				}

				GetTransform().SetLocalPosition(float4({ CurPos.x, DestPosY, CurPos.z }));
			}
		}

		else if (Phase::Phase3 == Level->GetPhase())
		{
			if (nullptr != LeaderCopter)
			{
				InGameMonsterState BossState = LeaderCopter->GetState();
				ElapsedYTime += _DeltaTime;
				float Time = ElapsedYTime / 30;

				float4 CurPos = GetTransform().GetWorldPosition();
				float DestPosY = CurPos.y;
				if (BossState == InGameMonsterState::RotateCameraIn)
				{
					DestPosY = -700.0f;
				}
				else
				{
					DestPosY = -680.0f;
				}
				float NewPosY = GameEngineMath::LerpLimit(CurPos.y, DestPosY, Time);

				if (abs(CurPos.y - (DestPosY)) <= 0.1)
				{
					IsPhase3MoveCompleted = true;
					ElapsedYTime = 0.0f;
				}

				GetTransform().SetLocalPosition(float4({ CurPos.x, NewPosY, CurPos.z }));
			}

		}
	}

	if (LeaderCopter != nullptr)
	{
		if (true == RotateLeaderCopter())
		{
			//GetLevel()->GetUICameraActor()->GetTransform().SetLocalRotate({ 0.0, 0.0, 90.0f });
		}
	}
	MoveDirection = float4::ZERO;
	IsOnWing = false;

	LeftCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D,
		std::bind(&CanteenPlane::CanMoveLeft, this, std::placeholders::_1, std::placeholders::_2));

	RightCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D,
		std::bind(&CanteenPlane::CanMoveRight, this, std::placeholders::_1, std::placeholders::_2));

	if (IsOnWing == false)
	{
		if (DestRotationDegree != 0)
		{
			DestRotationDegree = 0;
			ElapsedZTime = 0;
		}
	}

	ElapsedZTime += _DeltaTime;
	for (GameEngineRenderer* Renderer : Renderers)
	{
		float RotationZ = GameEngineMath::LerpLimit(Renderer->GetTransform().GetLocalRotation().z, DestRotationDegree, ElapsedZTime );
		Renderer->GetTransform().SetLocalRotation({ 0, 0, RotationZ });
	}

	if (ColMapTexture == nullptr)
	{
		ColMapTexture = ColMapImage->GetCurTexture();
	}

	while (ColMapTexture->GetPixelToFloat4(static_cast<int>(GetTransform().GetWorldPosition().x + 230.0f), static_cast<int>(-GetTransform().GetWorldPosition().y)).CompareInt4D(float4::BLACK))
	{
		MoveDirection = float4::ZERO;
		GetTransform().SetWorldMove(float4::LEFT * _DeltaTime);
	} 
	
	while (ColMapTexture->GetPixelToFloat4(static_cast<int>(GetTransform().GetWorldPosition().x - 230.0f), static_cast<int>(-GetTransform().GetWorldPosition().y)).CompareInt4D(float4::BLACK))
	{
		MoveDirection = float4::ZERO;
		GetTransform().SetWorldMove(float4::RIGHT * _DeltaTime);
	}
	
	GetTransform().SetWorldMove(MoveDirection * 100 * _DeltaTime);
}

void CanteenPlane::End()
{
}
