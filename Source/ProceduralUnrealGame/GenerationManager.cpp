// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralUnrealGame.h"
#include "GenerationManager.h"
#include "SquarifiedTreemap.h"
#include "ShapeGrammar.h"
#include "Maths.h"
#include "ProceduralActor.h"

// Sets default values for this component's properties
UGenerationManager::UGenerationManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGenerationManager::BeginPlay()
{
	Super::BeginPlay();

	Maths::ResetSeed();

	// start the generation process
	GenerateTreepmapArea();
}


// Called every frame
void UGenerationManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UGenerationManager::GenerateTreepmapArea( void )
{
	SquarifiedTreemap squarifiedTreemap;
	ShapeGrammar shapeGrammar;

	float scaleFactor = 20.0f;
	SquarifiedTreemapParameters stmParams;
	stmParams.randomiseSegmentCountPerRecursion = true;
	stmParams.depth = 6;
	stmParams.rootCell.points[0] = { -scaleFactor, -scaleFactor };
	stmParams.rootCell.points[1] = { scaleFactor, -scaleFactor };
	stmParams.rootCell.points[2] = { scaleFactor, scaleFactor };
	stmParams.rootCell.points[3] = { -scaleFactor, scaleFactor };

	TArray<FVector> vertices;

	squarifiedTreemap.GenerateSTM( stmParams, vertices );
	shapeGrammar.ExtrudePlane( vertices, true );
	UE_LOG( LogTemp, Warning, TEXT( "Generate treemap" ) );

	FActorSpawnParameters spawnParams;
	FVector position( 0.0f, 0.0f, 0.0f );
	FRotator rotation( 0.0f, 0.0f, 0.0f );

	AProceduralActor* p_obj = GetWorld()->SpawnActor<AProceduralActor>( AProceduralActor::StaticClass(), position, rotation, spawnParams );
	p_obj->SetVertices( vertices );
	p_obj->SetActorScale3D( FVector( 100.0f, 100.0f, 100.0f ) );

	/*TArray<FVector> verts;
	verts.Add( FVector( 0.0f, 0.0f, 1.0f ) );
	verts.Add( FVector( -1.0f, 0.0f, -1.0f ) );
	verts.Add( FVector( 1.0f, 0.0f, -1.0f ) );*/
}