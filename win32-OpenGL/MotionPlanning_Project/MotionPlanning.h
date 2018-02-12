/******************************************************************************/
/*!
\file MotionPlanning.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1150
\par Project #02
\date 01/03/2012
\brief
This is the motion planning class that will be used to generate and link trapezoids based on the provided line segments

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#ifndef _MOTIONPLANNING_H_
#define _MOTIONPLANNING_H_

#include <list>
#include <vector>
#include <unordered_map>
#include <hash_map>
#include <set>

#include "MathUtility.h"
#include "Graph.h"

#define BOUNDING_RECT_MARGIN	25

//forward declaration
class AG_State;

namespace
{
	const unsigned CHAR_BUFFER_SIZE = 4;
	const unsigned KEY_SIZE = 7;
}


class Trapezoid
{
public:
	Trapezoid();
	~Trapezoid();
	Trapezoid(const Trapezoid & tra);
	Trapezoid & operator=(const Trapezoid & tra);
	bool operator==(Trapezoid tra);
	
	LineSegment2D top;
	LineSegment2D bottom;
	Point2D leftPoint;
	Point2D rightPoint;
	Trapezoid * neighbours[4];
	//NOTES
	//neighbours[0] = upper left neighbour
	//neighbours[1] = lower left neighbour
	//neighbours[2] = upper right neighbour
	//neighbours[3] = lower right neighbour

	bool neighbourUsed[4];//for the graph (build)
	int stateIndex;//for the graph (navigation) - the state index of the state created in the middle of the trapezoid
	
	//Optional - to add any helper variables
	bool isVisited;
	AG_State * nodePtr; //the pointer to the node in the search tree
};



//Directed acyclic graph for point trapezoidal location problem
enum AG_TYPE {AG_XNODE,AG_YNODE,AG_LEAF};



//Directed acyclic graph State class
class AG_State
{
public:
	AG_State();
	~AG_State();
	AG_State(const AG_State & st);
	AG_State & operator=(const AG_State & st);	
	
	AG_State *left;
	AG_State *right;

	AG_TYPE type;

	Point2D point;
	LineSegment2D lineSegment;
	Trapezoid * trapezoid;//the trapezoid pointing into trapezoidalList

	std::vector<AG_State*> parents;
};



class MotionPlanning_PointRobot
{	
	std::list<Trapezoid> trapezoidalList;
	std::list<Trapezoid> unusedTrapezoidalList;//this is used only to display the unused trapezoids inside solid areas

	//To add any new private member data and member function if needed here
	//for debugging
	void DisplayTreeNodes( const AG_State & searchStructure, const unsigned offset ) const;
	//for traversing the tree
	void TraverseTree( AG_State * searchStructure );
	void DeleteTree( void );

	typedef std::unordered_map< const char *, Point2D >			PointMap;
	typedef std::hash_map< const std::string, Point2D >			PointStrMap;
	typedef std::vector< Point2D >								PointVector;

	std::set<AG_State * > agStateContainer;
	std::vector< Trapezoid * > trapezoidIntersections;
	PointVector usedPoints;
	PointMap usedPointsMap;

	Trapezoid * previousTopPosition;
	Trapezoid * previousBottomPosition;

	AG_State * currentStatePtr;

	int currentStateIndex;
	int tcount;

public:
	MotionPlanning_PointRobot();
	~MotionPlanning_PointRobot();

	Path * path;
	std::vector<LineSegment2D> segmentList;
	Trapezoid boundingRect;
	//searchStructure = point location data structure = search structure = 
	//directed acyclic graph with a single root and exactly one leaf for every trapezoid of the trapezoidal map.
	AG_State searchStructure;

	void Calculate_LineSegments_Normals();//this function computes the normal vectors of the line segments
	void Adjust_StartEnd_PointsSegment();//Adjust the start and end points of the line segments so that the start is always on the left.
	void TrapezoidalMap();//compute the trapezoids that form the free space and link them together
	void AdjustRemainingTrapezoids();//IS IMPLEMENTED - It adjusts the top and bottom line segments of every trapezoid
	void RemoveUnusedTrapezoids();//Remove the unused (solid areas) trapezoids
	void PathBuilding();// generates a graph with states and edges

	void StatesBuild(Trapezoid * next,int previousState);//to be used inside PathBuilding() fct - It is a recursive function that builds the states and edges of the graph
	Trapezoid * TrapezoidSearch(AG_State * searchS,Point2D pointS,Point2D pointE);//IS IMPLEMENTED
	Trapezoid Calculate_BoundingRectangle();//IS IMPLEMENTED
	
	//To add any new public member data and member function if needed here
	bool m_showBoundingRect;
	bool m_showMainSegments;
	bool m_showValidTrapezoids;
	bool m_showUnusedTrapezoids;
	bool m_showGraphStates;
	bool m_showGraphPath;
	bool m_showGraphStateIndices;

	void AddUsedPoint( const Point2D point );
	void GeneratePointKey( const Point2D point, char * pointKeyArr, const unsigned arrSize ) const;
	const bool IsPointUsed( Point2D point ) const;
	const bool IsPointUsedInMap( Point2D point) const;

	void TraverseIntersectedTrapezoids( Trapezoid * currentTrapezoid, const LineSegment2D & currLineSeg );

	//compute the trapezoids that form the free space and link them together
	void TrapezoidalMapHelperStartEndPtUsed( LineSegment2D & currLineSeg );
	void TrapezoidalMapHelperStartPtUsed( LineSegment2D & currLineSeg );
	void TrapezoidalMapHelperEndPtUsed( LineSegment2D & currLineSeg );
	void TrapezoidalMapHelperNoPtUsed( LineSegment2D & currLineSeg );

	void TrapezoidalMapHelperStartPtUsedMult( LineSegment2D & currLineSeg );
	void TrapezoidalMapHelperOtherPtComboUsedMult( LineSegment2D & currLineSeg );

	void TrapezoidalMapHelperMultSubseq( LineSegment2D & currLineSeg, int index );

	void TrapezoidalMapHelperEndPtUsedMultLast( LineSegment2D & currLineSeg, int index );
	void TrapezoidalMapHelperOtherPtComboUsedMultLast( LineSegment2D & currLineSeg, int index );	

	//link the middle trapezoid point states and shared between states to form the path
	void LinkNextAndPrevState( const int nextStateIndex, const int previousStateIndex );
	void LinkNeighbor( Trapezoid * trapezoid, const int trapMiddlePtIndex, const int neighborIndex, const int indexRelativeToNeighbor );
	
	const int GetStateIndex( const State & state ) const;

	//get the trapezoid lists
	const std::list<Trapezoid> & GetTrapezoidList( void ) const;
	const std::list<Trapezoid> & GetUnusedTrapezoidList( void ) const;	
};

#endif