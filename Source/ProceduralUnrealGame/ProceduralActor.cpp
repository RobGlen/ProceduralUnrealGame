// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralUnrealGame.h"
#include "ProceduralActor.h"


// Sets default values
AProceduralActor::AProceduralActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_pMesh = CreateDefaultSubobject<UProceduralMeshComponent>( TEXT( "GeneratedMesh" ) );
	//m_pMaterial = CreateDefaultSubobject<UMaterial>( TEXT( "MeshMaterial" ) );
	RootComponent = m_pMesh;
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

void AProceduralActor::SetVertices( TArray<FVector>& vertices, bool useCollision, float uvScale )
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
		uv[1] = { uvScale, 0.0f };
		uv[2] = { 0.0f, uvScale };

		uv[3] = { uvScale, uvScale };
		uv[4] = { 0.0f, uvScale };
		uv[5] = { uvScale, 0.0f };

		for ( int j = 0; j < 6; ++j )
		{
			uvs.Add( uv[j] );
		}
	}

	for ( int i = 0; i < vertices.Num(); i += 3 )
	{
		FVector ab = vertices[i+1] - vertices[i];
		FVector ac = vertices[i+2] - vertices[i];
		ab.Normalize();
		ac.Normalize();
		FVector normal = FVector::CrossProduct( ac, ab );
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

	m_pMesh->CreateMeshSection( 0, vertices, triangles, normals, uvs, colors, tangents, useCollision );

	//m_pMesh->AttachTo(RootComponent);
}

void AProceduralActor::SetMaterial( FString materialName )
{
	FString materialPath = "/Game/Materials/" + materialName + "." + materialName;
	//static ConstructorHelpers::FObjectFinder<UMaterial> Material( ( *materialPath ) );

	//m_pMaterial = LoadObject<UMaterial>( NULL, ( *materialPath ), NULL, LOAD_None, NULL );
	m_pMaterial = ( UMaterial* )StaticLoadObject( UMaterial::StaticClass(), nullptr, ( *materialPath ) );

	if ( !m_pMaterial )
	{
		UE_LOG( LogTemp, Warning, TEXT( "No Material!" ) );
		return;
	}
	
	UMaterialInstanceDynamic* p_matDynamic = UMaterialInstanceDynamic::Create( m_pMaterial, m_pMesh );

	if ( !p_matDynamic )
	{
		UE_LOG( LogTemp, Warning, TEXT( "No Dynamic Material!" ) );
		return;
	}

	m_pMesh->SetMaterial( 0, p_matDynamic );
	
	/*if ( Material.Object != NULL )
	{
		m_pMaterial = ( UMaterial* )Material.Object;

		
	}*/
}