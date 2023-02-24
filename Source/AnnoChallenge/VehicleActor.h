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

	UPROPERTY(EditAnywhere) UStaticMeshComponent* Mesh;
	bool isLoading = false;

	UPROPERTY(EditAnywhere, Category="Vehicle Properties")
	float loadingSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category="Vehicle Properties")
	float VehicleSpeed = 10.0f;

    int CheckLoad();
	float loadProgress = 0;
	float loadDuration = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float iron, coal, steel, lumber = 0;
	UPROPERTY(EditAnywhere, Category="Vehicle Properties")
	float maxLoad = 4;

	void loadMaterials(float DeltaTime);
	void GetMaterials(int32 matId, int32 &amount);


    void ClearDeliveryState();
	void StartDeliveryState(AActor *Building, int32 matId, int32 &amt);

	bool isDelivering = false;

	AActor* TargetBuilding;
	UPROPERTY(EditAnywhere, Category="Vehicle Properties")
	AActor* HomeBuilding;

};
