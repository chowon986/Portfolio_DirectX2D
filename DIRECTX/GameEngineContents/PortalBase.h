#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineCollision;
class GameEngineTextureRenderer;
class PortalBase : public GameEngineActor
{
public:
	// constrcuter destructer
	PortalBase();
	~PortalBase();

	// delete Function
	PortalBase(const PortalBase& _Other) = delete;
	PortalBase(PortalBase&& _Other) noexcept = delete;
	PortalBase& operator=(const PortalBase& _Other) = delete;
	PortalBase& operator=(PortalBase&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

protected:
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* PortalRenderer;
	GameEngineCollision* Collision;

protected:
	bool OnPortalCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
};

