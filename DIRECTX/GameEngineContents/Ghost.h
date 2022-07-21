#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "INonPlayerCharacterBase.h"
#include <string>

enum class GhostState
{
	Idle,
	Walk,
};

class GameEngineTextureRenderer;
class Ghost : public INonPlayerCharacterBase
{
public:
	// constrcuter destructer
	Ghost();
	~Ghost();

	// delete Function
	Ghost(const Ghost& _Other) = delete;
	Ghost(Ghost&& _Other) noexcept = delete;
	Ghost& operator=(const Ghost& _Other) = delete;
	Ghost& operator=(Ghost&& _Other) noexcept = delete;

public:
	void SetState(GhostState _State);
	GhostState GetState();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Talk() override;
	void Idle() override;


private:
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* HandRenderer;
	float Speed;
	GhostState State;
	std::string Dir;
};
