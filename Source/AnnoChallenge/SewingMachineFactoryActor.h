// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingActor.h"
#include "SewingMachineFactoryActor.generated.h"

UCLASS()
class ANNOCHALLENGE_API ASewingMachineFactoryActor : public ABuildingActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASewingMachineFactoryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void processMaterial(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere)
	int sewingMachinesHeld = 0;
	UPROPERTY(VisibleAnywhere)
	int steelHeld = 0;
	UPROPERTY(VisibleAnywhere)
	int lumberHeld = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ReceiveMaterials(int32 matId, int32 amount) override;
	
	virtual bool CanReceiveMats(int32 matId) override;

    int GetMaterialCount(int32 matId) override;
};