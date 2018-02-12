/******************************************************************************/
/*!
\file Grid2DBuilder.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 29/12/2011
\brief
This is the grid builder that will generate the mesh for the grid.

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#include "Grid2DBuilder.h"


namespace GraphicsFramework
{

	/******************************************************************************/
	/*!
	The constructor for the Grid2DBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	Grid2DBuilder::Grid2DBuilder( void )
		: m_xSubdivisions( 1 ),
		m_ySubdivisions( 1 ),
		m_width( 1.0F ),
		m_height( 1.0F ),
		m_xLimit( m_width / 2.0F ),
		m_xOffset( m_width / m_xSubdivisions ),	
		m_yLimit( m_height / 2.0F ),
		m_yOffset( m_height / m_ySubdivisions ),
		m_sTextureOffset( 1.0F / m_xSubdivisions ),
		m_tTextureOffset( 1.0F / m_ySubdivisions )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the Grid2DBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	Grid2DBuilder::~Grid2DBuilder( void )
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
	void Grid2DBuilder::ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values being passed
		this->m_width = ( meshParameterContainer.m_width < 0.0F ) ? 0.01F : meshParameterContainer.m_width;
		this->m_height = ( meshParameterContainer.m_height < 0.0F) ? 0.01F : meshParameterContainer.m_height;
		this->m_xSubdivisions = ( meshParameterContainer.m_xSubdivisions < 1 ) ? 1 : meshParameterContainer.m_xSubdivisions;
		this->m_ySubdivisions = ( meshParameterContainer.m_ySubdivisions < 1 ) ? 1 : meshParameterContainer.m_ySubdivisions;

		//invoke the subfunction
		this->ComputeGeometryBoundaryAndOffsetSubFunc( this->m_width, this->m_height, this->m_xSubdivisions, this->m_ySubdivisions );
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This computes the boundary and offset values used to create the geometry
	\param width
	the width of the geometry
	\param height
	the height of the geometry
	\param xSubdivisions
	the number of X subdivisions
	\param ySubdivisions
	the number of Y subdivisions
	\return
	*/
	/******************************************************************************/
	void Grid2DBuilder::ComputeGeometryBoundaryAndOffset( const GLfloat width, const GLfloat height, const GLuint xSubdivisions, const GLuint ySubdivisions )
	{
		//validate the values being passed
		this->m_width = ( width < 0.0F ) ? 0.01F : width;
		this->m_height = ( height < 0.0F ) ? 0.01F : height;
		this->m_xSubdivisions = ( xSubdivisions < 1 ) ? 1 : xSubdivisions;
		this->m_ySubdivisions = ( ySubdivisions < 1 ) ? 1 : ySubdivisions;

		//invoke the subfunction
		this->ComputeGeometryBoundaryAndOffsetSubFunc( this->m_width, this->m_height, this->m_xSubdivisions, this->m_ySubdivisions );		
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This computes the boundary and offset values used to create the geometry
	\param width
	the width of the geometry
	\param height
	the height of the geometry
	\param xSubdivisions
	the number of X subdivisions
	\param ySubdivisions
	the number of Y subdivisions
	\return
	*/
	/******************************************************************************/
	void Grid2DBuilder::ComputeGeometryBoundaryAndOffsetSubFunc( const GLfloat width, const GLfloat height, const GLuint xSubdivisions, const GLuint ySubdivisions )
	{
		this->m_xLimit = width / 2.0F;
		this->m_yLimit = height / 2.0F;
		this->m_xOffset = width / xSubdivisions;
		this->m_yOffset = height / ySubdivisions;
		this->m_sTextureOffset = 1.0F / xSubdivisions;
		this->m_tTextureOffset = 1.0F / ySubdivisions;

		//compute for the plane normal
		Math::Vector4 planeNormal = this->ComputePlaneNormal();
		this->m_normalX = planeNormal.GetFloatX();
		this->m_normalY = planeNormal.GetFloatY();
		this->m_normalZ = planeNormal.GetFloatZ();
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
	void Grid2DBuilder::LoadGeometryVertices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values being passed
		this->m_width = ( meshParameterContainer.m_width < 0.0F ) ? 0.01F : meshParameterContainer.m_width;
		this->m_height = ( meshParameterContainer.m_height < 0.0F) ? 0.01F : meshParameterContainer.m_height;
		this->m_xSubdivisions = ( meshParameterContainer.m_xSubdivisions < 1 ) ? 1 : meshParameterContainer.m_xSubdivisions;
		this->m_ySubdivisions = ( meshParameterContainer.m_ySubdivisions < 1 ) ? 1 : meshParameterContainer.m_ySubdivisions;

		//invoke the sub function
		this->LoadGeometryVerticesSubFunc( mesh, this->m_xSubdivisions, this->m_ySubdivisions, 
			meshParameterContainer.m_red, meshParameterContainer.m_green, meshParameterContainer.m_blue, meshParameterContainer.m_alpha );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the vertices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param width
	the width of the geometry
	\param height
	the height of the geometry
	\param xSubdivisions
	the number of X subdivisions
	\param ySubdivisions
	the number of Y subdivisions
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
	void Grid2DBuilder::LoadGeometryVertices( Mesh & mesh, 
			const GLfloat width , const GLfloat height, const GLuint xSubdivisions, const GLuint ySubdivisions,
			const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		//validate the values being passed
		this->m_width = ( width < 0.0F ) ? 0.01F : width;
		this->m_height = ( height < 0.0F) ? 0.01F : height;
		this->m_xSubdivisions = ( xSubdivisions < 1 ) ? 1 : xSubdivisions;
		this->m_ySubdivisions = ( ySubdivisions < 1 ) ? 1 : ySubdivisions;

		//invoke the sub function
		this->LoadGeometryVerticesSubFunc( mesh, this->m_xSubdivisions, this->m_ySubdivisions, red, green, blue, alpha );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the vertices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param xSubdivisions
	the number of X subdivisions
	\param ySubdivisions
	the number of Y subdivisions
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
	void Grid2DBuilder::LoadGeometryVerticesSubFunc( Mesh & mesh, 
			const GLuint xSubdivisions, const GLuint ySubdivisions,
			const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		GLuint index = 0;
		GLfloat xCoord = 0.0F;
		GLfloat yCoord = 0.0F;
		GLfloat sTexCoord = 1.0F;
		GLfloat tTexCoord = 1.0F;

		//compute for the number of vertices to be generated
		GLuint verticesPerRow = xSubdivisions + 1;
		GLuint verticesPerColumn = ySubdivisions + 1;
		mesh.SetNumberOfVertices( verticesPerRow * verticesPerColumn );

		//allocate the vertex array of the mesh in the heap
		mesh.InstantiateVertexArray( mesh.GetNumberOfVertices() );

		for ( GLuint xIndex = 0; xIndex < verticesPerRow; ++xIndex )
		{
			//on the first iteration, get the coordinate
			if ( xIndex == 0 )
			{
				xCoord = this->m_xLimit;
				sTexCoord = 1.0F;
			}
			//on the last iteration
			else if ( xIndex == xSubdivisions )
			{
				xCoord = -this->m_xLimit;
				sTexCoord = 0.0F;
			}
			//on subsequent iterations, apply the offset to the coordinate
			else
			{
				xCoord -= this->m_xOffset; 
				sTexCoord -= this->m_sTextureOffset;
			}

			for ( GLuint yIndex = 0; yIndex < verticesPerColumn; ++yIndex )
			{
				//on the first iteration, get the coordinate
				if ( yIndex == 0 )
				{
					yCoord = this->m_yLimit;
					tTexCoord = 1.0F;
				}
				//on the last iteration
				else if ( yIndex == ySubdivisions )
				{
					yCoord = -this->m_yLimit;
					tTexCoord = 0.0F;
				}
				//on subsequent iterations, apply the offset to the coordinate
				else
				{
					yCoord -= this->m_yOffset; 
					tTexCoord -= this->m_tTextureOffset;
				}

				//convert the x and y coordinates into an index to be used in a one-dimensional array
				index = (xIndex * verticesPerRow) + yIndex;

				//set the point coordinates
				mesh.GetVertexArray()[index].SetPointX( xCoord );
				mesh.GetVertexArray()[index].SetPointY( yCoord );
				mesh.GetVertexArray()[index].SetPointZ( 0.0F );

				//set the color values
				mesh.GetVertexArray()[index].SetColor( red, green, blue, alpha );

				//set the texture coordinates
				mesh.GetVertexArray()[index].SetTextureCoord( sTexCoord, tTexCoord );

				//set the normal values
				mesh.GetVertexArray()[index].SetNormal( this->m_normalX, this->m_normalY, this->m_normalZ );

			}//end for loop

		}//end for loop

		Vertex myVertex;
		for ( unsigned index = 0; index < mesh.GetNumberOfVertices(); ++index )
		{
			myVertex = mesh.GetVertexArray()[index];
		}

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
	void Grid2DBuilder::GenerateGeometryIndices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
	{		
		//validate the values being passed
		this->m_xSubdivisions = ( meshParameterContainer.m_xSubdivisions < 1 ) ? 1 : meshParameterContainer.m_xSubdivisions;
		this->m_ySubdivisions = ( meshParameterContainer.m_ySubdivisions < 1 ) ? 1 : meshParameterContainer.m_ySubdivisions;

		//invoke the sub function
		this->GenerateGeometryIndicesSubFunc( mesh, this->m_xSubdivisions, this->m_ySubdivisions );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the indices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param xSubdivisions
	the number of X subdivisions
	\param ySubdivisions
	the number of Y subdivisions
	\return
	*/
	/******************************************************************************/
	void Grid2DBuilder::GenerateGeometryIndices( Mesh & mesh, const GLuint xSubdivisions, const GLuint ySubdivisions )
	{		
		//validate the values being passed
		this->m_xSubdivisions = ( xSubdivisions < 1 ) ? 1 : xSubdivisions;
		this->m_ySubdivisions = ( ySubdivisions < 1 ) ? 1 : ySubdivisions;

		//invoke the sub function
		this->GenerateGeometryIndicesSubFunc( mesh, this->m_xSubdivisions, this->m_ySubdivisions );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the indices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param xSubdivisions
	the number of X subdivisions
	\param ySubdivisions
	the number of Y subdivisions
	\return
	*/
	/******************************************************************************/
	void Grid2DBuilder::GenerateGeometryIndicesSubFunc( Mesh & mesh, const GLuint xSubdivisions, const GLuint ySubdivisions )
	{		
		//compute for the number of vertices in each square column stack
		GLint verticesPerColumn = ySubdivisions + 1;
		GLuint numOfIndicesPerColStack = verticesPerColumn * 2;
		
		GLuint indexOffset = 0;
		GLushort indexElementValOffset = 0;
		GLushort indexElementVal = 0;

		//compute for the number of indices : number of vertices in each square column stack * number of slices
		mesh.SetNumberOfIndices( numOfIndicesPerColStack * xSubdivisions );

		//allocate the index array of the mesh in the heap
		mesh.InstantiateIndexArray( mesh.GetNumberOfIndices() );

		//iterate based on the number of slices
		for ( GLuint index = 0; index < xSubdivisions; ++index )
		{
			//algorithm for the index sequence per column stack
			/*
			example:
			*/
			for ( GLuint indexSub = 0; indexSub < numOfIndicesPerColStack; ++indexSub )
			{
				//for the first iteration
				if (indexSub == 0)
				{
					indexElementVal = 0;
				}
				//for every subsequent iteration
				else
				{
					//if even number
					if (indexSub % 2 == 0)
					{
						indexElementVal -= static_cast<GLushort>( ySubdivisions );
					}					
					//if odd number
					else
					{
						indexElementVal += static_cast<GLushort>( verticesPerColumn );
					}
				}

				//store the value
				mesh.GetIndexArray()[indexSub + indexOffset] = indexElementVal + indexElementValOffset;
			}//end for loop

			//set the offset values
			indexOffset += numOfIndicesPerColStack;
			indexElementValOffset += static_cast<GLushort>( verticesPerColumn );

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
	void Grid2DBuilder::DrawGeometry( const GLuint VAO ) const
	{
		// Render object
		glBindVertexArray( VAO );		
		
		//DRAW 2D GRID
		GLint offSetVal = 0;
		//compute for the number of vertices in each square column stack
		GLint verticesPerColumn = this->m_ySubdivisions + 1;
		GLuint numOfIndicesPerColStack = verticesPerColumn * 2;

		for ( GLuint index = 0; index < this->m_xSubdivisions; ++index )
		{
			//compute for the offset value
			offSetVal = index * numOfIndicesPerColStack * sizeof( GLushort );

			glDrawElements(
				GL_TRIANGLE_STRIP, 
				numOfIndicesPerColStack, 
				GL_UNSIGNED_SHORT, 
				( GLvoid* )offSetVal );
		}//end for loop
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
	void Grid2DBuilder::DrawGeometry( const GLuint VAO, const GLuint textureId ) const
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
	const Math::Vector4 Grid2DBuilder::ComputePlaneNormal( void ) const
	{
		//compute for the plane normal
		Math::Vector4 ptHor( this->m_xLimit, 0.0F, 0.0F, 1.0F );
		Math::Vector4 ptVert( 0.0F, this->m_yLimit, 0.0F, 1.0F );
		Math::Vector4 ptCtr( 0.0F, 0.0F, 0.0F, 1.0F );

		//compute for the plane normal using the cross product
		Math::Vector4 vectorU = ptHor - ptCtr;
		Math::Vector4 vectorV = ptVert - ptCtr;
		Math::Vector4 planeNormal = vectorU.Cross( vectorV );
		planeNormal.Normalize();

		return planeNormal;
	}

} // namespace GraphicsFramework