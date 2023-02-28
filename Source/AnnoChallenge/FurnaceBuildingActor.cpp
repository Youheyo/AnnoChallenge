// Fill out your copyright notice in the Description page of Project Settings.


#include "FurnaceBuildingActor.h"

// Sets default values
AFurnaceBuildingActor::AFurnaceBuildingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFurnaceBuildingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFurnaceBuildingActor::processMaterial(float DeltaTime)
{
		Super::processMaterial(DeltaTime);
	//UE_LOG(LogTemp, Display,TEXT("Generating Coal... %f"), processProgress);
	if(processProgress >= processDuration){
		processProgress = 0;
		steelHeld++;

		coalHeld--;
		ironHeld--;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Coal Held : %d"), ironHeld));
		isProcessing = false;
	}
}

// Called every frame
void AFurnaceBuildingActor::Tick(float DeltaTime)
{

	if(ironHeld > 0 && coalHeld > 0 && steelHeld < maxOutputMatsHeld && !isProcessing) isProcessing = true;

	Super::Tick(DeltaTime);

	if(steelHeld > 0 && Cast<ABuildingActor>(TargetBuilding)->CanReceiveMats(STEEL_MATERIAL)) callVehicle(STEEL_MATERIAL, steelHeld);

}

void AFurnaceBuildingActor::ReceiveMaterials(int32 matId, int32 amount)
{

	switch(matId){
		case 1:
			if(ironHeld < maxInputMatsHeld){
				ironHeld += amount;
				ironHeld = FMath::Clamp(ironHeld,0,maxInputMatsHeld);
			}
			else return;
			break;
		case 0:
			if(coalHeld < maxInputMatsHeld){
				coalHeld += amount;
				coalHeld = FMath::Clamp(coalHeld,0,maxInputMatsHeld);
			}
			else return;
			break;
		default:
		break;
	}
}

bool AFurnaceBuildingActor::CanReceiveMats(int32 matId){
	
	switch(matId){
			case 1:
			if(ironHeld < maxInputMatsHeld)
			return true;
			break;
		case 0:
			if(coalHeld < maxInputMatsHeld)
			return true;
			break;
	}
	return false;

}

int AFurnaceBuildingActor::GetMaterialCount(int32 matId){
	switch(matId){
		case 1:
			return ironHeld;
			break;
		case 0:
			return coalHeld;
			break;
		case 2:
			return steelHeld;
			break;
	}
	return -1;
}