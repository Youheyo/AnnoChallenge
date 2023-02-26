// Fill out your copyright notice in the Description page of Project Settings.


#include "LumberMillActor.h"

// Sets default values
ALumberMillActor::ALumberMillActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALumberMillActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALumberMillActor::processMaterial(float DeltaTime)
{
	Super::processMaterial(DeltaTime);
	//UE_LOG(LogTemp, Display,TEXT("Generating Coal... %f"), processProgress);
	if(processProgress >= processDuration){
		processProgress = 0;
		lumberHeld++;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Coal Held : %d"), lumberHeld));
		isProcessing = false;
	}
}


// Called every frame
void ALumberMillActor::Tick(float DeltaTime)
{
	if(lumberHeld < maxInputMatsHeld && !isProcessing) isProcessing = true;

	Super::Tick(DeltaTime);

	if(lumberHeld > 0 && Cast<ABuildingActor>(TargetBuilding)->CanReceiveMats(LUMBER_MATERIAL)) callVehicle(LUMBER_MATERIAL, lumberHeld);
}

