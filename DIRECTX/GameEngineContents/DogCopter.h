#pragma once
#include "IInGameMonsterBase.h"

enum class InGameMonsterState;
enum class InGameMonsterAttackState;
class GameEngineTextureRenderer;
class DogCopterArms;
class InGameMonsterAnimationControllerComponent;
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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void Prepare() override;
	void Idle() override;
	void TakeDamage() override;
	void Shoot() override;
	void Die() override;

private:
	GameEngineTextureRenderer* Renderer;
	DogCopterArms* CopterArms;
	InGameMonsterAnimationControllerComponent* Animation;
};

