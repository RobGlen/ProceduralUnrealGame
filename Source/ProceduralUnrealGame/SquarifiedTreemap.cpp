// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralUnrealGame.h"
#include "SquarifiedTreemap.h"
#include "Maths.h"

SquarifiedTreemap::SquarifiedTreemap()
{
}

// recursively delete each node in the tree
SquarifiedTreemap::~SquarifiedTreemap()
{
	DeleteTree( m_pRoot );
}

/*
	Begin the generation process for the squarified treemap
	Create the root, construct the tree, then use the tree to create the split planes
	And then convert the results into vertex data
*/
void SquarifiedTreemap::GenerateSTM( SquarifiedTreemapParameters& stmParams, TArray<FVector>& vertices  )
{
	m_pRoot = new Node;
	m_pRoot->cellValue = 1;
	m_stmParams = stmParams;
	GenerateTree( m_pRoot, stmParams.baseSegments, stmParams.depth, stmParams.decay );
	
	m_pRoot->cell = m_stmParams.rootCell;
	GenerateMap( m_pRoot, true );

	ConvertSTMToVertices( m_pRoot, vertices );
}

/*
	Recursively construct the tree
	Construct a child for each segment, add the child to the parent, and construct the child's children
*/
Node* SquarifiedTreemap::GenerateTree( Node* p_parent, int segments, int depth, int decay )
{
	if ( !p_parent || depth <= 0 )
	{
		return p_parent;
	}

	if ( m_stmParams.randomiseSegmentCountPerRecursion )
	{
		segments = Maths::RandomGen( 2, 4 );
	}

	for ( int i = 0; i < segments; ++i )
	{
		Node* node = new Node;
		node->cellValue = 1;

		if ( m_stmParams.randomiseCellsPerRecursion )
		{
			node->cellValue = Maths::RandomGen( 1, 4 );
		}

		p_parent->children.push_back( node );
		GenerateTree( node, segments - decay, depth - 1, decay );
	}

	return p_parent;
}

/*
	Split the plane up based on children recursively
	Set the child width based on parent width/height and child count
	then set right/bottom side points based on left/top side points + child width/height
	then set the position of points based on which child it is currently on
	then go to child method to split up that plane
*/
void SquarifiedTreemap::GenerateMap( Node* p_node, bool horizontal )
{
	if ( !p_node )
	{
		return;
	}

	float childCount = p_node->children.size();
	float parentWidth = p_node->cell.points[1].x - p_node->cell.points[0].x;
	float parentHeight = p_node->cell.points[3].y - p_node->cell.points[0].y;

	for ( int i = 0; i < childCount; ++i )
	{
		Node* thisnode = p_node->children[i];

		thisnode->cell = p_node->cell;

		if ( horizontal )
		{
			float childWidth = parentWidth / childCount;
			thisnode->cell.points[1].x = thisnode->cell.points[0].x + childWidth;
			thisnode->cell.points[2].x = thisnode->cell.points[3].x + childWidth;

			for ( int j = 0; j < 4; ++j )
			{
				thisnode->cell.points[j].x += childWidth * i;	
			}
		}
		else
		{
			float childHeight = parentHeight / childCount;
			thisnode->cell.points[2].y = thisnode->cell.points[1].y + childHeight;
			thisnode->cell.points[3].y = thisnode->cell.points[0].y + childHeight;

			for ( int j = 0; j < 4; ++j )
			{
				thisnode->cell.points[j].y += childHeight * i;	
			}
		}

		GenerateMap( thisnode, !horizontal );
	}
	
}

/*
	Go to leafs of tree (ends) and create vertex data from cell points
	All of the children will make up the total of the root plane
*/
void SquarifiedTreemap::ConvertSTMToVertices( Node* p_node, TArray<FVector>& vertices )
{
	if ( !p_node )
	{
		return;
	}

	//is a leaf
	if ( p_node->children.empty() )
	{
		FVector vert;
		//tri 1
		vert = { p_node->cell.points[0].x, p_node->cell.points[0].y, 0.0f };
		vertices.Add( vert );

		vert = { p_node->cell.points[3].x, p_node->cell.points[3].y, 0.0f };
		vertices.Add( vert );

		vert = { p_node->cell.points[1].x, p_node->cell.points[1].y, 0.0f };
		vertices.Add( vert );

		//tri 2
		vert = { p_node->cell.points[2].x, p_node->cell.points[2].y, 0.0f };
		vertices.Add( vert );

		vert = { p_node->cell.points[1].x, p_node->cell.points[1].y, 0.0f };
		vertices.Add( vert );

		vert = { p_node->cell.points[3].x, p_node->cell.points[3].y, 0.0f };
		vertices.Add( vert );
	}
	else
	{
		for ( std::vector<Node*>::iterator itr = p_node->children.begin(); itr != p_node->children.end(); ++itr )
		{
			ConvertSTMToVertices( ( *itr ), vertices );
		}
	}
}

/*
	If the current node is null return
	Recursively go through the children
	After that, delete the current node as every node below it has been deleted
*/
void SquarifiedTreemap::DeleteTree( Node* p_node )
{
	if ( !p_node )
	{
		return;
	}

	for ( std::vector<Node*>::iterator itr = p_node->children.begin(); itr != p_node->children.end(); ++itr )
	{
		DeleteTree( ( *itr ) );
	}

	delete p_node;
}