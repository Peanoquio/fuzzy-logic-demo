/******************************************************************************/
/*!
\file BaseGeometryBuilder.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 20/12/2011
\brief
This file will serve as the base class for the geometry builder.

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "BaseGeometryBuilder.h"


namespace GraphicsFramework
{
	/******************************************************************************/
	/*!
	The constructor for the BaseGeometryBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	BaseGeometryBuilder::BaseGeometryBuilder( void )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the BaseGeometryBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	BaseGeometryBuilder::~BaseGeometryBuilder( void )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This draws/renders the geometry
	\param VAO
	the Vertex Array Object
	\return
	*/
	/******************************************************************************/
	void BaseGeometryBuilder::DrawGeometry( const GLuint /*VAO*/ ) const
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This draws/renders the geometry
	\param VAO
	the Vertex Array Object
	\param texture Id
	the texture Id
	\return
	*/
	/******************************************************************************/
	void BaseGeometryBuilder::DrawGeometry( const GLuint /*VAO*/, const GLuint /*textureId*/ ) const
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Compute the boundary and offset values of the geometry
	\param meshParameterContainer
	the parameters to build the mesh
	\return
	*/
	/******************************************************************************/
	void BaseGeometryBuilder::ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & /*meshParameterContainer*/ )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the vertices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param meshParameterContainer
	the parameters to build the mesh
	\return
	*/
	/******************************************************************************/
	void BaseGeometryBuilder::LoadGeometryVertices( Mesh & /*mesh*/, const MeshParameterContainer & /*meshParameterContainer*/ )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the indices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param meshParameterContainer
	the parameters to build the mesh
	\return
	*/
	/******************************************************************************/
	void BaseGeometryBuilder::GenerateGeometryIndices( Mesh & /*mesh*/, const MeshParameterContainer & /*meshParameterContainer*/ )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This updates the behaviour of the geometry
	\param
	\return
	*/
	/******************************************************************************/
	void BaseGeometryBuilder::UpdateBehavior( float /*dt*/ ) const
	{
	}

} //end namespace GraphicsFramework