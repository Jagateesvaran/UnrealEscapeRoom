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

void UGrabberr::Grab() 
{

	UE_LOG(LogTemp, Error, TEXT("Grabber working"));



	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;


	// Get the player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	FHitResult HitResult = GetFirstPhsyicsBodyInReach();
	UPrimitiveComponent* ComponenetToGrab = HitResult.GetComponent();

	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation(ComponenetToGrab, NAME_None, LineTraceEnd);
	}

	

}

void UGrabberr::Release()
{
	UE_LOG(LogTemp, Error, TEXT("Grabber Realease working"));
	PhysicsHandle->ReleaseComponent();

}


// Called when the game starts
void UGrabberr::BeginPlay()
{
	Super::BeginPlay();

	// ...

	UE_LOG(LogTemp, Warning, TEXT("GRabber Reporting for duty"));

	

	
	FindPhysicsHandle();
	FindInputComponent();

}

void UGrabberr::FindPhysicsHandle() {
	
	// Check for Physics Handle Componet
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle) // to protect from crash
	{
		UE_LOG(LogTemp, Error, TEXT("UPhysicsHandleComponent Found on %s"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UPhysicsHandleComponent DOES NOT HAVE IT"));
	}
}


void UGrabberr::FindInputComponent() {

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) // to protect from crash
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent Found on %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabberr::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabberr::Release);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent not found on %s"), *GetOwner()->GetName());
	}
}

FHitResult UGrabberr::GetFirstPhsyicsBodyInReach() const {
	// ...
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;


	// Get the player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);


		//// Draw a line from player showing the reach
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	//DrawDebugLine(
	//	GetWorld(), PlayerViewPointLocation, LineTraceEnd, 
	//	FColor(0,255,0), false, 0.f, 0, 10.f);


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

	return hit;
}


// Called every frame
void UGrabberr::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;


	// Get the player viewpoint
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);


	//// Draw a line from player showing the reach
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}


}




