#pragma once
#include <UnrealEngine/UE.h>

FNamePool* NamePoolData = nullptr;
FUObjectArray* GUObjectArray = nullptr;
UWorldProxy* GWorld = nullptr;
int PROCESSEVENT_VTABLE_INDEX = 0;

void UObject::ProcessEvent(class UFunction* Function, void* Parms)
{
	void(*ProcessEventF)(UObject*, class UFunction*, void*) = reinterpret_cast<decltype(ProcessEventF)>(VTable[PROCESSEVENT_VTABLE_INDEX]);
	ProcessEventF(this, Function, Parms);
}

bool Initalize(uint64 BaseAddress)
{
	const IMAGE_DOS_HEADER* DOSHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(BaseAddress);

	const IMAGE_NT_HEADERS* NtHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(BaseAddress + DOSHeader->e_lfanew);
	
	const DWORD SizeOfImage = NtHeaders->OptionalHeader.SizeOfImage;

	GUObjectArray = PatternScan<FUObjectArray*>("48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 8D ? ? ? ? E8 ? ? ? ? 48 8D 8D", BaseAddress, SizeOfImage, true);
	if (!GUObjectArray) {
		LOGFAIL("FUObjectArray* GUObjectArray Was Not Found.\n\n")
		return false;
	}
	
	NamePoolData = PatternScan<FNamePool*>("48 8D 0D ? ? ? ? E8 ? ? ? ? C6 05 ? ? ? ? 01 0F 10", BaseAddress, SizeOfImage, true);
	if (!NamePoolData) {
		LOGFAIL("FNamePool* NamePoolData Was Not Found.\n\n")
		return false;
	}

	GWorld = PatternScan<UWorldProxy*>("48 8B 1D ? ? ? ? 48 85 DB 74 3B 41 B0 01 33 D2 48 8B CB E8", BaseAddress, SizeOfImage, true);
	if (!GWorld)
	{
		LOGFAIL("UWorldProxy* GWorld Was Not Found.\n\n")
		return false;
	}

	WIDECHAR GameFileDir[MAX_PATH];
	GetModuleFileNameW(NULL, GameFileDir, MAX_PATH);

	LOGINFO("Game Directory -> %ws\n\n", GameFileDir);

	LOGINFO("Game Module Base Address -> %llX \n\n", BaseAddress);

	LOGINFO("Size Of Game Module -> 0x%X\n\n", SizeOfImage);

	LOGINFO("FUObjectArray* GUObjectArray found -> Base Address + 0x%llX\n\n", reinterpret_cast<uint64>(GUObjectArray) - BaseAddress);

	LOGINFO("FNamePool* NamePoolData found -> Base Address + 0x%llX\n\n", reinterpret_cast<uint64>(NamePoolData) - BaseAddress);
	
	LOGINFO("UWorldProxy* GWorld found -> Base Address + 0x%llX\n\n", reinterpret_cast<uint64>(GWorld) - BaseAddress);

	return true;
}
