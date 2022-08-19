#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineTextureRenderer;
class DogCopterArms;
class InGameDogCopterAnimationControllerComponent;
class DogCopter : public IInGameMonsterBase
{
public:
	// constrcuter destructer
	DogCopter();
	~DogCopter();

	// delete Function
	DogCopter(const DogCopter& _Other) = delete;
	DogCopter(DogCopter&& _Other) noexcept = delete;
	DogCopter& operator=(const DogCopter& _Other) = delete;
	DogCopter& operator=(DogCopter&& _Other) noexcept = delete;

public:
	void OnIntroAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnIdleAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnAttack1AnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnAttack2AnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnRotateCameraAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnRotatedIdleAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnRotateCameraOutAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnAttack1AnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnRotateCameraAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnRotateCameraOutAnimationFrameChanged(const FrameAnimation_DESC& _Info);

	void OnTopPadOpenAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnTopPadCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnMidPadOpenAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnMidPadCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLowPadOpenAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLowPadCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info);

	void OnLaserTopAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserTopWarningAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserTopShootingAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserToCloseAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnLaserToCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info);

	void OnLaserMidAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserMidWarningAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserMidShootingAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	//void OnLaserToCloseAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	//void OnLaserToCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info);

	void OnLaserLowAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserLowWarningAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnLaserLowShootingAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	//void OnLaserToCloseAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	//void OnLaserToCloseAnimationFrameFinished(const FrameAnimation_DESC& _Info);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void Prepare() override;
	void Idle() override;
	void TakeDamage() override;
	void Shoot() override;
	void Die() override;
	void Attack1();
	void Attack1Start();
	void Attack2();
	void Attack2Start();
	void RotateCameraIn();
	void RotateCameraOut();
	void RotateCameraIdle();

private:
	GameEngineTextureRenderer* Renderer;
	DogCopterArms* CopterArms;
	InGameDogCopterAnimationControllerComponent* Animation;

	GameEngineTextureRenderer* ArmsRenderer;
	GameEngineTextureRenderer* WristRenderer;
	GameEngineTextureRenderer* LeftHandRenderer;
	GameEngineTextureRenderer* RightHandRenderer;

	GameEngineTextureRenderer* LeftTopPadRenderer;
	GameEngineTextureRenderer* LeftMidPadRenderer;
	GameEngineTextureRenderer* LeftLowPadRenderer;

	GameEngineTextureRenderer* RightTopPadRenderer;
	GameEngineTextureRenderer* RightMidPadRenderer;
	GameEngineTextureRenderer* RightLowPadRenderer;

	GameEngineTextureRenderer* LaserBeamTopRenderer;
	GameEngineTextureRenderer* LaserBeamMidRenderer;
	GameEngineTextureRenderer* LaserBeamLowRenderer;

	GameEngineTextureRenderer* LeftTopPadBackRenderer;
	GameEngineTextureRenderer* LeftMidPadBackRenderer;
	GameEngineTextureRenderer* LeftLowPadBackRenderer;
	GameEngineTextureRenderer* RightTopPadBackRenderer;
	GameEngineTextureRenderer* RightMidPadBackRenderer;
	GameEngineTextureRenderer* RightLowPadBackRenderer;

};

