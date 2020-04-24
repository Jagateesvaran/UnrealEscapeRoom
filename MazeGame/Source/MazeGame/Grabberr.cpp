// Copyright Jagatees 2020

#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Grabberr.h"

#define OUT

// Sets default values for this component's properties
UGrabberr::UGrabberr()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberr::BeginPlay()
{
	Super::BeginPlay();

	// ...

	UE_LOG(LogTemp, Warning, TEXT("GRabber Reporting for duty"));
	
}


// Called every frame
void UGrabberr::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;


	// Get the player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);


	/*UE_LOG(LogTemp, Warning, TEXT("Location : %s, Rotation : %s"), 
		*PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());*/

	// Draw a line from player showing the reach
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	DrawDebugLine(
		GetWorld(), PlayerViewPointLocation, LineTraceEnd, 
		FColor(0,255,0), false, 0.f, 0, 10.f);


	// Ray-Casting out to a certain distance (Reach)
	FHitResult hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());  // rule for what i going to hit and ignore myself becuase the ray i starting form inside me

	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // type we can hit with
		TraceParams
		);

	AActor* ActorHit = hit.GetActor();

	if (ActorHit) // check if got hit
	{
		UE_LOG(LogTemp, Error, TEXT("Line Trace has hit : %s"), *(ActorHit->GetName()));
	}


	// Logging out to test

	// seee what it hits

	
}

