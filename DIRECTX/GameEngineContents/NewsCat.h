#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "INonPlayerCharacterBase.h"
#include <string>

enum class NewsCatState
{
	Idle,
	Talk,
};

class GameEngineUIRenderer;
class GameEngineCollision;
class GameEngineTextureRenderer;
class NewsCat : public INonPlayerCharacterBase
{
public:
	// constrcuter destructer
	NewsCat();
	~NewsCat();

	// delete Function
	NewsCat(const NewsCat& _Other) = delete;
	NewsCat(NewsCat&& _Other) noexcept = delete;
	NewsCat& operator=(const NewsCat& _Other) = delete;
	NewsCat& operator=(NewsCat&& _Other) noexcept = delete;

public:
	void SetState(NewsCatState _State);
	NewsCatState GetState();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Talk() override;
	void Idle() override;

private:
	CollisionReturn OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	void GiveCoin();

private:
	GameEngineCollision* Collision;
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* TalkBubbleRenderer;
	GameEngineTextureRenderer* BackgroundRenderer;
	NewsCatState State;
	NewsCatState BeforeState;
	int CurAnimationNum;
	bool OnceCheck;
	float ElapsedTime;
	std::vector<GameEngineTextureRenderer*> CoinRenderers;
};
