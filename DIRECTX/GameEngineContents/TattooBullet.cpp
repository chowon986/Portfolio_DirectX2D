#include "PreCompile.h"
#include "TattooBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "TattooShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

TattooBullet::TattooBullet()
	: Weapon(nullptr)
	, Collision(nullptr)
	, ZeroDirectionElapsedTime(0.0f)
	, TimeCheckOn(false)
	, ColorCheckOn(true)
{
}

TattooBullet::~TattooBullet()
{
}

void TattooBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("BulldogTattooA", FrameAnimation_DESC("BulldogTattooA", 0.05f));
	Renderer->CreateFrameAnimationFolder("BulldogTattooB", FrameAnimation_DESC("BulldogTattooB", 0.05f));
	Renderer->CreateFrameAnimationFolder("BulldogTattooPink", FrameAnimation_DESC("BulldogTattooPink", 0.05f));
	Renderer->ChangeFrameAnimation("BulldogTattooA");
	Renderer->SetScaleModeImage();
	SetRenderer(Renderer);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);
}

void TattooBullet::Update(float _DeltaTime)
{
	//GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });

	if (ColMapImage == nullptr)
	{
		ColMapImage = GetLevel()->GetMainColMapImage();
		ColMapImage->SetPivot(PIVOTMODE::LEFTTOP);

	}

	if (ColMapTexture == nullptr)
	{
		ColMapTexture = ColMapImage->GetCurTexture();
	}

	if (ZeroDirectionElapsedTime > 1.0f)
	{
		LastDirection.x = LastDirection .x * -1;
		ZeroDirectionElapsedTime = 0.0f;
		SetDirection(LastDirection);
		TimeCheckOn = false;
	}

	if (true == TimeCheckOn)
	{
		ZeroDirectionElapsedTime += _DeltaTime;
	}

	if (true == ColorCheckOn &&
		true == ColMapTexture->GetPixelToFloat4(Renderer->GetTransform().GetWorldPosition().ix(), -Renderer->GetTransform().GetWorldPosition().iy()).CompareInt3D(float4::BLACK))
	{
		LastDirection = GetDirection();
		SetDirection(float4::ZERO);
		TimeCheckOn = true;
		ColorCheckOn = false;
	}

	if ((Renderer->GetTransform().GetWorldPosition().ix() < -50 || Renderer->GetTransform().GetWorldPosition().ix() > 1330) &&
		true == ColMapTexture->GetPixelToFloat4(Renderer->GetTransform().GetWorldPosition().ix(), -Renderer->GetTransform().GetWorldPosition().iy()).CompareInt3D(float4::BLACK))
	{
		Death();
	}
}

void TattooBullet::End()
{
}
