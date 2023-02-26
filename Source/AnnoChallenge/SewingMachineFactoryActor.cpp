// Fill out your copyright notice in the Description page of Project Settings.


#include "SewingMachineFactoryActor.h"

// Sets default values
ASewingMachineFactoryActor::ASewingMachineFactoryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASewingMachineFactoryActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASewingMachineFactoryActor::processMaterial(float DeltaTime)
{
	Super::processMaterial(DeltaTime);
	//UE_LOG(LogTemp, Display,TEXT("Generating Coal... %f"), processProgress);
	if(processProgress >= processDuration){
		processProgress = 0;
		steelHeld--;

		lumberHeld--;
		sewingMachinesHeld++;
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Coal Held : %d"), ironHeld));
		isProcessing = false;
	}
}

// Called every frame
void ASewingMachineFactoryActor::Tick(float DeltaTime)
{
	if(lumberHeld > 0 && steelHeld > 0 && !isProcessing) isProcessing = true;
	Super::Tick(DeltaTime);

}

void ASewingMachineFactoryActor::ReceiveMaterials(int32 matId, int32 amount)
{
	amount = FMath::Clamp(amount, 0, maxInputMatsHeld);
	switch(matId){
		case 2:
			if(steelHeld < maxInputMatsHeld)
			steelHeld += amount;
			else return;
			break;
		case 3:
			if(lumberHeld < maxInputMatsHeld)
			lumberHeld += amount;
			else return;
			break;
		default:
		break;
	}
}
