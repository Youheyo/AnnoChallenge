// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingActor.h"
#include "FurnaceBuildingActor.generated.h"

UCLASS()
class ANNOCHALLENGE_API AFurnaceBuildingActor : public ABuildingActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFurnaceBuildingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

void processMaterial(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere)
	int ironHeld = 0;
	UPROPERTY(VisibleAnywhere)
	int coalHeld = 0;
	UPROPERTY(VisibleAnywhere)
	int steelHeld = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ReceiveMaterials(int32 matId, int32 amount) override;

	virtual bool CanReceiveMats(int32 matId) override;

};
