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

///Handles the processing timers
///The check for isProcessing is done by the Tick() function
///Whatever object inheriting this MUST UPDATE isProcessing bool
void ABuildingActor::processMaterial(float DeltaTime)
{
	if(processProgress < processDuration){
		processProgress += DeltaTime * processSpeed;
	}
}

void ABuildingActor::callVehicle(int32 matId, int32 &amount)
{
	//UE_LOG(LogTemp, Display, TEXT("%s is calling vehicle..."), *this->GetName());
		TArray<AActor*> VehiclesToFind;
		AVehicleActor* vehicleActor = NULL;

		///Get all VehicleActors in the world
		if(UWorld* World = GetWorld()){
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AVehicleActor::StaticClass(), VehiclesToFind);
		}
		
		//Check for available Vehicle Actors
		for(int i = 0; i < VehiclesToFind.Num(); i++){
			//UE_LOG(LogTemp, Display, TEXT("%s found in world"), *VehiclesToFind[i]->GetName());
			if(Cast<AVehicleActor>(VehiclesToFind[i])->isDelivering == false){
				vehicleActor = Cast<AVehicleActor>(VehiclesToFind[i]);
				UE_LOG(LogTemp, Display, TEXT("%s is available to deliver"), *vehicleActor->GetName());
				break;
			}
			
		}

		//Initiate delivery if available 
		//Teleports the available vehicle to the calling building
		if(vehicleActor != NULL){

			//UE_LOG(LogTemp, Display, TEXT("%s now holds %d materials"), *this->GetName(), amount);
			vehicleActor->SetActorLocation(this->GetActorLocation());
			//UE_LOG(LogTemp, Display, TEXT("%s gave %s %d materials"),*this->GetName(), *vehicleActor->GetName(), amount);
			vehicleActor->StartDeliveryState(TargetBuilding, matId, amount);
		}

}

// Called every frame
void ABuildingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(isProcessing) processMaterial(DeltaTime);
}

void ABuildingActor::ReceiveMaterials(int32 matId ,int32 amount)
{
	
}

bool ABuildingActor::CanReceiveMats(int32 matId)
{
	if(this->TargetBuilding != NULL) return false;
	return true;
}
