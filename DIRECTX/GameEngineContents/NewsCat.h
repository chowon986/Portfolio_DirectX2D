#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "INonPlayerCharacterBase.h"
#include <string>

enum class NewsCatState
{
	Idle,
	Walk,
};

class GameEngineTextureRenderer;
class NewsCat : public INonPlayerCharacterBase
{
public:
	// constrcuter destructer
	NewsCat();
	~NewsCat();

	// delete Function
	NewsCat(const NewsCat& _Other) = delete;
	NewsCat(NewsCat&& _Other) noexcept = delete;
	NewsCat& operator=(const NewsCat& _Other) = delete;
	NewsCat& operator=(NewsCat&& _Other) noexcept = delete;

public:
	void SetState(NewsCatState _State);
	NewsCatState GetState();

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
	void Talk() override;
	void Idle() override;


private:
	GameEngineTextureRenderer* Renderer;
	float Speed;
	NewsCatState State;
	std::string Dir;
};
