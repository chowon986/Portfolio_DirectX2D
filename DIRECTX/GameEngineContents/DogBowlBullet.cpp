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

	srand(static_cast<unsigned int>(time(NULL)));

	Index = rand() % DirectionMap.size();
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
	if (GetColor() == "Red")
	{
		if (TrackCollision->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::TRACKING1, CollisionType::CT_AABB2D, std::bind(&DogBowlBullet::CanCollision, this, std::placeholders::_1, std::placeholders::_2)))
		{
			int a = 0;
		}
		else
		{
			Direction.x = Index == 0 ? -1.0f : 1.0f;
		}
	}
	else if (GetColor() == "Yellow")
	{
		if (TrackCollision->IsCollision(CollisionType::CT_AABB2D, (int)ObjectOrder::TRACKING2, CollisionType::CT_AABB2D, std::bind(&DogBowlBullet::CanCollision, this, std::placeholders::_1, std::placeholders::_2)))
		{
			int a = 0;
		}
		else
		{
			Direction.x = Index == 0 ? -1.0f : 1.0f;
		}
	}

	// 충돌하기 전에는 왼쪽, 오른쪽으로 가다가 충돌하면 오른쪽 왼쪽으로 간다.

	// 충돌 하기 전
	Direction.z += _DeltaTime;
	GetTransform().SetWorldMove(Direction * 200 * _DeltaTime);
}

void DogBowlBullet::End()
{
}

CollisionReturn DogBowlBullet::CanCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (GetMonsterPhysicsComponent() != nullptr)
	{
		GetMonsterPhysicsComponent()->Off();
	}

	Direction.x = Index == 0 ? 1.0f : -1.0f;

	return CollisionReturn::ContinueCheck;
}
