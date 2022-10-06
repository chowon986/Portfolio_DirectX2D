#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class IInGameCharacterBase;
class PlayerCard : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerCard();
	~PlayerCard();

	// delete Function
	PlayerCard(const PlayerCard& _Other) = delete;
	PlayerCard(PlayerCard&& _Other) noexcept = delete;
	PlayerCard& operator=(const PlayerCard& _Other) = delete;
	PlayerCard& operator=(PlayerCard&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

public:
	void SetPlayer(IInGameCharacterBase* _Player) { Player = _Player; }
	IInGameCharacterBase* GetPlayer() { return Player; }
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

private:
	GameEngineTextureRenderer* Renderer;
	IInGameCharacterBase* Player;
};

