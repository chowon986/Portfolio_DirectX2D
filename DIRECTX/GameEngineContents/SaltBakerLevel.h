#pragma once
#include "InGameLevelBase.h"

// Ό³Έν :
enum class Phase;
class GameEngineTextureRenderer;
class CharacterState;
class SaltBakerLevel : public InGameLevelBase
{
public:
	// constrcuter destructer
	SaltBakerLevel();
	~SaltBakerLevel();

	// delete Function
	SaltBakerLevel(const SaltBakerLevel& _Other) = delete;
	SaltBakerLevel(SaltBakerLevel&& _Other) noexcept = delete;
	SaltBakerLevel& operator=(const SaltBakerLevel& _Other) = delete;
	SaltBakerLevel& operator=(SaltBakerLevel&& _Other) noexcept = delete;

protected:
	void LevelStartEvent() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void EndAnimation(const FrameAnimation_DESC& _Info);

private:
	GameEngineTextureRenderer* ColMapRenderer;
	GameEngineTextureRenderer* KitchenRenderer;
	Phase BeforePhase;
	int HPCount;
	CharacterState* State;
};

