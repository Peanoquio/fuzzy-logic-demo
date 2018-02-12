/******************************************************************************/
/*!
\file BaseGeometryBuilder.h
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

////////////////////////////////////////////////////////////////////////////////
#ifndef BASEGEOMETRY_BUILDER_H
#define BASEGEOMETRY_BUILDER_H
////////////////////////////////////////////////////////////////////////////////

#include "../Graphics/MeshObj.h"

namespace GraphicsFramework
{
	class BaseGeometryBuilder
	{
	public:
		BaseGeometryBuilder( void );
		virtual ~BaseGeometryBuilder( void );

		virtual void DrawGeometry( const GLuint VAO ) const = 0;
		virtual void DrawGeometry( const GLuint VAO, const GLuint textureId ) const = 0;
		virtual void ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & meshParameterContainer ) = 0;
		virtual void LoadGeometryVertices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer ) = 0;
		virtual void GenerateGeometryIndices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer ) = 0;
		virtual void UpdateBehavior( float dt ) const;
	};

} //end namespace GraphicsFramework


#endif
////////////////////////////////////////////////////////////////////////////////