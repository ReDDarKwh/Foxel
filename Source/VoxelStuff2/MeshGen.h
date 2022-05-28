// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProceduralMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeshGen.generated.h"

UCLASS()
class VOXELSTUFF2_API AMeshGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeshGen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostLoad() override;
	virtual void PostActorCreated() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void GenerateMesh();
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent * mesh;
	void CreateTriangle();
	void GetCubeCornerVertices(TArray<FVector>& vertices, FVector vector);
	void CreateCube();
	void AddQuad(TArray<FVector>& vertices, TArray<int32>& triangles, TArray<FVector>& normals, FVector c0, FVector c1, FVector c2, FVector
	             c3, FVector normal);
};
