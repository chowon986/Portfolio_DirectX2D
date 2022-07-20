#pragma once
#include "ITalkable.h"
#include "IIdleable.h"

class INonPlayerCharacterBase : public GameEngineActor, public ITalkable, public IIdleable
{
public:
	// constrcuter destructer
	INonPlayerCharacterBase();
	~INonPlayerCharacterBase();

	// delete Function
	INonPlayerCharacterBase(const INonPlayerCharacterBase& _Other) = delete;
	INonPlayerCharacterBase(INonPlayerCharacterBase&& _Other) noexcept = delete;
	INonPlayerCharacterBase& operator=(const INonPlayerCharacterBase& _Other) = delete;
	INonPlayerCharacterBase& operator=(INonPlayerCharacterBase&& _Other) noexcept = delete;

private:

};

