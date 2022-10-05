#include "PreCompile.h"
#include "HydrantBulletPuff.h"

HydrantBulletPuff::HydrantBulletPuff()
	: Renderer(nullptr)
	, Boss(nullptr)
{
}

HydrantBulletPuff::~HydrantBulletPuff()
{
}

void HydrantBulletPuff::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("HydrantPuff", FrameAnimation_DESC("HydrantPuff", 0.05f, true));
	Renderer->ChangeFrameAnimation("HydrantPuff");
	Renderer->AnimationBindEnd("HydrantPuff", std::bind(&HydrantBulletPuff::OnHydrantPuffAnimationFrameFinished, this, std::placeholders::_1));
	Renderer->SetScaleModeImage();
	Renderer->ChangeCamera(CAMERAORDER::ROTATECAMERA);
}

void HydrantBulletPuff::Update(float _DeltaTime)
{
}

void HydrantBulletPuff::End()
{
}

void HydrantBulletPuff::OnHydrantPuffAnimationFrameFinished(const FrameAnimation_DESC& _Info)
{
	Death();
}