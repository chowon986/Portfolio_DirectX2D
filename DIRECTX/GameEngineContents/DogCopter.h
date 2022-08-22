#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineTextureRenderer;
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
	void OnIdleAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnRotateCameraAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnRotatedIdleAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnRotateCameraOutAnimationFrameFinished(const FrameAnimation_DESC& _Info);
	void OnRotateCameraAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnRotateCameraOutAnimationFrameChanged(const FrameAnimation_DESC& _Info);

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
	void Attack2();
	void RotateCameraIn();
	void RotateCameraOut();
	void RotateCameraIdle();
	void BeforeRoateCameraIn();

private:
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* ArmsRenderer;
	GameEngineTextureRenderer* WristRenderer;
	GameEngineTextureRenderer* LeftHandRenderer;
	GameEngineTextureRenderer* RightHandRenderer;
};

