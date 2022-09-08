#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class TutorialPhase
{
	Phase1,
	Phase2,
	Phase3,
};
// Ό³Έν :
class GameEngineTextureRenderer;
class InGameCuphead;
class TutorialLevel : public GameEngineLevel
{
public:
	TutorialLevel();
	~TutorialLevel();

	// delete Function
	TutorialLevel(const TutorialLevel& _Other) = delete;
	TutorialLevel(TutorialLevel&& _Other) noexcept = delete;
	TutorialLevel& operator=(const TutorialLevel& _Other) = delete;
	TutorialLevel& operator=(TutorialLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

private:
	GameEngineTextureRenderer* BackgroundRenderer;
	GameEngineTextureRenderer* ColMapRenderer;
	GameEngineTextureRenderer* WheatARenderer;
	GameEngineTextureRenderer* WheatBRenderer;
	GameEngineTextureRenderer* WheatCRenderer;
	GameEngineTextureRenderer* RipRenderer;
	GameEngineActor* WheatA;
	GameEngineActor* WheatB;
	GameEngineActor* WheatC;
	GameEngineActor* Rip;
	GameEngineCollision* WheatACollision;
	GameEngineCollision* WheatBCollision;
	GameEngineCollision* WheatCCollision;
	GameEngineCollision* RipCollision;
	bool IsWheatAParriable;
	bool IsWheatBParriable;
	bool IsWheatCParriable;

	bool OnWheatACollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool OnWheatBCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool OnWheatCCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool OnRipCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

	void SetPhase(TutorialPhase _Phase) { CurPhase = _Phase; }
	TutorialPhase GetPhase() { return CurPhase; }

private:
	TutorialPhase CurPhase;
	InGameCuphead* Cuphead;
};

