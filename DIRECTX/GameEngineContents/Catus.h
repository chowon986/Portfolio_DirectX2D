#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "INonPlayerCharacterBase.h"
#include <string>

enum class CatusState
{
	Idle,
	Walk,
};

class GameEngineTextureRenderer;
class Catus : public INonPlayerCharacterBase
{
public:
	// constrcuter destructer
	Catus();
	~Catus();

	// delete Function
	Catus(const Catus& _Other) = delete;
	Catus(Catus&& _Other) noexcept = delete;
	Catus& operator=(const Catus& _Other) = delete;
	Catus& operator=(Catus&& _Other) noexcept = delete;

public:
	void SetState(CatusState _State);
	CatusState GetState();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Talk() override;
	void Idle() override;


private:
	GameEngineTextureRenderer* Renderer;
	float Speed;
	CatusState State;
	std::string Dir;
};
