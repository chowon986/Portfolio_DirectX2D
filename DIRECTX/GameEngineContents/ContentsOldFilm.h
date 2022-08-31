#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineRenderSet.h>

// Ό³Έν :
class ContentsOldFilm : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	ContentsOldFilm();
	~ContentsOldFilm();

	// delete Function
	ContentsOldFilm(const ContentsOldFilm& _Other) = delete;
	ContentsOldFilm(ContentsOldFilm&& _Other) noexcept = delete;
	ContentsOldFilm& operator=(const ContentsOldFilm& _Other) = delete;
	ContentsOldFilm& operator=(ContentsOldFilm&& _Other) noexcept = delete;

	virtual void EffectInit();
	virtual void Effect(GameEngineRenderTarget* _Render);

protected:
	GameEngineRenderTarget* CopyTarget;
	GameEngineRenderSet EffectSet;

private:
};

