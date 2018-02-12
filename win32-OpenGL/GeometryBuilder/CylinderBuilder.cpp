/******************************************************************************/
/*!
\file CylinderBuilder.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 30/12/2011
\brief
This is the cylinder builder that will generate the mesh for the cylinder.

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "CylinderBuilder.h"
#include "Polygon2DBuilder.h"


namespace GraphicsFramework
{
	/******************************************************************************/
	/*!
	The constructor for the CylinderBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	CylinderBuilder::CylinderBuilder( void )
		: m_radius( 0.5F ),
		m_height( 1.0F ),
		m_slices( 3 ),
		m_stacks( 1 ),
		m_yLimit( m_height / 2.0F ),
		m_yOffset( m_height / m_stacks)
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the CylinderBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	CylinderBuilder::~CylinderBuilder( void )
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
	void CylinderBuilder::ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values
		this->m_height = ( meshParameterContainer.m_height < 0.0F ) ? 0.01F : meshParameterContainer.m_height;
		this->m_stacks = ( meshParameterContainer.m_stacks < 1 ) ? 1 : meshParameterContainer.m_stacks;

		//invoke the subfunction
		this->ComputeGeometryBoundaryAndOffsetSubFunc( this->m_height, this->m_stacks );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This computes the boundary and offset values used to create the geometry
	\param height
	the height of the geometry
	\param stacks
	the number of stacks in the geometry
	\return
	*/
	/******************************************************************************/
	void CylinderBuilder::ComputeGeometryBoundaryAndOffset( const GLfloat height, const GLuint stacks )
	{
		//validate the values
		this->m_height = ( height < 0.0F ) ? 0.01F : height;
		this->m_stacks = ( stacks < 1 ) ? 1 : stacks;

		//invoke the subfunction
		this->ComputeGeometryBoundaryAndOffsetSubFunc( this->m_height, this->m_stacks );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This computes the boundary and offset values used to create the geometry
	\param height
	the height of the geometry
	\param stacks
	the number of stacks in the geometry
	\return
	*/
	/******************************************************************************/
	void CylinderBuilder::ComputeGeometryBoundaryAndOffsetSubFunc( const GLfloat height, const GLuint stacks )
	{
		this->m_yLimit = height / 2.0F;
		this->m_yOffset = height / stacks;	
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
	void CylinderBuilder::LoadGeometryVertices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values being passed
		this->m_radius = ( meshParameterContainer.m_radius < 0.0F ) ? 0.01F : meshParameterContainer.m_radius;
		this->m_slices = ( meshParameterContainer.m_slices < 3 ) ? 3 : meshParameterContainer.m_slices;
		this->m_stacks = ( meshParameterContainer.m_stacks < 1 ) ? 1 : meshParameterContainer.m_stacks;

		//invoke the subfunction
		this->LoadGeometryVerticesSubFunc( mesh, this->m_radius, this->m_slices, this->m_stacks, 
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
	\param height
	the height of the geometry
	\param slices
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
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
	void CylinderBuilder::LoadGeometryVertices( Mesh & mesh, 
			const GLfloat radius, const GLuint slices, const GLuint stacks, 
			const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		//validate the values being passed
		this->m_radius = ( radius < 0.0F ) ? 0.01F : radius;
		this->m_slices = ( slices < 3 ) ? 3 : slices;
		this->m_stacks = ( stacks < 1 ) ? 1 : stacks;

		//invoke the subfunction
		this->LoadGeometryVerticesSubFunc( mesh, this->m_radius, this->m_slices, this->m_stacks, red, green, blue, alpha );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the vertices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param radius
	the radius of the geometry
	\param height
	the height of the geometry
	\param slices
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
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
	void CylinderBuilder::LoadGeometryVerticesSubFuncLessVtx( Mesh & mesh, 
			const GLfloat radius, const GLuint slices, const GLuint stacks, 
			const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		PolygonBuilder	polyFanBuilder;
		Mesh			polyFanMesh;
		PolygonBuilder	polyRingBuilder;
		Mesh			polyRingMesh;

		//allocate the vertex array in the memory heap
		//base and top fans + rings
		mesh.SetNumberOfVertices( ( ( slices + 1 ) * 2 ) + ( slices * ( stacks - 1 ) ) );
		mesh.InstantiateVertexArray( mesh.GetNumberOfVertices() );

		//generate the bottom base		
		polyFanBuilder.LoadGeometryVertices( polyFanMesh, radius, slices, -this->m_yLimit, GL_TRUE, -this->m_yLimit, red, green, blue, alpha );

		for ( GLuint index = 0; index < polyFanMesh.GetNumberOfVertices(); ++index )
		{
			mesh.GetVertexArray()[index] = polyFanMesh.GetVertexArray()[index];

			//if there is only cylinder one stack, generate its top base as well
			if ( stacks == 1 )
			{
				//apply the offset to the vertical position as well as to the array element
				polyFanMesh.GetVertexArray()[index].m_point.m_y += this->m_yOffset;
				mesh.GetVertexArray()[index + polyFanMesh.GetNumberOfVertices()] = polyFanMesh.GetVertexArray()[index];
			}
		}//end for loop


		//generate the subsequent rings of the cylinder if there is more than one stack
		if ( stacks > 1 )
		{
			//generate the ring of the cylinder starting from the bottom
			polyRingBuilder.LoadGeometryVertices( polyRingMesh, radius, slices, -this->m_yLimit, GL_FALSE, -this->m_yLimit, red, green, blue, alpha );

			//loop through each stack with the starting index offset from the initial base
			GLuint indexStackOffset = 0;

			for ( GLuint indexStack = 0; indexStack < stacks; ++indexStack )
			{	
				//on the first iteration
				if ( indexStack == 0 )
				{
					indexStackOffset = polyFanMesh.GetNumberOfVertices();
				}
				else
				{
					indexStackOffset += polyRingMesh.GetNumberOfVertices();
				}

				//on the last iteration, generate the top polygon fan to close the cylinder
				if ( indexStack + 1 == stacks )
				{
					//loop through each vertex in the polygon fan
					for ( GLuint index = 0; index < polyFanMesh.GetNumberOfVertices(); ++index )
					{
						//apply the offset to the vertical position as well as to the array element
						polyFanMesh.GetVertexArray()[index].m_point.m_y = this->m_yLimit; 
						mesh.GetVertexArray()[index + indexStackOffset] = polyFanMesh.GetVertexArray()[index];
					}//end for loop
				}
				else
				{
					//loop through each vertex in the polygon ring
					for ( GLuint index = 0; index < polyRingMesh.GetNumberOfVertices(); ++index )
					{
						//apply the offset to the vertical position as well as to the array element
						//on the first stack iteration, generate the bottom polygon ring
						polyRingMesh.GetVertexArray()[index].m_point.m_y += this->m_yOffset; 
						mesh.GetVertexArray()[index + indexStackOffset] = polyRingMesh.GetVertexArray()[index];
					}//end for loop
				}
		
			}//end for loop
		}

		//delete the vertex array from the heap
		polyFanMesh.DeleteVertexArray();
		polyRingMesh.DeleteVertexArray();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the vertices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param radius
	the radius of the geometry
	\param height
	the height of the geometry
	\param slices
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
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
	void CylinderBuilder::LoadGeometryVerticesSubFunc( Mesh & mesh, 
			const GLfloat radius, const GLuint slices, const GLuint stacks, 
			const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		PolygonBuilder	polyFanBuilder;
		Mesh			polyFanBottomMesh;
		Mesh			polyFanTopMesh;
		PolygonBuilder	polyRingBuilder;
		Mesh			polyRingMesh;

		//set the texture offsets
		this->m_sTextureOffset = 1.0F / slices;
		this->m_tTextureOffset = 1.0F / stacks;
		GLfloat sTexCoord = 0.0F;
		GLfloat tTexCoord = 0.0F;

		GLuint indexStackOffset = 0;

		//allocate the vertex array in the memory heap
		//base and top fans + rings
		mesh.SetNumberOfVertices( ( ( slices + 2 ) * 2 ) + ( ( slices + 1 ) * ( stacks + 1 ) ) );
		mesh.InstantiateVertexArray( mesh.GetNumberOfVertices() );

		//generate the bottom base		
		polyFanBuilder.LoadGeometryVertices( polyFanBottomMesh, radius, slices, -this->m_yLimit, GL_TRUE, -this->m_yLimit, GL_FALSE, red, green, blue, alpha );

		for ( GLuint index = 0; index < polyFanBottomMesh.GetNumberOfVertices(); ++index )
		{
			mesh.GetVertexArray()[index] = polyFanBottomMesh.GetVertexArray()[index];
			//set the normal
			mesh.GetVertexArray()[index].SetNormal( 0.0F, -1.0F, 0.0F );
		}//end for loop


		indexStackOffset = polyFanBottomMesh.GetNumberOfVertices();		


		//generate the ring of the cylinder starting from the bottom
		polyRingBuilder.LoadGeometryVertices( polyRingMesh, radius, slices, -this->m_yLimit, GL_FALSE, -this->m_yLimit, GL_FALSE, red, green, blue, alpha );

		//loop through each vertex in the polygon ring
		for ( GLuint index = 0; index < polyRingMesh.GetNumberOfVertices(); ++index )
		{
			//apply the offset to the vertical position as well as to the array element
			//on the first stack iteration, generate the bottom polygon ring
			polyRingMesh.GetVertexArray()[index].m_point.m_y = -this->m_yLimit; 
			mesh.GetVertexArray()[index + indexStackOffset] = polyRingMesh.GetVertexArray()[index];

			//on the first iteration
			if ( index == 0 )
			{
				sTexCoord = 0.0F;
			}
			//on the last iteration
			else if ( index + 1 == polyRingMesh.GetNumberOfVertices() )
			{
				sTexCoord = 1.0F;
			}
			//on subsequent iterations
			else
			{
				sTexCoord += this->m_sTextureOffset;
			}
			//set the texture coordinates
			mesh.GetVertexArray()[index + indexStackOffset].SetTextureCoord( sTexCoord, tTexCoord );
			
		}//end for loop


		//loop through each stack with the starting index offset from the initial base
		for ( GLuint indexStack = 0; indexStack < stacks; ++indexStack )
		{	
			indexStackOffset += polyRingMesh.GetNumberOfVertices();			

			//on the last iteration, generate the top polygon ring and fan to close the cylinder
			if ( indexStack + 1 == stacks )
			{				
				//close the t texture coordinate
				tTexCoord = 1.0F;

				//loop through each vertex in the polygon ring
				for ( GLuint index = 0; index < polyRingMesh.GetNumberOfVertices(); ++index )
				{
					//apply the offset to the vertical position as well as to the array element
					//on the first stack iteration, generate the bottom polygon ring
					polyRingMesh.GetVertexArray()[index].m_point.m_y = this->m_yLimit; 
					mesh.GetVertexArray()[index + indexStackOffset] = polyRingMesh.GetVertexArray()[index];
					
					//on the first iteration
					if ( index == 0 )
					{
						sTexCoord = 0.0F;
					}
					//on the last iteration
					else if ( index + 1 == polyRingMesh.GetNumberOfVertices() )
					{
						sTexCoord = 1.0F;
					}
					//on subsequent iterations
					else
					{
						sTexCoord += this->m_sTextureOffset;
					}
					//set the texture coordinates
					mesh.GetVertexArray()[index + indexStackOffset].SetTextureCoord( sTexCoord, tTexCoord );

				}//end for loop

				indexStackOffset += polyRingMesh.GetNumberOfVertices();


				//generate the top base	
				//invert the normals of the polygon fan mesh
				polyFanBuilder.LoadGeometryVertices( polyFanTopMesh, radius, slices, -this->m_yLimit, GL_TRUE, -this->m_yLimit, GL_TRUE, red, green, blue, alpha );

				//loop through each vertex in the polygon fan
				for ( GLuint index = 0; index < polyFanTopMesh.GetNumberOfVertices(); ++index )
				{
					//apply the offset to the vertical position as well as to the array element
					polyFanTopMesh.GetVertexArray()[index].m_point.m_y = this->m_yLimit; 
					mesh.GetVertexArray()[index + indexStackOffset] = polyFanTopMesh.GetVertexArray()[index];	
					//set the normal
					mesh.GetVertexArray()[index + indexStackOffset].SetNormal( 0.0F, 1.0F, 0.0F );
				}//end for loop
			}
			else
			{
				//increment the t texture coordinate
				tTexCoord += this->m_tTextureOffset;

				//loop through each vertex in the polygon ring
				for ( GLuint index = 0; index < polyRingMesh.GetNumberOfVertices(); ++index )
				{
					//apply the offset to the vertical position as well as to the array element
					//on the first stack iteration, generate the bottom polygon ring
					polyRingMesh.GetVertexArray()[index].m_point.m_y += this->m_yOffset; 
					mesh.GetVertexArray()[index + indexStackOffset] = polyRingMesh.GetVertexArray()[index];

					//on the first iteration
					if ( index == 0 )
					{
						sTexCoord = 0.0F;
					}
					//on the last iteration
					else if ( index + 1 == polyRingMesh.GetNumberOfVertices() )
					{
						sTexCoord = 1.0F;
					}
					//on subsequent iterations
					else
					{
						sTexCoord += this->m_sTextureOffset;
					}
					//set the texture coordinates
					mesh.GetVertexArray()[index + indexStackOffset].SetTextureCoord( sTexCoord, tTexCoord );

				}//end for loop
			}
		
		}//end for loop

		//delete the vertex array from the heap
		polyFanBottomMesh.DeleteVertexArray();
		polyFanTopMesh.DeleteVertexArray();
		polyRingMesh.DeleteVertexArray();
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
	void CylinderBuilder::GenerateGeometryIndices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values being passed
		this->m_slices = ( meshParameterContainer.m_slices < 3 ) ? 3 : meshParameterContainer.m_slices;
		this->m_stacks = ( meshParameterContainer.m_stacks < 1 ) ? 1 : meshParameterContainer.m_stacks;

		//invoke the subfunction
		this->GenerateGeometryIndicesSubFunc( mesh, this->m_slices, this->m_stacks );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the indices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param radius
	the radius of the geometry
	\param slices
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
	\return
	*/
	/******************************************************************************/
	void CylinderBuilder::GenerateGeometryIndices( Mesh & mesh, const GLuint slices, const GLuint stacks )
	{
		//validate the values being passed
		this->m_slices = ( slices < 3 ) ? 3 : slices;
		this->m_stacks = ( stacks < 1 ) ? 1 : stacks;

		//invoke the subfunction
		this->GenerateGeometryIndicesSubFunc( mesh, this->m_slices, this->m_stacks );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the indices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param radius
	the radius of the geometry
	\param slices
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
	\return
	*/
	/******************************************************************************/
	void CylinderBuilder::GenerateGeometryIndicesSubFunc( Mesh & mesh, const GLuint slices, const GLuint stacks )
	{
		PolygonBuilder	polyFanBuilder;
		Mesh			polyFanMesh;

		polyFanBuilder.GenerateGeometryIndices( polyFanMesh, slices, GL_TRUE );

		GLuint indexOffset = 0;
		GLuint elementValOffset = 0;
		GLuint startVertexOfLastQuad = 0;

		//algorithm for the index values of the quad in each stack
		GLuint startVertex = polyFanMesh.GetNumberOfIndices() + ( slices + 1 ) + 1;
		GLuint secondVertex = startVertex - 1;
		GLuint thirdVertex = secondVertex - slices;
		GLuint endVertex = thirdVertex - 1;

		//allocate the index array in the memory heap
		//top and bottom fans + rings
		mesh.SetNumberOfIndices( ( polyFanMesh.GetNumberOfIndices() * 2 ) + ( 4 * slices * stacks) );
		mesh.InstantiateIndexArray( mesh.GetNumberOfIndices() );


		//generate indices for the bottom base	
		//logic to invert the normals by tracing the indices clockwise
		//0 1 2 3 4 5 -> 0 5 4 3 2 1
		for ( GLuint index = 0; index < polyFanMesh.GetNumberOfIndices(); ++index )
		{			
			//on the first iteration
			if ( index == 0 )
			{
				//copy the first element (center point of origin)
				mesh.GetIndexArray()[index] = polyFanMesh.GetIndexArray()[index];
			}
			//on subsequent iterations
			else
			{
				//copy starting from the last element in reverse order
				mesh.GetIndexArray()[index] = polyFanMesh.GetIndexArray()[polyFanMesh.GetNumberOfIndices() - index];
			}
		}//end for loop	
			

		for ( GLuint indexStack = 0; indexStack < stacks; ++indexStack )
		{
			elementValOffset = indexStack * ( slices + 1 );

			//on the first iteration
			if ( indexStack == 0 )
			{
				indexOffset = polyFanMesh.GetNumberOfIndices();
			}

			//generate the indices for the body of the cylinder
			for ( GLuint indexSlice = 0; indexSlice < slices; ++indexSlice )
			{
				mesh.GetIndexArray()[0 + indexOffset] = static_cast<GLushort>( startVertex + indexSlice + elementValOffset );
				mesh.GetIndexArray()[1 + indexOffset] = static_cast<GLushort>( secondVertex + indexSlice + elementValOffset );
				mesh.GetIndexArray()[2 + indexOffset] = static_cast<GLushort>( thirdVertex + indexSlice + elementValOffset );
				mesh.GetIndexArray()[3 + indexOffset] = static_cast<GLushort>( endVertex + indexSlice + elementValOffset );

				indexOffset += 4;

				//check if it is the last slice iteration 
				if ( indexSlice + 1 == slices )
				{
					startVertexOfLastQuad = startVertex + indexSlice + elementValOffset;
				}

			}//end for loop


			//on the last iteration, generate the indices for the top polygon fan to close the cylinder
			if ( indexStack + 1 == stacks )
			{
				//generate indices for the top base		
				for ( GLuint index = 0; index < polyFanMesh.GetNumberOfIndices(); ++index )
				{
					mesh.GetIndexArray()[index + indexOffset] = static_cast<GLushort>( polyFanMesh.GetIndexArray()[index] + ( startVertexOfLastQuad + 1 ) );
				}//end for loop
			}
	
		}//end for loop

		//delete the index array from the heap
		polyFanMesh.DeleteIndexArray();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This generates the indices of the geometry
	\param mesh
	the mesh to contain the geometry vertices and indices
	\param radius
	the radius of the geometry
	\param slices
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
	\return
	*/
	/******************************************************************************/
	void CylinderBuilder::GenerateGeometryIndicesSubFuncLessIdx( Mesh & mesh, const GLuint slices, const GLuint stacks )
	{
		PolygonBuilder	polyFanBuilder;
		Mesh			polyFanMesh;

		polyFanBuilder.GenerateGeometryIndices( polyFanMesh, slices, GL_TRUE );

		GLuint indexOffset = 0;
		GLuint elementValOffset = 0;

		//algorithm for the index values of the quad in each stack
		GLuint startVertex = slices * 2;
		GLuint secondVertex = startVertex - 1;
		GLuint thirdVertex = startVertex - slices;
		GLuint endVertex = ( startVertex - 1 ) - slices;

		//algorithm for the index values of the last quad in the stack
		GLuint closingStartVertex = slices + 1;
		GLuint closingSecondVertex = slices * 2;
		GLuint closingThirdVertex = 1;
		GLuint closingEndVertex = slices;

		//allocate the index array in the memory heap
		//top and bottom fans + rings
		mesh.SetNumberOfIndices( ( polyFanMesh.GetNumberOfIndices() * 2 ) + ( 4 * slices * stacks) );
		mesh.InstantiateIndexArray( mesh.GetNumberOfIndices() );


		//generate indices for the bottom base	
		//logic to invert the normals by tracing the indices clockwise
		//0 1 2 3 4 1 -> 0 4 3 2 1 4
		for ( GLuint index = 0; index < polyFanMesh.GetNumberOfIndices(); ++index )
		{			
			//on the first iteration
			if ( index == 0 )
			{
				//copy the first element (center point of origin)
				mesh.GetIndexArray()[index] = polyFanMesh.GetIndexArray()[index];
			}
			//on the last iteration
			else if ( index + 1 == polyFanMesh.GetNumberOfIndices() )
			{
				//copy the second to the last element to close the fan
				mesh.GetIndexArray()[index] = polyFanMesh.GetIndexArray()[polyFanMesh.GetNumberOfIndices() - 2];
			}
			//on subsequent iterations
			else
			{
				//copy starting from the second to the last element in reverse order (excludes the old closing vertex element)
				mesh.GetIndexArray()[index] = polyFanMesh.GetIndexArray()[polyFanMesh.GetNumberOfIndices() - ( index + 1 )];
			}
		}//end for loop	
			

		for ( GLuint indexStack = 0; indexStack < stacks; ++indexStack )
		{
			elementValOffset = indexStack * slices;

			//on the first iteration
			if ( indexStack == 0 )
			{
				indexOffset = polyFanMesh.GetNumberOfIndices();
			}

			//generate the indices for the body of the cylinder
			for ( GLuint indexSlice = 0; indexSlice < slices; ++indexSlice )
			{
				//check if it is the last slice iteration to complete the cylinder body ring
				if ( indexSlice + 1 == slices )
				{
					//on the last stack iteration generate the indices for the body of the cylinder to link with the top base
					if ( indexStack + 1 == stacks )
					{
						mesh.GetIndexArray()[0 + indexOffset] = static_cast<GLushort>( closingStartVertex + ( elementValOffset + 1 ) );
						mesh.GetIndexArray()[1 + indexOffset] = static_cast<GLushort>( closingSecondVertex + ( elementValOffset + 1 ) );
					}
					//on subsequent stack iterations
					else
					{
						mesh.GetIndexArray()[0 + indexOffset] = static_cast<GLushort>( closingStartVertex + elementValOffset );
						mesh.GetIndexArray()[1 + indexOffset] = static_cast<GLushort>( closingSecondVertex + elementValOffset );
					}						
					mesh.GetIndexArray()[2 + indexOffset] = static_cast<GLushort>( closingThirdVertex + elementValOffset );
					mesh.GetIndexArray()[3 + indexOffset] = static_cast<GLushort>( closingEndVertex + elementValOffset );
				}
				else
				{
					//on the last stack iteration generate the indices for the body of the cylinder to link with the top base
					if ( indexStack + 1 == stacks )
					{
						mesh.GetIndexArray()[0 + indexOffset] = static_cast<GLushort>( startVertex + ( elementValOffset + 1 ) - indexSlice );
						mesh.GetIndexArray()[1 + indexOffset] = static_cast<GLushort>( secondVertex + ( elementValOffset + 1 ) - indexSlice );
					}
					//on subsequent stack iterations
					else
					{
						mesh.GetIndexArray()[0 + indexOffset] = static_cast<GLushort>( startVertex + elementValOffset - indexSlice );
						mesh.GetIndexArray()[1 + indexOffset] = static_cast<GLushort>( secondVertex + elementValOffset - indexSlice );
					}						
					mesh.GetIndexArray()[2 + indexOffset] = static_cast<GLushort>( thirdVertex + elementValOffset - indexSlice );
					mesh.GetIndexArray()[3 + indexOffset] = static_cast<GLushort>( endVertex + elementValOffset - indexSlice );
				}

				indexOffset += 4;

			}//end for loop


			//on the last iteration, generate the indices for the top polygon fan to close the cylinder
			if ( indexStack + 1 == stacks )
			{
				//generate indices for the top base		
				for ( GLuint index = 0; index < polyFanMesh.GetNumberOfIndices(); ++index )
				{
					mesh.GetIndexArray()[index + indexOffset] = static_cast<GLushort>( polyFanMesh.GetIndexArray()[index] + ( slices * stacks + 1 ) );
				}//end for loop
			}
	
		}//end for loop

		//delete the index array from the heap
		polyFanMesh.DeleteIndexArray();
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
	void CylinderBuilder::DrawGeometry( const GLuint VAO ) const
	{
		// Render object
		glBindVertexArray( VAO );

		GLuint offSetVal = 0;
		GLuint numOfFaces = this->m_slices * this->m_stacks + 2;
		//there are two additional indices: one for the point of origin and the other one to close the fan
		GLuint numOfPolyFanIndices = this->m_slices + 2;

		for ( GLuint index = 0; index < numOfFaces; ++index )
		{
			//if first or last iteration
			if ( index == 0 || index + 1 == numOfFaces )
			{
				//draw top and bottom
				glDrawElements(
					GL_TRIANGLE_FAN, 
					numOfPolyFanIndices, 
					GL_UNSIGNED_SHORT, 
					(GLvoid*)offSetVal);

				offSetVal += numOfPolyFanIndices * sizeof(GLushort);
			}
			else
			{
				//draw each quad face around cylinder body
				glDrawElements(
					GL_TRIANGLE_STRIP, 
					4,
					GL_UNSIGNED_SHORT, 
					(GLvoid*)offSetVal);

				offSetVal += 4 * sizeof(GLushort);
			}		
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
	void CylinderBuilder::DrawGeometry( const GLuint VAO, const GLuint textureId ) const
	{
		// bind the texture name to the texture target
		glBindTexture( GL_TEXTURE_2D, textureId );

		//draw/render the geometry through the VAO
		this->DrawGeometry( VAO );
	}


} // namespace GraphicsFramework