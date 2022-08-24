#include "PreCompile.h"
#include "CanteenPlane.h"
#include "Canteen.h"
#include "Ph1Dog.h"
#include "DogCopter.h"
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
{
}

CanteenPlane::~CanteenPlane()
{
}

bool CanteenPlane::CanMove(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
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
	//GetLevel()->GetUICamera()->SetCameraOrder(this, CAMERAORDER::UICAMERA);

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneBody", FrameAnimation_DESC("CanteenPlaneBody", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneBody");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, 0, (int)ZOrder::NPC });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlanePropeller", FrameAnimation_DESC("CanteenPlanePropeller", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlanePropeller");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, -40, (int)ZOrder::Player - 1 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneTail", FrameAnimation_DESC("CanteenPlaneTail", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneTail");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, +50, (int)ZOrder::NPC + 3 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneTopWing", FrameAnimation_DESC("CanteenPlaneTopWing", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneTopWing");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, +40, (int)ZOrder::NPC - 1 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneWheels", FrameAnimation_DESC("CanteenPlaneWheels", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneWheels");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, -70, (int)ZOrder::NPC + 2 });
	}

	{
		GameEngineTextureRenderer* Renderer = CreateComponent<GameEngineTextureRenderer>();
		Renderer->CreateFrameAnimationFolder("CanteenPlaneWing", FrameAnimation_DESC("CanteenPlaneWing", 0.1f, true));
		Renderer->ChangeFrameAnimation("CanteenPlaneWing");
		Renderer->ScaleToTexture();
		Renderer->GetTransform().SetLocalPosition({ 0, 0, (int)ZOrder::NPC + 2 });
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
	GameEngineDebug::DrawBox(LeftCollision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
	GameEngineDebug::DrawBox(RightCollision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
	GameEngineDebug::DrawBox(GroundCollision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });

	if (LeaderCopter != nullptr)
	{
		if (true == RotateLeaderCopter())
		{
			//GetLevel()->GetUICameraActor()->GetTransform().SetLocalRotate({ 0.0, 0.0, 90.0f });
		}
	}

	if (LeftCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D,
		std::bind(&CanteenPlane::CanMove, this, std::placeholders::_1, std::placeholders::_2)))
	{
		MoveDirection = float4::LEFT;
	}

	else if (RightCollision->IsCollision(CollisionType::CT_AABB2D, ObjectOrder::PC, CollisionType::CT_AABB2D,
		std::bind(&CanteenPlane::CanMove, this, std::placeholders::_1, std::placeholders::_2)))
	{
		
		MoveDirection = float4::RIGHT;
	}

	else
	{
		MoveDirection = float4::ZERO;
	}

	if (ColMapTexture == nullptr)
	{
		ColMapTexture = ColMapImage->GetCurTexture();
	}

	while (ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x + 230.0f, -GetTransform().GetWorldPosition().y).CompareInt4D(float4::BLACK))
	{
		MoveDirection = float4::ZERO;
		GetTransform().SetWorldMove(float4::LEFT * _DeltaTime);
	} 
	
	while (ColMapTexture->GetPixelToFloat4(GetTransform().GetWorldPosition().x - 230.0f, -GetTransform().GetWorldPosition().y).CompareInt4D(float4::BLACK))
	{
		MoveDirection = float4::ZERO;
		GetTransform().SetWorldMove(float4::RIGHT * _DeltaTime);
	}
	
	GetTransform().SetWorldMove(MoveDirection * 100 * _DeltaTime);
}

void CanteenPlane::End()
{
}
