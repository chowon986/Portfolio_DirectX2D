#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class InGameCharacterState;
class InGameCharacterAnimationControllerComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	InGameCharacterAnimationControllerComponent();
	~InGameCharacterAnimationControllerComponent();

	// delete Function
	InGameCharacterAnimationControllerComponent(const InGameCharacterAnimationControllerComponent& _Other) = delete;
	InGameCharacterAnimationControllerComponent(InGameCharacterAnimationControllerComponent&& _Other) noexcept = delete;
	InGameCharacterAnimationControllerComponent& operator=(const InGameCharacterAnimationControllerComponent& _Other) = delete;
	InGameCharacterAnimationControllerComponent& operator=(InGameCharacterAnimationControllerComponent&& _Other) noexcept = delete;


	void OnStateChanged(InGameCharacterState _State);
	void OnVerticalDirectionChanged(std::string _Dir);
	void OnHorizontalDirectionChanged(std::string _Dir);
	void OnIdleDownStartAnimationEnded(const FrameAnimation_DESC& _Info);

	void SetCharacterName(std::string _CharacterName);
	std::string GetCharacterName() { return CharacterName; }

private:
	void UpdateAnimation();


protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);
	virtual void End();

private:
	std::string CharacterName;
	bool IsIdleDownStartAnimationChanged;
	std::string BeforeDir;
};

