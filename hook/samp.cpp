#pragma once

#include "main.h"

struct actor_info *actor_info_get(int id, int flags)
{
	struct actor_info	*info;

	if (id == pSAMP->getPlayers()->sLocalPlayerID)
	{
		info = (struct actor_info *)(UINT_PTR) * (uint32_t *)0x00B7CD98;
		return info;
	}
	return false;
}

struct actor_info *getGTAPedFromSAMPPlayerID(int iPlayerID)
{
	if (pSAMP->getPlayers() == NULL || iPlayerID < 0 || iPlayerID > SAMP_MAX_PLAYERS)
		return NULL;
	if (iPlayerID == pSAMP->getPlayers()->sLocalPlayerID)
		return actor_info_get(pSAMP->getPlayers()->sLocalPlayerID, 0);

	if (pSAMP->getPlayers()->iIsListed[iPlayerID] != 1)
		return NULL;
	if (pSAMP->getPlayers()->pRemotePlayer[iPlayerID] == NULL)
		return NULL;
	if (pSAMP->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData == NULL)
		return NULL;
	if (pSAMP->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL)
		return NULL;
	if (pSAMP->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL)
		return NULL;

	// return actor_info, null or otherwise
	return pSAMP->getPlayers()->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor->pGTA_Ped;
}

void SAMPFramework::addMessageToChat(D3DCOLOR cColor, char *szMsg, ...)
{
	if (g_Chat == nullptr)
		return;

	void(__thiscall *AddToChatWindowBuffer) (const void *_this, int iType, char *szText, char *szPrefix, DWORD cColor, DWORD cPrefixColor) =
		(void(__thiscall *) (const void *, int, char *, char *, DWORD, DWORD)) (dwSAMPAddr + SAMP_FUNC_ADDTOCHATWND);

	if (szMsg == NULL)
		return;

	va_list ap;
	char tmp[512];
	memset(tmp, 0, 512);
	va_start(ap, szMsg);
	vsnprintf(tmp, sizeof(tmp) - 1, szMsg, ap);
	va_end(ap);

	return AddToChatWindowBuffer((void *) g_Chat, 8, tmp, NULL, cColor, 0x00);
}

void SAMPFramework::addClientCommand(char *szCmd, CMDPROC pFunc)
{
	if (g_Input == nullptr)
		return;

	void(__thiscall *AddClientCommand) (const void *_this, char *szCommand, CMDPROC pFunc) =
		(void(__thiscall *) (const void *, char *, CMDPROC)) (dwSAMPAddr + SAMP_FUNC_ADDCLIENTCMD);

	if (szCmd == NULL)
		return;

	return AddClientCommand(g_Input, szCmd, pFunc);
}

void SAMPFramework::sendPacket(BitStream *bsParams)
{
	g_RakClient->Send(bsParams, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0);
}

void SAMPFramework::sendRPC(int rpcId, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	g_RakClient->RPC(&rpcId, bitStream, priority, reliability, orderingChannel, shiftTimestamp);
}

void SAMPFramework::restartGame()
{
	if (g_SAMP == nullptr)
		return;

	uint32_t samp_info = dwSAMPAddr + SAMP_INFO_OFFSET;
	uint32_t func = dwSAMPAddr + SAMP_FUNC_RESTARTGAME;

	__asm mov eax, dword ptr[samp_info]
		__asm mov ecx, dword ptr[eax]
		__asm call func
	__asm pop eax
	__asm pop ecx
}