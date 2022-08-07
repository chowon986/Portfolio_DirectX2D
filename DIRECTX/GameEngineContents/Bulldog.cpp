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
	Renderer->ChangeFrameAnimation("BulldogIntro");
	Renderer->ScaleToTexture();
	Renderer->SetPivot(PIVOTMODE::BOT);
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
}

void Bulldog::Shoot()
{
}

void Bulldog::Die()
{
}
