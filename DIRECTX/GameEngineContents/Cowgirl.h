#pragma once
#include "PortalBase.h"

// Ό³Έν :
class GameEngineTextureRenderer;
class Cowgirl : public PortalBase
{
public:
	// constrcuter destructer
	Cowgirl();
	~Cowgirl();

	// delete Function
	Cowgirl(const Cowgirl& _Other) = delete;
	Cowgirl(Cowgirl&& _Other) noexcept = delete;
	Cowgirl& operator=(const Cowgirl& _Other) = delete;
	Cowgirl& operator=(Cowgirl&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
};

