// Fill out your copyright notice in the Description page of Project Settings.


#include "MeshGen.h"


// Called when the game starts or when spawned
void AMeshGen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeshGen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AMeshGen::AMeshGen()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = mesh;
	// New in UE 4.17, multi-threaded PhysX cooking.
	mesh->bUseAsyncCooking = true;
}


// This is called when actor is spawned (at runtime or when you drop it into the world in editor)
void AMeshGen::PostActorCreated()
{
	Super::PostActorCreated();
	GenerateMesh();
}

// This is called when actor is already in level and map is opened
void AMeshGen::PostLoad()
{
	Super::PostLoad();
	GenerateMesh();
}

void AMeshGen::GenerateMesh()
{
	CreateCube();
}

void AMeshGen::AddQuad(TArray<FVector>& vertices, TArray<int32>& triangles, TArray<FVector>& normals, FVector c0, FVector c1, FVector c2, FVector c3, FVector normal)
{
	int indexOffset = vertices.Num();

	vertices.Add(c0);
	vertices.Add(c1);
	vertices.Add(c2);
	vertices.Add(c3);
	
	triangles.Add(indexOffset);
	triangles.Add(indexOffset + 1);
	triangles.Add(indexOffset + 2);
	triangles.Add(indexOffset);
	triangles.Add(indexOffset + 2);
	triangles.Add(indexOffset + 3);

	normals.Add(normal);
	normals.Add(normal);
	normals.Add(normal);
	normals.Add(normal);
}

void AMeshGen::CreateCube()
{

	float size = 100;
	
	TArray<FVector> vertices;
	TArray<int32> triangles;
	TArray<FVector> normals;

	FVector cb0 = FVector(0,0,0);
	FVector cb1 = FVector(size,0,0);
	FVector cb2 = FVector(size,size,0);
	FVector cb3 = FVector(0,size,0);
	FVector topOffset = FVector(0,0,size);
	AddQuad(vertices, triangles, normals, cb0,cb1,cb2,cb3, FVector(0,0,-1)); // bottom
	AddQuad(vertices, triangles, normals, cb3 + topOffset,cb2 + topOffset,cb1 + topOffset,cb0 + topOffset, FVector(0,0,1)); // top

	FVector cl0 = FVector(0,0,0);
	FVector cl1 = FVector(0,0,size);
	FVector cl2 = FVector(0,size,size);
	FVector cl3 = FVector(0,size,0);
	FVector rightOffset = FVector(size,0,0);
	AddQuad(vertices, triangles, normals, cl3, cl2, cl1, cl0, FVector(-1, 0 ,0)); // left
	AddQuad(vertices, triangles, normals, cl0 + rightOffset, cl1 + rightOffset, cl2 + rightOffset, cl3 + rightOffset, FVector(1, 0, 0)); // right

	FVector cf0 = FVector(0,size,0);
	FVector cf1 = FVector(size,size,0);
	FVector cf2 = FVector(size,size,size);
	FVector cf3 = FVector(0,size,size);
	FVector backOffset = FVector(0,-size,0);
	AddQuad(vertices, triangles, normals, cf0, cf1, cf2, cf3, FVector(0, 1, 0)); // front
	AddQuad(vertices, triangles, normals, cf3 + backOffset,cf2 + backOffset,cf1 + backOffset, cf0 + backOffset, FVector(0, -1, 0)); // back

	TArray<FVector2d> emptyUV;
	TArray<FColor> emptyColor;
	TArray<FProcMeshTangent> emptyTangent;

	mesh->CreateMeshSection(0, vertices, triangles, normals,  emptyUV , emptyColor, emptyTangent, true );
	
}
