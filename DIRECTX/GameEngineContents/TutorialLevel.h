#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum class TutorialPhase
{
	Phase1,
	Phase2,
	Phase3,
};
// ���� :
class GameEngineTextureRenderer;
class InGameCuphead;
class CharacterState;
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
	void LevelStartEvent() override;
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void ColMapOnOffSwitch();
private:
	GameEngineTextureRenderer* TutorialRenderer;
	GameEngineTextureRenderer* BackgroundRenderer;
	GameEngineTextureRenderer* ColMapRenderer;
	GameEngineTextureRenderer* WheatARenderer;
	GameEngineTextureRenderer* WheatBRenderer;
	GameEngineTextureRenderer* WheatCRenderer;
	GameEngineTextureRenderer* RipRenderer;
	GameEngineTextureRenderer* CoinRenderer;
	GameEngineTextureRenderer* EnterRenderer;
	GameEngineActor* WheatA;
	GameEngineActor* WheatB;
	GameEngineActor* WheatC;
	GameEngineActor* Coin;
	GameEngineActor* Rip;
	GameEngineCollision* WheatACollision;
	GameEngineCollision* WheatBCollision;
	GameEngineCollision* WheatCCollision;
	GameEngineCollision* RipCollision;
	GameEngineCollision* CoinCollision;
	GameEngineCollision* EnterCollision;


	bool IsWheatAParriable;
	bool IsWheatBParriable;
	bool IsWheatCParriable;

	bool OnWheatACollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool OnWheatBCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool OnWheatCCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool OnRipCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool OnCoinCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

	void OnTutorialCoinDeathAnimationFinished(const FrameAnimation_DESC& _Info);
	void OnTutorialStartBackgroundAnimationEnd(const FrameAnimation_DESC& _Info);
	void OnTutorialBackgroundAnimationEnd(const FrameAnimation_DESC& _Info);

	void SetPhase(TutorialPhase _Phase) { CurPhase = _Phase; }
	TutorialPhase GetPhase() { return CurPhase; }

	bool IsObjectOn;

private:
	CharacterState* State;
	TutorialPhase CurPhase;
	InGameCuphead* Cuphead;
	int CurCoin;
};

