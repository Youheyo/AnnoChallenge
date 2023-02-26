// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VehicleActor.generated.h"

UCLASS()
class ANNOCHALLENGE_API AVehicleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVehicleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Static Mesh of Vehicle
	UPROPERTY(EditAnywhere) UStaticMeshComponent* Mesh;

	//Vehicle Speed Value
	UPROPERTY(EditAnywhere, Category="Vehicle Properties")
	float VehicleSpeed = 10.0f;

	//Material Loading Values
	UPROPERTY(EditAnywhere, Category="Vehicle Properties")
	float loadingSpeed = 1.0f;
    int CheckLoad();
	bool isLoading = false;
	float loadProgress = 0;
	float loadDuration = 0;

	//Location Related
	FVector Direction;

	float TotalDistance;
	float currDistance;

	FVector StartLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Material Count
	UPROPERTY(VisibleAnywhere, Category="Vehicle Properties")
	float iron = 0;
	UPROPERTY(VisibleAnywhere, Category="Vehicle Properties")
 	float coal = 0;
	UPROPERTY(VisibleAnywhere, Category="Vehicle Properties")
 	float lumber = 0;
	UPROPERTY(VisibleAnywhere, Category="Vehicle Properties")
 	float steel = 0;
	UPROPERTY(EditAnywhere, Category="Vehicle Properties")
	float maxLoad = 4;

	//Delivery Related Functions
	void loadMaterials(float DeltaTime);
	void GetMaterials(int32 matId, int32 &amount);

	void StartDeliveryState(AActor *Building, int32 matId, int32 &amt);
    void ClearDeliveryState();

	UPROPERTY(VisibleAnywhere, Category="Vehicle Properties")
	bool isDelivering = false;

	//Actor Targets and Home
	AActor* TargetBuilding;
	UPROPERTY(EditAnywhere, Category="Vehicle Properties")
	AActor* HomeBuilding;

};
