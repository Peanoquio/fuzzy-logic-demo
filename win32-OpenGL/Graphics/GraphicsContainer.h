/******************************************************************************/
/*!
\file GraphicsContainer.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 22/12/2011
\brief
This is the graphics container that will contain the graphics object, the mesh and the geometry builder

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef GRAPHICS_CONTAINER_H
#define GRAPHICS_CONTAINER_H
////////////////////////////////////////////////////////////////////////////////

#include "GraphicsObj.h"
#include "MeshObj.h"
#include "../GeometryBuilder/BaseGeometryBuilder.h"

namespace GraphicsFramework
{
	class GraphicsContainer
	{
	public:
		GraphicsContainer( void );
		~GraphicsContainer( void );

		GraphicsObject				GetGraphicsObj( void ) const;
		Mesh						GetMesh( void ) const;
		const BaseGeometryBuilder*	GetBaseGeometryBuilder( void ) const;

		void						SetGraphicsObj( const GraphicsObject & graphicsObj );
		void						SetMesh( const Mesh & mesh );
		void						SetBaseGeometryBuilder( const BaseGeometryBuilder* const baseGeometryBuilderPtr );

	private:
		GraphicsObject				m_graphicsObj;
		Mesh						m_mesh;
		const BaseGeometryBuilder* 	m_baseGeometryBuilderPtr;
	};

} //end namespace GraphicsFramework

#endif
////////////////////////////////////////////////////////////////////////////////