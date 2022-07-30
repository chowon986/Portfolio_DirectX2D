#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class WorldMapCharacterState;
class WorldMapCharacterAnimationControllerComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	WorldMapCharacterAnimationControllerComponent();
	~WorldMapCharacterAnimationControllerComponent();

	// delete Function
	WorldMapCharacterAnimationControllerComponent(const WorldMapCharacterAnimationControllerComponent& _Other) = delete;
	WorldMapCharacterAnimationControllerComponent(WorldMapCharacterAnimationControllerComponent&& _Other) noexcept = delete;
	WorldMapCharacterAnimationControllerComponent& operator=(const WorldMapCharacterAnimationControllerComponent& _Other) = delete;
	WorldMapCharacterAnimationControllerComponent& operator=(WorldMapCharacterAnimationControllerComponent&& _Other) noexcept = delete;


	void OnStateChanged(WorldMapCharacterState _State);
	void OnDirectionChanged(std::string _Dir);

	void SetCharacterName(std::string _CharacterName)
	{
		CharacterName = _CharacterName;
	}
	std::string GetCharacterName() { return CharacterName; }

private:
	void UpdateAnimation();

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	std::string CharacterName;
};

