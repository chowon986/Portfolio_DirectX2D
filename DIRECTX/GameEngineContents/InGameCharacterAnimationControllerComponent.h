#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class InGameCharacterState;
enum class InGameCharacterAttackState;
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
	void OnAttackStateChanged(InGameCharacterAttackState _AttackState);
	void OnVerticalDirectionChanged(std::string _Dir);
	void OnHorizontalDirectionChanged(std::string _Dir);
	void OnIdleDownStartAnimationEnded(const FrameAnimation_DESC& _Info);
	void OnIsOnGroundChanged(bool _IsOnGround);

	void SetCharacterName(std::string _CharacterName);
	std::string GetCharacterName() { return CharacterName; }

private:
	void UpdateAnimation();


protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	std::string CharacterName;
	bool IsIdleDownStartAnimationChanged;
	std::string BeforeDir;
};

