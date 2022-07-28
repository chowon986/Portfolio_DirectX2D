#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class InGameCharacterState;

class InGameCharacterMovementCompmonent : public GameEngineComponent
{
public:
	// constrcuter destructer
	InGameCharacterMovementCompmonent();
	~InGameCharacterMovementCompmonent();

	// delete Function
	InGameCharacterMovementCompmonent(const InGameCharacterMovementCompmonent& _Other) = delete;
	InGameCharacterMovementCompmonent(InGameCharacterMovementCompmonent&& _Other) noexcept = delete;
	InGameCharacterMovementCompmonent& operator=(const InGameCharacterMovementCompmonent& _Other) = delete;
	InGameCharacterMovementCompmonent& operator=(InGameCharacterMovementCompmonent&& _Other) noexcept = delete;

	float4 GetDirection() const { return Direction; }
	void SetDirection(float4 _Direction) { Direction = _Direction; }

	void OnStateChanged(InGameCharacterState _State);
	void OnDirectionChanged(std::string _Dir);

private:
	void UpdateDirection();

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime);
	virtual void End();

private:
	float4 Direction;
	float Speed;
};

