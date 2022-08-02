#pragma once
#include "PortalBase.h"

// Ό³Έν :
class GameEngineTextureRenderer;
class Rumrunners : public PortalBase
{
public:
	// constrcuter destructer
	Rumrunners();
	~Rumrunners();

	// delete Function
	Rumrunners(const Rumrunners& _Other) = delete;
	Rumrunners(Rumrunners&& _Other) noexcept = delete;
	Rumrunners& operator=(const Rumrunners& _Other) = delete;
	Rumrunners& operator=(Rumrunners&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

};

