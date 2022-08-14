#include <UnrealEngine/UE.h>

/** IMPORTANT TO CHANGE THIS TO THE STEAM ID OF WHO WILL GET ADMIN... */
#define STEAMID L"77777777777777777"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return FALSE;

    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    uint64 ModuleBase = reinterpret_cast<uint64>(GetModuleHandleA(NULL));
    if (!ModuleBase) return FALSE;

    Initalize(ModuleBase);

    UWorld* World = GWorld->World;
    if (!World)
    {
        LOGFAIL("UWorld* GWorld->World Was Null.\n\n")
        return FALSE;
    }

    LOGSUCCESS("UWorld* GWorld->World | 0x%p\n\n", World);

    PROCESSEVENT_VTABLE_INDEX = ScanVTable("40 55 56 57 41 54", World);
    if (!PROCESSEVENT_VTABLE_INDEX) {
        LOGFAIL("Could not locate ProcessEvent's VTable index.\n");
        return FALSE;
    }

    LOGINFO("UObject::ProcessEvent found-> Object->VTable[0x%X] / BaseAddress + 0x%llX\n\n", PROCESSEVENT_VTABLE_INDEX, reinterpret_cast<uint64>(World->VTable[PROCESSEVENT_VTABLE_INDEX]) - ModuleBase);

    UGameInstance* OwningGameInstance = World->OwningGameInstance;
    if (!OwningGameInstance)
    {
        LOGFAIL("UGameInstance* World->OwningGameInstance Was Null.\n\n")
        return FALSE;
    }

    LOGSUCCESS("UGameInstance* World->OwningGameInstance | 0x%p\n\n", OwningGameInstance);

    TArray<UPlayer*> LocalPlayers = OwningGameInstance->LocalPlayers;
    if (!LocalPlayers.AllocatorInstance)
    {
        LOGFAIL("LocalPlayers.AllocatorInstance Was Null.\n\n")
        return FALSE;
    }

    LOGSUCCESS("TArray<UPlayer*> OwningGameInstance->LocalPlayers.AllocatorInstance | 0x%p\n\n", LocalPlayers.AllocatorInstance);

    UPlayer* LocalPlayer = LocalPlayers[0];
    if (!LocalPlayer)
    {
        LOGFAIL("UPlayer* LocalPlayers[0] Was Null.\n\n")
        return FALSE;
    }

    LOGSUCCESS("UPlayer* LocalPlayers[0] | 0x%p\n\n", LocalPlayer);

    APlayerController* PlayerController = LocalPlayer->PlayerController;
    if (!PlayerController)
    {
        LOGFAIL("APlayerController* LocalPlayer->PlayerController Was Null.\n\n")
        return FALSE;
    }

    LOGSUCCESS("APlayerController* LocalPlayers[0] | 0x%p\n\n", PlayerController);

    APawn* AcknowledgedPawn = PlayerController->AcknowledgedPawn;
    if (!AcknowledgedPawn)
    {
        LOGFAIL("APawn* PlayerController->AcknowledgedPawn Was Null.\n\n")
        return FALSE;
    }

    LOGSUCCESS("APawn* PlayerController->AcknowledgedPawn | 0x%p\n\n", AcknowledgedPawn);

    FString SteamID = FString(STEAMID);

    AcknowledgedPawn->AddMeAsAdmin(SteamID);

    LOGSUCCESS("Added Admin For Steam ID -> %ws\n", SteamID.c_str());

    return TRUE;
}

