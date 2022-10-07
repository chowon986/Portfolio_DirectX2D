#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

class IWorldMapCharacterBase;
enum class WorldMapCharacterState;
class GameEngineTextureRenderer;
class WorldMapCharacterDust : public GameEngineActor
{
public:
	WorldMapCharacterDust();
	~WorldMapCharacterDust();

	WorldMapCharacterDust(const WorldMapCharacterDust& _Other) = delete;
	WorldMapCharacterDust(WorldMapCharacterDust&& _Other) noexcept = delete;
	WorldMapCharacterDust& operator=(const WorldMapCharacterDust& _Other) = delete;
	WorldMapCharacterDust& operator=(WorldMapCharacterDust&& _Other) noexcept = delete;

public:
	void SetBoss(IWorldMapCharacterBase* _Boss) { Boss = _Boss; }
	IWorldMapCharacterBase* GetBoss() { return Boss; }

	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

private:
	void OnDustAnimationFrameFinished(const FrameAnimation_DESC& _Info);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	IWorldMapCharacterBase* Boss;
	GameEngineTextureRenderer* Renderer;
	float ElapsedTime;
	WorldMapCharacterState BeforeState;
};

