#pragma once
#include "PortalBase.h"

// Ό³Έν :
class GameEngineTextureRenderer;
class Dogfight : public PortalBase
{
public:
	// constrcuter destructer
	Dogfight();
	~Dogfight();

	// delete Function
	Dogfight(const Dogfight& _Other) = delete;
	Dogfight(Dogfight&& _Other) noexcept = delete;
	Dogfight& operator=(const Dogfight& _Other) = delete;
	Dogfight& operator=(Dogfight&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	CollisionReturn OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other) override;

private:
	bool DogFightEntryBubbleOn;
};

