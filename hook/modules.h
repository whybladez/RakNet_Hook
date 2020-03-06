#pragma once

float fWeaponDamage[55] =
{
	1.0, // 0 - Fist
	1.0, // 1 - Brass knuckles
	1.0, // 2 - Golf club
	1.0, // 3 - Nitestick
	1.0, // 4 - Knife
	1.0, // 5 - Bat
	1.0, // 6 - Shovel
	1.0, // 7 - Pool cue
	1.0, // 8 - Katana
	1.0, // 9 - Chainsaw
	1.0, // 10 - Dildo
	1.0, // 11 - Dildo 2
	1.0, // 12 - Vibrator
	1.0, // 13 - Vibrator 2
	1.0, // 14 - Flowers
	1.0, // 15 - Cane
	82.5, // 16 - Grenade
	0.0, // 17 - Teargas
	1.0, // 18 - Molotov
	9.9, // 19 - Vehicle M4 (custom)
	46.2, // 20 - Vehicle minigun (custom)
	0.0, // 21
	8.25, // 22 - Colt 45
	13.2, // 23 - Silenced
	46.2, // 24 - Deagle
	49.5,//3.3, // 25 - Shotgun
	49.5,//3.3, // 26 - Sawed-off
	39.6,//4.95, // 27 - Spas
	6.6, // 28 - UZI
	8.25, // 29 - MP5
	9.900001, // 30 - AK47
	9.900001, // 31 - M4
	6.6, // 32 - Tec9
	24.750001, // 33 - Cuntgun
	41.25, // 34 - Sniper
	82.5, // 35 - Rocket launcher
	82.5, // 36 - Heatseeker
	1.0, // 37 - Flamethrower
	46.2, // 38 - Minigun
	82.5, // 39 - Satchel
	0.0, // 40 - Detonator
	0.33, // 41 - Spraycan
	0.33, // 42 - Fire extinguisher
	0.0, // 43 - Camera
	0.0, // 44 - Night vision
	0.0, // 45 - Infrared
	0.0, // 46 - Parachute
	0.0, // 47 - Fake pistol
	2.64, // 48 - Pistol whip (custom)
	9.9, // 49 - Vehicle
	330.0, // 50 - Helicopter blades
	82.5, // 51 - Explosion
	1.0, // 52 - Car park (custom)
	1.0, // 53 - Drowning
	165.0f // 54 - Splat
};

inline float vect3_length(const float in[3])
{
	return sqrtf(in[0] * in[0] + in[1] * in[1] + in[2] * in[2]);
}

inline void vect3_copy(const float in[3], float out[3])
{
	memcpy(out, in, sizeof(float) * 3);
}

void SendFakeOnfootSyncData(float fPos[3], float fHealth, float fSpeed[3])
{
	stOnFootData ofSync; BitStream bsOnfootSync;
	memcpy(&ofSync, &pSAMP->getPlayers()->pLocalPlayer->onFootData, sizeof(stOnFootData));

	ofSync.byteHealth = (uint8_t)fHealth;
	vect3_copy(fPos, ofSync.fPosition);
	vect3_copy(fSpeed, ofSync.fMoveSpeed);

	bsOnfootSync.Write((BYTE)ID_PLAYER_SYNC);
	bsOnfootSync.Write((PCHAR)&ofSync, sizeof(stOnFootData));

	pSAMP->sendPacket(&bsOnfootSync);
}

void SendFakeAimSyncData(int playerId)
{
	stAimData aimSync;
	ZeroMemory(&aimSync, sizeof(stAimData));

	aimSync.fAimZ = pSAMP->getPlayers()->pLocalPlayer->aimData.fAimZ;
	aimSync.byteCamMode = pSAMP->getPlayers()->pLocalPlayer->aimData.byteCamMode;

	aimSync.vecAimPos[0] = pSAMP->getPlayers()->pRemotePlayer[playerId]->pPlayerData->fOnFootPos[0];
	aimSync.vecAimPos[1] = pSAMP->getPlayers()->pRemotePlayer[playerId]->pPlayerData->fOnFootPos[1];
	aimSync.vecAimPos[2] = pSAMP->getPlayers()->pRemotePlayer[playerId]->pPlayerData->fOnFootPos[2];

	aimSync.vecAimf1[0] = pSAMP->getPlayers()->pRemotePlayer[playerId]->pPlayerData->fOnFootPos[0];
	aimSync.vecAimf1[1] = pSAMP->getPlayers()->pRemotePlayer[playerId]->pPlayerData->fOnFootPos[1];
	aimSync.vecAimf1[2] = pSAMP->getPlayers()->pRemotePlayer[playerId]->pPlayerData->fOnFootPos[2];

	BitStream bsAimSync;
	bsAimSync.Write((BYTE)PacketEnumeration::ID_AIM_SYNC);
	bsAimSync.Write((PCHAR)&aimSync, sizeof(stBulletData));
	pSAMP->sendPacket(&bsAimSync);
}

