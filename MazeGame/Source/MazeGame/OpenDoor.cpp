// Copyright Jagatees 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h" // to get the player in the scene
#include "Engine/World.h" // to get 
#include "GameFramework/PlayerController.h" // get player controller

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}


void UOpenDoor::OpenDoor(float dt)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, targetYaw, dt * 1.f);

	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

}

void UOpenDoor::CloseDoor(float dt)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, closeYaw, dt * 1.f);

	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...

	IntialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = IntialYaw;
	targetYaw += IntialYaw;

	if (!PressurePlate)// help to protec yourself aginst null poniter objects
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the open door compnetn on it but no pressureplate set"), *GetOwner()->GetName())
	}

	// on start get player and set the player to it 
	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoor(DeltaTime);
		// Door Last Opened When the door was opened
	}
	else if(PressurePlate && !PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		// if the door has been open long than x seconds
		CloseDoor(DeltaTime);
	}



}

