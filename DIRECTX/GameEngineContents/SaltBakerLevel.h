#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class SaltBakerLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SaltBakerLevel();
	~SaltBakerLevel();

	// delete Function
	SaltBakerLevel(const SaltBakerLevel& _Other) = delete;
	SaltBakerLevel(SaltBakerLevel&& _Other) noexcept = delete;
	SaltBakerLevel& operator=(const SaltBakerLevel& _Other) = delete;
	SaltBakerLevel& operator=(SaltBakerLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
private:
	void EndAnimation(const FrameAnimation_DESC& _Info);

private:
	GameEngineTextureRenderer* ColMapRenderer;
	GameEngineTextureRenderer* KitchenRenderer;
};

