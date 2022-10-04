#include "PreCompile.h"
#include "TennisballBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "TennisballShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

TennisballBullet::TennisballBullet()
	: Weapon(nullptr)
	, Collision(nullptr)
{
}

TennisballBullet::~TennisballBullet()
{
}

void TennisballBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("TennisBall", FrameAnimation_DESC("TennisBall", 0.1f));

	Renderer->ChangeFrameAnimation("TennisBall");
	Renderer->SetScaleModeImage();
	SetRenderer(Renderer);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 40.0f, 40.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(600.0f);

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);

}

void TennisballBullet::Update(float _DeltaTime)
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

	if (Renderer->GetTransform().GetWorldPosition().iy() < - 770 &&
		true == ColMapTexture->GetPixelToFloat4(Renderer->GetTransform().GetWorldPosition().ix(), -Renderer->GetTransform().GetWorldPosition().iy()).CompareInt3D(float4::BLACK))
	{
		Death();
	}
}

void TennisballBullet::End()
{
}
