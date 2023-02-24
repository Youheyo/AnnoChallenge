// Fill out your copyright notice in the Description page of Project Settings.


#include "CoalMineActor.h"

// Sets default values
ACoalMineActor::ACoalMineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACoalMineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACoalMineActor::processMaterial(float DeltaTime)
{
	Super::processMaterial(DeltaTime);
	UE_LOG(LogTemp, Display,TEXT("Generating Coal... %f"), processProgress);
	if(processProgress >= processDuration){
		processProgress = 0;
		coalHeld++;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Coal Held : %d"), coalHeld));
		isProcessing = false;
	}
}

// Called every frame
void ACoalMineActor::Tick(float DeltaTime)
{
	if(coalHeld < maxInputMatsHeld && !isProcessing) isProcessing = true;

	Super::Tick(DeltaTime);

	if(coalHeld > 0) callVehicle(COAL_MATERIAL, coalHeld);
}

