// Fill out your copyright notice in the Description page of Project Settings.


#include "IronMineActor.h"

// Sets default values
AIronMineActor::AIronMineActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIronMineActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AIronMineActor::processMaterial(float DeltaTime)
{
	Super::processMaterial(DeltaTime);
	//UE_LOG(LogTemp, Display,TEXT("Generating Coal... %f"), processProgress);
	if(processProgress >= processDuration){
		processProgress = 0;
		ironHeld++;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Coal Held : %d"), ironHeld));
		isProcessing = false;
	}
}

// Called every frame
void AIronMineActor::Tick(float DeltaTime)
{
	if(ironHeld < maxInputMatsHeld && !isProcessing) isProcessing = true;
	
	Super::Tick(DeltaTime);

	if(ironHeld > 0 && Cast<ABuildingActor>(TargetBuilding)->CanReceiveMats(IRON_MATERIAL)) callVehicle(IRON_MATERIAL, ironHeld);

}

