#pragma once
#include "PortalBase.h"

// Ό³Έν :
class GameEngineTextureRenderer;
class Ladder : public PortalBase
{
public:
	// constrcuter destructer
	Ladder();
	~Ladder();

	// delete Function
	Ladder(const Ladder& _Other) = delete;
	Ladder(Ladder&& _Other) noexcept = delete;
	Ladder& operator=(const Ladder& _Other) = delete;
	Ladder& operator=(Ladder&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
};

