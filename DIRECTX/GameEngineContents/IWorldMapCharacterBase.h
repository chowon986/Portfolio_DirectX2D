#pragma once
#include "Iwalkable.h"
#include "IIdleable.h"

class IWorldMapCharacterBase : public IWalkable, public IIdleable
{
public:
	// constrcuter destructer
	IWorldMapCharacterBase();
	~IWorldMapCharacterBase();

	// delete Function
	IWorldMapCharacterBase(const IWorldMapCharacterBase& _Other) = delete;
	IWorldMapCharacterBase(IWorldMapCharacterBase&& _Other) noexcept = delete;
	IWorldMapCharacterBase& operator=(const IWorldMapCharacterBase& _Other) = delete;
	IWorldMapCharacterBase& operator=(IWorldMapCharacterBase&& _Other) noexcept = delete;

private:

};

