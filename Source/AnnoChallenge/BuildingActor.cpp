// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingActor.h"
#include "VehicleActor.h"
// Sets default values
ABuildingActor::ABuildingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuildingActor::processMaterial(float DeltaTime)
{
	if(processProgress < processDuration){
		processProgress += DeltaTime * processSpeed;
	}else
	{
		isProcessing = false;
	}
}

void ABuildingActor::callVehicle(int32 matId, int32 &amount)
{
		TArray<AActor*> VehiclesToFind;
		//AActor* Vehicle;
		AVehicleActor* vehicleActor = NULL;
		if(UWorld* World = GetWorld()){
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVehicleActor::StaticClass(), VehiclesToFind);
		}
		
		for(int i = 0; i < VehiclesToFind.Num(); i++){
			vehicleActor = Cast<AVehicleActor>(VehiclesToFind[i]->GetComponentByClass(AVehicleActor::StaticClass()));
			if(!vehicleActor->isDelivering){
				break;
			}
		}
		if(vehicleActor != NULL){

			//AVehicleActor* vehicleActor = Cast<AVehicleActor>(Vehicle->GetComponentByClass(AVehicleActor::StaticClass()));
			vehicleActor->StartDeliveryState(TargetBuilding, matId, amount);
			vehicleActor->SetActorLocation(this->GetActorLocation());
		}
}

// Called every frame
void ABuildingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!isProcessing) processMaterial(DeltaTime);
}

