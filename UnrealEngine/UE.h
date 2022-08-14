#pragma once

#include <Windows.h>
#include <Utilities/Types.h>
#include <Utilities/Log.h>

#include <UnrealEngine/FNamePool/FNamePool.h>
#include <UnrealEngine/UObject/CoreUObject.h>
#include <UnrealEngine/FUObjectArray/FUObjectArray.h>
#include <UnrealEngine/Containers.h>
#include <Utilities/PatternScanner.h> 

extern FNamePool* NamePoolData;
extern FUObjectArray* GUObjectArray;
extern int PROCESSEVENT_VTABLE_INDEX;

bool Initalize(uint64 GameModule);

class APawn : public UObject
{
public:

	void AddMeAsAdmin(FString ID) {

		struct {
			FString ID;
		} Parameters;

		Parameters.ID = ID;

		static UFunction* Function = nullptr;
		if (!Function) Function = GUObjectArray->ObjObjects.FindUObject<UFunction*>("Function BP_SGKMasterCharacter.BP_SGKMasterCharacter_C.AddMeAsAdmin");

		ProcessEvent(Function, &Parameters);
	}

};

class APlayerController
{
public:
	char Hey[0x2a0];
	class APawn* AcknowledgedPawn;
};

class UPlayer
{
public:
	char Hey[0x30];
	class APlayerController* PlayerController;
};

class UGameInstance
{
public:
	char Hey[0x38];
	TArray<class UPlayer*> LocalPlayers;
};

class UWorld : public UObject
{
public:
	char Hey[0x158];
	class UGameInstance* OwningGameInstance;
};

class UWorldProxy
{
public:
	UWorldProxy() :
		World(0)
	{}

	inline bool operator==(const UWorldProxy& Other) const
	{
		return World == Other.World;
	}

	class UWorld* World;
};



extern UWorldProxy* GWorld;