void SendGiveDamage(int iPlayerID, float fDamage, int iWeaponID, int iBodyPart)
{
	BitStream bsGiveDamage;

	bsGiveDamage.Write((BYTE)ID_RPC);
	bsGiveDamage.Write((BYTE)115);

	bsGiveDamage.Write<bool>(false);
	bsGiveDamage.Write<WORD>(iPlayerID);
	bsGiveDamage.Write<float>(fDamage);
	bsGiveDamage.Write<int>(iWeaponID);
	bsGiveDamage.Write<int>(iBodyPart);
	pSAMP->sendPacket(&bsGiveDamage);
	
}

void BulletData(int i)
{
	stRemotePlayer *pPlayer = pSAMP->getPlayers()->pRemotePlayer[i];
	if (!pPlayer) return;
	stBulletData sync;
	ZeroMemory(&sync, sizeof(stBulletData));

	sync.sTargetID = i;

	sync.fOrigin[0] = pSAMP->getPlayers()->pLocalPlayer->onFootData.fPosition[0] + rand() %1 - 0.9f;
	sync.fOrigin[1] = pSAMP->getPlayers()->pLocalPlayer->onFootData.fPosition[1] + rand() % 1 - 0.6f;
	sync.fOrigin[2] = pSAMP->getPlayers()->pLocalPlayer->onFootData.fPosition[2] + rand() % 1 - 0.8f;

	sync.fTarget[0] = pPlayer->pPlayerData->fOnFootPos[0] + rand() % 1 - 0.5f;
	sync.fTarget[1] = pPlayer->pPlayerData->fOnFootPos[1] + rand() % 1 - 0.9f;
	sync.fTarget[2] = pPlayer->pPlayerData->fOnFootPos[2] + rand() % 1 - 0.4f;

	sync.fCenter[0] = 0.0 + rand() % 1 - 0.8f;
	sync.fCenter[1] = 0.0 + rand() % 1 - 0.7f;
	sync.fCenter[2] = 0.5 + rand() % 1 - 0.8f;

	sync.byteWeaponID = pSAMP->getPlayers()->pLocalPlayer->byteCurrentWeapon;

	sync.byteType = 1;

	BitStream BulletSync;
	BulletSync.Write((BYTE)PacketEnumeration::ID_BULLET_SYNC);
	BulletSync.Write((PCHAR)&sync, sizeof(stBulletData));
	pSAMP->sendPacket(&BulletSync);
}

void CalcScreenCoors(CVector* vecWorld, CVector* vecScreen)
{
	D3DXMATRIX      m((float*)(0xB6FA2C));

	DWORD* dwLenX = (DWORD*)(0xC17044);
	DWORD* dwLenY = (DWORD*)(0xC17048);

	vecScreen->x = (vecWorld->z * m._31) + (vecWorld->y * m._21) + (vecWorld->x * m._11) + m._41;
	vecScreen->y = (vecWorld->z * m._32) + (vecWorld->y * m._22) + (vecWorld->x * m._12) + m._42;
	vecScreen->z = (vecWorld->z * m._33) + (vecWorld->y * m._23) + (vecWorld->x * m._13) + m._43;

	double  fRecip = (double)1.0 / vecScreen->z;
	vecScreen->x *= (float)(fRecip * (*dwLenX));
	vecScreen->y *= (float)(fRecip * (*dwLenY));
}

int GetPlayerTarget(int radius)
{
	static float iX;
	static float iY;

	stPlayerPool * pPlayerPool = pSAMP->getPlayers();
	for (int i = 0; i < SAMP_MAX_PLAYERS; i++)
	{
		if (pPlayerPool->pRemotePlayer[i])
		{
			if (pPlayerPool->pLocalPlayer)
			{
				CVector pPed, screen;
				pPed.x = pPlayerPool->pRemotePlayer[i]->pPlayerData->fOnFootPos[0];
				pPed.y = pPlayerPool->pRemotePlayer[i]->pPlayerData->fOnFootPos[1];
				pPed.z = pPlayerPool->pRemotePlayer[i]->pPlayerData->fOnFootPos[2];

				CalcScreenCoors(&pPed, &screen);

				if (screen.z < 1.f)
					continue;

				iX = GetSystemMetrics(SM_CXSCREEN) * 0.5299999714f;
				iY = GetSystemMetrics(SM_CYSCREEN) * 0.4f;

				if ((screen.x > iX + (radius)) || (screen.y > iY + (radius)) || (screen.x < iX - (radius)) || (screen.y < iY - (radius)))
					continue;

				return i;
			}
		}
	}
	return -1;
}