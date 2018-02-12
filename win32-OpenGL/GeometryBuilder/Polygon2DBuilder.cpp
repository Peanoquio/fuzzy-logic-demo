/******************************************************************************/
/*!
\file Polygon2DBuilder.cpp
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

#include "Polygon2DBuilder.h"
#include "../Math/MyMath.h"


namespace GraphicsFramework
{
	/******************************************************************************/
	/*!
	The constructor for the PolygonBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	PolygonBuilder::PolygonBuilder( void )
		: m_slices( 3 ),
		m_radius( 0.5F ),
		m_verticalPos( 0.0F ),
		m_ctrPtVertPos( 0.0F ),
		m_hasCenterPoint( GL_TRUE ),
		m_invertPlaneNormal( GL_FALSE ),
		m_planeNormalX( 0.0F ),
		m_planeNormalY( 0.0F ),
		m_planeNormalZ( 0.0F )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the PolygonBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	PolygonBuilder::~PolygonBuilder( void )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This computes the boundary and offset values used to create the geometry
	\param meshParameterContainer
	the parameters to build the mesh
	\return
	*/
	/******************************************************************************/
	void PolygonBuilder::ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & /*meshParameterContainer*/ )
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
	void PolygonBuilder::LoadGeometryVertices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values
		this->m_radius = ( meshParameterContainer.m_radius < 0.0F ) ? 0.01F : meshParameterContainer.m_radius;
		this->m_slices = ( meshParameterContainer.m_slices < 3 ) ? 3 : meshParameterContainer.m_slices;
		this->m_verticalPos = meshParameterContainer.m_verticalPos;
		this->m_ctrPtVertPos = meshParameterContainer.m_ctrPtVertPos;
		this->m_hasCenterPoint = meshParameterContainer.m_hasCenterPoint;
		this->m_invertPlaneNormal = meshParameterContainer.m_invertPlaneNormal;

		//invoke the sub function
		this->LoadGeometryVerticesSubFunc( mesh, this->m_radius, this->m_slices, 
			this->m_verticalPos, this->m_hasCenterPoint, this->m_ctrPtVertPos, this->m_invertPlaneNormal,
			meshParameterContainer.m_red, meshParameterContainer.m_green, meshParameterContainer.m_blue, meshParameterContainer.m_alpha );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the vertices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param radius
	the radius of the geometry
	\param slices
	the number fo slices in the geometry
	\param verticalPos
	the vertical position of the vertices
	\param hasCenterPoint
	the flag to determine whether to generate a center point for the base
	\param ctrPtVertPos
	the vertical position of the central point in the fan base
	\param red
	the red value
	\param green
	the green value
	\param blue
	the blue value
	\param alpha
	the alpha value
	\return
	*/
	/******************************************************************************/
	void PolygonBuilder::LoadGeometryVertices( Mesh & mesh, 
			const GLfloat radius, const GLuint slices, const GLfloat verticalPos, 
			const GLboolean hasCenterPoint, const GLfloat ctrPtVertPos,  const GLboolean invertPlaneNormal,
			const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		//validate the values
		this->m_radius = ( radius < 0.0F ) ? 0.01F : radius;
		this->m_slices = ( slices < 3 ) ? 3 : slices;
		this->m_verticalPos = verticalPos;
		this->m_ctrPtVertPos = ctrPtVertPos;
		this->m_hasCenterPoint = hasCenterPoint;
		this->m_invertPlaneNormal = invertPlaneNormal;

		//invoke the sub function
		this->LoadGeometryVerticesSubFunc( mesh, this->m_radius, this->m_slices, 
			this->m_verticalPos, this->m_hasCenterPoint, this->m_ctrPtVertPos, this->m_invertPlaneNormal, 
			red, green, blue, alpha );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the vertices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param radius
	the radius of the geometry
	\param slices
	the number fo slices in the geometry
	\param verticalPos
	the vertical position of the vertices
	\param hasCenterPoint
	the flag to determine whether to generate a center point for the base
	\param ctrPtVertPos
	the vertical position of the central point in the fan base
	\param red
	the red value
	\param green
	the green value
	\param blue
	the blue value
	\param alpha
	the alpha value
	\return
	*/
	/******************************************************************************/
	void PolygonBuilder::LoadGeometryVerticesSubFuncLessVtx( Mesh & mesh, 
			const GLfloat radius, const GLuint slices, const GLfloat verticalPos, 
			const GLboolean hasCenterPoint, const GLfloat ctrPtVertPos,
			const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		if ( hasCenterPoint == GL_TRUE )
		{
			//there is an additional vertex: one for the point of origin 
			mesh.SetNumberOfVertices( slices + 1 );
		}
		else
		{
			mesh.SetNumberOfVertices( slices );
		}
		
		//allocate the vertex array of the mesh in the heap
		mesh.InstantiateVertexArray( mesh.GetNumberOfVertices() );

		//get the degrees per angle based on the number of slices
		GLfloat degreesPerAngle = Math::REVOLUTION_DEGREES / slices;	
		//compute for the corresponding radian value of the degree angle
		GLfloat radianVal = Math::DegreeToRadian( degreesPerAngle );
		GLfloat tempRadianVal = 0.0F;

		for ( GLuint index = 0; index < mesh.GetNumberOfVertices(); ++index )
		{
			//on the first iteration and if there is a center point
			if (index == 0 && hasCenterPoint == GL_TRUE)
			{
				//create the point of origin
				mesh.GetVertexArray()[index].SetPointX( 0.0F );
				mesh.GetVertexArray()[index].SetPointY( ctrPtVertPos );
				mesh.GetVertexArray()[index].SetPointZ( 0.0F );
			}
			else
			{
				mesh.GetVertexArray()[index].SetPointX( sin( tempRadianVal ) * radius );
				mesh.GetVertexArray()[index].SetPointY( verticalPos );
				mesh.GetVertexArray()[index].SetPointZ( cos( tempRadianVal ) * radius );

				//increment the degree of the angle
				tempRadianVal += radianVal;		
			}

			//set the color values
			mesh.GetVertexArray()[index].SetColor( red, green, blue, alpha );

		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the vertices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param radius
	the radius of the geometry
	\param slices
	the number fo slices in the geometry
	\param verticalPos
	the vertical position of the vertices
	\param hasCenterPoint
	the flag to determine whether to generate a center point for the base
	\param ctrPtVertPos
	the vertical position of the central point in the fan base
	\param invertPlaneNormal
	the flag to determine whether to invert the plane normal
	\param red
	the red value
	\param green
	the green value
	\param blue
	the blue value
	\param alpha
	the alpha value
	\return
	*/
	/******************************************************************************/
	void PolygonBuilder::LoadGeometryVerticesSubFunc( Mesh & mesh, 
			const GLfloat radius, const GLuint slices, const GLfloat verticalPos, 
			const GLboolean hasCenterPoint, const GLfloat ctrPtVertPos, const GLboolean invertPlaneNormal,
			const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		float normalX = 0.0F;
		float normalY = 0.0F;
		float normalZ = 0.0F;

		if ( hasCenterPoint == GL_TRUE )
		{
			//compute for the plane normal
			Math::Vector4 planeNormal = this->ComputePlaneNormal();
			this->m_planeNormalX = planeNormal.GetFloatX();
			this->m_planeNormalY = planeNormal.GetFloatY();
			this->m_planeNormalZ = planeNormal.GetFloatZ();

			if ( invertPlaneNormal == GL_TRUE )
			{
				this->InvertPlaneNormal();
			}

			normalX = this->m_planeNormalX;
			normalY = this->m_planeNormalY;
			normalZ = this->m_planeNormalZ;

			//there are two additional vertices: 
			//1. one for the point of origin
			//2. one to close the fan
			mesh.SetNumberOfVertices( slices + 2 );
		}
		else
		{
			//there is an additional vertex: one to close the fan
			mesh.SetNumberOfVertices( slices + 1 );
		}
		
		//allocate the vertex array of the mesh in the heap
		mesh.InstantiateVertexArray( mesh.GetNumberOfVertices() );

		//get the degrees per angle based on the number of slices
		GLfloat degreesPerAngle = Math::REVOLUTION_DEGREES / slices;	
		//compute for the corresponding radian value of the degree angle
		GLfloat radianVal = Math::DegreeToRadian( degreesPerAngle );
		GLfloat tempRadianVal = 0.0F;
		GLfloat texCoordRadius = 0.5F;

		for ( GLuint index = 0; index < mesh.GetNumberOfVertices(); ++index )
		{
			//on the first iteration and if there is a center point
			if ( index == 0 && hasCenterPoint == GL_TRUE )
			{
				//create the point of origin
				mesh.GetVertexArray()[index].SetPointX( 0.0F );
				mesh.GetVertexArray()[index].SetPointY( ctrPtVertPos );
				mesh.GetVertexArray()[index].SetPointZ( 0.0F );

				//set texture coordinate values
				mesh.GetVertexArray()[index].SetTextureCoord( texCoordRadius, texCoordRadius );				

				//set the normal
				Math::Vector4 normal;
				normal.SetFloatX( mesh.GetVertexArray()[index].GetPoint().m_x );
				normal.SetFloatY( mesh.GetVertexArray()[index].GetPoint().m_y );
				normal.SetFloatZ( mesh.GetVertexArray()[index].GetPoint().m_z );
				normal.Normalize();

				mesh.GetVertexArray()[index].SetNormal(
					normal.GetFloatX(),
					normal.GetFloatY(),
					normal.GetFloatZ()
					);	
			}
			//on the last iteration, close the polygon
			else if ( index + 1 == mesh.GetNumberOfVertices() )
			{
				GLuint closingIndex = 0;
				//if there is a center point
				if ( hasCenterPoint == GL_TRUE )
				{
					closingIndex = 1;
				}

				//close the polygon by repeating the vertex position of the starting vertex around the polygon
				Vertex closingVertex = mesh.GetVertexArray()[closingIndex];
				mesh.GetVertexArray()[index].SetPointX( closingVertex.GetPoint().m_x );
				mesh.GetVertexArray()[index].SetPointY( closingVertex.GetPoint().m_y );
				mesh.GetVertexArray()[index].SetPointZ( closingVertex.GetPoint().m_z );

				//set texture coordinate values
				GLfloat sVal = sin( tempRadianVal ) * texCoordRadius + texCoordRadius;
				GLfloat tVal = cos( tempRadianVal ) * texCoordRadius + texCoordRadius;
				mesh.GetVertexArray()[index].SetTextureCoord( sVal, tVal );	

				//compute the side normals instead
				if ( hasCenterPoint == GL_FALSE )
				{
					//set the normal
					Math::Vector4 normal;
					normal.SetFloatX( mesh.GetVertexArray()[index].GetPoint().m_x );
					normal.SetFloatY( mesh.GetVertexArray()[index].GetPoint().m_y );
					normal.SetFloatZ( mesh.GetVertexArray()[index].GetPoint().m_z );
					normal.Normalize();

					normalX = normal.GetFloatX();
					normalY = normal.GetFloatY();
					normalZ = normal.GetFloatZ();
				}

				//set the normal values
				mesh.GetVertexArray()[index].SetNormal( normalX, normalY, normalZ );
			}
			else
			{
				mesh.GetVertexArray()[index].SetPointX( sin( tempRadianVal ) * radius );
				mesh.GetVertexArray()[index].SetPointY( verticalPos );
				mesh.GetVertexArray()[index].SetPointZ( cos( tempRadianVal ) * radius );

				//set texture coordinate values
				GLfloat sVal = sin( tempRadianVal ) * texCoordRadius + texCoordRadius;
				GLfloat tVal = cos( tempRadianVal ) * texCoordRadius + texCoordRadius;
				mesh.GetVertexArray()[index].SetTextureCoord( sVal, tVal );

				//compute the side normals instead
				if ( hasCenterPoint == GL_FALSE )
				{
					//set the normal
					Math::Vector4 normal;
					normal.SetFloatX( mesh.GetVertexArray()[index].GetPoint().m_x );
					normal.SetFloatY( mesh.GetVertexArray()[index].GetPoint().m_y );
					normal.SetFloatZ( mesh.GetVertexArray()[index].GetPoint().m_z );
					normal.Normalize();

					normalX = normal.GetFloatX();
					normalY = normal.GetFloatY();
					normalZ = normal.GetFloatZ();
				}

				//set the normal values
				mesh.GetVertexArray()[index].SetNormal( normalX, normalY, normalZ );

				//increment the radian value of the angle
				tempRadianVal += radianVal;		
			}

			//set the color values
			mesh.GetVertexArray()[index].SetColor( red, green, blue, alpha );

		}//end for loop
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
	void PolygonBuilder::GenerateGeometryIndices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
	{	
		//validate the values
		this->m_slices = ( meshParameterContainer.m_slices < 3 ) ? 3 : meshParameterContainer.m_slices;
		this->m_hasCenterPoint = meshParameterContainer.m_hasCenterPoint;

		//invoke the sub function
		this->GenerateGeometryIndicesSubFunc( mesh, this->m_slices, this->m_hasCenterPoint );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the indices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param slices
	the number fo slices in the geometry
	\param hasCenterPoint
	the flag to determine whether to generate a center point for the base
	\return
	*/
	/******************************************************************************/
	void PolygonBuilder::GenerateGeometryIndices( Mesh & mesh, const GLuint slices, const GLboolean hasCenterPoint )
	{
		//validate the values
		this->m_slices = ( slices < 3 ) ? 3 : slices;
		this->m_hasCenterPoint = hasCenterPoint;

		//invoke the sub function
		this->GenerateGeometryIndicesSubFunc( mesh, this->m_slices, this->m_hasCenterPoint );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the indices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param slices
	the number fo slices in the geometry
	\param hasCenterPoint
	the flag to determine whether to generate a center point for the base
	\return
	*/
	/******************************************************************************/
	void PolygonBuilder::GenerateGeometryIndicesSubFuncLessIdx( Mesh & mesh, const GLuint slices, const GLboolean hasCenterPoint )
	{
		GLushort elementVal = 0;
		GLushort closingElementVal = 0;

		if ( hasCenterPoint == GL_TRUE )
		{
			//there are two additional indices: one for the point of origin and the other one to close the fan
			mesh.SetNumberOfIndices( slices + 2 );
			closingElementVal = 1;
		}
		else
		{
			//there are is an additional index to close the fan
			//mesh.SetNumberOfIndices( slices + 1 );
			mesh.SetNumberOfIndices( slices );
		}

		//allocate the index array of the mesh in the heap
		mesh.InstantiateIndexArray( mesh.GetNumberOfIndices() );		

		for ( GLuint index = 0; index < mesh.GetNumberOfIndices(); ++index )
		{
			//check if it is the last iteration and if the polygon has a center point
			if ( index + 1 == mesh.GetNumberOfIndices() && hasCenterPoint == GL_TRUE )
			{
				//close the fan
				mesh.GetIndexArray()[index] = closingElementVal;
			}
			else
			{
				mesh.GetIndexArray()[index] = elementVal;
				++elementVal;
			}
		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the indices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param slices
	the number fo slices in the geometry
	\param hasCenterPoint
	the flag to determine whether to generate a center point for the base
	\return
	*/
	/******************************************************************************/
	void PolygonBuilder::GenerateGeometryIndicesSubFunc( Mesh & mesh, const GLuint slices, const GLboolean hasCenterPoint )
	{
		GLushort elementVal = 0;
		GLushort closingElementVal = 0;

		if ( hasCenterPoint == GL_TRUE )
		{
			//there are two additional indices: one for the point of origin and the other one to close the fan
			mesh.SetNumberOfIndices( slices + 2 );
			closingElementVal = static_cast<GLushort>( mesh.GetNumberOfIndices() - 1 );
		}
		else
		{
			//there are is an additional index to close the fan
			mesh.SetNumberOfIndices( slices + 1 );
		}

		//allocate the index array of the mesh in the heap
		mesh.InstantiateIndexArray( mesh.GetNumberOfIndices() );		

		for ( GLuint index = 0; index < mesh.GetNumberOfIndices(); ++index )
		{
			//check if it is the last iteration and if the polygon has a center point
			if ( index + 1 == mesh.GetNumberOfIndices() && hasCenterPoint == GL_TRUE )
			{
				//close the fan
				mesh.GetIndexArray()[index] = closingElementVal;
			}
			else
			{
				mesh.GetIndexArray()[index] = elementVal;
				++elementVal;
			}
		}//end for loop
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
	void PolygonBuilder::DrawGeometry( const GLuint VAO ) const
	{
		// Render object
		glBindVertexArray( VAO );

		unsigned numberOfIndices = 0;
		if ( this->m_hasCenterPoint == GL_TRUE )
		{
			//there are two additional indices: one for the point of origin and the other one to close the fan
			numberOfIndices = this->m_slices + 2;
		}
		else
		{
			//there are is an additional index to close the fan
			numberOfIndices = this->m_slices;
		}

		//DRAW 2D POLYGON FAN
		glDrawElements(
			GL_TRIANGLE_FAN, 
			numberOfIndices, 
			GL_UNSIGNED_SHORT, 
			(GLvoid*)0);
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
	void PolygonBuilder::DrawGeometry( const GLuint VAO, const GLuint textureId ) const
	{
		// bind the texture name to the texture target
		glBindTexture( GL_TEXTURE_2D, textureId );

		//draw/render the geometry through the VAO
		this->DrawGeometry( VAO );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This computes the plane normal
	\param
	\return
	*/
	/******************************************************************************/
	const Math::Vector4 PolygonBuilder::ComputePlaneNormal( void ) const
	{
		float ctrPtVertPos = 0.0F;
		if ( this->m_hasCenterPoint == GL_TRUE )
		{
			ctrPtVertPos = this->m_ctrPtVertPos;
		}

		//compute for the plane normal
		Math::Vector4 ptCtr( 0.0F, ctrPtVertPos, 0.0F, 1.0F );
		Math::Vector4 ptOne( this->m_radius, ctrPtVertPos, 0.0F, 1.0F );
		Math::Vector4 ptTwo( 0.0F, ctrPtVertPos, this->m_radius, 1.0F );

		//compute for the plane normal using the cross product
		Math::Vector4 vectorU = ptOne - ptCtr;
		Math::Vector4 vectorV = ptTwo - ptCtr;
		//z cross x will result in a normal pointing down along the y-axis
		Math::Vector4 planeNormal = vectorU.Cross( vectorV );
		planeNormal.Normalize();

		return planeNormal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This inverts the plane normal
	\param
	\return
	*/
	/******************************************************************************/
	void PolygonBuilder::InvertPlaneNormal( void )
	{
		this->m_planeNormalX *= -1.0F; 
		this->m_planeNormalY *= -1.0F; 
		this->m_planeNormalZ *= -1.0F; 
	}

} // namespace GraphicsFramework