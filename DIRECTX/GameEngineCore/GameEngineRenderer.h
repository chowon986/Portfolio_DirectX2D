#pragma once
#include "GameEngineTransformComponent.h"
#include "GameEngineLevel.h"

struct RenderOption
{
	float DeltaTime = 0.0f;
	float SumDeltaTime = 0.0f;
	int ColorInversion;
	int Temp;
};
//
//class GameEngineRenderSet 
//{
//public:
//    // 이미 만들어진 랜더링 파이프라인을 얻어와서 쓴다.
//    GameEngineRenderingPipeLine* PipeLine;
//    GameEngineShaderResourcesHelper ShaderHelper;
//
//
//
//};

// 설명 :
class GameEngineRenderingPipeLine;
class GameEngineRenderer : public GameEngineTransformComponent
{
	friend class GameEngineLevel;
	friend class GameEngineCamera;

public:
	RenderOption renderOption;

	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	// float4x4 ViewPort;
	void ChangeCamera(CAMERAORDER _Order);

	GameEngineRenderingPipeLine* GetClonePipeLine(GameEngineRenderingPipeLine* _Rendering);

	inline int GetRenderingOrder()
	{
		return RenderingOrder;
	}

	void SetRenderingOrder(int _Order);

	virtual void InstancingOn()
	{
		IsInstancing = true;
	};

protected:
	virtual void Start();
	virtual void Update(float _DeltaTime) {}
	virtual void End() {}

	void PushRendererToMainCamera();
	void PushRendererToUICamera();
	void PushRendererToUICamera2();
	void PushRendererToDarknessCamera();

	class GameEngineCamera* Camera;
	CAMERAORDER CameraOrder;
	int RenderingOrder;
	bool IsInstancing;

private:
	virtual void Render(float _DeltaTime) = 0;

};

