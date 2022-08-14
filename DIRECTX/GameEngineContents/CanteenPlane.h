#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineTextureRenderer;
class IInGameCharacterBase;
class Canteen;
class CanteenPlane : public GameEngineActor
{
public:
	// constrcuter destructer
	CanteenPlane();
	~CanteenPlane();

	// delete Function
	CanteenPlane(const CanteenPlane& _Other) = delete;
	CanteenPlane(CanteenPlane&& _Other) noexcept = delete;
	CanteenPlane& operator=(const CanteenPlane& _Other) = delete;
	CanteenPlane& operator=(CanteenPlane&& _Other) noexcept = delete;

public:
	void SetPlayer(IInGameCharacterBase* _Player) { Player = _Player; }
	IInGameCharacterBase* GetPlayer() { return Player; }

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	IInGameCharacterBase* Player;
	Canteen* CaptainCanteen;
};

