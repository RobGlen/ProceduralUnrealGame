// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralUnrealGame.h"
#include "ProceduralActor.h"


// Sets default values
AProceduralActor::AProceduralActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_pMesh = CreateDefaultSubobject<UProceduralMeshComponent>( TEXT( "GeneratedMesh" ) );
}

// Called when the game starts or when spawned
void AProceduralActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProceduralActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProceduralActor::SetVertexData(	TArray<FVector>& vertices,
										TArray<FVector2D>& uvs,
										TArray<FVector>& normals,
										TArray<int>& triangles )
{
	TArray<FColor> colors;
	TArray<FProcMeshTangent> tangents;
	m_pMesh->CreateMeshSection( 1, vertices, triangles, normals, uvs, colors, tangents, false );
}

void AProceduralActor::SetVertices( TArray<FVector>& vertices )
{
	TArray<FVector2D> uvs;
	TArray<FVector> normals;
	TArray<int> triangles;
	TArray<FColor> colors;
	TArray<FProcMeshTangent> tangents;

	for ( int i = 0; i < vertices.Num(); i += 6 )
	{
		FVector2D uv[6];
		uv[0] = { 0.0f, 0.0f };
		uv[1] = { 1.0f, 0.0f };
		uv[2] = { 0.0f, 1.0f };

		uv[3] = { 1.0f, 1.0f };
		uv[4] = { 0.0f, 1.0f };
		uv[5] = { 1.0f, 0.0f };

		for ( int j = 0; j < 6; ++j )
		{
			uvs.Add( uv[j] );
		}
	}

	for ( int i = 0; i < vertices.Num(); i += 3 )
	{
		FVector ab = vertices[i+1] - vertices[i];
		FVector ac = vertices[i+2] - vertices[i];
		FVector normal = FVector::CrossProduct( ab, ac );
		normals.Add( normal );
		normals.Add( normal );
		normals.Add( normal );
	}

	for ( int i = 0; i < vertices.Num(); ++i )
	{
		triangles.Add( i );
	}

	colors.Add( FColor( 255, 255, 255, 255 ) );
	tangents.Add( FProcMeshTangent( 1, 1, 1 ) );

	m_pMesh->CreateMeshSection( 1, vertices, triangles, normals, uvs, colors, tangents, true );

	//m_pMesh->AttachTo(RootComponent);
}