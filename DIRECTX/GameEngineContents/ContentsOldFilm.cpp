#include "PreCompile.h"
#include "ContentsOldFilm.h"
#include <GameEngineBase/GameEngineWindow.h>

ContentsOldFilm::ContentsOldFilm()
	: CopyTarget(nullptr)
	, OldFilmTexture(nullptr)
{
}

ContentsOldFilm::~ContentsOldFilm()
{
	if (nullptr != CopyTarget)
	{
		delete CopyTarget;
		CopyTarget = nullptr;
	}
}

void ContentsOldFilm::EffectInit()
{
	CopyTarget = new GameEngineRenderTarget();
	CopyTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	OldFilmTexture = GameEngineFolderTexture::Find("03ScreenFX");

	EffectSet.SetPipeLine("OldFilm");
}

void ContentsOldFilm::Effect(GameEngineRenderTarget* _Target)
{
	CopyTarget->Copy(_Target);

	//EffectSet.ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));
	EffectSet.ShaderResources.SetTexture("Tex", OldFilmTexture->GetTexture(0));

	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);
}