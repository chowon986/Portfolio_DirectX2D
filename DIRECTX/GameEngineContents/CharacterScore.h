#pragma once
#include <GameEngineContents/Enums.h>
#include <GameEngineCore/GameEngineActor.h>

class ItemBase;
class CharacterScore : public GameEngineActor
{
public:
	// constrcuter destructer
	CharacterScore();
	~CharacterScore();

	// delete Function
	CharacterScore(const CharacterScore& _Other) = delete;
	CharacterScore(CharacterScore&& _Other) noexcept = delete;
	CharacterScore& operator=(const CharacterScore& _Other) = delete;
	CharacterScore& operator=(CharacterScore&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

public:
	float PlayTime;
	int HP;
	int Parry;
	int UseCard;
	int SkillLevel;
	std::string Score;
};

