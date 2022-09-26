#pragma once
#include "InGameLevelBase.h"

// Ό³Έν :
enum class Phase;
class GameEngineTextureRenderer;
class CharacterState;
class Chicken;
class SaltBaker;
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

public:
	SaltBaker* GetSaltBaker() { return Ph1Boss; }
	Chicken* GetChicken() { return Ph1Monster; }
	GameEngineTextureRenderer* OldFilmRenderer;
	bool AlphaSettingOn;

protected:
	void LevelStartEvent() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void EndAnimation(const FrameAnimation_DESC& _Info);
	void OnIrisAnimationFrameEnd(const FrameAnimation_DESC& _Info);

private:
	GameEngineTextureRenderer* ColMapRenderer;
	GameEngineTextureRenderer* KitchenRenderer;
	GameEngineTextureRenderer* IrisRenderer;
	Phase BeforePhase;
	int HPCount;
	CharacterState* State;
	float ElapsedTime;
	bool OnceCheck;
	SaltBaker* Ph1Boss;
	Chicken* Ph1Monster;
};

