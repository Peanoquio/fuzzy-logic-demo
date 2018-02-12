/******************************************************************************/
/*!
\file MotionPlanning.cpp
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

#include "MotionPlanning.h"
#include <math.h>

#include <iostream>
#include <iomanip>


//Trapezoid class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The constructor for the Trapezoid class

\param

\return
*/
/******************************************************************************/
Trapezoid::Trapezoid()
{
	neighbours[0]=NULL;
	neighbours[1]=NULL;
	neighbours[2]=NULL;
	neighbours[3]=NULL;	

	neighbourUsed[0] = false;
	neighbourUsed[1] = false;
	neighbourUsed[2] = false;
	neighbourUsed[3] = false;

	isVisited = false;

	stateIndex = -1;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The destructor for the Trapezoid class

\param

\return
*/
/******************************************************************************/
Trapezoid::~Trapezoid()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The assignment operator overload for the Trapezoid class

\param tra
the Trapezoid class to be assigned

\return Trapezoid
the Trapezoid
*/
/******************************************************************************/
Trapezoid & Trapezoid::operator=(const Trapezoid & tra)
{
	top = tra.top;
	bottom = tra.bottom;
	leftPoint = tra.leftPoint;
	rightPoint = tra.rightPoint;
	neighbours[0] = tra.neighbours[0];
	neighbours[1] = tra.neighbours[1];
	neighbours[2] = tra.neighbours[2];
	neighbours[3] = tra.neighbours[3];
	neighbourUsed[0] = tra.neighbourUsed[0];
	neighbourUsed[1] = tra.neighbourUsed[1];
	neighbourUsed[2] = tra.neighbourUsed[2];
	neighbourUsed[3] = tra.neighbourUsed[3];
	stateIndex = tra.stateIndex;
	isVisited = tra.isVisited;
	return *this;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The overloaded equality operator for the Trapezoid class

\param tra
the Trapezoid class to be compared

\return bool
if true, the trapezoid being compared is the same, otherwise false
*/
/******************************************************************************/
bool Trapezoid::operator==(Trapezoid tra)
{
	return ( (top == tra.top) &&
			 (bottom == tra.bottom) &&
			 (leftPoint == tra.leftPoint) &&
			 (rightPoint==tra.rightPoint) );//&&
			// (neighbours[0]==tra.neighbours[0]) &&
			// (neighbours[1]==tra.neighbours[1]) &&
			// (neighbours[2]==tra.neighbours[2]) &&
			// (neighbours[3]==tra.neighbours[3]) );			 
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The copy constructor for the Trapezoid class

\param tra
the Trapezoid class to be assigned

\return
*/
/******************************************************************************/
Trapezoid::Trapezoid(const Trapezoid & tra)
{
	top=tra.top;
	bottom=tra.bottom;
	leftPoint=tra.leftPoint;
	rightPoint=tra.rightPoint;
	neighbours[0]=tra.neighbours[0];
	neighbours[1]=tra.neighbours[1];
	neighbours[2]=tra.neighbours[2];
	neighbours[3]=tra.neighbours[3];
	neighbourUsed[0] = tra.neighbourUsed[0];
	neighbourUsed[1] = tra.neighbourUsed[1];
	neighbourUsed[2] = tra.neighbourUsed[2];
	neighbourUsed[3] = tra.neighbourUsed[3];
	stateIndex = tra.stateIndex;
	isVisited = tra.isVisited;
}
//End Trapezoid class


//AG_State class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The constructor for the AG_State class

\param

\return
*/
/******************************************************************************/
AG_State::AG_State()
{
	left = NULL;
	right = NULL;
	type = AG_LEAF;
	point = Point2D(0,0);
	lineSegment = LineSegment2D(Point2D(0,0),Point2D(0,0));
	trapezoid = NULL;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The destructor for the AG_State class

\param

\return
*/
/******************************************************************************/
AG_State::~AG_State()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The copy constructor for the AG_State class

\param st
the AG_State class to be assigned

\return
*/
/******************************************************************************/
AG_State::AG_State(const AG_State & st)
{
	left = st.left;
	right = st.right;
	type = st.type;
	point = st.point;
	lineSegment = st.lineSegment;
	trapezoid = st.trapezoid;
	for(unsigned int i = 0; i < st.parents.size(); i++)
		parents.push_back(st.parents[i]);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The assignment operator overload for the AG_State class

\param st
the AG_State class to be assigned

\return AG_State
the AG_State
*/
/******************************************************************************/
AG_State & AG_State::operator=(const AG_State & st)
{
	left = st.left;
	right = st.right;
	type = st.type;
	point = st.point;
	lineSegment = st.lineSegment;
	trapezoid = st.trapezoid;
	for(unsigned int i = 0; i < st.parents.size(); i++)
		parents.push_back(st.parents[i]);

	return *this;
}	
//End AG_State class


//MotionPlanning_PointRobot class
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the constructor for the MotionPlanning_PointRobot class

\param

\return
*/
/******************************************************************************/
MotionPlanning_PointRobot::MotionPlanning_PointRobot()
	: trapezoidalList(),
	unusedTrapezoidalList(),
	trapezoidIntersections(),
	usedPoints(),
	usedPointsMap(),
	previousTopPosition( 0 ),
	previousBottomPosition( 0 ),
	currentStatePtr( 0 ),
	currentStateIndex( -1 ),
	segmentList(),
	boundingRect(),
	searchStructure(),
	//display control flags
	m_showBoundingRect( true ),
	m_showMainSegments( true ),
	m_showValidTrapezoids( true ),
	m_showUnusedTrapezoids( true ),
	m_showGraphStates( true ),
	m_showGraphPath( true ),
	m_showGraphStateIndices( true )
{
	path = NULL;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the destructor for the MotionPlanning_PointRobot class

\param

\return
*/
/******************************************************************************/
MotionPlanning_PointRobot::~MotionPlanning_PointRobot()
{
	if(path)
	{
		delete path;
        path = NULL;
	}		

	//delete the AG State search tree
	this->DeleteTree();

	this->segmentList.clear();
	this->trapezoidIntersections.clear();
	this->trapezoidalList.clear();
	this->unusedTrapezoidalList.clear();
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Compute the normals of the line segments
\param
\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::Calculate_LineSegments_Normals()
{
	LineSegment2D lineSeg;
	Vector2D vec;

	//loop through each line segment in the list
	for ( unsigned int index = 0; index < this->segmentList.size(); ++index )
	{
		//get each line segment
		lineSeg = this->segmentList.at( index );

		//compute the vector
		vec.x = lineSeg.start.x - lineSeg.end.x;
		vec.y = lineSeg.start.y - lineSeg.end.y;

		//compute the normal
		lineSeg.normal.x = -vec.y;
		lineSeg.normal.y = vec.x;
		
		//get the magnitude of the normal vector
		float vecMagnitude = sqrt( ( lineSeg.normal.x * lineSeg.normal.x ) + ( lineSeg.normal.y * lineSeg.normal.y ) );
		//normalize the normal
		lineSeg.normal.x = lineSeg.normal.x / vecMagnitude;
		lineSeg.normal.y = lineSeg.normal.y / vecMagnitude;

		this->segmentList.at( index ) = lineSeg;

	}//for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
this will put the point with the lower x-value to the start point
end the point with the higher x-value to the end point
\param
\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::Adjust_StartEnd_PointsSegment()
{
	LineSegment2D lineSeg;
	float tempX = 0.0F;
	float tempY = 0.0F;

	//loop through each line segment in the list
	for ( unsigned int index = 0; index < this->segmentList.size(); ++index )
	{
		//each line segment
		lineSeg = this->segmentList.at( index );

		//compare the x values
		if ( lineSeg.end.x < lineSeg.start.x )
		{
			//if the x value of the end point is lower, swap the start and end points
			tempX = lineSeg.start.x;
			tempY = lineSeg.start.y;
			lineSeg.start.x = lineSeg.end.x;
			lineSeg.start.y = lineSeg.end.y;
			lineSeg.end.x = tempX; 
			lineSeg.end.y = tempY; 

			this->segmentList.at( index ) = lineSeg;
		}
	}//for loop
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
We give to this function a start point-segment and shall return the current
trapezoid in the search tree that holds this point (pointS).
(pointE) help us to classify the line segment (pointS,pointE) if pointS lies on a line-segment.

\param searchS
Directed acyclic graph State class
\param pointS
the start point of the intersecting line segment
\param pointE
the end point of the intersecting line segment

\return Trapezoid *
the trapezoid pointing into this->trapezoidalList
*/
/******************************************************************************/
Trapezoid * MotionPlanning_PointRobot::TrapezoidSearch( AG_State * searchS, Point2D pointS, Point2D pointE )
{
	AG_State * temp = searchS;
	while(temp)
	{
		switch(temp->type)
		{
		case AG_XNODE:
			//NOTES
			//because of the line segments general positions strategy
			//the points should not have the same x.

			if(pointS.x < temp->point.x)
				temp = temp->left;
			else
				temp = temp->right;
			break;
		case AG_YNODE:
			//NOTES
			//if p lies on the current segment (this can only happen if both segments
			//share their left end point)
			//so we only compare their slopes to classify the point

			switch( Classify_Point_To_LineSegment(pointS,temp->lineSegment) )
			{
			case CL_ABOVE:
				temp = temp->left;
				break;
			case CL_UNDER:
				temp = temp->right;
				break;
			case CL_ON:
				if( Classify_Point_To_LineSegment(pointE,temp->lineSegment) == CL_ABOVE )
					temp = temp->left;
				else
					temp = temp->right;
				break;
			}
			break;
		case AG_LEAF:
			//added by Oliver Chong - 26 Feb 2012
			//store the pointer to the current state in the search tree
			this->currentStatePtr = temp;
			return temp->trapezoid;
			break;
		}
	}
	return NULL;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This clears the AG State search tree

\param

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::DeleteTree( void )
{
	this->TraverseTree( & this->searchStructure );

	//remove the root ( which is on the stack )
	this->agStateContainer.erase( & this->searchStructure );

	std::set< AG_State * >::iterator itor = this->agStateContainer.begin();
	
	for ( ; itor != this->agStateContainer.end(); ++itor )
	{
		delete *itor;
	}//end for loop

	this->agStateContainer.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This function prints out the contents of the search tree to a console

\param searchStructure
the search tree
\param offset
the offset value to indent the text

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TraverseTree( AG_State * searchStructure )
{
	this->agStateContainer.insert( searchStructure );

	/*
	if ( searchStructure->type == AG_XNODE )
	{
	}
	else if ( searchStructure->type == AG_YNODE )
	{
	}
	else if ( searchStructure->type == AG_LEAF )
	{
	}
	*/
	
	if ( searchStructure->left )
	{
		this->TraverseTree( searchStructure->left );
	}

	if ( searchStructure->right )
	{
		this->TraverseTree( searchStructure->right );
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This function prints out the contents of the search tree to a console

\param searchStructure
the search tree
\param offset
the offset value to indent the text

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::DisplayTreeNodes( const AG_State & searchStructure, const unsigned offset ) const
{
	std::cout << std::setfill (' ') << std::setw( offset ) << "====================" << std::endl;

	if ( searchStructure.type == AG_XNODE )
	{
		std::cout << std::setfill (' ') << std::setw( offset ) << " X NODE xxxxxxxxxx : " << searchStructure.point.x << ", " << searchStructure.point.y << std::endl;
	}
	else if ( searchStructure.type == AG_YNODE )
	{
		std::cout << std::setfill (' ') << std::setw( offset ) << " Y NODE line start : " << searchStructure.lineSegment.start.x << ", " << searchStructure.lineSegment.start.y << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << " Y NODE line end : " << searchStructure.lineSegment.end.x << ", " << searchStructure.lineSegment.end.y << std::endl;
	}
	else if ( searchStructure.type == AG_LEAF )
	{
		std::cout << std::setfill (' ') << std::setw( offset ) << " LEAF NODE left point : " << searchStructure.trapezoid->leftPoint.x << ", " << searchStructure.trapezoid->leftPoint.y << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << " LEAF NODE right point : " << searchStructure.trapezoid->rightPoint.x << ", " << searchStructure.trapezoid->rightPoint.y << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << " LEAF NODE top start : " << searchStructure.trapezoid->top.start.x << ", " << searchStructure.trapezoid->top.start.y << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << " LEAF NODE top end : " << searchStructure.trapezoid->top.end.x << ", " << searchStructure.trapezoid->top.end.y << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << " LEAF NODE bottom start : " << searchStructure.trapezoid->bottom.start.x << ", " << searchStructure.trapezoid->bottom.start.y << std::endl;
		std::cout << std::setfill (' ') << std::setw( offset ) << " LEAF NODE bottom end : " << searchStructure.trapezoid->bottom.end.x << ", " << searchStructure.trapezoid->bottom.end.y << std::endl;
	}
	
	if ( searchStructure.left )
	{
		std::cout << std::setfill (' ') << std::setw( offset ) << " START LEFT " << std::endl;
		unsigned newOffset = offset + 10;
		this->DisplayTreeNodes( *searchStructure.left, newOffset );
		std::cout << std::setfill (' ') << std::setw( offset ) << " END LEFT " << std::endl;
	}

	if ( searchStructure.right )
	{
		std::cout << std::setfill (' ') << std::setw( offset ) << " START RIGHT " << std::endl;\
		unsigned newOffset = offset + 10;
		this->DisplayTreeNodes( *searchStructure.right, newOffset );
		std::cout << std::setfill (' ') << std::setw( offset ) << " END RIGHT " << std::endl;
	}

	std::cout << std::setfill (' ') << std::setw( offset ) << " RETURN " << std::endl;
	std::cout << std::setfill (' ') << std::setw( offset ) << "====================" << std::endl;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This function gets the other intersected trapezoids starting from the left-most trapezoid based on the provided line segment

\param currentTrapezoid
the pointer to the left-most intersected trapezoid
\param currLineSeg
the line segment that intersects the trapezoids

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TraverseIntersectedTrapezoids( Trapezoid * currentTrapezoid, const LineSegment2D & currLineSeg )
{
	if ( currentTrapezoid != 0 )
	{
		//store the left-most intersected trapezoid
		this->trapezoidIntersections.clear();
		this->trapezoidIntersections.push_back( currentTrapezoid );

		//After finding the first trapezoid where the left point of the segment i is, 
		//Trapezoid * currentTrapezoid = this->trapezoidIntersections[0];//the first trapezoid found before 
		currentTrapezoid = this->trapezoidIntersections.back();//the first trapezoid found before 

		this->tcount = 1; 

		//the intersecting trapezoids from left to right are all the trapezoids 
		//having a right x value less than the segment end point x-value.
		//After adding all these trapezoids we add the final one that contains the end point of segment i.
		while ( currLineSeg.end.x > currentTrapezoid->rightPoint.x ) 
		{ 
			if( Classify_Point_To_LineSegment( currentTrapezoid->rightPoint, currLineSeg ) == CL_ABOVE ) 
			{
				//If the current intersected trapezoid's rightPoint member is above the current tested line segment, 
				//then the next intersected trapezoid to be added to "trapezoidIntersections" 
				//is the current intersected trapezoid's bottom right neighbor trapezoid
				//this->trapezoidIntersections[tcount] = this->trapezoidIntersections[tcount-1]->neighbours[3];
				//this->trapezoidIntersections.push_back( this->trapezoidIntersections[tcount-1]->neighbours[3] );
				this->trapezoidIntersections.push_back( currentTrapezoid->neighbours[3] );
			}
			else 
			{
				//the top right neighbor will be added
				//trapezoidIntersections[tcount] = this->trapezoidIntersections[tcount-1]->neighbours[2]; 
				//this->trapezoidIntersections.push_back( this->trapezoidIntersections[tcount-1]->neighbours[2] );
				this->trapezoidIntersections.push_back( currentTrapezoid->neighbours[2] );
			}
				
			//currentTrapezoid = this->trapezoidIntersections[tcount]; 
			currentTrapezoid = this->trapezoidIntersections.back(); 
			this->tcount++; 

		}//end while loop

	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
The following function is based on the general position strategy.

\param

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TrapezoidalMap()
{
	//Initialization of the trapezoidal map structure
	//The first trapezoid will be the bounding rectangle that bound all of the input line-segments
	this->boundingRect = this->Calculate_BoundingRectangle();
	this->trapezoidalList.push_back(boundingRect);

	//Initialization of the search structure for the trapezoidal map
	//searchStructure : root of the directed acyclic binary search tree - (one single root for all)
	this->searchStructure.type = AG_LEAF;
	std::list<Trapezoid>::iterator temptr1;
	temptr1 = this->trapezoidalList.begin();
	this->searchStructure.trapezoid = &(*temptr1);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//continue here	

	LineSegment2D currLineSeg;

	//loop through each line segment in the list
	for ( unsigned int index = 0; index < this->segmentList.size(); ++index )
	{		
		currLineSeg = this->segmentList[index];

		//we start by finding the first trapezoid from the left. 
		//This is done by finding in which trapezoid the start point of the current line segment resides.
		Trapezoid * currentTrapezoid = this->TrapezoidSearch( 
			& this->searchStructure, 
			currLineSeg.start, 
			currLineSeg.end );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//DEBUG
		std::cout << "------------------------------------------------------------------------" << std::endl;
		//std::cout << " lineSegStart : " << currLineSeg.start.x << ", " << currLineSeg.start.y << std::endl;
		//std::cout << " lineSegEnd : " << currLineSeg.end.x << ", " << currLineSeg.end.y << std::endl;
		std::cout << " currentTrapezoid LEFT PT : " << currentTrapezoid->leftPoint.x << ", " << currentTrapezoid->leftPoint.y << std::endl;
		std::cout << " currentTrapezoid RIGHT PT : " << currentTrapezoid->rightPoint.x << ", " << currentTrapezoid->rightPoint.y << std::endl;
		std::cout << "------------------------------------------------------------------------" << std::endl;

		//this->DisplayTreeNodes( this->searchStructure, 20 );
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if ( currentTrapezoid != NULL )
		{
			//traverse and find the other intersected trapezoids starting from the left-most intersected trapezoid
			this->TraverseIntersectedTrapezoids( currentTrapezoid, currLineSeg );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			bool startPointUsed = false;
			bool endPointUsed = false;

			//on subsequent line segments
			if ( index > 0 )
			{
				//startPointUsed = this->IsPointUsedInMap( currLineSeg.start );
				//endPointUsed = this->IsPointUsedInMap( currLineSeg.end );
				startPointUsed = this->IsPointUsed( currLineSeg.start );
				endPointUsed = this->IsPointUsed( currLineSeg.end );
			}

			//save the point of the added line segment
			this->AddUsedPoint( currLineSeg.start );
			this->AddUsedPoint( currLineSeg.end );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//loop through each intersected trapezoid based on the current line segment
			//for ( unsigned index = 0; index < tcount; ++index )
			//{
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//on the first trapezoid - first general case
				if ( this->tcount == 1 )
				{
					//4 SUB-CASES 
					//1st CASE OUT OF 4 
					if ( startPointUsed == true && endPointUsed == true )//two new trapezoids
					{
						this->TrapezoidalMapHelperStartEndPtUsed( currLineSeg );
					}
					//2nd CASE OUT OF 4
					//else if( startPointUsed == true && endPointUsed == false ) //three new trapezoids
					else if( startPointUsed == true ) //three new trapezoids
					{					
						this->TrapezoidalMapHelperStartPtUsed( currLineSeg );
					}
					//3rd CASE OUT OF 4
					//else if( startPointUsed == false && endPointUsed == true ) //three new trapezoids
					else if( endPointUsed == true ) //three new trapezoids
					{
						this->TrapezoidalMapHelperEndPtUsed( currLineSeg );
					}
					//4th CASE OUT OF 4
					else //four new trapezoids
					{
						this->TrapezoidalMapHelperNoPtUsed( currLineSeg );
					}	

					//remove the old trapezoid
					this->trapezoidalList.remove( *this->trapezoidIntersections[0] );
			
				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Multiple trapezoids intersections – Second general case
				else
				{
					//STEP1
					//updating the first trapezoid it could be 2 or 3 trapezoids -> (2 trapezoids if one of the end points is already used by another segment)
					//if ( startPointUsed == true && endPointUsed == false ) //2 trapezoids
					if ( startPointUsed == true ) //2 trapezoids
					{
						this->TrapezoidalMapHelperStartPtUsedMult( currLineSeg );
					}
					else //3 trapezoids
					{
						this->TrapezoidalMapHelperOtherPtComboUsedMult( currLineSeg );
					}


					//STEP2
					//process subsequent intermediate trapezoids
					//continue with 1 to (last intersected trapezoid)-1
					for ( int t = 1; t < this->tcount-1; t++ ) 
					{
						this->TrapezoidalMapHelperMultSubseq( currLineSeg, t );
					}//end for loop


					//STEP3 - End with the last intersected trapezoid 
					int tcount2 = this->tcount-1;
					//2 global cases

					//if ( endPointUsed == true && startPointUsed == false ) 
					if ( endPointUsed == true ) 
					{ 
						this->TrapezoidalMapHelperEndPtUsedMultLast( currLineSeg, tcount2 );
					}
					else
					{						
						this->TrapezoidalMapHelperOtherPtComboUsedMultLast( currLineSeg, tcount2 );
					}

					//remove all the old (intersected) trapezoids
					//for ( int k = 0; k < tcount; k++ )
					for ( unsigned k = 0; k < this->trapezoidIntersections.size(); ++k )
					{
						this->trapezoidalList.remove( *this->trapezoidIntersections[k] );
					}//end for loop

				}


			//}//end for loop
		}


	}//end for loop

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the helper function if both the start and end points are used
to compute the trapezoids that form the free space and link them together

\param currLineSeg
the current line segment

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TrapezoidalMapHelperStartEndPtUsed( LineSegment2D & currLineSeg )
{
	Trapezoid trapValA;
	Trapezoid trapValB;

	trapValA.leftPoint = currLineSeg.start; 
	trapValA.rightPoint = currLineSeg.end; 
	trapValA.top = this->trapezoidIntersections[0]->top; 
	trapValA.bottom = currLineSeg; 
						
	trapValB.leftPoint = currLineSeg.start; 
	trapValB.rightPoint = currLineSeg.end; 
	trapValB.top = currLineSeg; 
	trapValB.bottom = this->trapezoidIntersections[0]->bottom;
	
	//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
	this->trapezoidalList.push_back( trapValA );
	Trapezoid * trapA = &( this->trapezoidalList.back() );
	this->trapezoidalList.push_back( trapValB );
	Trapezoid * trapB = &( this->trapezoidalList.back() );

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//build the searchTree
	AG_State * leftNode = new AG_State;
	leftNode->type = AG_LEAF;
	leftNode->trapezoid = trapA;
	leftNode->parents.push_back( this->currentStatePtr );

	trapA->nodePtr = leftNode;

	AG_State * rightNode = new AG_State;
	rightNode->type = AG_LEAF;
	rightNode->trapezoid = trapB;
	rightNode->parents.push_back( this->currentStatePtr );

	trapB->nodePtr = rightNode;

	//replace the current node
	this->currentStatePtr->trapezoid = 0;
	this->currentStatePtr->type = AG_YNODE;
	//this->currentStatePtr->lineSegment.start = currLineSeg.start;
	//this->currentStatePtr->lineSegment.end = currLineSeg.end;	
	this->currentStatePtr->lineSegment = currLineSeg;
	this->currentStatePtr->left = leftNode;
	this->currentStatePtr->right = rightNode;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Seven different sub-cases to link the neighbors appear:
	bool startOnTop = PointOnLineSegment( currLineSeg.start, this->trapezoidIntersections[0]->top );
	bool startOnBottom = PointOnLineSegment( currLineSeg.start, this->trapezoidIntersections[0]->bottom );
	bool endOnTop = PointOnLineSegment( currLineSeg.end, this->trapezoidIntersections[0]->top );
	bool endOnBottom = PointOnLineSegment( currLineSeg.end, this->trapezoidIntersections[0]->bottom );

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( startOnBottom && endOnTop )
	{
		trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0]; 
		if( trapA->neighbours[0] ) 
		{
			trapA->neighbours[0]->neighbours[2] = trapA;
		}

		trapB->neighbours[3] = this->trapezoidIntersections[0]->neighbours[3]; 
		if( trapB->neighbours[3] ) 
		{
			trapB->neighbours[3]->neighbours[1] = trapB;
		}

	} 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if ( startOnTop && endOnBottom )
	{
		trapA->neighbours[2] = this->trapezoidIntersections[0]->neighbours[2];
		if( trapA->neighbours[2] )
		{
			trapA->neighbours[2]->neighbours[0] = trapA;
		}

		trapB->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
		if(trapB->neighbours[1])
		{
			trapB->neighbours[1]->neighbours[3] = trapB;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if ( startOnTop )
	{
		trapA->neighbours[2] = this->trapezoidIntersections[0]->neighbours[2];
		if( trapA->neighbours[2] )
		{
			trapA->neighbours[2]->neighbours[0] = trapA;
		}

		trapB->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
		trapB->neighbours[3] = this->trapezoidIntersections[0]->neighbours[3];
		if( trapB->neighbours[1] )
		{
			trapB->neighbours[1]->neighbours[3] = trapB;
		}
		if( trapB->neighbours[3] )
		{
			trapB->neighbours[3]->neighbours[1] = trapB;
		}	
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if ( startOnBottom )
	{
		trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
		trapA->neighbours[2] = this->trapezoidIntersections[0]->neighbours[2];
		if( trapA->neighbours[0 ])
		{
			trapA->neighbours[0]->neighbours[2] = trapA;
		}
		if( trapA->neighbours[2] )
		{
			trapA->neighbours[2]->neighbours[0] = trapA;
		}

		trapB->neighbours[3] = this->trapezoidIntersections[0]->neighbours[3];
		if( trapB->neighbours[3] )
		{
			trapB->neighbours[3]->neighbours[1] = trapB;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if ( endOnTop )
	{
		trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
		if( trapA->neighbours[0] )
		{
			trapA->neighbours[0]->neighbours[2] = trapA;
		}

		trapB->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
		trapB->neighbours[3] = this->trapezoidIntersections[0]->neighbours[3];
		if( trapB->neighbours[1] )
		{
			trapB->neighbours[1]->neighbours[3] = trapB;
		}
		if( trapB->neighbours[3] )
		{
			trapB->neighbours[3]->neighbours[1] = trapB;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if ( endOnBottom )
	{
		trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
		trapA->neighbours[2] = this->trapezoidIntersections[0]->neighbours[2];
		if( trapA->neighbours[0] )
		{
			trapA->neighbours[0]->neighbours[2] = trapA;
		}
		if( trapA->neighbours[2] )
		{
			trapA->neighbours[2]->neighbours[0] = trapA;
		}

		trapB->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
		if( trapB->neighbours[1] )
		{
			trapB->neighbours[1]->neighbours[3] = trapB;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else
	{
		trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
		trapA->neighbours[2] = this->trapezoidIntersections[0]->neighbours[2];
		if ( trapA->neighbours[0] )
		{
			trapA->neighbours[0]->neighbours[2] = trapA;
		}
		if ( trapA->neighbours[2] )
		{
			trapA->neighbours[2]->neighbours[0] = trapA;
		}

		trapB->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
		trapB->neighbours[3] = this->trapezoidIntersections[0]->neighbours[3];
		if ( trapB->neighbours[1] )
		{
			trapB->neighbours[1]->neighbours[3] = trapB;
		}
		if ( trapB->neighbours[3] )
		{
			trapB->neighbours[3]->neighbours[1] = trapB;
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the helper function if the start point is used
to compute the trapezoids that form the free space and link them together

\param currLineSeg
the current line segment

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TrapezoidalMapHelperStartPtUsed( LineSegment2D & currLineSeg )
{
	Trapezoid trapValA;
	Trapezoid trapValB;
	Trapezoid trapValC;

	trapValA.leftPoint = currLineSeg.end;
	trapValA.rightPoint = this->trapezoidIntersections[0]->rightPoint;
	trapValA.top = this->trapezoidIntersections[0]->top;
	trapValA.bottom = this->trapezoidIntersections[0]->bottom;

	trapValB.leftPoint = currLineSeg.start;
	trapValB.rightPoint = currLineSeg.end;
	trapValB.top = this->trapezoidIntersections[0]->top;
	trapValB.bottom = currLineSeg;

	trapValC.leftPoint = currLineSeg.start;
	trapValC.rightPoint = currLineSeg.end;
	trapValC.top = currLineSeg;
	trapValC.bottom = this->trapezoidIntersections[0]->bottom;

	//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
	this->trapezoidalList.push_back( trapValA );
	Trapezoid * trapA = &( this->trapezoidalList.back() );
	this->trapezoidalList.push_back( trapValB );
	Trapezoid * trapB = &( this->trapezoidalList.back() );
	this->trapezoidalList.push_back( trapValC );
	Trapezoid * trapC = &( this->trapezoidalList.back() );

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//build the searchTree
	AG_State * leftNode2Lvl = new AG_State;
	AG_State * rightNode2Lvl = new AG_State;
	AG_State * leftNode3Lvl = new AG_State;
	AG_State * rightNode3Lvl = new AG_State;

	//third level	
	leftNode3Lvl->type = AG_LEAF;
	leftNode3Lvl->trapezoid = trapB;
	leftNode3Lvl->parents.push_back( leftNode2Lvl );

	trapB->nodePtr = leftNode3Lvl;
	
	rightNode3Lvl->type = AG_LEAF;
	rightNode3Lvl->trapezoid = trapC;
	rightNode3Lvl->parents.push_back( leftNode2Lvl );

	trapC->nodePtr = rightNode3Lvl;

	//second level
	leftNode2Lvl->type = AG_YNODE;
	//leftNode2Lvl->lineSegment.start = currLineSeg.start;
	//leftNode2Lvl->lineSegment.end = currLineSeg.end;	
	leftNode2Lvl->lineSegment = currLineSeg;	
	leftNode2Lvl->left = leftNode3Lvl;
	leftNode2Lvl->right = rightNode3Lvl;
	leftNode2Lvl->parents.push_back( this->currentStatePtr );

	rightNode2Lvl->type = AG_LEAF;
	rightNode2Lvl->trapezoid = trapA;
	rightNode2Lvl->parents.push_back( this->currentStatePtr );

	trapA->nodePtr = rightNode2Lvl;

	//replace the current node
	this->currentStatePtr->trapezoid = 0;
	this->currentStatePtr->type = AG_XNODE;
	this->currentStatePtr->point.x = currLineSeg.end.x;
	this->currentStatePtr->point.y = currLineSeg.end.y;
	this->currentStatePtr->left = leftNode2Lvl;
	this->currentStatePtr->right = rightNode2Lvl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Three different sub-cases to link the neighbors appear:
	bool startOnTop = PointOnLineSegment( currLineSeg.start, this->trapezoidIntersections[0]->top );//Figure09
	bool startOnBottom = PointOnLineSegment( currLineSeg.start, this->trapezoidIntersections[0]->bottom );//Figure10

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	trapA->neighbours[0] = trapB;
	trapA->neighbours[1] = trapC;
	trapA->neighbours[2] = this->trapezoidIntersections[0]->neighbours[2];
	trapA->neighbours[3] = this->trapezoidIntersections[0]->neighbours[3];
	if(trapA->neighbours[2])
	{
		trapA->neighbours[2]->neighbours[0] = trapA;
	}
	if(trapA->neighbours[3])
	{
		trapA->neighbours[3]->neighbours[1] = trapA;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( startOnTop )
	{
		trapB->neighbours[2] = trapA;

		trapC->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
		trapC->neighbours[3] = trapA;
		if(trapC->neighbours[1])
		{
			trapC->neighbours[1]->neighbours[3] = trapC;
		}
						
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if ( startOnBottom ) 
	{
		trapB->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
		trapB->neighbours[2] = trapA;
		if(trapB->neighbours[0])
		{
			trapB->neighbours[0]->neighbours[2] = trapB;
		}

		trapC->neighbours[3] = trapA;
						
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else//Figure11
	{
		trapB->neighbours[2] = trapA;
		trapB->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
		if(trapB->neighbours[0])
		{
			trapB->neighbours[0]->neighbours[2] = trapB;
		}
							
		trapC->neighbours[3] = trapA;
		trapC->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
		if(trapC->neighbours[1])
		{
			trapC->neighbours[1]->neighbours[3] = trapC;
		}						
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the helper function if the end point is used
to compute the trapezoids that form the free space and link them together

\param currLineSeg
the current line segment

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TrapezoidalMapHelperEndPtUsed( LineSegment2D & currLineSeg )
{
	Trapezoid trapValA;
	Trapezoid trapValB;
	Trapezoid trapValC;

	trapValA.leftPoint = this->trapezoidIntersections[0]->leftPoint;
	trapValA.rightPoint = currLineSeg.start;
	trapValA.top = this->trapezoidIntersections[0]->top;
	trapValA.bottom = this->trapezoidIntersections[0]->bottom;

	trapValB.leftPoint = currLineSeg.start;
	trapValB.rightPoint = currLineSeg.end;
	trapValB.top = this->trapezoidIntersections[0]->top;
	trapValB.bottom = currLineSeg;

	trapValC.leftPoint = currLineSeg.start;
	trapValC.rightPoint = currLineSeg.end;
	trapValC.top = currLineSeg;
	trapValC.bottom = this->trapezoidIntersections[0]->bottom;

	//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
	this->trapezoidalList.push_back( trapValA );
	Trapezoid * trapA = &( this->trapezoidalList.back() );
	this->trapezoidalList.push_back( trapValB );
	Trapezoid * trapB = &( this->trapezoidalList.back() );
	this->trapezoidalList.push_back( trapValC );
	Trapezoid * trapC = &( this->trapezoidalList.back() );

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//build the searchTree
	AG_State * leftNode2Lvl = new AG_State;
	AG_State * rightNode2Lvl = new AG_State;
	AG_State * leftNode3Lvl = new AG_State;
	AG_State * rightNode3Lvl = new AG_State;

	//third level	
	leftNode3Lvl->type = AG_LEAF;
	leftNode3Lvl->trapezoid = trapB;
	leftNode3Lvl->parents.push_back( rightNode2Lvl );

	trapB->nodePtr = leftNode3Lvl;
	
	rightNode3Lvl->type = AG_LEAF;
	rightNode3Lvl->trapezoid = trapC;
	rightNode3Lvl->parents.push_back( rightNode2Lvl );

	trapC->nodePtr = rightNode3Lvl;

	//second level
	rightNode2Lvl->type = AG_YNODE;
	//rightNode2Lvl->lineSegment.start = currLineSeg.start;
	//rightNode2Lvl->lineSegment.end = currLineSeg.end;	
	rightNode2Lvl->lineSegment = currLineSeg;	
	rightNode2Lvl->left = leftNode3Lvl;
	rightNode2Lvl->right = rightNode3Lvl;
	rightNode2Lvl->parents.push_back( this->currentStatePtr );

	leftNode2Lvl->type = AG_LEAF;
	leftNode2Lvl->trapezoid = trapA;
	leftNode2Lvl->parents.push_back( this->currentStatePtr );

	trapA->nodePtr = leftNode2Lvl;

	//replace the current node
	this->currentStatePtr->trapezoid = 0;
	this->currentStatePtr->type = AG_XNODE;
	this->currentStatePtr->point.x = currLineSeg.start.x;
	this->currentStatePtr->point.y = currLineSeg.start.y;
	this->currentStatePtr->left = leftNode2Lvl;
	this->currentStatePtr->right = rightNode2Lvl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Three different sub-cases to link the neighbors appear:
	bool endOnTop = PointOnLineSegment( currLineSeg.end, this->trapezoidIntersections[0]->top );//Figure12
	bool endOnBottom = PointOnLineSegment( currLineSeg.end, this->trapezoidIntersections[0]->bottom );//Figure13

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
	trapA->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
	trapA->neighbours[2] = trapB;
	trapA->neighbours[3] = trapC;
	if(trapA->neighbours[0])
	{
		trapA->neighbours[0]->neighbours[2] = trapA;
	}
	if(trapA->neighbours[1])
	{
		trapA->neighbours[1]->neighbours[3] = trapA;
	}
	*/
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( endOnTop )//Figure12
	{
		trapA->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
		trapA->neighbours[2] = trapB;
		trapA->neighbours[3] = trapC;
		if(trapA->neighbours[1])
		{
			trapA->neighbours[1]->neighbours[3] = trapA;
		}


		trapB->neighbours[0] = trapA;

		trapC->neighbours[1] = trapA;
		trapC->neighbours[3] = this->trapezoidIntersections[0]->neighbours[3];
		if(trapC->neighbours[3])
		{
			trapC->neighbours[3]->neighbours[1] = trapC;
		}	

	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if ( endOnBottom )//Figure13
	{
		trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
		trapA->neighbours[2] = trapB;
		trapA->neighbours[3] = trapC;
		if(trapA->neighbours[0])
		{
			trapA->neighbours[0]->neighbours[2] = trapA;
		}

		trapB->neighbours[0] = trapA;
		trapB->neighbours[2] = this->trapezoidIntersections[0]->neighbours[2];
		if(trapB->neighbours[2])
		{
			trapB->neighbours[2]->neighbours[0] = trapB;
		}
		
		trapC->neighbours[1] = trapA;
	
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else//Figure14
	{
		trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
		trapA->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
		trapA->neighbours[2] = trapB;
		trapA->neighbours[3] = trapC;
		if(trapA->neighbours[0])
		{
			trapA->neighbours[0]->neighbours[2] = trapA;
		}
		if(trapA->neighbours[1])
		{
			trapA->neighbours[1]->neighbours[3] = trapA;
		}

		trapB->neighbours[0] = trapA;
		trapB->neighbours[2] = this->trapezoidIntersections[0]->neighbours[2];
		if(trapB->neighbours[2])
		{
			trapB->neighbours[2]->neighbours[0] = trapB;
		}
		
		trapC->neighbours[1] = trapA;
		trapC->neighbours[3] = this->trapezoidIntersections[0]->neighbours[3];
		if(trapC->neighbours[3])
		{
			trapC->neighbours[3]->neighbours[1] = trapC;
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the helper function if none of the points are used
to compute the trapezoids that form the free space and link them together

\param currLineSeg
the current line segment

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TrapezoidalMapHelperNoPtUsed( LineSegment2D & currLineSeg )
{
	Trapezoid trapValA;
	Trapezoid trapValB;
	Trapezoid trapValC;
	Trapezoid trapValD;

	trapValA.leftPoint = this->trapezoidIntersections[0]->leftPoint;
	trapValA.rightPoint = currLineSeg.start;
	trapValA.top = this->trapezoidIntersections[0]->top;
	trapValA.bottom = this->trapezoidIntersections[0]->bottom;
	
	trapValB.leftPoint = currLineSeg.end;
	trapValB.rightPoint = this->trapezoidIntersections[0]->rightPoint;
	trapValB.top = this->trapezoidIntersections[0]->top;
	trapValB.bottom = this->trapezoidIntersections[0]->bottom;
	
	trapValC.leftPoint = currLineSeg.start;
	trapValC.rightPoint = currLineSeg.end;
	trapValC.top = this->trapezoidIntersections[0]->top;
	trapValC.bottom = currLineSeg;
	
	trapValD.leftPoint = currLineSeg.start;
	trapValD.rightPoint = currLineSeg.end;
	trapValD.top = currLineSeg;
	trapValD.bottom = this->trapezoidIntersections[0]->bottom;

	//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
	this->trapezoidalList.push_back( trapValA );
	Trapezoid * trapA = &( this->trapezoidalList.back() );
	this->trapezoidalList.push_back( trapValB );
	Trapezoid * trapB = &( this->trapezoidalList.back() );
	this->trapezoidalList.push_back( trapValC );
	Trapezoid * trapC = &( this->trapezoidalList.back() );
	this->trapezoidalList.push_back( trapValD );
	Trapezoid * trapD = &( this->trapezoidalList.back() );

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//build the searchTree
	AG_State * leftNode2Lvl = new AG_State;
	AG_State * rightNode2Lvl = new AG_State;
	AG_State * leftNode3Lvl = new AG_State;
	AG_State * rightNode3Lvl = new AG_State;
	AG_State * leftNode4Lvl = new AG_State;
	AG_State * rightNode4Lvl = new AG_State;

	//fourth level	
	leftNode4Lvl->type = AG_LEAF;
	leftNode4Lvl->trapezoid = trapC;
	leftNode4Lvl->parents.push_back( leftNode3Lvl );

	trapC->nodePtr = leftNode4Lvl;
	
	rightNode4Lvl->type = AG_LEAF;
	rightNode4Lvl->trapezoid = trapD;
	rightNode4Lvl->parents.push_back( leftNode3Lvl );

	trapD->nodePtr = rightNode4Lvl;

	//third level
	leftNode3Lvl->type = AG_YNODE;
	//leftNode3Lvl->lineSegment.start = currLineSeg.start;
	//leftNode3Lvl->lineSegment.end = currLineSeg.end;	
	leftNode3Lvl->lineSegment = currLineSeg;	
	leftNode3Lvl->left = leftNode4Lvl;
	leftNode3Lvl->right = rightNode4Lvl;
	leftNode3Lvl->parents.push_back( rightNode2Lvl );

	rightNode3Lvl->type = AG_LEAF;
	rightNode3Lvl->trapezoid = trapB;
	rightNode3Lvl->parents.push_back( rightNode2Lvl );

	trapB->nodePtr = rightNode3Lvl;

	//second level
	leftNode2Lvl->type = AG_LEAF;
	leftNode2Lvl->trapezoid = trapA;
	leftNode2Lvl->parents.push_back( this->currentStatePtr );

	trapA->nodePtr = leftNode2Lvl;

	rightNode2Lvl->type = AG_XNODE;
	rightNode2Lvl->point.x = currLineSeg.end.x;
	rightNode2Lvl->point.y = currLineSeg.end.y;
	rightNode2Lvl->left = leftNode3Lvl;
	rightNode2Lvl->right = rightNode3Lvl;
	rightNode2Lvl->parents.push_back( this->currentStatePtr );

	//replace the current node
	this->currentStatePtr->trapezoid = 0;
	this->currentStatePtr->type = AG_XNODE;
	this->currentStatePtr->point.x = currLineSeg.start.x;
	this->currentStatePtr->point.y = currLineSeg.start.y;
	this->currentStatePtr->left = leftNode2Lvl;
	this->currentStatePtr->right = rightNode2Lvl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//One single case to link the neighbors:
	trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
	trapA->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
	trapA->neighbours[2] = trapC;
	trapA->neighbours[3] = trapD;
	if(trapA->neighbours[0])
	{
		trapA->neighbours[0]->neighbours[2] = trapA;
	}
	if(trapA->neighbours[1])
	{
		trapA->neighbours[1]->neighbours[3] = trapA;
	}

	trapB->neighbours[0] = trapC;
	trapB->neighbours[1] = trapD;
	trapB->neighbours[2] = this->trapezoidIntersections[0]->neighbours[2];
	trapB->neighbours[3] = this->trapezoidIntersections[0]->neighbours[3];
	if(trapB->neighbours[2])
	{
		trapB->neighbours[2]->neighbours[0] = trapB;
	}
	if(trapB->neighbours[3])
	{
		trapB->neighbours[3]->neighbours[1] = trapB;
	}
	
	trapC->neighbours[0] = trapA;
	trapC->neighbours[2] = trapB;
	
	trapD->neighbours[1] = trapA;
	trapD->neighbours[3] = trapB;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the helper function if the start point is used ( for multiple intersected trapezoids )
to compute the trapezoids that form the free space and link them together

\param currLineSeg
the current line segment

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TrapezoidalMapHelperStartPtUsedMult( LineSegment2D & currLineSeg )
{
	Trapezoid trapValA;
	Trapezoid trapValB;

	trapValA.leftPoint = currLineSeg.start; 
	trapValA.rightPoint = this->trapezoidIntersections[0]->rightPoint; 
	trapValA.top = this->trapezoidIntersections[0]->top; 
	trapValA.bottom = currLineSeg; 

	trapValB.leftPoint = currLineSeg.start; 
	trapValB.rightPoint = this->trapezoidIntersections[0]->rightPoint; 
	trapValB.top = currLineSeg; 
	trapValB.bottom = this->trapezoidIntersections[0]->bottom;

	//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
	this->trapezoidalList.push_back( trapValA );
	Trapezoid * trapA = &( this->trapezoidalList.back() );
	this->trapezoidalList.push_back( trapValB );
	Trapezoid * trapB = &( this->trapezoidalList.back() );

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//for later use 
	//Save the previous top trapezoid pointer (trapA) from the this->trapezoidalList.
	this->previousTopPosition = trapA;
	//Save the previous bottom trapezoid pointer (trapB) from the this->trapezoidalList.
	this->previousBottomPosition = trapB;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//update the search tree
	AG_State * leftNode = new AG_State;
	AG_State * rightNode = new AG_State;

	leftNode->type = AG_LEAF;
	leftNode->trapezoid = trapA;
	leftNode->parents.push_back( this->currentStatePtr );

	trapA->nodePtr = leftNode;
						
	rightNode->type = AG_LEAF;
	rightNode->trapezoid = trapB;
	rightNode->parents.push_back( this->currentStatePtr );

	trapB->nodePtr = rightNode;

	//replace the current node
	this->currentStatePtr->trapezoid = 0;
	this->currentStatePtr->type = AG_YNODE;
	//this->currentStatePtr->lineSegment.start = currLineSeg.start;
	//this->currentStatePtr->lineSegment.end = currLineSeg.end;
	this->currentStatePtr->lineSegment = currLineSeg;
	this->currentStatePtr->left = leftNode;
	this->currentStatePtr->right = rightNode;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Two different sub-cases to link the neighbors:
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( Classify_Point_To_LineSegment( this->trapezoidIntersections[0]->rightPoint, currLineSeg ) == CL_ABOVE ) //Figure17 And Figure18 
	{ 
		trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0]; 
		if(trapA->neighbours[0]) 
		{
			trapA->neighbours[0]->neighbours[2] = trapA;
		}
		trapA->neighbours[2] = this->trapezoidIntersections[0]->neighbours[2]; 
		if(trapA->neighbours[2]) 
		{
			trapA->neighbours[2]->neighbours[0] = trapA;
		}

		trapB->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
		if(trapB->neighbours[1])
		{
			trapB->neighbours[1]->neighbours[3] = trapB;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else//Figure19 and Figure20
	{
		trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
		if(trapA->neighbours[0])
		{
			trapA->neighbours[0]->neighbours[2] = trapA;
		}

		trapB->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
		if(trapB->neighbours[1])
		{
			trapB->neighbours[1]->neighbours[3] = trapB;
		}
		trapB->neighbours[3] = this->trapezoidIntersections[0]->neighbours[3];
		if(trapB->neighbours[3])
		{
			trapB->neighbours[3]->neighbours[1] = trapB;
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the helper function for other point combinations used ( for multiple intersected trapezoids )
to compute the trapezoids that form the free space and link them together

\param currLineSeg
the current line segment

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TrapezoidalMapHelperOtherPtComboUsedMult( LineSegment2D & currLineSeg )
{
	Trapezoid trapValA;
	Trapezoid trapValB;
	Trapezoid trapValC;

	trapValA.leftPoint = this->trapezoidIntersections[0]->leftPoint;
	trapValA.rightPoint = currLineSeg.start;
	trapValA.top = this->trapezoidIntersections[0]->top;
	trapValA.bottom = this->trapezoidIntersections[0]->bottom;

	trapValB.leftPoint = currLineSeg.start;
	trapValB.rightPoint = this->trapezoidIntersections[0]->rightPoint;
	trapValB.top = this->trapezoidIntersections[0]->top;
	trapValB.bottom = currLineSeg;
						
	trapValC.leftPoint = currLineSeg.start;
	trapValC.rightPoint = this->trapezoidIntersections[0]->rightPoint;
	trapValC.top = currLineSeg;
	trapValC.bottom = this->trapezoidIntersections[0]->bottom;

	//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
	this->trapezoidalList.push_back( trapValA );
	Trapezoid * trapA = &( this->trapezoidalList.back() );
	this->trapezoidalList.push_back( trapValB );
	Trapezoid * trapB = &( this->trapezoidalList.back() );
	this->trapezoidalList.push_back( trapValC );
	Trapezoid * trapC = &( this->trapezoidalList.back() );

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//for later use 
	//Save the previous top trapezoid pointer (trapB) from the this->trapezoidalList.
	this->previousTopPosition = trapB;
	//Save the previous bottom trapezoid pointer (trapC) from the this->trapezoidalList.
	this->previousBottomPosition = trapC;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//build the searchTree
	AG_State * leftNode2Lvl = new AG_State;
	AG_State * rightNode2Lvl = new AG_State;
	AG_State * leftNode3Lvl = new AG_State;
	AG_State * rightNode3Lvl = new AG_State;

	//third level	
	leftNode3Lvl->type = AG_LEAF;
	leftNode3Lvl->trapezoid = trapB;
	leftNode3Lvl->parents.push_back( rightNode2Lvl );

	trapB->nodePtr = leftNode3Lvl;
	
	rightNode3Lvl->type = AG_LEAF;
	rightNode3Lvl->trapezoid = trapC;
	rightNode3Lvl->parents.push_back( rightNode2Lvl );

	trapC->nodePtr = rightNode3Lvl;

	//second level
	rightNode2Lvl->type = AG_YNODE;
	//rightNode2Lvl->lineSegment.start = currLineSeg.start;
	//rightNode2Lvl->lineSegment.end = currLineSeg.end;	
	rightNode2Lvl->lineSegment = currLineSeg;
	rightNode2Lvl->left = leftNode3Lvl;
	rightNode2Lvl->right = rightNode3Lvl;
	rightNode2Lvl->parents.push_back( this->currentStatePtr );

	leftNode2Lvl->type = AG_LEAF;
	leftNode2Lvl->trapezoid = trapA;
	leftNode2Lvl->parents.push_back( this->currentStatePtr );

	trapA->nodePtr = leftNode2Lvl;

	//replace the current node
	this->currentStatePtr->trapezoid = 0;
	this->currentStatePtr->type = AG_XNODE;
	this->currentStatePtr->point.x = currLineSeg.start.x;
	this->currentStatePtr->point.y = currLineSeg.start.y;
	this->currentStatePtr->left = leftNode2Lvl;
	this->currentStatePtr->right = rightNode2Lvl;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Two different sub-cases to link the neighbors:
	trapA->neighbours[0] = this->trapezoidIntersections[0]->neighbours[0];
	trapA->neighbours[1] = this->trapezoidIntersections[0]->neighbours[1];
	trapA->neighbours[2] = trapB;
	trapA->neighbours[3] = trapC;
	if(trapA->neighbours[0])
	{
		trapA->neighbours[0]->neighbours[2] = trapA;
	}
	if(trapA->neighbours[1])
	{
		trapA->neighbours[1]->neighbours[3] = trapA;
	}
						
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( Classify_Point_To_LineSegment( this->trapezoidIntersections[0]->rightPoint, currLineSeg ) == CL_ABOVE )//Figure21 and Figure22
	{
		trapB->neighbours[0] = trapA;
		if (trapB->neighbours[0])
		{
			trapB->neighbours[0]->neighbours[2] = trapB;
		}
		trapB->neighbours[2] = this->trapezoidIntersections[0]->neighbours[2];
		if (trapB->neighbours[2])
		{
			trapB->neighbours[2]->neighbours[0] = trapB;
		}

		trapC->neighbours[1] = trapA;
		if (trapC->neighbours[1])
		{
			trapC->neighbours[1]->neighbours[3] = trapC;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else//Figure23 and Figure24
	{
		trapB->neighbours[0] = trapA;
		if(trapB->neighbours[0])
		{
			trapB->neighbours[0]->neighbours[2] = trapB;
		}

		trapC->neighbours[1] = trapA;
		if(trapC->neighbours[1])
		{
			trapC->neighbours[1]->neighbours[3] = trapC;
		}
		trapC->neighbours[3] = this->trapezoidIntersections[0]->neighbours[3];
		if(trapC->neighbours[3])
		{
			trapC->neighbours[3]->neighbours[1] = trapC;
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the helper function for multiple subsequent intersected trapezoids
to compute the trapezoids that form the free space and link them together

\param currLineSeg
the current line segment
\param index
the index of the intersected trapezoid list

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TrapezoidalMapHelperMultSubseq( LineSegment2D & currLineSeg, int index )
{
	/*
	for every intermediate trapezoid there are 2 main cases:
	We test the “leftPoint” of the current intersected trapezoid to see if it's above or under the current line segment. 
	If it is above it, then our new bottom partition is linked to the previous bottom partition to form one single trapezoid. 
	Otherwise the top partition is linked to the previous top partition.
	*/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if ( Classify_Point_To_LineSegment( this->trapezoidIntersections[index]->leftPoint, currLineSeg ) == CL_ABOVE )//Figure25
	{ 
		Trapezoid trapValA;
		trapValA.leftPoint = this->trapezoidIntersections[index]->leftPoint; 
		trapValA.rightPoint = this->trapezoidIntersections[index]->rightPoint; 
		trapValA.top = this->trapezoidIntersections[index]->top; 
		trapValA.bottom = currLineSeg; 

		//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
		this->trapezoidalList.push_back( trapValA );
		Trapezoid * trapA = &( this->trapezoidalList.back() );

		//previous bottom partition (to be linked)
		Trapezoid * trapB = this->previousBottomPosition; 
		trapB->rightPoint = this->trapezoidIntersections[index]->rightPoint;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//update the search tree
		AG_State * leftNode = new AG_State;
		//AG_State * rightNode = new AG_State;
		//reuse the previous node
		AG_State * rightNode = this->previousBottomPosition->nodePtr;

		leftNode->type = AG_LEAF;
		leftNode->trapezoid = trapA;
		leftNode->parents.push_back( this->currentStatePtr );

		trapA->nodePtr = leftNode;
		
		rightNode->parents.push_back( this->currentStatePtr );
		/*
		rightNode->type = AG_LEAF;
		rightNode->trapezoid = this->previousBottomPosition;
		rightNode->parents.push_back( this->currentStatePtr );

		this->previousBottomPosition->nodePtr = rightNode;
		*/

		//replace the current node
		this->currentStatePtr = this->trapezoidIntersections[index]->nodePtr;

		this->currentStatePtr->trapezoid = 0;
		this->currentStatePtr->type = AG_YNODE;
		//this->currentStatePtr->lineSegment.start = currLineSeg.start;
		//this->currentStatePtr->lineSegment.end = currLineSeg.end;	
		this->currentStatePtr->lineSegment = currLineSeg;	
		this->currentStatePtr->left = leftNode;
		this->currentStatePtr->right = rightNode;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//One case to link the neighbors:
		trapA->neighbours[1] = this->previousTopPosition; 
		if(trapA->neighbours[1]) 
		{
			trapA->neighbours[1]->neighbours[3] = trapA;
		}
		trapA->neighbours[0] = this->trapezoidIntersections[index]->neighbours[0]; 
		if(trapA->neighbours[0]) 
		{
			trapA->neighbours[0]->neighbours[2] = trapA;
		}
		trapA->neighbours[2] = this->trapezoidIntersections[index]->neighbours[2]; 
		if(trapA->neighbours[2]) 
		{
			trapA->neighbours[2]->neighbours[0] = trapA;
		}

		trapB->neighbours[3] = this->trapezoidIntersections[index]->neighbours[3]; 
		if(trapB->neighbours[3]) 
		{
			trapB->neighbours[3]->neighbours[1] = trapB;
		}	

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//for later use
		//Save the previous top trapezoid pointer (trapA) from the this->trapezoidalList.
		this->previousTopPosition = trapA;
		//previousBottomPosition still the same (trapB).
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else//Figure26
	{
		Trapezoid * trapA = this->previousTopPosition;//previous top partition (to be linked)
		trapA->rightPoint = this->trapezoidIntersections[index]->rightPoint;

		Trapezoid trapValB;			
		trapValB.leftPoint = this->trapezoidIntersections[index]->leftPoint;
		trapValB.rightPoint = this->trapezoidIntersections[index]->rightPoint;
		trapValB.top = currLineSeg;
		trapValB.bottom = this->trapezoidIntersections[index]->bottom;
							
		//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
		this->trapezoidalList.push_back( trapValB );
		Trapezoid * trapB = &( this->trapezoidalList.back() );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//update the search tree
		//AG_State * leftNode = new AG_State;
		//reuse the previous node
		AG_State * leftNode = this->previousTopPosition->nodePtr;
		AG_State * rightNode = new AG_State;

		leftNode->parents.push_back( this->currentStatePtr );
		/*
		leftNode->type = AG_LEAF;
		leftNode->trapezoid = this->previousTopPosition;
		leftNode->parents.push_back( this->currentStatePtr );

		this->previousTopPosition->nodePtr = leftNode;
		*/
						
		rightNode->type = AG_LEAF;
		rightNode->trapezoid = trapB;
		rightNode->parents.push_back( this->currentStatePtr );

		trapB->nodePtr = rightNode;

		//replace the current node
		this->currentStatePtr = this->trapezoidIntersections[index]->nodePtr;

		this->currentStatePtr->trapezoid = 0;
		this->currentStatePtr->type = AG_YNODE;
		//this->currentStatePtr->lineSegment.start = currLineSeg.start;
		//this->currentStatePtr->lineSegment.end = currLineSeg.end;	
		this->currentStatePtr->lineSegment = currLineSeg;
		this->currentStatePtr->left = leftNode;
		this->currentStatePtr->right = rightNode;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//One case to link the neighbors:
		trapA->neighbours[2] = this->trapezoidIntersections[index]->neighbours[2];
		if(trapA->neighbours[2])
		{
			trapA->neighbours[2]->neighbours[0] = trapA;
		}
							
		trapB->neighbours[0] = this->previousBottomPosition;//previous bottom partition
		if(trapB->neighbours[0])
		{
			trapB->neighbours[0]->neighbours[2] = trapB;
		}
		trapB->neighbours[1] = this->trapezoidIntersections[index]->neighbours[1];
		if(trapB->neighbours[1])
		{
			trapB->neighbours[1]->neighbours[3] = trapB;
		}	
		trapB->neighbours[3] = this->trapezoidIntersections[index]->neighbours[3];
		if(trapB->neighbours[3])
		{
			trapB->neighbours[3]->neighbours[1] = trapB;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//for later use
		//previousTopPosition still the same (trapA).
		//Save the previous bottom trapezoid pointer (trapB) from the this->trapezoidalList.
		this->previousBottomPosition = trapB;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the helper function if the end point is used ( for multiple intersected trapezoids )
to compute the trapezoids that form the free space and link them together

\param currLineSeg
the current line segment
\pqram index
the index of the intersected trapezoid list

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TrapezoidalMapHelperEndPtUsedMultLast( LineSegment2D & currLineSeg, int index )
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//There are 2 sub-cases
	if ( Classify_Point_To_LineSegment( this->trapezoidIntersections[index]->leftPoint, currLineSeg ) == CL_ABOVE )//Figure27 
	{ 
		Trapezoid trapValA;
		trapValA.leftPoint = this->trapezoidIntersections[index]->leftPoint; 
		trapValA.rightPoint = this->trapezoidIntersections[index]->rightPoint; 
		trapValA.top = this->trapezoidIntersections[index]->top; 
		trapValA.bottom = currLineSeg;

		//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
		this->trapezoidalList.push_back( trapValA );
		Trapezoid * trapA = &( this->trapezoidalList.back() );
						
		//previous bottom partition. (to be linked) 
		Trapezoid * trapB = this->previousBottomPosition;
		trapB->rightPoint = this->trapezoidIntersections[index]->rightPoint; 	

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//update the search tree
		AG_State * leftNode = new AG_State;
		//AG_State * rightNode = new AG_State;
		//reuse the previous node
		AG_State * rightNode = this->previousBottomPosition->nodePtr;

		leftNode->type = AG_LEAF;
		leftNode->trapezoid = trapA;
		leftNode->parents.push_back( this->currentStatePtr );

		trapA->nodePtr = leftNode;
		
		rightNode->parents.push_back( this->currentStatePtr );
		/*
		rightNode->type = AG_LEAF;
		rightNode->trapezoid = this->previousBottomPosition;
		rightNode->parents.push_back( this->currentStatePtr );

		this->previousBottomPosition->nodePtr = rightNode;
		*/

		//replace the current node
		this->currentStatePtr = this->trapezoidIntersections[index]->nodePtr;

		this->currentStatePtr->trapezoid = 0;
		this->currentStatePtr->type = AG_YNODE;
		//this->currentStatePtr->lineSegment.start = currLineSeg.start;
		//this->currentStatePtr->lineSegment.end = currLineSeg.end;	
		this->currentStatePtr->lineSegment = currLineSeg;
		this->currentStatePtr->left = leftNode;
		this->currentStatePtr->right = rightNode;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//One case to link the neighbors:
		trapA->neighbours[0] = this->trapezoidIntersections[index]->neighbours[0]; 
		if(trapA->neighbours[0]) 
		{
			trapA->neighbours[0]->neighbours[2] = trapA; 
		}
		trapA->neighbours[1] = this->previousTopPosition;//previous top partition 
		if(trapA->neighbours[1]) 
		{
			trapA->neighbours[1]->neighbours[3] = trapA;
		}
		trapA->neighbours[2] = this->trapezoidIntersections[index]->neighbours[2]; 
		if(trapA->neighbours[2]) 
		{
			trapA->neighbours[2]->neighbours[0] = trapA;
		}

		trapB->neighbours[3] = this->trapezoidIntersections[index]->neighbours[3]; 
		if(trapB->neighbours[3]) 
		{
			trapB->neighbours[3]->neighbours[1] = trapB;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else//Figure28
	{
		//previous top partition. (to be linked)
		Trapezoid * trapA = this->previousTopPosition;
		trapA->rightPoint = this->trapezoidIntersections[index]->rightPoint;

		Trapezoid trapValB;
		trapValB.leftPoint = this->trapezoidIntersections[index]->leftPoint;
		trapValB.rightPoint = this->trapezoidIntersections[index]->rightPoint;
		trapValB.top = currLineSeg;
		trapValB.bottom = this->trapezoidIntersections[index]->bottom;

		//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
		this->trapezoidalList.push_back( trapValB );
		Trapezoid * trapB = &( this->trapezoidalList.back() );

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//update the search tree
		//AG_State * leftNode = new AG_State;
		//reuse the previous node
		AG_State * leftNode = this->previousTopPosition->nodePtr;
		AG_State * rightNode = new AG_State;

		leftNode->parents.push_back( this->currentStatePtr );
		/*
		leftNode->type = AG_LEAF;
		leftNode->trapezoid = this->previousTopPosition;
		leftNode->parents.push_back( this->currentStatePtr );

		this->previousTopPosition->nodePtr = leftNode;
		*/
						
		rightNode->type = AG_LEAF;
		rightNode->trapezoid = trapB;
		rightNode->parents.push_back( this->currentStatePtr );

		trapB->nodePtr = rightNode;

		//replace the current node
		this->currentStatePtr = this->trapezoidIntersections[index]->nodePtr;

		this->currentStatePtr->trapezoid = 0;
		this->currentStatePtr->type = AG_YNODE;
		//this->currentStatePtr->lineSegment.start = currLineSeg.start;
		//this->currentStatePtr->lineSegment.end = currLineSeg.end;	
		this->currentStatePtr->lineSegment = currLineSeg;
		this->currentStatePtr->left = leftNode;
		this->currentStatePtr->right = rightNode;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//One case to link the neighbors:
		trapA->neighbours[2] = this->trapezoidIntersections[index]->neighbours[2];
		if(trapA->neighbours[2])
		{
			trapA->neighbours[2]->neighbours[0] = trapA;
		}

		trapB->neighbours[0] = this->previousBottomPosition;//previous bottom partition
		trapB->neighbours[1] = this->trapezoidIntersections[index]->neighbours[1];
		if(trapB->neighbours[0])
		{
			trapB->neighbours[0]->neighbours[2] = trapB;
		}
		if(trapB->neighbours[1])
		{
			trapB->neighbours[1]->neighbours[3] = trapB;
		}
		trapB->neighbours[3] = this->trapezoidIntersections[index]->neighbours[3];
		if(trapB->neighbours[3])
		{
			trapB->neighbours[3]->neighbours[1] = trapB;
		}	
						
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the helper function for any other combination of points used ( for multiple intersected trapezoids )
to compute the trapezoids that form the free space and link them together

\param currLineSeg
the current line segment
\pqram index
the index of the intersected trapezoid list

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::TrapezoidalMapHelperOtherPtComboUsedMultLast( LineSegment2D & currLineSeg, int index )
{
	Trapezoid trapValA;
	trapValA.leftPoint = currLineSeg.end;
	trapValA.rightPoint = this->trapezoidIntersections[index]->rightPoint;
	trapValA.top = this->trapezoidIntersections[index]->top;
	trapValA.bottom = this->trapezoidIntersections[index]->bottom;

	//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
	this->trapezoidalList.push_back( trapValA );
	Trapezoid * trapA = &( this->trapezoidalList.back() );
						
	Trapezoid * trapB = 0;
	Trapezoid * trapC = 0;

	//two sub-cases
	bool above = false;
	if ( Classify_Point_To_LineSegment( this->trapezoidIntersections[index]->leftPoint, currLineSeg ) == CL_ABOVE )//Figure29
	{
		above = true;

		Trapezoid trapValB;
		trapValB.leftPoint = this->trapezoidIntersections[index]->leftPoint;
		trapValB.rightPoint = currLineSeg.end;
		trapValB.top = this->trapezoidIntersections[index]->top;
		trapValB.bottom = currLineSeg;

		//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
		this->trapezoidalList.push_back( trapValB );
		trapB = &( this->trapezoidalList.back() );

		//previous bottom partition. (to be linked)
		trapC = this->previousBottomPosition;
		trapC->rightPoint = currLineSeg.end;

	}
	else//Figure30
	{
		//previous top partition. (to be linked)
		trapB = this->previousTopPosition;
		trapB->rightPoint = currLineSeg.end;

		Trapezoid trapValC;
		trapValC.leftPoint = this->trapezoidIntersections[index]->leftPoint;
		trapValC.rightPoint = currLineSeg.end;
		trapValC.top = currLineSeg;
		trapValC.bottom = this->trapezoidIntersections[index]->bottom;

		//store the new trapezoids in the trapezoidal list and retrieve the pointer to the trapezoid from the list
		this->trapezoidalList.push_back( trapValC );
		trapC = &( this->trapezoidalList.back() );
	}

	//Two cases to link the neighbors (depends on the value of “above” variable):
	if ( above )//C is the previous partition to be linked 
	{ 
		trapA->neighbours[0] = trapB;//B 
		trapA->neighbours[1] = trapC;//C 
	} 
	else//B is the previous partition to be linked 
	{ 
		//trapC = this->trapezoidalList.end();//C 
		//trapC--; 
		trapA->neighbours[0] = trapB;//B 
		trapA->neighbours[1] = trapC;//C 
	}

	trapA->neighbours[2] = this->trapezoidIntersections[index]->neighbours[2]; 
	trapA->neighbours[3] = this->trapezoidIntersections[index]->neighbours[3]; 
	if(trapA->neighbours[0]) 
	{
		trapA->neighbours[0]->neighbours[2] = trapA; 
	}
	if(trapA->neighbours[1]) 
	{
		trapA->neighbours[1]->neighbours[3] = trapA; 
	}
	if(trapA->neighbours[2]) 
	{
		trapA->neighbours[2]->neighbours[0] = trapA; 
	}
	if(trapA->neighbours[3]) 
	{
		trapA->neighbours[3]->neighbours[1] = trapA;
	}

	if ( above )//C is the previous partition to be linked 
	{ 
		trapB->neighbours[0] = this->trapezoidIntersections[index]->neighbours[0]; 
		if(trapB->neighbours[0]) 
		{
			trapB->neighbours[0]->neighbours[2] = trapB; 
		}
		trapB->neighbours[1] = this->previousTopPosition;//previous top partition 
		if(trapB->neighbours[1]) 
		{
			trapB->neighbours[1]->neighbours[3] = trapB;
		}
		trapB->neighbours[2] = trapA; 
		if(trapB->neighbours[2]) 
		{
			trapB->neighbours[2]->neighbours[0] = trapB;
		}

		trapC->neighbours[3] = trapA; 
	}
	else//B is the previous partition to be linked 
	{ 
		trapB->neighbours[2] = trapA; 

		trapC->neighbours[0] = this->previousBottomPosition;//previous bottom partition
		if(trapC->neighbours[0])
		{
			trapC->neighbours[0]->neighbours[2] = trapC;
		}
		trapC->neighbours[3] = trapA;
		if(trapC->neighbours[3])
		{
			trapC->neighbours[3]->neighbours[1] = trapC;
		}
		trapC->neighbours[1] = this->trapezoidIntersections[index]->neighbours[1];
		if(trapC->neighbours[1])
		{
			trapC->neighbours[1]->neighbours[3] = trapC;
		}
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//build the searchTree
	AG_State * leftNode2Lvl = new AG_State;
	AG_State * rightNode2Lvl = new AG_State;
	AG_State * leftNode3Lvl = 0;
	AG_State * rightNode3Lvl = 0;

	if ( above )
	{
		//third level	
		leftNode3Lvl = new AG_State;

		leftNode3Lvl->type = AG_LEAF;
		leftNode3Lvl->trapezoid = trapB;
		leftNode3Lvl->parents.push_back( leftNode2Lvl );

		trapB->nodePtr = leftNode3Lvl;
	
		//reuse the previous node
		rightNode3Lvl = this->previousBottomPosition->nodePtr;
		rightNode3Lvl->parents.push_back( leftNode2Lvl );

		/*
		rightNode3Lvl->type = AG_LEAF;
		rightNode3Lvl->trapezoid = this->previousBottomPosition;
		rightNode3Lvl->parents.push_back( leftNode2Lvl );

		this->previousBottomPosition->nodePtr = rightNode3Lvl;
		*/
	}
	else
	{
		//third level	

		//reuse the previous node
		leftNode3Lvl = this->previousTopPosition->nodePtr;
		leftNode3Lvl->parents.push_back( leftNode2Lvl );

		/*
		leftNode3Lvl->type = AG_LEAF;
		leftNode3Lvl->trapezoid = this->previousTopPosition;
		leftNode3Lvl->parents.push_back( leftNode2Lvl );

		this->previousTopPosition->nodePtr = leftNode3Lvl;
		*/
	
		rightNode3Lvl = new AG_State;

		rightNode3Lvl->type = AG_LEAF;
		rightNode3Lvl->trapezoid = trapC;
		rightNode3Lvl->parents.push_back( leftNode2Lvl );

		trapC->nodePtr = rightNode3Lvl;
	}

	//second level
	leftNode2Lvl->type = AG_YNODE;
	//leftNode2Lvl->lineSegment.start = currLineSeg.start;
	//leftNode2Lvl->lineSegment.end = currLineSeg.end;	
	leftNode2Lvl->lineSegment = currLineSeg;
	leftNode2Lvl->left = leftNode3Lvl;
	leftNode2Lvl->right = rightNode3Lvl;
	leftNode2Lvl->parents.push_back( this->currentStatePtr );

	rightNode2Lvl->type = AG_LEAF;
	rightNode2Lvl->trapezoid = trapA;
	rightNode2Lvl->parents.push_back( this->currentStatePtr );

	trapA->nodePtr = rightNode2Lvl;

	//replace the current node
	this->currentStatePtr = this->trapezoidIntersections[index]->nodePtr;

	this->currentStatePtr->trapezoid = 0;
	this->currentStatePtr->type = AG_XNODE;
	this->currentStatePtr->point.x = currLineSeg.end.x;
	this->currentStatePtr->point.y = currLineSeg.end.y;
	this->currentStatePtr->left = leftNode2Lvl;
	this->currentStatePtr->right = rightNode2Lvl;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
All the trapezoids found within the solid area need to be removed. 
In other words, we just need the trapezoids that lie in the free empty spaces. 
The recognition of the trapezoids that reside inside a solid space from those who reside in free spaces is done 
by comparing the line segments' normal vectors of the top and bottom trapezoid's line segment saved previously.

\param

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::RemoveUnusedTrapezoids()
{
	//loop through the trapezoidal list
	std::list<Trapezoid>::iterator itor = this->trapezoidalList.begin();
	std::list<Trapezoid>::iterator end = this->trapezoidalList.end();

	while ( itor != end )
	{
		/*
		If the trapezoid's y component of the top line segment is negative, and the y component of the bottom line segment is positive, 
		then the trapezoid is removed because it resides in a solid space.
		Notice that a y component of a top or a bottom line segment in a trapezoid can't be equal to zero due to the general position strategy.
		*/
		if ( itor->top.normal.y < 0.0F && itor->bottom.normal.y > 0.0F )
		//if ( itor->top.normal.y < 0.0F || itor->bottom.normal.y > 0.0F )
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//When a solid trapezoid is found, its neighbors that are pointing to it should be updated so that they point to NULL.
			//loop through the trapezoidal list
			Trapezoid * solidTrapezoidPtr = &(*itor);

			if ( solidTrapezoidPtr->neighbours[0] )
				solidTrapezoidPtr->neighbours[0]->neighbours[2] = NULL;
			if ( solidTrapezoidPtr->neighbours[1] )
				solidTrapezoidPtr->neighbours[1]->neighbours[3] = NULL;
			if ( solidTrapezoidPtr->neighbours[2] )
				solidTrapezoidPtr->neighbours[2]->neighbours[0] = NULL;
			if ( solidTrapezoidPtr->neighbours[3] )
				solidTrapezoidPtr->neighbours[3]->neighbours[1] = NULL;

			/*
			std::list<Trapezoid>::iterator itor2 = this->trapezoidalList.begin();
			std::list<Trapezoid>::iterator end2 = this->trapezoidalList.end();
			while ( itor2 != end2 )
			{
				if ( itor2->neighbours[0] == solidTrapezoidPtr )
				{
					itor2->neighbours[0] = NULL;
				}
				if ( itor2->neighbours[1] == solidTrapezoidPtr )
				{
					itor2->neighbours[1] = NULL;
				}
				if ( itor2->neighbours[2] == solidTrapezoidPtr )
				{
					itor2->neighbours[2] = NULL;
				}
				if ( itor2->neighbours[3] == solidTrapezoidPtr )
				{
					itor2->neighbours[3] = NULL;
				}

				++itor2;
			}//end while loop
			*/

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//In the search tree the trapezoid data member should be set to NULL.
			solidTrapezoidPtr->nodePtr->trapezoid = NULL;

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//It should be removed from the “trapezoidList” and added to “unusedTrapezoidalList“.
			this->unusedTrapezoidalList.push_back( * solidTrapezoidPtr );
			//this->trapezoidalList.remove( * solidTrapezoidPtr );

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
	
		++itor;

	}//end while loop

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//loop through the trapezoidal list
	std::list<Trapezoid>::iterator itorUnused = this->unusedTrapezoidalList.begin();
	std::list<Trapezoid>::iterator endUnused = this->unusedTrapezoidalList.end();

	while ( itorUnused != endUnused )
	{
		Trapezoid * solidTrapezoidPtr = &(*itorUnused);

		//delete the unused trapezoids from the trapezoid list
		this->trapezoidalList.remove( * solidTrapezoidPtr );

		++itorUnused;
	}//end while loop	

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Before calling this function all of our created trapezoids have their top and bottom line segment's edges relative to the initial line segment's edges. 
This function cuts these segments so that they fit the exact size of the trapezoid along the x-axis.

\param

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::AdjustRemainingTrapezoids()
{
	//Adjust the end points of all of the trapezoid's top-bottom line segments.
	std::list<Trapezoid>::iterator tr;
	for(tr = this->trapezoidalList.begin(); tr != this->trapezoidalList.end(); tr++)
	{
		float starty,endy,topslope;
		//set the end-points of the top segment
		topslope = (tr->top.end.y - tr->top.start.y)/(tr->top.end.x - tr->top.start.x);//different x(s)
		starty = topslope*(tr->leftPoint.x - tr->top.start.x) + tr->top.start.y;
		endy = topslope*(tr->rightPoint.x - tr->top.start.x) + tr->top.start.y;

		tr->top.start.x = tr->leftPoint.x;
		tr->top.start.y = starty;
		tr->top.end.x = tr->rightPoint.x;
		tr->top.end.y = endy;

        //set the end-points of the bottom segment
		topslope = (tr->bottom.end.y - tr->bottom.start.y)/(tr->bottom.end.x - tr->bottom.start.x);//different x(s)
		starty = topslope*(tr->leftPoint.x - tr->bottom.start.x) + tr->bottom.start.y;
		endy = topslope*(tr->rightPoint.x - tr->bottom.start.x) + tr->bottom.start.y;

		tr->bottom.start.x = tr->leftPoint.x;
		tr->bottom.start.y = starty;
		tr->bottom.end.x = tr->rightPoint.x;
		tr->bottom.end.y = endy;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This is the main function that generates the path

\param

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::PathBuilding()
{
	this->path = new Path;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//get “startTrapezoid“ which is the left most trapezoid

	std::list<Trapezoid>::iterator itor = this->trapezoidalList.begin();
	std::list<Trapezoid>::iterator end = this->trapezoidalList.end();
	//loop through the list of trapezoids
	while ( itor != end )
	{
		//if the left point of the current trapezoid in the list has the same left point as the bounding rectangle
		//it is the left-most trapezoid
		if ( itor->leftPoint == this->boundingRect.leftPoint )
		{
			//invoke function that builds the states and edges of the graph
			this->StatesBuild( &( *itor ), -1 );
			break;
		}

		++itor;
	}//end while loop
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Initialize Floyd’s algorithm

	//Create the weights (cost) matrix as input to Floyd’s algorithm
	//The cost between two states is the distance between their positions
	this->path->GenerateMatrix();	

	//Call Floyd’s shortest path algorithm
	this->path->FloydAlgorithm();		
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Gets the state index of the state

\param state
the state in the path

\return int
the state index
*/
/******************************************************************************/
const int MotionPlanning_PointRobot::GetStateIndex( const State & state ) const
{
	int stateIndex = -1;

	//loop through the states in the path
	for ( unsigned index = 0; index < this->path->states.size(); ++index )
	{
		State currState = this->path->states.at( index );
		//validate if the state is already existing in the list
		//if ( currState.worldPositionX == state.worldPositionX && currState.worldPositionY == state.worldPositionY )
		if ( FloatValueSame( currState.worldPositionX, state.worldPositionX ) && FloatValueSame( currState.worldPositionY, state.worldPositionY ) )
		{
			stateIndex = index;
			break;
		}
	}

	return stateIndex;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Link the next and previous states by adding edges

\param nextStateIndex
The first argument is the state index of the middle point in the trapezoid that we are going to test
\param previousStateIndex
the second argument is the number of the previous state added in a previous call to “StatesBuild” function so that we can link both states together
The state number passed by the second argument belongs to the state built between both the current and the previous trapezoids.

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::LinkNextAndPrevState( const int nextStateIndex, const int previousStateIndex )
{
	//link next->stateIndex to previousState states by adding edges
	Edge edgeNext;
	edgeNext.from = nextStateIndex;
	edgeNext.to = previousStateIndex;
	//add the edge
	this->path->states.at( nextStateIndex ).edges.push_back( edgeNext );

	Edge edgePrev;
	edgePrev.from = previousStateIndex;
	edgePrev.to = nextStateIndex;
	//add the edge
	this->path->states.at( previousStateIndex ).edges.push_back( edgePrev );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Link the middle point of the current trapezoid with the line shared with its neighbor by creating edges

\param trapezoid
the pointer to the trapezoid
\param trapMiddlePtIndex
the index of the middle point of the trapezoid
\param neighborIndex
the index of the trapezoids neighbor
\param indexRelativeToNeighbor
the index of the trapezoid relative to its neighbor

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::LinkNeighbor( Trapezoid * trapezoid, const int trapMiddlePtIndex, const int neighborIndex, const int indexRelativeToNeighbor )
{
	//if the neighbor is not null
	if ( trapezoid->neighbours[ neighborIndex ] )
	{

		//if the neighbor is not yet visited
		if ( !trapezoid->neighbourUsed[ neighborIndex ] )
		{
			trapezoid->neighbourUsed[ neighborIndex ] = true;
			trapezoid->neighbours[ neighborIndex ]->isVisited = true;
		
			trapezoid->neighbours[ neighborIndex ]->neighbourUsed[ indexRelativeToNeighbor ] = true;
			trapezoid->neighbours[ neighborIndex ]->neighbours[ indexRelativeToNeighbor ]->isVisited = true;

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			Edge edgeMid;
			Edge edgeBet;

			//in between state (state between 2 trapezoids)			
			State between;
			if ( neighborIndex == 0 )
			{
				between.worldPositionX = trapezoid->top.start.x;
				between.worldPositionY = ( trapezoid->top.start.y + trapezoid->leftPoint.y ) / 2;
			}
			else if ( neighborIndex == 2 )
			{
				between.worldPositionX = trapezoid->top.end.x;
				between.worldPositionY = ( trapezoid->top.end.y + trapezoid->rightPoint.y ) / 2;
			}
			else if ( neighborIndex == 1 )
			{
				between.worldPositionX = trapezoid->bottom.start.x;
				between.worldPositionY = ( trapezoid->bottom.start.y + trapezoid->leftPoint.y ) / 2;
			}
			else if ( neighborIndex == 3 )
			{
				between.worldPositionX = trapezoid->bottom.end.x;
				between.worldPositionY = ( trapezoid->bottom.end.y + trapezoid->rightPoint.y ) / 2;
			}

			//get the state index of the state
			int stateIndex = this->GetStateIndex( between );
			//if the state is not yet in the path
			if  ( stateIndex == -1 )
			{
				//add the between state to the path
				this->path->states.push_back( between );
				stateIndex = this->path->states.size() - 1;

				this->currentStateIndex++;
			}	

			//link between and middle states by adding edges
			edgeMid.from = trapMiddlePtIndex;
			edgeBet.to = trapMiddlePtIndex;
			edgeMid.to = stateIndex;
			edgeBet.from = stateIndex;	

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			//get the reference to the between state
			State & betweenPt = this->path->states.at( stateIndex );
			//get the reference to the middle state
			State & trapMiddlePt = this->path->states.at( trapMiddlePtIndex );			

			trapMiddlePt.edges.push_back( edgeMid );
			betweenPt.edges.push_back( edgeBet );	
			
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//may need to add a condition for this line to execute
			//recursive function
			this->StatesBuild( trapezoid->neighbours[ neighborIndex ], this->currentStateIndex );
		}

	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
to be used inside PathBuilding() fct - It is a recursive function that builds the states and edges of the graph

\param next
The first argument is a pointer to a trapezoid that we are going to test
\param previousState
the second argument is the number of the previous state added in a previous call to “StatesBuild” function so that we can link both states together
The state number passed by the second argument belongs to the state built between both the current and the previous trapezoids.

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::StatesBuild( Trapezoid * next, int previousState )
{
	//Base case
	//If all the neighbors of next are already used
	if ( ( next->neighbourUsed[0] == true || next->neighbours[0] == NULL )
		&& ( next->neighbourUsed[1] == true || next->neighbours[1] == NULL ) 
		&& ( next->neighbourUsed[2] == true || next->neighbours[2] == NULL )
		&& ( next->neighbourUsed[3] == true || next->neighbours[3] == NULL ) )
	{
		if ( next->stateIndex != -1 )
		{
			//link next->stateIndex to previousState states by adding edges
			this->LinkNextAndPrevState( next->stateIndex, previousState );

			return;
		}
	}	

	//Middle state (the middle of the trapezoid)
	State middle;
	middle.worldPositionX = ( next->top.start.x + next->top.end.x +
		next->bottom.start.x + next->bottom.end.x ) / 4;
	middle.worldPositionY = ( next->top.start.y + next->top.end.y +
		next->bottom.start.y + next->bottom.end.y ) / 4;

	//get the state index of the state
	int stateIndex = this->GetStateIndex( middle );
	//if the state is not yet in the path
	if  ( stateIndex == -1 )
	{
		this->currentStateIndex++;
		//store the index in the trapezoid
		next->stateIndex = this->currentStateIndex;

		//add the new state to the path and get its index
		this->path->states.push_back( middle );
		stateIndex = this->path->states.size() - 1;

		//get the pointer to the middle point from the state list
		//State * middlePtr = &( this->path->states.back() );
	}		
	
	//link the neighbors
	this->LinkNeighbor( next, stateIndex, 0, 2 );	
	this->LinkNeighbor( next, stateIndex, 1, 3 );	
	this->LinkNeighbor( next, stateIndex, 2, 0 );	
	this->LinkNeighbor( next, stateIndex, 3, 1 );	
	
	if ( previousState != -1 ) //in first state
	{
		//link next->stateIndex to previousState states by adding edges
		this->LinkNextAndPrevState( next->stateIndex, previousState );
	}

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This calculates the bounding rectangle of the trapezoid

\param

\return Trapezoid
the trapezoid
*/
/******************************************************************************/
Trapezoid MotionPlanning_PointRobot::Calculate_BoundingRectangle()
{
	Trapezoid res;
	float minX=MAX_DISTANCE,maxX=0.0f,minY=MAX_DISTANCE,maxY=0.0f;

	unsigned int sizeLS = segmentList.size();
	for(unsigned int i = 0; i < sizeLS; i++)
	{
		if(segmentList[i].start.x < minX)
			minX = segmentList[i].start.x;
		if(segmentList[i].start.x > maxX)
			maxX = segmentList[i].start.x;

		if(segmentList[i].start.y < minY)
			minY = segmentList[i].start.y;
		if(segmentList[i].start.y > maxY)
			maxY = segmentList[i].start.y;

		if(segmentList[i].end.x < minX)
			minX = segmentList[i].end.x;
		if(segmentList[i].end.x > maxX)
			maxX = segmentList[i].end.x;

		if(segmentList[i].end.y < minY)
			minY = segmentList[i].end.y;
		if(segmentList[i].end.y > maxY)
			maxY = segmentList[i].end.y;
	}
	minX -= BOUNDING_RECT_MARGIN;
	maxX += BOUNDING_RECT_MARGIN;
	minY -= BOUNDING_RECT_MARGIN;
	maxY += BOUNDING_RECT_MARGIN;

	res.leftPoint.x = minX;
	res.leftPoint.y = maxY;
	res.rightPoint.x = maxX;
	res.rightPoint.y = minY;

	res.top.start.x = minX;
	res.top.start.y = minY;
	res.top.end.x = maxX;
	res.top.end.y = minY;
	res.bottom.start.x = minX;
	res.bottom.start.y = maxY;
	res.bottom.end.x = maxX;
	res.bottom.end.y = maxY;

	res.neighbours[0] = NULL;
	res.neighbours[1] = NULL;
	res.neighbours[2] = NULL;
	res.neighbours[3] = NULL;

	res.top.normal.x = 0;
	res.top.normal.y = 1;

	res.bottom.normal.x = 0;
	res.bottom.normal.y = -1;

	return res;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Generates the key based on the point values

\param point
the point to be validated if it has been used
\param pointKey
the point key to be generated
\param arrSize
the size of the point key array

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::GeneratePointKey( const Point2D point, char * pointKeyArr, const unsigned arrSize ) const
{
	char charBuffer [CHAR_BUFFER_SIZE];
	char pointKeyBuffer [KEY_SIZE];
	//std::string strPointKey;

	//convert integer to characters
	int xVal = static_cast<int>(point.x);
	_itoa_s( xVal, charBuffer, CHAR_BUFFER_SIZE, 10 );
	//store the character array in the string
	//strPointKey.append( charBuffer );
	strcpy_s( pointKeyBuffer, charBuffer );
	//strcpy_s( pointKeyArr, arrSize, charBuffer );

	//add the delimeter
	char charDelim[2] = { 'x' };
	strcat_s( pointKeyBuffer, charDelim );

	//convert integer to characters
	int yVal = static_cast<int>(point.y);
	_itoa_s( yVal, charBuffer, CHAR_BUFFER_SIZE, 10 );
	//store the character array in the string
	//strPointKey.append( charBuffer );
	strcat_s( pointKeyBuffer, charBuffer );
	//strcpy_s( pointKeyArr, arrSize, charBuffer );

	//perform a deep coopy of the array contents
	for ( unsigned index = 0; index < arrSize; ++index )
	{
		pointKeyArr[index] = pointKeyBuffer[index];
	}//end for loop

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Adds the used point to the map

\param point
the point to be validated if it has been used

\return
*/
/******************************************************************************/
void MotionPlanning_PointRobot::AddUsedPoint( const Point2D point )
{
	/*
	char * pointKey = new char[KEY_SIZE];

	//generate the point key
	this->GeneratePointKey( point, pointKey, KEY_SIZE );

	//validate if the point key is already existing in the used point map
	bool isPointUsed = this->IsPointUsedInMap( point );
	if ( isPointUsed == false )
	{
		//save the point of the added line segment
		this->usedPointsMap.insert( std::make_pair( pointKey, point ) );
	}
	*/

	//validate if the point key is already existing in the used point map
	bool isPointUsed = this->IsPointUsed( point );
	if ( isPointUsed == false )
	{
		//save the point of the added line segment
		this->usedPoints.push_back( point );
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This validates if the point has already been used

\param point
the point to be validated if it has been used

\return bool
if true, the point is used, otherwise false
*/
/******************************************************************************/
const bool MotionPlanning_PointRobot::IsPointUsed( Point2D point ) const
{
	bool isPointUsed = false;
	Point2D usedPoint;

	//loop through the vector containing used points
	for ( unsigned index = 0; index < this->usedPoints.size(); ++index )
	{
		usedPoint = this->usedPoints.at( index );

		//validate if the point is used
		if ( point == usedPoint )
		{
			isPointUsed = true;
			break;
		}
	}//end for loop

	return isPointUsed;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
This validates if the point has already been used

\param pointKey
the point key to be validated in the map if it has been used

\return bool
if true, the point is used, otherwise false
*/
/******************************************************************************/
const bool MotionPlanning_PointRobot::IsPointUsedInMap( Point2D point ) const
{
	bool isPointUsed = true;
	char * pointKey = new char[KEY_SIZE];

	//generate the point key
	this->GeneratePointKey( point, pointKey, KEY_SIZE );
	//find the key
	PointMap::const_iterator itor = this->usedPointsMap.find( pointKey );

	delete [] pointKey;

	//validate if the point key is in the map
	if ( itor == this->usedPointsMap.end() )
	{
		isPointUsed = false;
	}

	return isPointUsed;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Gets the trapezoid list

\param

\return std::list<Trapezoid> &
the reference to the trapezoid list
*/
/******************************************************************************/
const std::list<Trapezoid> & MotionPlanning_PointRobot::GetTrapezoidList( void ) const
{
	return this->trapezoidalList;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*!
Gets the unused trapezoid list

\param

\return std::list<Trapezoid> &
the reference to the unused trapezoid list
*/
/******************************************************************************/
const std::list<Trapezoid> & MotionPlanning_PointRobot::GetUnusedTrapezoidList( void ) const
{
	return this->unusedTrapezoidalList;
}