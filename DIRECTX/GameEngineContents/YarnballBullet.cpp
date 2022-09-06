#include "PreCompile.h"
#include "YarnballBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "YarnballShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

YarnballBullet::YarnballBullet()
	: Weapon(nullptr)
	, Collision(nullptr)
{
}

YarnballBullet::~YarnballBullet()
{
}

void YarnballBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("Yarnball1", FrameAnimation_DESC("Yarnball1", 0.1f));
	Renderer->CreateFrameAnimationFolder("Yarnball2", FrameAnimation_DESC("Yarnball2", 0.1f));
	Renderer->CreateFrameAnimationFolder("Yarnball3", FrameAnimation_DESC("Yarnball3", 0.1f));
	Renderer->ChangeFrameAnimation("Yarnball1");
	Renderer->SetScaleModeImage();
	SetRenderer(Renderer);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 80.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(400.0f);

	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);
}

void YarnballBullet::Update(float _DeltaTime)
{
	if (ColMapImage == nullptr)
	{
		ColMapImage = GetLevel()->GetMainColMapImage();
		ColMapImage->SetPivot(PIVOTMODE::LEFTTOP);

	}

	if (ColMapTexture == nullptr)
	{
		ColMapTexture = ColMapImage->GetCurTexture();
	}
	//GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });

	if ((Renderer->GetTransform().GetWorldPosition().ix() < -50 || Renderer->GetTransform().GetWorldPosition().ix() > 1330) &&
		true == ColMapTexture->GetPixelToFloat4(Renderer->GetTransform().GetWorldPosition().ix(), -Renderer->GetTransform().GetWorldPosition().iy()).CompareInt3D(float4::BLACK))
	{
		Death();
	}
}

void YarnballBullet::End()
{
}
