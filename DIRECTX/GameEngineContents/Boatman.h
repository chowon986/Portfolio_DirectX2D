#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "INonPlayerCharacterBase.h"
#include <string>

enum class BoatmanState
{
	Idle,
	Walk,
};

class GameEngineTextureRenderer;
class Boatman : public INonPlayerCharacterBase
{
public:
	// constrcuter destructer
	Boatman();
	~Boatman();

	// delete Function
	Boatman(const Boatman& _Other) = delete;
	Boatman(Boatman&& _Other) noexcept = delete;
	Boatman& operator=(const Boatman& _Other) = delete;
	Boatman& operator=(Boatman&& _Other) noexcept = delete;

public:
	void SetState(BoatmanState _State);
	BoatmanState GetState();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Talk() override;
	void Idle() override;


private:
	GameEngineTextureRenderer* Renderer;
	float Speed;
	BoatmanState State;
	std::string Dir;
};
