#pragma once
#include "InGameLevelBase.h"

// Ό³Έν :
enum class Phase;
class GameEngineTextureRenderer;
class CharacterState;
class Chicken;
class SaltBaker;
class CharacterScore;
class Background;
class InGameCuphead;
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
	bool BackgroundMoveOn;
	bool BackgroundMoveFinished;
	bool Phase2BreakOn;

public: 	
	std::map<int, GameEngineActor*> BackgroundActor;

protected:
	void LevelStartEvent() override;
	void LevelEndEvent() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void EndAnimation(const FrameAnimation_DESC& _Info);
	void OnIrisAnimationFrameEnd(const FrameAnimation_DESC& _Info);
	void OnPh4WarningSkyAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnSaltManBustCrackAnimationFrameChanged(const FrameAnimation_DESC& _Info);
	void OnSaltManBustRightFrameChanged(const FrameAnimation_DESC& _Info);

private:
	GameEngineTextureRenderer* ColMapRenderer;
	GameEngineTextureRenderer* KitchenRenderer;
	GameEngineTextureRenderer* KitchenRendererTopper;
	GameEngineTextureRenderer* IrisRenderer;
	Phase BeforePhase;
	CharacterState* State;
	CharacterScore* Score;
	int HPCount;
	int RendererNum;
	int ActorNum;
	bool OnceCheck;
	bool OldFilmOnceCheck;
	bool TornadoCheck;
	float BreakTime;
	float ElapsedTime;
	float PlayElapsedTime;
	float OldFilmElapsedTime;
	float TornadoElapsedTime;
	SaltBaker* Ph1Boss;
	Chicken* Ph1Monster;
	Background* KitchenTopper;
	Background* Kitchen;
	std::map<int, GameEngineActor*> BreakObjectActor;
	std::map<int, GameEngineActor*> LittleTornadoActor;
	InGameCuphead* Cuphead;
	bool OldFilmTimeCountOn;
};

