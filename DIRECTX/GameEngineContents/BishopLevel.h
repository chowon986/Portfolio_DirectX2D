#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class InGameCuphead;
class Pawn;
class GameEngineTextureRenderer;
class BishopLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BishopLevel();
	~BishopLevel();

	// delete Function
	BishopLevel(const BishopLevel& _Other) = delete;
	BishopLevel(BishopLevel&& _Other) noexcept = delete;
	BishopLevel& operator=(const BishopLevel& _Other) = delete;
	BishopLevel& operator=(BishopLevel&& _Other) noexcept = delete;

protected:
	void Start() override {}
	void LevelStartEvent() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void ColMapOnOffSwitch();
	CollisionReturn OnIndexCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn IndexCollisionOn(GameEngineCollision* _This, GameEngineCollision* _Other);

private:
	GameEngineTextureRenderer* BackgroundRenderer;
	GameEngineTextureRenderer* ColMapRenderer;
	InGameCuphead* Cuphead;
	GameEngineTexture* ColMapTexture;
	std::vector<float> PawnPosX;
	std::vector<Pawn*> BossPawnActors;
	GameEngineCollision* IndexCollisionA;
	GameEngineCollision* IndexCollisionB;
	GameEngineCollision* IndexCollisionC;
	GameEngineCollision* IndexCollisionD;
	GameEngineCollision* IndexCollisionE;
	GameEngineCollision* IndexCollisionF;
	GameEngineCollision* IndexCollisionG;
	GameEngineCollision* IndexCollisionH;
	std::vector<GameEngineCollision*> Collisions;
	std::vector<float> AttackIntervalTimes;
};

