#pragma once
#include <GameEngineCore/GameEngineComponent.h>

enum class InGameCharacterState;
class IInGameCharacterBase;
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
	bool CanMoveAreaCheck();
	bool IsOnGround();

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	GameEngineTextureRenderer* ColMapImage;
	GameEngineTexture* ColMapTexture;
	IInGameCharacterBase* InGameCharacter;
	float4 Direction;
	float Speed;
	float DropSpeed;
	float Gravity;
	float JumpHeight;
	float4 DownDir;
	float4 RightColor;
	float4 RightUpColor;
	float4 RightDownColor;
	float4 Transform;
	float4 LeftColor;
	float4 LeftUpColor;
	float4 LeftDownColor;
	float4 CurrentColor;
	float4 UpColor;
	float4 DownColor;
	std::string VerticalDir;
		std::string HorizontalDir;
};

