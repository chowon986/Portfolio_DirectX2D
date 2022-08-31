#include "PreCompile.h"
#include "ContentsOldFilm.h"
#include <GameEngineBase/GameEngineWindow.h>

ContentsOldFilm::ContentsOldFilm()
	: CopyTarget(nullptr)
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

	EffectSet.SetPipeLine("TextureAtlas");
	EffectSet.GetPipeLine()->SetOutputMergerBlend("OldFilm");
	// EffetSet
}

void ContentsOldFilm::Effect(GameEngineRenderTarget* _Target)
{
	CopyTarget->Copy(_Target);

	EffectSet.ShaderResources.SetTexture("Tex", CopyTarget->GetRenderTargetTexture(0));
	_Target->Clear();
	_Target->Setting();
	_Target->Effect(EffectSet);
}