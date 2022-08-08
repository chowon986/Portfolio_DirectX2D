#include "PreCompile.h"
#include "Bulldog.h"
#include "InGameMonsterAnimationControllerComponent.h"
#include "InGameMonsterMovementComponent.h"

Bulldog::Bulldog()
{
}

Bulldog::~Bulldog()
{
}

void Bulldog::Start()
{
	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("BulldogIntro", FrameAnimation_DESC("BulldogIntro", 0.1f));
	Renderer->AnimationBindEnd("BulldogIntro", &Bulldog::SetStateIdle, this);
	Renderer->CreateFrameAnimationFolder("BulldogIdle", FrameAnimation_DESC("BulldogIdle", 0.1f));
	Renderer->ChangeFrameAnimation("BulldogIntro");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::BOT);
	SetRenderer(Renderer);
	Prepare();

	Movement = CreateComponent<InGameMonsterMovementComponent>();
	Animation = CreateComponent<InGameMonsterAnimationControllerComponent>();
	Animation->SetMonsterName("Bulldog");
}

void Bulldog::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
}

void Bulldog::TakeDamage()
{
}

void Bulldog::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void Bulldog::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void Bulldog::Shoot()
{
}

void Bulldog::Die()
{
}

void Bulldog::SetStateIdle(const FrameAnimation_DESC& _Info)
{
	SetState(InGameMonsterState::Idle);
}
