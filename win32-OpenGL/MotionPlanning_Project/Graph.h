/******************************************************************************/
/*!
\file Graph.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #02
\date 01/03/2012
\brief
This is the graph class that will be used to generate the graph to be used by the algorithm to find the shortest path

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <list>

//Edge
class Edge
{
public:
	Edge();
	~Edge();
	Edge(const Edge & ed);
	Edge & operator=(const Edge & ed);
	
	int from;
	int to;
};

//State
class State
{
public:
	State();
	~State();
	State(const State & st);
	State & operator=(const State & st);
	
	float worldPositionX;
	float worldPositionY;

	std::vector<Edge> edges;
};

#define MAX_DISTANCE	9999999
#define DIRECT_LINK		888
#define NO_LINK			-1

//Path
class Path
{
public:
	Path();
	~Path();
	Path & operator=(Path & pa1);
	
	//to add Floyd's path algorithm here
	std::vector<State> states;
	std::vector<State> shortestPathStates;
	std::list<int> shortestPathIndices;
	std::vector<int> intermediateNodes;
	

	typedef std::vector< std::vector< float > > VectorFloatArr2D;
	typedef std::vector< std::vector< int > > VectorIntArr2D;
	VectorFloatArr2D		m_distanceMtx;
	VectorIntArr2D			m_pathMtx;

	void GenerateMatrix( void );
	void InitMatrix( void );
	void PopulateMatrix( void );

	void FloydAlgorithm( void );
	void ComputeShortestPath( const int startIndex, const int endIndex );

	void FindIntermediateNodes( const int startIndex, const int endIndex, bool leftToRight );
	void AddNodeIndex( const int stateIndex );
};

#endif