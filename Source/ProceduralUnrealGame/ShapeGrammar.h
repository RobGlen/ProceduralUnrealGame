// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class PROCEDURALUNREALGAME_API ShapeGrammar
{
private:
	void CreateSide( const FVector& a, const FVector& b, const FVector& c, const FVector& d,  TArray<FVector>& verts );

public:
	ShapeGrammar();
	~ShapeGrammar();
	void ExtrudePlane( TArray<FVector>& vertices, bool randomiseHeights = false, TArray<FVector>* normals = nullptr );
};
