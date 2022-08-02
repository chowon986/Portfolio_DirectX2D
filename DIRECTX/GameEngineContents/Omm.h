#pragma once
#include "PortalBase.h"

// Ό³Έν :
class GameEngineTextureRenderer;
class Omm : public PortalBase
{
public:
	// constrcuter destructer
	Omm();
	~Omm();

	// delete Function
	Omm(const Omm& _Other) = delete;
	Omm(Omm&& _Other) noexcept = delete;
	Omm& operator=(const Omm& _Other) = delete;
	Omm& operator=(Omm&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};

