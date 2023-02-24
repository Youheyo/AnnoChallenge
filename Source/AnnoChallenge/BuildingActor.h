// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "BuildingActor.generated.h"

UCLASS()
class ANNOCHALLENGE_API ABuildingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//STATIC MESH OF BUILDING
	UPROPERTY(EditAnywhere, Category="Building Property")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category="Building Property")
	AActor* TargetBuilding;

	///PROCESSING MATERIAL PROPERTIES
	UPROPERTY(EditAnywhere, Category="Building Property")
	int32 maxInputMatsHeld = 3;
	UPROPERTY(EditAnywhere, Category="Building Property")
	int32 maxOutputMatsHeld = 3;

	///PROCESSING RELATED VALUES
	virtual void processMaterial(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	virtual void callVehicle(int32 matId, int32 &amount);
	bool isProcessing = false;

	UPROPERTY(EditAnywhere, Category="Building Property")
	float processDuration = 5.0f;
	UPROPERTY(EditAnywhere, Category="Building Property")
	float processSpeed = 1.0f;
	float processProgress = 0.0f;

	int32 COAL_MATERIAL = 0;
	int32 IRON_MATERIAL = 1;
	int32 STEEL_MATERIAL = 2;
	int32 LUMBER_MATERIAL = 3;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ReceiveMaterials(int32 amount);

};
