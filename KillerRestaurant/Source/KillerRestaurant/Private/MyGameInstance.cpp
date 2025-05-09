// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

FName UMyGameInstance::GetRowKey(FName Chapter, FName Stage)
{
	return FName(*FString::Printf(TEXT("%s_%s"), *Chapter.ToString(), *Stage.ToString()));
}
