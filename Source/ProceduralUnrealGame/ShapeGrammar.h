// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */

struct Line
{
	FVector a, b;
};

class PROCEDURALUNREALGAME_API ShapeGrammar
{
private:
	void CreateSide( const FVector& a, const FVector& b, const FVector& c, const FVector& d,  TArray<FVector>& verts );

public:
	ShapeGrammar();
	~ShapeGrammar();
	void ExtrudePlanes( TArray<FVector>& vertices, bool randomiseHeights = false, float min = 1.0f, float max = 1.0f, TArray<FVector>* normals = nullptr );
	void CreatePathMesh( TArray<Line>& path, TArray<FVector>& vertices, float width );
	void CreatePlane( TArray<FVector>& vertices, float scale = 1.0f );
};
