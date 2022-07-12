#include "PreCompile.h"
#include "ContentsCore.h"
#include "GameEngineContents/TitleLevel.h"
#include "GameEngineContents/PlayLevel.h"

#pragma comment(lib, "GameEngineBase.lib")

ContentsCore::ContentsCore() 
	: GameEngineCore()
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	//CreateLevel<TitleLevel>("Title");
	//CreateLevel<PlayLevel>("Play");
	//ChangeLevel("Play");
}

void ContentsCore::Update(float _DeltaTime)
{
	
	
}

void ContentsCore::End()
{
	int a = 0;
}