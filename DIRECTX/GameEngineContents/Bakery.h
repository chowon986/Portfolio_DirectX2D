#pragma once
#include "PortalBase.h"

// Ό³Έν :
class GameEngineTextureRenderer;
class Bakery : public PortalBase
{
public:
	// constrcuter destructer
	Bakery();
	~Bakery();

	// delete Function
	Bakery(const Bakery& _Other) = delete;
	Bakery(Bakery&& _Other) noexcept = delete;
	Bakery& operator=(const Bakery& _Other) = delete;
	Bakery& operator=(Bakery&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	CollisionReturn OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other) override;
};

