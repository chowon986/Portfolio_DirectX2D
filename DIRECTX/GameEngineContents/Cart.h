#pragma once
#include "PortalBase.h"

// Ό³Έν :
class GameEngineTextureRenderer;
class Cart : public PortalBase
{
public:
	// constrcuter destructer
	Cart();
	~Cart();

	// delete Function
	Cart(const Cart& _Other) = delete;
	Cart(Cart&& _Other) noexcept = delete;
	Cart& operator=(const Cart& _Other) = delete;
	Cart& operator=(Cart&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	CollisionReturn OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other) override;
};

