#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "INonPlayerCharacterBase.h"
#include <string>

enum class ShovelState
{
	Idle,
	Walk,
};

class GameEngineTextureRenderer;
class Shovel : public INonPlayerCharacterBase
{
public:
	// constrcuter destructer
	Shovel();
	~Shovel();

	// delete Function
	Shovel(const Shovel& _Other) = delete;
	Shovel(Shovel&& _Other) noexcept = delete;
	Shovel& operator=(const Shovel& _Other) = delete;
	Shovel& operator=(Shovel&& _Other) noexcept = delete;

public:
	void SetState(ShovelState _State);
	ShovelState GetState();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Talk() override;
	void Idle() override;


private:
	GameEngineTextureRenderer* Renderer;
	float Speed;
	ShovelState State;
	std::string Dir;
};
