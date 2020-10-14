#include <Windows.h>
#include <iostream>
#include <ctime>
#include <TlHelp32.h>
#include <Psapi.h>
#include "Funções.h"

using namespace std;

// Colocar aqui abaixo os opcodes que desejo escrever na memória após o acesso. 

char jump_oc[] = "\x90\x90\x90\x90\x90";

char forceattack_oc[] = "\x90\x90\x90";

//char health_oc[] = // Para o futuro projeto;



void InitializeHooks() {
    // Selecionar o findpattern para cada caso;

    //First one = jump_opcode;

    DWORD jump_address = FindPattern("proven_ground_client.exe", "\xF3\x0F\x58\x49\x00\xF3\x0F\x11\x49\x00\xC3", "xxxx?xxxx?x");

    //jump_address += X;

    MsgBoxAddy(jump_address);

    if (GetAsyncKeyState(VK_F1)) {

        WTM(jump_address, jump_oc, 5);

    }



    DWORD forceattack_address = FindPattern("proven_ground_client.exe", "\x80\x79\x08\x00\x75\x0A", "xxxxxx");
    // forceattack_address += X;

    MsgBoxAddy(forceattack_address);

    if (GetAsyncKeyState(VK_F2)) {

        WTM(forceattack_address, forceattack_oc, 3);

    }
}



BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) 
{



    switch (ul_reason_for_call)

    {

    case DLL_PROCESS_ATTACH:

        MessageBoxA(NULL, "Injetado!", "", 0);


        InitializeHooks();
        break;

    case DLL_THREAD_ATTACH:

    case DLL_THREAD_DETACH:

    case DLL_PROCESS_DETACH:

        break;

    }

    return TRUE;
}

