// Fill out your copyright notice in the Description page of Project Settings.

// good website



#include "WorldPosition.h"
#include "GameFramework/Actor.h" // to get the player in the scene

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts  -> This is the start for this code
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	// ...

	FString Objectname = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Objectname);

	FString objectPosition = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *objectPosition);


	//FString Log = TEXT("Hello!");
	//FString* PtrLog = &Log; //it just got the reference 

	//Log.Len();
	//
	//(*PtrLog).Len(); 
	//PtrLog->Len();

	//UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog);


	/*UE_LOG(LogTemp, Display, TEXT("This is a Warning!"));
	UE_LOG(LogTemp, Warning, TEXT("This is a Warning!"));
	UE_LOG(LogTemp, Error, TEXT("This is a Warning!"));*/
	
}


// Called every frame (Upadte Function)
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

