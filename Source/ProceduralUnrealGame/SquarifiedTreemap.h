// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
/**
 * 
 */

struct XY
{
	float x, y;
};

struct Cell
{
	XY points[4];
};

struct Node
{
	int cellValue;
	Cell cell;
	std::vector<Node*> children;
};

struct SquarifiedTreemapParameters
{
	bool randomiseCellsPerRecursion = false;
	bool useCellValues = false;
	bool randomiseSegmentCountPerRecursion = false;
	Cell rootCell;
	int baseSegments = 2;
	int depth = 1;
	int decay = 0;
};

class PROCEDURALUNREALGAME_API SquarifiedTreemap
{
private:
	Node* m_pRoot = nullptr;
	SquarifiedTreemapParameters m_stmParams;

	Node* GenerateTree( Node* p_parent, int segments, int depth, int decay );
	void GenerateMap( Node* p_node, bool horizontal );
	void ConvertSTMToVertices( Node* p_node, TArray<FVector>& vertices );
	void DeleteTree( Node* p_node );

public:
	SquarifiedTreemap();
	~SquarifiedTreemap();
	void GenerateSTM( SquarifiedTreemapParameters& stmParams, TArray<FVector>& vertices );
};
