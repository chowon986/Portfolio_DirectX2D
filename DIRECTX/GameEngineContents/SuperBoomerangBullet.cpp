#include "PreCompile.h"
#include "SuperBoomerangBullet.h"
#include "GameEngineCore/GameEngineTextureRenderer.h"
#include "BoomerangShooter.h"
#include "SuperBoomerangBulletMovementComponent.h"
#include "IInGameCharacterBase.h"
#include "InGameLevelBase.h"

SuperBoomerangBullet::SuperBoomerangBullet()
	: Weapon(nullptr)
{
}

SuperBoomerangBullet::~SuperBoomerangBullet()
{
}

void SuperBoomerangBullet::Start()
{

	Renderer = CreateComponent<GameEngineTextureRenderer>();
	Renderer->CreateFrameAnimationFolder("ConvergeA", FrameAnimation_DESC("ConvergeA", 0.1f));

	Renderer->ChangeFrameAnimation("ConvergeA");
	Renderer->ScaleToTexture();

	SuperMovementComponent = CreateComponent<SuperBoomerangBulletMovementComponent>();
	MovementComponent = SuperMovementComponent;

	Renderer->ChangeCamera(CAMERAORDER::IRISCAMERA);

}

void SuperBoomerangBullet::Update(float _DeltaTime)
{
	Renderer->ScaleToTexture();
	ElapsedTime += _DeltaTime;

	if (InGameLevelBase* Level = dynamic_cast<InGameLevelBase*>(GetLevel()))
	{
		if (IInGameCharacterBase* Character = Level->GetPlayer())
		{
			float4 CharacterPos = Character->GetTransform().GetWorldPosition();
			CharacterPos.y = CharacterPos.y + 100;
			float4 MyPos = GetTransform().GetWorldPosition();
			Direction = CharacterPos - MyPos;
			Direction.z = 0.0f;
			if (ElapsedTime > 3.0f)
			{
				if (Direction.x * Direction.x + Direction.y * Direction.y < 50 * 50)
				{
					Death();
					return;
				}
			}
			if (Direction.x * Direction.x + Direction.y * Direction.y > 400 * 400)
			{
				Direction.Normalize();
				float4 Gravity = SuperMovementComponent->GetGravity();
				if (float4::DotProduct3D(Direction, Gravity) < -0.5)
				{
					SuperMovementComponent->Reset();
					SuperMovementComponent->SetGravity(Direction);
				}
			}
		}
	}
}

void SuperBoomerangBullet::End()
{
}

void SuperBoomerangBullet::SuperBoomerangshotLoop(const FrameAnimation_DESC& _DESC)
{
	Renderer->ChangeFrameAnimation("SuperBoomerangshotLoop");
}
