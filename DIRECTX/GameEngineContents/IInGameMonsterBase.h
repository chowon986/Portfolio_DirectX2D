#pragma once
#include "Delegates.h"
#include "IDamageable.h"
#include "IDieable.h"
#include "IIdleable.h"
#include "IPreparable.h"
#include "IShootable.h"
#include "GameEngineCore/GameEngineActor.h"

enum class InGameDogCopterState
{
	Prepare,
	RotatedIdle,
	Idle,
	Attack,
	TakeDamage,
	RotateCamera,
	RotateCameraOut,
	Die
};

enum class InGamePh2DogState
{
	Prepare1,
	Prepare2,
	Prepare3,
	Prepare4,
	Idle,
	Attack,
	TakeDamage,
	Die,
	None,
};

enum class InGameMonsterState
{
	Prepare, // �Ϸ�
	Idle, // �Ϸ�
	TakeDamage,
	Unmount,
	Mount,
	Die,
	Enter,
	Attack1,
	Attack2,
	Attack3,
	Attack4,
	Attack5,
	PrepareAttack1,
	PrepareAttack2,
	AttackFinish1,
	AttackFinish2,
	LookRight,
	LookLeft,
	Blink,
	Look,
};

enum class InGameMonsterAttackState
{
	None,
	YarnBall1, // Yellow
	YarnBall2, // Green
	YarnBall3, // Red
	Tattoo1,
	Tattoo2,
	Tattoo3, // Pink
	TennisBall,
	BowWow,
};

enum class Phase;
class BulldogPlane;
class IInGameMonsterBase : public GameEngineActor, public IDamageable, public IDieable, public IPreparable, public IIdleable, public IShootable
{
public:
	// constrcuter destructer
	IInGameMonsterBase();
	~IInGameMonsterBase();

	// delete Function
	IInGameMonsterBase(const IInGameMonsterBase& _Other) = delete;
	IInGameMonsterBase(IInGameMonsterBase&& _Other) noexcept = delete;
	IInGameMonsterBase& operator=(const IInGameMonsterBase& _Other) = delete;
	IInGameMonsterBase& operator=(IInGameMonsterBase&& _Other) noexcept = delete;

public:
	void SetState(InGameMonsterState _State);
	InGameMonsterState GetState() { return  State; }

	void SetPh2DogState(InGamePh2DogState _State);
	InGamePh2DogState GetPh2DogState() { return  Ph2DogState; }

	void SetDogCopterState(InGameDogCopterState _State);
	InGameDogCopterState GetDogCopterState() { return  DogCopterState; }

	virtual void SetAttackState(InGameMonsterAttackState _State);
	InGameMonsterAttackState GetAttackState() { return  AttackState; }

	void SetRenderer(GameEngineTextureRenderer* _Renderer);
	GameEngineTextureRenderer* GetRenderer() { return Renderer; }

	MulticastDelegate<InGameMonsterState>& GetStateChangedDelegate() { return StateChangedDelegate; }
	MulticastDelegate<InGameDogCopterState>& GetDogCopterStateChangedDelegate() { return DogCopterStateChangedDelegate; }
	MulticastDelegate<InGamePh2DogState>& GetPh2DogStateChangedDelegate() { return Ph2DogStateChangedDelegate; }
	MulticastDelegate<InGameMonsterAttackState>& GetAttackStateChangedDelegate() { return AttackStateChangedDelegate; }

	virtual void OnPhaseChanged(Phase _Phase);
	
	float GetHP() { return HP; }
	void SetHP(float _HP) { HP = _HP; }

	void SetColMapImage(GameEngineTextureRenderer* _ColMapImage) { ColMapImage = _ColMapImage; }
	GameEngineTextureRenderer* GetColMapImage() { return ColMapImage; }
	
	void SetStartPos(float4 _StartPos) { StartPos = _StartPos; }
	float4 GetStartPos() { return StartPos; }

	void SetEndPos(float4 _EndPos) { EndPos = _EndPos; }
	float4 GetEndPos() { return EndPos; }

	bool GetIsAnimatedOrderPositive() { return IsAnimatedOrderPositive; }
	std::string GetStringNumber() { Number = std::to_string(AnimationNum); return Number; }
	int GetAnimationNum() { return AnimationNum; }

	void SetIsAnimatedOrderPositive(bool _IsAnimatedOrderPositive) { IsAnimatedOrderPositive = _IsAnimatedOrderPositive; }
	void SetStringNumber(std::string _Number) {Number = _Number; }
	void SetAnimationNum(int _AnimationNum) { AnimationNum = _AnimationNum; }

	float GetAngle() { return Angle; }
	void SetAngle(float _Angle) { Angle = _Angle; }

	void SetStartAngle(float _Angle) { StartAngle = _Angle; }
	float GetStartAngle() { return StartAngle; }


protected:
	void Start() override;
	virtual void MoveToEndPos(float4 _StartPos, float4 _EndPos, BulldogPlane* _Plane = nullptr);
	virtual bool IsEndPosArrived();

protected:
	float4 StartPos;
	float4 EndPos;
	float4 MoveDirection;
	float4 MoveSpeed;

	bool IsAnimatedOrderPositive;
	std::string Number;
	int AnimationNum;
	float Angle;

private:
	float HP;
	float StartAngle;
	float4 Direction;
	BulldogPlane* Plane;
	InGameMonsterState State;
	InGamePh2DogState Ph2DogState;
	InGameDogCopterState DogCopterState;
	InGameMonsterAttackState AttackState;
	GameEngineTextureRenderer* Renderer;
	GameEngineTextureRenderer* ColMapImage;
	MulticastDelegate<InGameMonsterState> StateChangedDelegate;
	MulticastDelegate<InGamePh2DogState> Ph2DogStateChangedDelegate;
	MulticastDelegate<InGameDogCopterState> DogCopterStateChangedDelegate;
	MulticastDelegate<InGameMonsterAttackState> AttackStateChangedDelegate;
};

