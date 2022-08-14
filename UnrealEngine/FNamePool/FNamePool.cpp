#include <UnrealEngine/UE.h>

void FNameEntry::GetAnsiName(ANSICHAR(&Out)[NAME_SIZE]) const
{
	if (!IsWide()) {
		CopyUnterminatedName(Out);
		Out[Header.Len] = '\0';
	}
	else {
		LOGFAIL("GetAnsiName was called while the name is wide.\n\n");
	}
}

void FNameEntry::GetWideName(WIDECHAR(&Out)[NAME_SIZE]) const
{
	if (IsWide()) {
		CopyUnterminatedName(Out);
		Out[Header.Len] = '\0';
	}
	else {
		LOGFAIL("GetWideName was called while the name is not wide.\n\n");
	}
}

std::string FNameEntry::String()
{
	if (IsWide()) {
		std::wstring Wide(WideName, Header.Len);
		return std::string(Wide.begin(), Wide.end());
	}
	return std::string(AnsiName, Header.Len);
}

std::string FName::GetName()
{
	FNameEntry Entry = NamePoolData->Entries.Resolve(GetDisplayIndex());

	std::string Name = Entry.String();

	if (Number > 0)
	{
		/** Not the first instance of this name so add instance number. */
		Name += '_' + std::to_string(Number);
	}

	/** Find the last '/' and start the string from there + 1 so the name doesnt contain extra length and info and look ugly. */
	std::size_t Pos = Name.rfind('/');

	if (Pos != std::string::npos) Name = Name.substr(Pos + 1);

	return Name;
}

const FNameEntry* FName::GetDisplayNameEntry() const
{
	return &NamePoolData->Entries.Resolve(GetDisplayIndex());
}

int32 FNameEntry::GetSize(int32 Length, bool bIsPureAnsi)
{
	int32 Bytes = GetDataOffset() + Length * (bIsPureAnsi ? sizeof(ANSICHAR) : sizeof(WIDECHAR));
	return Align(Bytes, alignof(FNameEntry));
}