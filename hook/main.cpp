#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include "modules.h"

SAMPFramework *pSAMP;

void mainThread(void *pvParams)
{
	if (pSAMP)
	{
		while (!pSAMP->tryInit())
			Sleep(100);

		raknet_plugin_attacher_instance.attach(pSAMP->getRakClientInterface(), new packet_handler);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	switch (dwReasonForCall)
	{
		case DLL_PROCESS_ATTACH:
		{
			AllocConsole();
			freopen("CONOUT$", "w", stdout);
			pSAMP = new SAMPFramework(GetModuleHandle("samp.dll"));
			_beginthread(mainThread, NULL, NULL);

			break;
		}
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}