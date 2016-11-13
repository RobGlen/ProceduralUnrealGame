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

/*
	Go through every 6 vertices (as two triangles make up a plane)
	Copy the verts and move them along the normal vector
	Create the sides between the new top and bottom planes
	Add the new vertices to the original vertex array
*/
void ShapeGrammar::ExtrudePlanes( TArray<FVector>& vertices, bool randomiseHeights, float min, float max, TArray<FVector>* normals )
{
	TArray<FVector> newverts;
	FVector defaultNormal( 0.0f, 0.0f, 1.0f );
	FVector normal = defaultNormal;

	for ( int i = 0; i < vertices.Num(); i += 6 )
	{
		//if we are not using default extrusion
		normal = ( normals ) ? ( *normals )[i] : defaultNormal;

		if ( randomiseHeights )
		{
			normal *= Maths::RandomGen( min, max );
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

/*
	Add the six vertices that make up the sides
*/
void ShapeGrammar::CreateSide( const FVector& a, const FVector& b, const FVector& c, const FVector& d, TArray<FVector>& verts )
{
	verts.Add( a );
	verts.Add( b );
	verts.Add( c );
	verts.Add( d );
	verts.Add( c );
	verts.Add( b );
}

/*
	Take each line in the path and add vertices based on the left and right vector of a and b of the line
*/
void ShapeGrammar::CreatePathMesh( TArray<Line>& path, TArray<FVector>& vertices, float width )
{
	for ( int i = 0; i < path.Num(); ++i )
	{
		FVector lineDir = path[i].b - path[i].a;
		lineDir.Normalize();
		FVector leftDir = lineDir.RotateAngleAxis( -90, FVector( 0.0f, 0.0f, 1.0f ) );
		FVector rightDir = lineDir.RotateAngleAxis( 90, FVector( 0.0f, 0.0f, 1.0f ) );
		FVector verts[4];
		verts[0] = path[i].b + leftDir;
		verts[1] = path[i].a + leftDir;
		verts[2] = path[i].b + rightDir;
		verts[3] = path[i].a + rightDir;

		vertices.Add( verts[0] );
		vertices.Add( verts[1] );
		vertices.Add( verts[2] );

		vertices.Add( verts[3] );
		vertices.Add( verts[2] );
		vertices.Add( verts[1] );
	}
}

/*
	Create a basic plane on the x and y axis based on the scale value
	(Should maybe add a way to make a plane perpendicular to a normal instead of just making them perpendicular to world up)
*/
void ShapeGrammar::CreatePlane( TArray<FVector>& vertices, float scale )
{
	FVector verts[4];
	verts[0] = { -scale, -scale, 0.0f };
	verts[1] = { -scale, scale, 0.0f };
	verts[2] = { scale, -scale, 0.0f };
	verts[3] = { scale, scale, 0.0f };

	vertices.Add( verts[0] );
	vertices.Add( verts[1] );
	vertices.Add( verts[2] );
	vertices.Add( verts[3] );
	vertices.Add( verts[2] );
	vertices.Add( verts[1] );
}