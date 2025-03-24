#pragma once 

#include "UObject/Object.h"

#pragma region Log

#define CALLED_FROM (TEXT(__FUNCTION__) + FString::Printf(TEXT("(%d)"), __LINE__))
#define CUSTOM_LOG(Verbosity, Format, ...) UE_LOG(LogTemp, Verbosity, TEXT("%s %s"), *CALLED_FROM, *FString::Printf(Format, ##__VA_ARGS__))
#define CUSTOM_LOG_SCREEN(LifeTime, Color, Format, ...) GEngine->AddOnScreenDebugMessage(-1, LifeTime, Color, FString::Printf(Format, ##__VA_ARGS__))

#define TRACE_LOG(Format, ...) \
	CUSTOM_LOG(Log, Format, ##__VA_ARGS__); \
	CUSTOM_LOG_SCREEN(4.0f, FColor::Green, Format, ##__VA_ARGS__);

#define TRACE_WARNING(Format, ...) \
	CUSTOM_LOG(Warning, Format, ##__VA_ARGS__); \
	CUSTOM_LOG_SCREEN(4.0f, FColor::Yellow, Format, ##__VA_ARGS__);

#define TRACE_ERROR(Format, ...) \
	CUSTOM_LOG(Error, Format, ##__VA_ARGS__); \
	ensure(false);

#pragma endregion

template <typename T>
FORCEINLINE bool IsValid(const TWeakObjectPtr<T>& _weak_obj_ptr)
{
	return _weak_obj_ptr.IsValid();
}

template <typename T>
FORCEINLINE bool IsValid(const TObjectPtr<T>* _obj_ptr)
{
	return _obj_ptr != nullptr;
}

FORCEINLINE bool IsAllValid()
{
	return true;
}

template <typename... Args>
FORCEINLINE bool IsAllValid(const UObject* _obj, Args... _rest)
{
	return IsValid(_obj) && IsAllValid(_rest...);
}

FORCEINLINE bool IsInvalid(const UObject* _obj)
{
	return !IsValid(_obj);
}

template <typename T>
FORCEINLINE bool IsInvalid(const TWeakObjectPtr<T>& _weak_obj_ptr)
{
	return !IsValid(_weak_obj_ptr);
}

FORCEINLINE bool IsAnyInvalid()
{
	return false;
}

template <typename... Args>
FORCEINLINE bool IsAnyInvalid(const UObject* _obj, Args... _rest)
{
	return IsInvalid(_obj) || IsAnyInvalid(_rest...);
}
