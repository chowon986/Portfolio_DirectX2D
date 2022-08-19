#pragma once
#include <GameEngineContents/Enums.h>
#include <GameEngineCore/GameEngineActor.h>

class CharacterState : public GameEngineActor
{
public:
	// constrcuter destructer
	CharacterState();
	~CharacterState();

	// delete Function
	CharacterState(const CharacterState& _Other) = delete;
	CharacterState(CharacterState&& _Other) noexcept = delete;
	CharacterState& operator=(const CharacterState& _Other) = delete;
	CharacterState& operator=(CharacterState&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

public:
	CharacterType Type;
	int HP;
};

