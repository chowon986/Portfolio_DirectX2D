#include "PreCompile.h"
#include "Laser.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "TattooShooter.h"
#include "BulletMovementComponent.h"
#include "IInGameCharacterBase.h"

Laser::Laser()
	: Weapon(nullptr)
	, Collision(nullptr)
{
}

Laser::~Laser()
{
}

void Laser::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("LaserWarningA", FrameAnimation_DESC("LaserWarningA", 0.1f)); // 왼쪽 위 오른쪽 아래 대각선 모양
	Renderer->CreateFrameAnimationFolder("LaserWarningB", FrameAnimation_DESC("LaserWarningB", 0.1f)); 
	Renderer->CreateFrameAnimationFolder("LaserWarningC", FrameAnimation_DESC("LaserWarningC", 0.1f)); 
	Renderer->CreateFrameAnimationFolder("LaserBeamTop", FrameAnimation_DESC("LaserBeamTop", 0.1f)); 
	Renderer->CreateFrameAnimationFolder("LaserBeamMid", FrameAnimation_DESC("LaserBeamMid", 0.1f));
	Renderer->CreateFrameAnimationFolder("LaserBeamLow", FrameAnimation_DESC("LaserBeamLow", 0.1f));
	Renderer->ChangeFrameAnimation("LaserWarningA");

	Renderer->AnimationBindEnd("LaserWarningA", std::bind(&Laser::OnLaserWarningAAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("LaserWarningB", std::bind(&Laser::OnLaserWarningBAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("LaserWarningC", std::bind(&Laser::OnLaserWarningCAnimationFrameFinished, this, std::placeholders::_1));

	Renderer->AnimationBindEnd("LaserBeamTop", std::bind(&Laser::OnLaserBeamAnimationFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("LaserBeamMid", std::bind(&Laser::OnLaserBeamAnimationFinished, this, std::placeholders::_1));
	Renderer->AnimationBindEnd("LaserBeamLow", std::bind(&Laser::OnLaserBeamAnimationFinished, this, std::placeholders::_1));

	Renderer->ScaleToTexture();
	SetRenderer(Renderer);
	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform().SetLocalScale({ 5.0f, 80.0f, 1.0f });
	Collision->ChangeOrder(ObjectOrder::MONSTER_BULLET);

	MovementComponent = CreateComponent<BulletMovementComponent>();
	MovementComponent->SetSpeed(10.0f);
}

void Laser::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	GameEngineDebug::DrawBox(Collision->GetTransform(), { 1.0f, 0.0f,0.0f, 0.5f });
}

void Laser::End()
{
}

void Laser::OnLaserWarningAAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->ChangeFrameAnimation("LaserBeamTop");
	Collision->GetTransform().SetLocalRotate({ 0.0f, 0.0f, 45.0f });
}

void Laser::OnLaserWarningBAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->ChangeFrameAnimation("LaserBeamMid");
	Collision->GetTransform().SetLocalRotate({ 0.0f, 0.0f, 45.0f });
}

void Laser::OnLaserWarningCAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->ChangeFrameAnimation("LaserBeamLow");
	Collision->GetTransform().SetLocalRotate({ 0.0f, 0.0f, 90.0f });
}

void Laser::OnLaserBeamAnimationFinished(const FrameAnimation_DESC& _Info)
{
	Renderer->Death();
	Renderer = nullptr;
	Collision->Death();
	Collision = nullptr;
}
