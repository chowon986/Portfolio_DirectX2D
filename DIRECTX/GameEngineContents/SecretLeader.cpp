#include "PreCompile.h"
#include "SecretLeader.h"

SecretLeader::SecretLeader()
{
}

SecretLeader::~SecretLeader()
{
}

void SecretLeader::Start()
{
}

void SecretLeader::Update(float _DeltaTime)
{
}

void SecretLeader::TakeDamage()
{
	SetState(InGameMonsterState::TakeDamage);
}

void SecretLeader::Prepare()
{
	SetState(InGameMonsterState::Prepare);
}

void SecretLeader::Idle()
{
	SetState(InGameMonsterState::Idle);
}

void SecretLeader::Shoot()
{
	SetState(InGameMonsterState::Attack1);
}

void SecretLeader::Die()
{
	SetState(InGameMonsterState::Die);
}
