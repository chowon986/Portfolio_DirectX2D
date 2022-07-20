#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "INonPlayerCharacterBase.h"
#include <string>

enum class PickaxeState
{
	Idle,
	Walk,
};

class GameEngineTextureRenderer;
class Pickaxe : public INonPlayerCharacterBase
{
public:
	// constrcuter destructer
	Pickaxe();
	~Pickaxe();

	// delete Function
	Pickaxe(const Pickaxe& _Other) = delete;
	Pickaxe(Pickaxe&& _Other) noexcept = delete;
	Pickaxe& operator=(const Pickaxe& _Other) = delete;
	Pickaxe& operator=(Pickaxe&& _Other) noexcept = delete;

public:
	void SetState(PickaxeState _State);
	PickaxeState GetState();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Talk() override;
	void Idle() override;


private:
	GameEngineTextureRenderer* Renderer;
	float Speed;
	PickaxeState State;
	std::string Dir;
};
