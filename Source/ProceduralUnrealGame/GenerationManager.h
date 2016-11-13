// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SceneComponent.h"
#include "GenerationManager.generated.h"

class ShapeGrammar;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDURALUNREALGAME_API UGenerationManager : public USceneComponent
{
	GENERATED_BODY()

private:
	ShapeGrammar* m_pShapeGrammar;
	APawn* m_pPlayer;

public:	
	// Sets default values for this component's properties
	UGenerationManager();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void Generate( void );
	void CreateWater( void );
	void GenerateTreepmapArea( FVector& position, float& minHeight, float& maxHeight );
	
};
