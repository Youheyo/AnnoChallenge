// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleActor.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AVehicleActor::AVehicleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AVehicleActor::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorLocation(HomeBuilding->GetActorLocation());
	
}

// Called every frame
void AVehicleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(isDelivering){
		//UE_LOG(LogTemp, Display, TEXT("Loading Materials... %s"), (isLoading ? TEXT("In progress") : TEXT("COMPLETE!") ));
		if(isLoading){
			loadMaterials(DeltaTime);
		}else{
			if(currDistance < TotalDistance){
				FVector Location = this->GetActorLocation();
				Location += Direction * VehicleSpeed * DeltaTime;
				this->SetActorLocation(Location);

				currDistance = (Location - StartLocation).Size();
			}
			else{
				ClearDeliveryState();
			}
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Distance from Goal %f"), TotalDistance-currDistance));
		}
	}
}

/// @brief Starts and ends the loading state of the vehicle
/// @param DeltaTime 
void AVehicleActor::loadMaterials(float DeltaTime)
{
	loadProgress += DeltaTime * loadingSpeed;
	if(loadProgress > loadDuration) {
		isLoading = false;
	}
}

///Vehicle gets materials from the Building that called it
///Asks for materialId (matId) and amount being given then gives back the excess 
void AVehicleActor::GetMaterials(int32 matId, int32 &amount)
{
	if(CheckLoad() > maxLoad){
		return;
	}
	int excess = 0;
	if(amount > maxLoad){
		excess = amount - maxLoad;
	}
	UE_LOG(LogTemp, Display, TEXT("Received %d amount of materials"), amount);
	switch(matId){
		case 0:
			coal += amount;
			break;
		case 1:
			iron += amount;
			break;
		case 2:
			steel += amount;
			break;
		case 3:
			lumber += amount;
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("UNKNOWN MATERIAL NAME"));
	}
	amount = excess;
}

/// @brief Adds up the total resource held by Vehicle
/// @return total of resources
int AVehicleActor::CheckLoad(){
	return coal + iron + steel + lumber; 
}

/// @brief Reset everything about delivery then go back to warehouse
void AVehicleActor::ClearDeliveryState()
{
	isDelivering = false;
	isLoading = false;
	loadProgress = 0;
	if(HomeBuilding != NULL){
		this->SetActorLocation(HomeBuilding->GetActorLocation());
		TargetBuilding = HomeBuilding;
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("DELIVERY COMPLETE")));

}

///Initializes the states of the vehicle and a random loadDuration
///Requests the target building, material id, and amount given
void AVehicleActor::StartDeliveryState(AActor *Building, int32 matId, int32 &amt)
{
	isDelivering = true;
	isLoading = true;
	GetMaterials(matId, amt);
	loadDuration = FMath::RandRange(1.0f, 3.0f);

	TargetBuilding = Building;
	StartLocation = this->GetActorLocation();
	Direction = TargetBuilding->GetActorLocation() - StartLocation;
	TotalDistance = Direction.Size();

	Direction = Direction.GetSafeNormal();
	currDistance = 0.0f;
}
