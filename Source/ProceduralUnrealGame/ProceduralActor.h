// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralActor.generated.h"

//#include "StaticMeshComponent.h"

UCLASS()
class PROCEDURALUNREALGAME_API AProceduralActor : public AActor
{
	GENERATED_BODY()
private:
	UProceduralMeshComponent* m_pMesh = nullptr;
	//TArray<FVector>& vertices;

public:	
	// Sets default values for this actor's properties
	AProceduralActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetVertexData(	TArray<FVector>& vertices,
						TArray<FVector2D>& uvs,
						TArray<FVector>& normals,
						TArray<int>& triangles );

	void SetVertices( TArray<FVector>& vertices );
	
};
