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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Material Count
	float iron, coal, steel, lumber = 0;
	UPROPERTY(EditAnywhere, Category="Vehicle Properties")
	float maxLoad = 4;

	//Delivery Related Functions
	void loadMaterials(float DeltaTime);
	void GetMaterials(int32 matId, int32 &amount);

	void StartDeliveryState(AActor *Building, int32 matId, int32 &amt);
    void ClearDeliveryState();

	bool isDelivering = false;

	//Actor Targets and Home
	AActor* TargetBuilding;
	UPROPERTY(EditAnywhere, Category="Vehicle Properties")
	AActor* HomeBuilding;

};
