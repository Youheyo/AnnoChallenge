// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleActor.h"
#include "Math/UnrealMathUtility.h"
#include "BuildingActor.h"

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
		}else if(CheckLoad() != 0){
			if(currDistance < TotalDistance){
				FVector Location = this->GetActorLocation();
				Location += Direction * VehicleSpeed * DeltaTime;
				this->SetActorLocation(Location);

				currDistance = (Location - StartLocation).Size();

				timeTookForDelivery += DeltaTime;
			}
			
			else{

				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Delivery Completed in %.2f seconds"), timeTookForDelivery));
				//Vehicle only holds 1 type of material. Shouldn't be a problem but could be improved
				int32 matId;
				if(coal > 0) matId = 0;
				else if(iron > 0) matId = 1;
				else if(steel > 0) matId = 2;
				else if(lumber > 0) matId = 3;

				//Gives and dumps the extras for now
				Cast<ABuildingActor>(TargetBuilding)->ReceiveMaterials(matId, CheckLoad());
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
	
	if(!isLoading && CheckLoad() == 0){
		
		isDelivering = false;
		if(HomeBuilding != NULL){
			this->SetActorLocation(HomeBuilding->GetActorLocation());
			//TargetBuilding = HomeBuilding;
		}

		loadProgress = 0;
	}
}

///Vehicle gets materials from the Building that called it
///Asks for materialId (matId) and amount being given then gives back the excess 
/// Might remove matId since vehicle only has 1 Target and 1 Material Type
void AVehicleActor::GetMaterials(int32 matId, int32 &amount)
{
	if(CheckLoad() > maxLoad){
		return;
	}
	int excess = 0;
	if(amount > maxLoad){
		excess = amount - maxLoad;
	}
	//UE_LOG(LogTemp, Display, TEXT("Received %d amount of materials"), amount);
/// Replace to 1 statement if only 1 material is used
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
/// Might remove since vehicle only has 1 Target and 1 Material Type
int AVehicleActor::CheckLoad(){
	return coal + iron + steel + lumber; 
}

/// @brief Reset everything about delivery then go back to warehouse
void AVehicleActor::ClearDeliveryState()
{
	loadProgress = 0;
	timeTookForDelivery = 0;

	coal = 0;
	iron = 0;
	steel = 0;
	lumber = 0;

	loadDuration = FMath::RandRange(1.0f, 3.0f);
	isLoading = true;

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("DELIVERY COMPLETE")));

}

///Initializes the states of the vehicle and a random loadDuration
///Requests the target building, material id, and amount given
void AVehicleActor::StartDeliveryState(AActor *Building, int32 matId, int32 &amt)
{

	TargetBuilding = Building;
	StartLocation = this->GetActorLocation();
	Direction = TargetBuilding->GetActorLocation() - StartLocation;

	
	TotalDistance = Direction.Size();

	Direction = Direction.GetSafeNormal();

	VehicleSpeed = TotalDistance / minDeliveryTime;

	isDelivering = true;
	isLoading = true;
	GetMaterials(matId, amt);
	loadDuration = FMath::RandRange(1.0f, 3.0f);

	currDistance = 0.0f;
}
