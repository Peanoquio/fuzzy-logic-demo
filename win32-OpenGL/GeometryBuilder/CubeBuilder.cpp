/******************************************************************************/
/*!
\file CubeBuilder.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 29/12/2011
\brief
This is the cube builder that will generate the mesh for the cube.

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "CubeBuilder.h"
#include "../Utility/Utility.h"


namespace GraphicsFramework
{
	/******************************************************************************/
	/*!
	The constructor for the CubeBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	CubeBuilder::CubeBuilder( void )
		: m_gridBuilder(),
		m_gridMesh(),
		m_xSubdivisions( 1 ),
		m_ySubdivisions( 1 ),
		m_width( 1.0F ),
		m_height( 1.0F ),
		m_xLimit( m_width / 2.0F ),
		m_xOffset( m_width / m_xSubdivisions ),	
		m_yLimit( m_height / 2.0F ),
		m_yOffset( m_height / m_ySubdivisions ),
		m_zLimit( m_xLimit ),
		m_zOffset( m_xOffset )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the CubeBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	CubeBuilder::~CubeBuilder( void )
	{
		this->m_gridMesh.DeleteVertexArray();
		this->m_gridMesh.DeleteIndexArray();
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
	void CubeBuilder::ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & meshParameterContainer )
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
	void CubeBuilder::ComputeGeometryBoundaryAndOffset( const GLfloat width, const GLfloat height, const GLuint xSubdivisions, const GLuint ySubdivisions )
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
	void CubeBuilder::ComputeGeometryBoundaryAndOffsetSubFunc( const GLfloat width, const GLfloat height, 
		const GLuint xSubdivisions, const GLuint ySubdivisions )
	{
		this->m_xLimit = width / 2.0F;
		this->m_yLimit = height / 2.0F;
		this->m_zLimit = this->m_xLimit;
		this->m_xOffset = width / xSubdivisions;
		this->m_yOffset = height / ySubdivisions;
		this->m_zOffset = this->m_xOffset;

		//grid builder
		this->m_gridBuilder.ComputeGeometryBoundaryAndOffset( width, height, xSubdivisions, ySubdivisions );
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
	void CubeBuilder::LoadGeometryVertices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values being passed
		this->m_width = ( meshParameterContainer.m_width < 0.0F ) ? 0.01F : meshParameterContainer.m_width;
		this->m_height = ( meshParameterContainer.m_height < 0.0F) ? 0.01F : meshParameterContainer.m_height;
		this->m_xSubdivisions = ( meshParameterContainer.m_xSubdivisions < 1 ) ? 1 : meshParameterContainer.m_xSubdivisions;
		this->m_ySubdivisions = ( meshParameterContainer.m_ySubdivisions < 1 ) ? 1 : meshParameterContainer.m_ySubdivisions;

		//invoke the sub function
		this->LoadGeometryVerticesSubFunc( mesh, this->m_width, this->m_height, this->m_xSubdivisions, this->m_ySubdivisions, 
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
	void CubeBuilder::LoadGeometryVertices( Mesh & mesh, 
			const GLfloat width , const GLfloat height, const GLuint xSubdivisions, const GLuint ySubdivisions,
			const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		//validate the values being passed
		this->m_width = ( width < 0.0F ) ? 0.01F : width;
		this->m_height = ( height < 0.0F) ? 0.01F : height;
		this->m_xSubdivisions = ( xSubdivisions < 1 ) ? 1 : xSubdivisions;
		this->m_ySubdivisions = ( ySubdivisions < 1 ) ? 1 : ySubdivisions;

		//invoke the sub function
		this->LoadGeometryVerticesSubFunc( mesh, this->m_width, this->m_height, this->m_xSubdivisions, this->m_ySubdivisions, red, green, blue, alpha );
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
	void CubeBuilder::LoadGeometryVerticesSubFunc( Mesh & mesh, 
			const GLfloat width, const GLfloat height, const GLuint xSubdivisions, const GLuint ySubdivisions, 
			const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		//generate the vertices for the grid mesh
		this->m_gridBuilder.LoadGeometryVertices( this->m_gridMesh, width, height, xSubdivisions, ySubdivisions, red, green, blue, alpha );

		GLuint sidesPerCube = 6;

		//allocate the temporary vertex array for each cube side in the heap
		Vertex * tempVertexArr = new Vertex[this->m_gridMesh.GetNumberOfVertices()];
		//allocate the vertex array for the cube in the heap
		mesh.SetNumberOfVertices( sidesPerCube * this->m_gridMesh.GetNumberOfVertices() );
		mesh.InstantiateVertexArray( mesh.GetNumberOfVertices() );

		//invoke the Matrix constructor
		Math::Mtx44 mainTransformationMtx;
		Math::Mtx44 transformationMtx;

		///////////////////////////////////////////////////////////////////////////////////////
		//cube face #1 (front)
		mainTransformationMtx.SetToIdentity();
		//create the translation matrix
		mainTransformationMtx.SetToTranslation( 0.0F, 0.0F, this->m_zLimit );		

		//invoke function to transform each vertex in the array
		this->ApplyTransformToVertices( mainTransformationMtx, this->m_gridMesh, tempVertexArr );		

		//store the transformed side vertex array in the cube vertex array
		Utility::CopyArrayBasedOnOffset( tempVertexArr, this->m_gridMesh.GetNumberOfVertices(),
			mesh.GetVertexArray(), mesh.GetNumberOfVertices(), 0 );	

		///////////////////////////////////////////////////////////////////////////////////////
		//cube face #2 (back)
		mainTransformationMtx.SetToIdentity();
		//create the rotation matrix
		mainTransformationMtx.SetToRotationDegreesY( -180.0F );

		transformationMtx.SetToIdentity();
		//create the translation matrix
		transformationMtx.SetToTranslation( 0.0F, 0.0F, -this->m_zLimit );

		//rotate then translate
		mainTransformationMtx = transformationMtx * mainTransformationMtx;
		
		//invoke function to transform each vertex in the array
		this->ApplyTransformToVertices( mainTransformationMtx, this->m_gridMesh, tempVertexArr );

		//store the transformed side vertex array in the cube vertex array
		Utility::CopyArrayBasedOnOffset( tempVertexArr, this->m_gridMesh.GetNumberOfVertices(),
			mesh.GetVertexArray(), mesh.GetNumberOfVertices(), this->m_gridMesh.GetNumberOfVertices() );	

		///////////////////////////////////////////////////////////////////////////////////////
		//cube face #3 (left)
		mainTransformationMtx.SetToIdentity();
		//create the rotation matrix
		mainTransformationMtx.SetToRotationDegreesY( -90.0F );

		transformationMtx.SetToIdentity();
		//create the translation matrix
		transformationMtx.SetToTranslation( -this->m_xLimit, 0.0F, 0.0F );

		//rotate then translate
		mainTransformationMtx = transformationMtx * mainTransformationMtx;
		
		//invoke function to transform each vertex in the array
		this->ApplyTransformToVertices( mainTransformationMtx, this->m_gridMesh, tempVertexArr );	

		//store the transformed side vertex array in the cube vertex array
		Utility::CopyArrayBasedOnOffset( tempVertexArr, this->m_gridMesh.GetNumberOfVertices(),
			mesh.GetVertexArray(), mesh.GetNumberOfVertices(), this->m_gridMesh.GetNumberOfVertices() * 2 );

		///////////////////////////////////////////////////////////////////////////////////////
		//cube face #4 (right)
		mainTransformationMtx.SetToIdentity();
		//create the rotation matrix
		mainTransformationMtx.SetToRotationDegreesY( 90.0F );

		transformationMtx.SetToIdentity();
		//create the translation matrix
		transformationMtx.SetToTranslation( this->m_xLimit, 0.0F, 0.0F );

		//rotate then translate
		mainTransformationMtx = transformationMtx * mainTransformationMtx;
		
		//invoke function to transform each vertex in the array
		this->ApplyTransformToVertices( mainTransformationMtx, this->m_gridMesh, tempVertexArr );

		//store the transformed side vertex array in the cube vertex array
		Utility::CopyArrayBasedOnOffset( tempVertexArr, this->m_gridMesh.GetNumberOfVertices(),
			mesh.GetVertexArray(), mesh.GetNumberOfVertices(), this->m_gridMesh.GetNumberOfVertices() * 3 );

		///////////////////////////////////////////////////////////////////////////////////////
		//cube face #5 (top)
		mainTransformationMtx.SetToIdentity();
		//create the rotation matrix
		mainTransformationMtx.SetToRotationDegreesX( -90.0F );

		transformationMtx.SetToIdentity();
		//create the translation matrix
		transformationMtx.SetToTranslation( 0.0F, this->m_yLimit, 0.0F );

		//rotate then translate
		mainTransformationMtx = transformationMtx * mainTransformationMtx;
		
		//invoke function to transform each vertex in the array
		this->ApplyTransformToVertices( mainTransformationMtx, this->m_gridMesh, tempVertexArr );	

		//store the transformed side vertex array in the cube vertex array
		Utility::CopyArrayBasedOnOffset( tempVertexArr, this->m_gridMesh.GetNumberOfVertices(),
			mesh.GetVertexArray(), mesh.GetNumberOfVertices(), this->m_gridMesh.GetNumberOfVertices() * 4 );

		///////////////////////////////////////////////////////////////////////////////////////
		//cube face #6 (bottom)
		mainTransformationMtx.SetToIdentity();
		//create the rotation matrix
		mainTransformationMtx.SetToRotationDegreesX( 90.0F );

		transformationMtx.SetToIdentity();
		//create the translation matrix
		transformationMtx.SetToTranslation( 0.0F, -this->m_yLimit, 0.0F );

		//rotate then translate
		mainTransformationMtx = transformationMtx * mainTransformationMtx;
		
		//invoke function to transform each vertex in the array
		this->ApplyTransformToVertices( mainTransformationMtx, this->m_gridMesh, tempVertexArr );

		//store the transformed side vertex array in the cube vertex array
		Utility::CopyArrayBasedOnOffset( tempVertexArr, this->m_gridMesh.GetNumberOfVertices(),
			mesh.GetVertexArray(), mesh.GetNumberOfVertices(), this->m_gridMesh.GetNumberOfVertices() * 5 );

		//delete from the heap
		delete [] tempVertexArr;
		tempVertexArr = 0;
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
	void CubeBuilder::GenerateGeometryIndices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
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
	void CubeBuilder::GenerateGeometryIndices( Mesh & mesh, const GLuint xSubdivisions, const GLuint ySubdivisions )
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
	void CubeBuilder::GenerateGeometryIndicesSubFunc( Mesh & mesh, const GLuint xSubdivisions, const GLuint ySubdivisions )
	{
		//generate the indices for the grid mesh
		this->m_gridBuilder.GenerateGeometryIndices( this->m_gridMesh, xSubdivisions, ySubdivisions );

		GLuint sidesPerCube = 6;

		//allocate the index array for the cube in the heap
		mesh.SetNumberOfIndices( sidesPerCube * this->m_gridMesh.GetNumberOfIndices() );
		mesh.InstantiateIndexArray( mesh.GetNumberOfIndices() );

		GLuint indexComputed = 0;
		GLuint indexOffset = 0;
		GLushort indexElementValOffset = 0;
		GLushort indexElementVal = 0;
		//generate the index arrays of the cube based on each grid index array
		for (GLuint index1 = 0; index1 < sidesPerCube; ++index1)
		{
			for ( GLuint index2 = 0; index2 < this->m_gridMesh.GetNumberOfIndices(); ++index2 )
			{
				indexComputed = index2 + indexOffset;
				indexElementVal = this->m_gridMesh.GetIndexArray()[index2] + indexElementValOffset;
				mesh.GetIndexArray()[indexComputed] = indexElementVal;
			}//end for loop

			//set the offset values
			indexOffset += this->m_gridMesh.GetNumberOfIndices();
			indexElementValOffset += static_cast<GLushort>(this->m_gridMesh.GetNumberOfVertices());
		}//end for loop
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This applies a matrix transformation on the vertices
	\param transformationMtx
	the transformation matrix
	\param sourceMesh
	the mesh that contains the geometry vertices and indices
	\param destVertexArr
	the vertex array that will contain the transformed vertices of the mesh
	\return
	*/
	/******************************************************************************/
	void CubeBuilder::ApplyTransformToVertices( const Math::Mtx44 & transformationMtx, const Mesh & sourceMesh, Vertex * destVertexArr )
	{
		for ( GLuint index = 0; index < sourceMesh.GetNumberOfVertices(); ++index )
		{
			//store the point coordinates of the grid in a vector
			Math::Vector4 pointVec(
				sourceMesh.GetVertexArray()[index].m_point.m_x,
				sourceMesh.GetVertexArray()[index].m_point.m_y,
				sourceMesh.GetVertexArray()[index].m_point.m_z,				 
				1.0F);		

			//apply the transformation to the vector
			pointVec = transformationMtx * pointVec;

			//store the translated point coordinates into the vertex array
			destVertexArr[index].m_point.m_x = pointVec.GetFloatX();
			destVertexArr[index].m_point.m_y = pointVec.GetFloatY();
			destVertexArr[index].m_point.m_z = pointVec.GetFloatZ();

			//set the color values
			destVertexArr[index].m_color.m_r = sourceMesh.GetVertexArray()[index].m_color.m_r;
			destVertexArr[index].m_color.m_g = sourceMesh.GetVertexArray()[index].m_color.m_g;
			destVertexArr[index].m_color.m_b = sourceMesh.GetVertexArray()[index].m_color.m_b;
			destVertexArr[index].m_color.m_a = sourceMesh.GetVertexArray()[index].m_color.m_a;

			//set the texture values
			destVertexArr[index].m_textureCoord.m_s = sourceMesh.GetVertexArray()[index].m_textureCoord.m_s;
			destVertexArr[index].m_textureCoord.m_t = sourceMesh.GetVertexArray()[index].m_textureCoord.m_t;

			//store the normal coordinates of the grid in a vector
			Math::Vector4 normalVec(
				sourceMesh.GetVertexArray()[index].m_normal.m_x,
				sourceMesh.GetVertexArray()[index].m_normal.m_y,
				sourceMesh.GetVertexArray()[index].m_normal.m_z,				 
				0.0F);		

			//apply the transformation to the normal
			normalVec = transformationMtx * normalVec;
			normalVec.Normalize();

			//set the normal values
			destVertexArr[index].m_normal.m_x = normalVec.GetFloatX();
			destVertexArr[index].m_normal.m_y = normalVec.GetFloatY();
			destVertexArr[index].m_normal.m_z = normalVec.GetFloatZ();

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
	void CubeBuilder::DrawGeometry( const GLuint VAO ) const
	{
		// Render object
		glBindVertexArray( VAO );		
		
		//DRAW CUBE
		GLuint sidesPerCube = 6;
		GLuint numOfXSubDivOfCube = this->m_xSubdivisions * sidesPerCube;
		GLuint offSetVal = 0;
		GLuint numOfIndicesPerColStack = this->m_gridMesh.GetNumberOfIndices() / this->m_xSubdivisions;

		//loop through every X subdivision in each side of the cube
		for (GLuint index = 0; index < numOfXSubDivOfCube; ++index)
		{
			//compute for the offset value
			offSetVal = index * numOfIndicesPerColStack * sizeof(GLushort);

			glDrawElements(
				GL_TRIANGLE_STRIP, 
				numOfIndicesPerColStack, 
				GL_UNSIGNED_SHORT, 
				(GLvoid*)offSetVal);
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
	void CubeBuilder::DrawGeometry( const GLuint VAO, const GLuint textureId ) const
	{
		// bind the texture name to the texture target
		glBindTexture( GL_TEXTURE_2D, textureId );

		//draw/render the geometry through the VAO
		this->DrawGeometry( VAO );
	}


} // namespace GraphicsFramework