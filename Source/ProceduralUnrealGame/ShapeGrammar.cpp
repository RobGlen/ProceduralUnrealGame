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
	FVector& normal = defaultNormal;
	float randomFactor = 1.0f;

	for ( int i = 0; i < vertices.Num(); i += 6 )
	{
		//if we are not using default extrusion
		normal = ( normals ) ? ( *normals )[i] : defaultNormal;

		if ( randomiseHeights )
		{
			randomFactor = Maths::RandomGen( 0.4f, 2.0f );
			normal *= randomFactor;
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

		FVector side[4];
		for ( int j = 0; j < 4; ++j )
		{
			int next = ( j+1 >= 4 ) ? 0 : j+1;
			//newverts.Add( newverts[j] );
			//newverts.Add( verts[j+1] );
		}
	}

	vertices.Append( newverts );
}