#pragma once

template<class T>
class TArray
{
public:

	FORCEINLINE int32 Num() const
	{
		return ArrayNum;
	};

	FORCEINLINE int32 Max() const
	{
		return ArrayMax;
	};

	FORCEINLINE T& operator[](int32 i) const
	{
		return AllocatorInstance[i];
	};

	FORCEINLINE T& operator[](int32 i)
	{
		return AllocatorInstance[i];
	};

	FORCEINLINE bool IsValidIndex(int32 i) const
	{
		return i < Num();
	}

	T* AllocatorInstance;
	int32 ArrayNum;
	int32 ArrayMax;
};

class FString
{
public:
	TArray<TCHAR> Data;

	FORCEINLINE FString() {};

	FORCEINLINE FString(const wchar_t* other)
	{
		Data.ArrayMax = Data.ArrayNum = *other ? static_cast<uint32>(std::wcslen(other)) + 1 : 0;

		if (Data.ArrayNum)
		{
			Data.AllocatorInstance = const_cast<wchar_t*>(other);
		}
	};

	FORCEINLINE bool IsValid() const
	{
		return Data.AllocatorInstance != nullptr;
	}

	FORCEINLINE const wchar_t* c_str() const
	{
		return Data.AllocatorInstance;
	}

	std::string ToString() const
	{
		size_t Length = std::wcslen(Data.AllocatorInstance);

		std::string String(Length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data.AllocatorInstance, Data.AllocatorInstance + Length, '?', &String[0]);

		return String;
	}
};
