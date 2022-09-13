#pragma once
#include "BulletBase.h"

class GameEngineCollision;
class BulletMovementComponent;
class GameEngineTextureRenderer;
class LeafBullet : public BulletBase
{
public:
	LeafBullet();
	~LeafBullet();
	LeafBullet(const LeafBullet& _Other) = delete;
	LeafBullet(LeafBullet&& _Other) noexcept = delete;
	LeafBullet& operator=(const LeafBullet& _Other) = delete;
	LeafBullet& operator=(LeafBullet&& _Other) noexcept = delete;

public:
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }
	void SetRenderer(GameEngineTextureRenderer* _Renderer) { Renderer = _Renderer; }

	std::string GetStartPosName() { return StartPosName; }
	void SetStartPosName(std::string _Pos) { StartPosName = _Pos; }

	void SetIndexNum(int _Num) { IndexNum = _Num; }
	int GetIndexName() { return IndexNum; }

private:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
	virtual void End() override;

private:
	GameEngineCollision* Collision;
	float LerpTime;
	float ElapsedTime;
	std::string StartPosName;
	std::map<int, float> StartPosX;
	std::map<int, float> DestPosX;
	bool IsLeafPosRightEnd;
	float4 LerpPos;
	int IndexNum;
};

