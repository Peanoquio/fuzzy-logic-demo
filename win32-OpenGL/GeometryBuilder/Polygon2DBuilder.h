/******************************************************************************/
/*!
\file Polygon2DBuilder.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 30/12/2011
\brief
This is the 2D polygon builder that will generate the mesh for the 2D polygon.

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef POLYGON_2D_BUILDER_H
#define POLYGON_2D_BUILDER_H
////////////////////////////////////////////////////////////////////////////////

#include "BaseGeometryBuilder.h"
#include "../Math/Vector4.h"


namespace GraphicsFramework
{
	class PolygonBuilder : public BaseGeometryBuilder
	{
	public:
		PolygonBuilder( void );
		virtual ~PolygonBuilder( void );

		virtual void DrawGeometry( const GLuint VAO ) const;
		virtual void DrawGeometry( const GLuint VAO, const GLuint textureId ) const;

		//option #1
		virtual void ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & meshParameterContainer );
		virtual void LoadGeometryVertices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer );
		virtual void GenerateGeometryIndices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer );

		//option #2
		void LoadGeometryVertices( Mesh & mesh, 
			const GLfloat radius = 0.5F, const GLuint slices = 3, const GLfloat verticalPos = 0.0F, 
			const GLboolean hasCenterPoint = GL_TRUE, const GLfloat ctrPtVertPos = 0.0F, const GLboolean invertPlaneNormal = GL_FALSE,
			const GLubyte red = 0, const GLubyte green = 0, const GLubyte blue = 0, const GLubyte alpha = 255 );
		void GenerateGeometryIndices( Mesh & mesh, const GLuint slices = 3, const GLboolean hasCenterPoint = GL_TRUE ); 

	private:
		GLuint		m_slices;
		GLfloat		m_radius;
		GLfloat		m_verticalPos;
		GLfloat		m_ctrPtVertPos;
		GLboolean	m_hasCenterPoint;
		GLboolean	m_invertPlaneNormal;
		GLfloat		m_planeNormalX;
		GLfloat		m_planeNormalY;
		GLfloat		m_planeNormalZ;

		void LoadGeometryVerticesSubFunc( Mesh & mesh, 
			const GLfloat radius = 0.5F, const GLuint slices = 3, const GLfloat verticalPos = 0.0F, 
			const GLboolean hasCenterPoint = GL_TRUE, const GLfloat ctrPtVertPos = 0.0F,  const GLboolean invertPlaneNormal = GL_FALSE,
			const GLubyte red = 0, const GLubyte green = 0, const GLubyte blue = 0, const GLubyte alpha = 255 );
		void LoadGeometryVerticesSubFuncLessVtx( Mesh & mesh, 
			const GLfloat radius = 0.5F, const GLuint slices = 3, const GLfloat verticalPos = 0.0F, 
			const GLboolean hasCenterPoint = GL_TRUE, const GLfloat ctrPtVertPos = 0.0F,
			const GLubyte red = 0, const GLubyte green = 0, const GLubyte blue = 0, const GLubyte alpha = 255 );
		
		void GenerateGeometryIndicesSubFunc( Mesh & mesh, const GLuint slices = 3, const GLboolean hasCenterPoint = GL_TRUE ); 
		void GenerateGeometryIndicesSubFuncLessIdx( Mesh & mesh, const GLuint slices = 3, const GLboolean hasCenterPoint = GL_TRUE ); 

		const Math::Vector4 ComputePlaneNormal( void ) const;
		void InvertPlaneNormal( void );
	};

} // namespace GraphicsFramework


#endif
////////////////////////////////////////////////////////////////////////////////