// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class PROCEDURALUNREALGAME_API ShapeGrammar
{
public:
	ShapeGrammar();
	~ShapeGrammar();
	void ExtrudePlane( TArray<FVector>& vertices, bool randomiseHeights = false, TArray<FVector>* normals = nullptr );
};
