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

	Maths::ResetSeed();
	// ...
}


// Called when the game starts
void UGenerationManager::BeginPlay()
{
	Super::BeginPlay();
	// start the generation process
	Generate();
}

// Called every frame
void UGenerationManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UGenerationManager::Generate( void )
{
	int rows = 6, columns = 6;
	FVector position( 0.0f, 0.0f, 0.0f );
	float offset = 5000.0f;
	m_pShapeGrammar = new ShapeGrammar();

	CreateWater();

	for ( int i = 0; i < rows; ++i )
	{
		for ( int j = 0; j < columns; ++j )
		{
			position.X = ( ( float )i * offset ) + Maths::RandomGen( -500, 500 );
			position.Y = ( ( float )j * offset ) + Maths::RandomGen( -500, 500 );
			float randmin = Maths::RandomGen( 0.4f, 20.4 );
			float randmax = randmin + Maths::RandomGen( 0.6f, 10.0f );
			GenerateTreepmapArea( position, randmin, randmax );
		}
	}

	delete m_pShapeGrammar;
}

void UGenerationManager::CreateWater( void )
{
	TArray<FVector> vertices;
	FActorSpawnParameters spawnParams;
	FVector position( 0.0f, 0.0f, 2.0f );
	FRotator rotation( 0.0f, 0.0f, 0.0f );

	float planeScale = 1000.0f;
	m_pShapeGrammar->CreatePlane( vertices, planeScale );

	AProceduralActor* p_obj = GetWorld()->SpawnActor<AProceduralActor>( AProceduralActor::StaticClass(), position, rotation, spawnParams );
	p_obj->SetVertices( vertices, false, planeScale );
	p_obj->SetActorScale3D( FVector( 100.0f, 100.0f, 100.0f ) );
	p_obj->SetMaterial( "M_Water_Ocean" );
}

void UGenerationManager::GenerateTreepmapArea( FVector& position, float& minHeight, float& maxHeight  )
{
	SquarifiedTreemap squarifiedTreemap;
	

	float scaleFactor = 20.0f;
	SquarifiedTreemapParameters stmParams;
	stmParams.randomiseSegmentCountPerRecursion = true;
	stmParams.depth = Maths::RandomGen( 4, 8 );
	stmParams.rootCell.points[0] = { -scaleFactor, -scaleFactor };
	stmParams.rootCell.points[1] = { scaleFactor, -scaleFactor };
	stmParams.rootCell.points[2] = { scaleFactor, scaleFactor };
	stmParams.rootCell.points[3] = { -scaleFactor, scaleFactor };

	TArray<FVector> vertices;

	UE_LOG( LogTemp, Warning, TEXT( "Generate treemap" ) );
	squarifiedTreemap.GenerateSTM( stmParams, vertices );
	m_pShapeGrammar->ExtrudePlanes( vertices, true, minHeight, maxHeight );

	FActorSpawnParameters spawnParams;
	//FVector position( 0.0f, 0.0f, 0.0f );
	FRotator rotation( 0.0f, 0.0f, 0.0f );

	AProceduralActor* p_obj = GetWorld()->SpawnActor<AProceduralActor>( AProceduralActor::StaticClass(), position, rotation, spawnParams );
	p_obj->SetVertices( vertices );
	p_obj->SetActorScale3D( FVector( 100.0f, 100.0f, 100.0f ) );
	p_obj->SetMaterial( "M_Concrete_Tiles" );
}