// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingActor.h"
#include "IronMineActor.generated.h"

UCLASS()
class ANNOCHALLENGE_API AIronMineActor : public ABuildingActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIronMineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void processMaterial(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere)
	int ironHeld = 0;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    int GetMaterialCount(int32 matId) override;
};
