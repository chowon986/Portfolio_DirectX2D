#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class BackgroundObject : public GameEngineActor
{
public:
	// constrcuter destructer
	BackgroundObject();
	~BackgroundObject();

	// delete Function
	BackgroundObject(const BackgroundObject& _Other) = delete;
	BackgroundObject(BackgroundObject&& _Other) noexcept = delete;
	BackgroundObject& operator=(const BackgroundObject& _Other) = delete;
	BackgroundObject& operator=(BackgroundObject&& _Other) noexcept = delete;

public:
	void SetRenderer(GameEngineTextureRenderer* _Renderer);
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

	void SetDirection(float4 _Direction);
	float4 GetDirection() { return Direction; }

	void SetMoveSpeed(float _MoveSpeed);
	float GetMoveSpeed() { return MoveSpeed; }

	void SetStartPosition(float4 _StartPosition);
	float4 GetStartPosition() { return StartPosition; }


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* Renderer;
	float4 Direction;
	float4 StartPosition;
	float MoveSpeed;
};

