#include "PreCompile.h"
#include "CharacterScore.h"
#include "WeaponItemBase.h"
#include "CharmItemBase.h"
#include "SuperItemBase.h"
#include "PeaShooterItem.h"

CharacterScore::CharacterScore()
	: PlayTime(0.0f)
	, HP(0)
	, Parry(0)
	, UseCard(0)
	, Score("")
{

}

CharacterScore::~CharacterScore()
{
}

void CharacterScore::Start()
{
}

void CharacterScore::Update(float _DeltaTime)
{
}

void CharacterScore::End()
{
}
