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
	, Direction(float4::ZERO)
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
	DirectionMap.insert(std::make_pair<int, float4>(0, { 400, 300,(int)ZOrder::Player + 1 }));
	DirectionMap.insert(std::make_pair<int, float4>(1, { 800, 300,(int)ZOrder::Player + 1 }));

	srand(time(NULL));

	int Index = rand() % DirectionMap.size();
	GetTransform().SetLocalPosition(DirectionMap[Index]);
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("RedDogBowlDrop", FrameAnimation_DESC("RedDogBowlDrop", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("RedDogBowlShoot", FrameAnimation_DESC("RedDogBowlShoot", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("YellowDogBowlDrop", FrameAnimation_DESC("YellowDogBowlDrop", 0.1f, true));
	Renderer->CreateFrameAnimationFolder("YellowDogBowlShoot", FrameAnimation_DESC("YellowDogBowlShoot", 0.1f, true));
	Renderer->ChangeFrameAnimation("RedDogBowlDrop");
	Renderer->SetScaleModeImage();


	SetMonsterPhysicsComponent(CreateComponent<MonsterPhysicsComponent>());

	TrackCollision = CreateComponent<GameEngineCollision>();
	TrackCollision->ChangeOrder((int)ObjectOrder::MONSTER_BULLET);
	TrackCollision->GetTransform().SetLocalScale({ 50.0f, 50.0f, 1 });
	
	Renderer->ChangeCamera(CAMERAORDER::IRISCAMERA);

}

void DogBowlBullet::Update(float _DeltaTime)
{
	//GameEngineDebug::DrawBox(TrackCollision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });

	if (TrackCollision->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::TRACKING1, CollisionType::CT_AABB2D, std::bind(&DogBowlBullet::CanCollision, this, std::placeholders::_1, std::placeholders::_2)))
	{
		if (GetMonsterPhysicsComponent() != nullptr)
		{
			GetMonsterPhysicsComponent()->Off();
		}
	}


	if (Direction.x != 0)
	{
		GetTransform().SetWorldMove(Direction * 200 * _DeltaTime);
	}
	//RotateAngle += _DeltaTime;

	//if (false == Direction.CompareInt2D(float4::UP) ||
	//	false == Direction.CompareInt2D(float4::DOWN))
	//{
	//	Renderer->GetTransform().SetLocalRotate({ 0,0, RotateAngle });
	//}
}

void DogBowlBullet::End()
{
}

bool DogBowlBullet::CanCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (Direction.x != 0)
	{
		return false;
	}

	if (MonsterPhysicsComponent* PhysicsComponent = GetMonsterPhysicsComponent())
	{
		if (GameEngineActor* Actor = dynamic_cast<GameEngineActor*>(_Other->GetParent()))
		{
			Direction = Actor->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
			Direction.y = 0;
			Direction.z = 0;
			Direction.x = Direction.x > 0 ? 1 : -1;
		}
		// 캐릭터 쪽으로 움직인다.
	}

	return true;
}
