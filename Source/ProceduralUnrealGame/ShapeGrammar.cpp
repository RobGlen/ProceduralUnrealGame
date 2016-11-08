// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralUnrealGame.h"
#include "ShapeGrammar.h"
#include "Maths.h"

ShapeGrammar::ShapeGrammar()
{
}

ShapeGrammar::~ShapeGrammar()
{
}

void ShapeGrammar::ExtrudePlane( TArray<FVector>& vertices, bool randomiseHeights, TArray<FVector>* normals )
{
	TArray<FVector> newverts;
	FVector defaultNormal( 0.0f, 0.0f, 1.0f );
	FVector normal = defaultNormal;
	float randomFactor = 1.0f;

	for ( int i = 0; i < vertices.Num(); i += 6 )
	{
		//if we are not using default extrusion
		normal = ( normals ) ? ( *normals )[i] : defaultNormal;

		if ( randomiseHeights )
		{
			randomFactor = Maths::RandomGen( 0.4f, 1.0f );
			normal *= randomFactor;
			UE_LOG( LogTemp, Warning, TEXT( "%f: ( %f, %f, %f )" ), randomFactor, normal.X, normal.Y, normal.Z );
		}

		FVector verts[4];
		verts[0] = vertices[i] + normal;
		verts[1] = vertices[i+1] + normal;
		verts[2] = vertices[i+2] + normal;
		verts[3] = vertices[i+3] + normal;
		
		newverts.Add( verts[0] );
		newverts.Add( verts[1] );
		newverts.Add( verts[2] );
		newverts.Add( verts[3] );
		newverts.Add( verts[2] );
		newverts.Add( verts[1] );

		CreateSide( verts[0],		vertices[i],	verts[1],		vertices[i+1],	newverts );
		CreateSide( verts[3],		vertices[i+3],	verts[2],		vertices[i+2],	newverts );
		CreateSide( verts[2],		vertices[i+2],	verts[0],		vertices[i],	newverts );
		CreateSide( verts[1],		vertices[i+1],	verts[3],		vertices[i+3],	newverts );
	}

	vertices.Append( newverts );
}

void ShapeGrammar::CreateSide( const FVector& a, const FVector& b, const FVector& c, const FVector& d, TArray<FVector>& verts )
{
	verts.Add( a );
	verts.Add( b );
	verts.Add( c );
	verts.Add( d );
	verts.Add( c );
	verts.Add( b );
}