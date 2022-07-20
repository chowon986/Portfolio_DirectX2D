#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "INonPlayerCharacterBase.h"
#include <string>

enum class LanternState
{
	Idle,
	Walk,
};

class GameEngineTextureRenderer;
class Lantern : public INonPlayerCharacterBase
{
public:
	// constrcuter destructer
	Lantern();
	~Lantern();

	// delete Function
	Lantern(const Lantern& _Other) = delete;
	Lantern(Lantern&& _Other) noexcept = delete;
	Lantern& operator=(const Lantern& _Other) = delete;
	Lantern& operator=(Lantern&& _Other) noexcept = delete;

public:
	void SetState(LanternState _State);
	LanternState GetState();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Talk() override;
	void Idle() override;


private:
	GameEngineTextureRenderer* Renderer;
	float Speed;
	LanternState State;
	std::string Dir;
};
