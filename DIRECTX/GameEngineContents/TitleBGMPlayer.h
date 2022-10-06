#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TitleBGMPlayer : public GameEngineActor
{
public:
	TitleBGMPlayer();
	~TitleBGMPlayer();

	// delete Function
	TitleBGMPlayer(const TitleBGMPlayer& _Other) = delete;
	TitleBGMPlayer(TitleBGMPlayer&& _Other) noexcept = delete;
	TitleBGMPlayer& operator=(const TitleBGMPlayer& _Other) = delete;
	TitleBGMPlayer& operator=(TitleBGMPlayer&& _Other) noexcept = delete;

public:
	GameEngineSoundPlayer BGMPlayer;
};

