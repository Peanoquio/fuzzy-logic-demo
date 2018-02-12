/******************************************************************************/
/*!
\file ConeBuilder.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 30/12/2011
\brief
This is the cone builder that will generate the mesh for the cone.

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "ConeBuilder.h"
#include "Polygon2DBuilder.h"

#include <iostream>
#include <iomanip>


namespace GraphicsFramework
{
	/******************************************************************************/
	/*!
	The constructor for the ConeBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	ConeBuilder::ConeBuilder( void )
		: m_radius( 0.5F ),		
		m_height( 1.0F ),
		m_slices( 3 ),
		m_stacks( 1 ),
		m_yLimit( m_height / 2.0F ),
		m_yOffset( m_height / m_stacks),
		m_radiusOffset( m_radius / m_stacks )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the ConeBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	ConeBuilder::~ConeBuilder( void )
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
	void ConeBuilder::ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values being passed
		this->m_radius = ( meshParameterContainer.m_radius < 0.0F ) ? 0.01F : meshParameterContainer.m_radius;
		this->m_height = ( meshParameterContainer.m_height < 0.0F) ? 0.01F : meshParameterContainer.m_height;
		this->m_stacks = ( meshParameterContainer.m_stacks < 1) ? 1 : meshParameterContainer.m_stacks;

		//invoke the subfunction
		this->ComputeGeometryBoundaryAndOffsetSubFunc( this->m_radius, this->m_height, this->m_stacks );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This computes the boundary and offset values used to create the geometry
	\param radius
	the radius of the geometry
	\param height
	the height of the geometry
	\param stacks
	the number of stacks in the geometry
	\return
	*/
	/******************************************************************************/
	void ConeBuilder::ComputeGeometryBoundaryAndOffset( const GLfloat radius, const GLfloat height, const GLuint stacks )
	{
		//validate the values being passed
		this->m_radius = ( radius < 0.0F ) ? 0.01F : radius;
		this->m_height = ( height < 0.0F ) ? 0.01F : height;
		this->m_stacks = ( stacks < 1 ) ? 1 : stacks;

		//invoke the subfunction
		this->ComputeGeometryBoundaryAndOffsetSubFunc( this->m_radius, this->m_height, this->m_stacks );
	}
		
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This computes the boundary and offset values used to create the geometry
	\param radius
	the radius of the geometry
	\param height
	the height of the geometry
	\param stacks
	the number of stacks in the geometry
	\return
	*/
	/******************************************************************************/
	void ConeBuilder::ComputeGeometryBoundaryAndOffsetSubFunc( const GLfloat radius, const GLfloat height, const GLuint stacks )
	{
		this->m_yLimit = height / 2.0F;
		this->m_yOffset = height / stacks;
		this->m_radiusOffset = radius / stacks;
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
	void ConeBuilder::LoadGeometryVertices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values
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
	void ConeBuilder::LoadGeometryVertices( Mesh & mesh, 
		const GLfloat radius, const GLuint slices, const GLuint stacks, 
		const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		//validate the values
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
	void ConeBuilder::LoadGeometryVerticesSubFunc( Mesh & mesh, 
		const GLfloat radius, const GLuint slices, const GLuint stacks, 
		const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		PolygonBuilder	polyFanBuilder;
		Mesh			polyFanMesh;
		PolygonBuilder	polyRingBuilder;
		Mesh			polyRingMesh;	
		Mesh			normalMesh;

		//set the texture offsets
		this->m_sTextureOffset = 1.0F / slices;
		this->m_tTextureOffset = 1.0F / stacks;
		GLfloat sTexCoord = 0.0F;
		GLfloat tTexCoord = 0.0F;

		//allocate the vertex array in the memory heap
		//base and subsequent rings all the way to the top
		mesh.SetNumberOfVertices( ( slices + 2 ) + ( ( slices + 1 ) * stacks ) );
		mesh.InstantiateVertexArray( mesh.GetNumberOfVertices() );
		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//generate the bottom fan base			
		polyFanBuilder.LoadGeometryVertices( polyFanMesh, radius, slices, -this->m_yLimit, GL_TRUE, -this->m_yLimit, red, green, blue, alpha );

		for ( GLuint index = 0; index < polyFanMesh.GetNumberOfVertices(); ++index )
		{
			mesh.GetVertexArray()[index] = polyFanMesh.GetVertexArray()[index];
			//set the normal
			mesh.GetVertexArray()[index].SetNormal( 0.0F, -1.0F, 0.0F );
			//set the bi-normal
			mesh.GetVertexArray()[index].SetBiNormal( 0.0F, 0.0F, 1.0F );
			//set the tangent
			mesh.GetVertexArray()[index].SetTangent( -1.0F, 0.0F, 0.0F );
		}//end for loop

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//generate the subsequent rings
		GLfloat computedRadius = radius;	
		GLfloat computedYOffset = -this->m_yLimit;

		//loop through each stack with the starting index offset from the initial base
		GLuint indexStackOffset = 0;			
		GLuint stackLimit = stacks + 1;

		for ( GLuint indexStack = 0; indexStack < stackLimit; ++indexStack )
		{
			//on the last iteration, set the radius to zero to create a converging point for the cone tip
			if ( indexStack + 1 == stackLimit )
			{
				computedRadius = 0;	
			}

			//delete the vertices from the heap memory before creating another mesh
			polyRingMesh.DeleteVertexArray();

			//generate the ring of the cone starting from the vertical offset
			polyRingBuilder.LoadGeometryVertices( polyRingMesh, computedRadius, slices, computedYOffset, GL_FALSE, computedYOffset, red, green, blue, alpha );

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//on the first stack iteration
			if ( indexStack == 0 )
			{
				indexStackOffset = polyFanMesh.GetNumberOfVertices();

				//generate the ring of the cone starting from the vertical offset
				polyRingBuilder.LoadGeometryVertices( normalMesh, computedRadius, slices, computedYOffset, GL_FALSE, computedYOffset, red, green, blue, alpha );
			}
			//on the last stack iteration
			else if ( indexStack + 1 == stackLimit )
			{
				tTexCoord = 1.0F;
			}
			//on subsequent stack iterations
			else
			{
				indexStackOffset += polyRingMesh.GetNumberOfVertices();

				//increment the t texture coordinate
				tTexCoord += this->m_tTextureOffset;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//loop through each vertex in the polygon ring
			for ( GLuint index = 0; index < polyRingMesh.GetNumberOfVertices(); ++index )
			{
				//on the first stack iteration
				if ( indexStack == 0 )
				{					
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
					//TANGENT
					//get the horizontal vector				
					Math::Vector4 horizontalVec( polyRingMesh.GetVertexArray()[index].GetPoint().m_x, 
						polyRingMesh.GetVertexArray()[index].GetPoint().m_y, 
						polyRingMesh.GetVertexArray()[index].GetPoint().m_z, 
						0.0F );
					//get the vertical vector
					Math::Vector4 verticalVec( 0.0F, 1.0F, 0.0F, 0.0F );
					//compute for the tangent
					Math::Vector4 tangentVec = horizontalVec.Cross( verticalVec );
					tangentVec.Normalize();
					normalMesh.GetVertexArray()[index].SetTangent( tangentVec.GetFloatX(), tangentVec.GetFloatY(), tangentVec.GetFloatZ() );

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					//BI-NORMAL
					//compute for the bi-normal
					Math::Vector4 coneTip( 0.0F, this->m_yLimit, 0.0F, 1.0F );
					Math::Vector4 coneRingPt( polyRingMesh.GetVertexArray()[index].GetPoint().m_x, 
						polyRingMesh.GetVertexArray()[index].GetPoint().m_y, 
						polyRingMesh.GetVertexArray()[index].GetPoint().m_z, 
						1.0F );
					Math::Vector4 biNormalVec = coneTip - coneRingPt;
					biNormalVec.Normalize();
					normalMesh.GetVertexArray()[index].SetBiNormal( biNormalVec.GetFloatX(), biNormalVec.GetFloatY(), biNormalVec.GetFloatZ() );

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					//NORMAL
					//compute for the normal
					Math::Vector4 normalVec = biNormalVec.Cross( tangentVec );
					normalVec.Normalize();
					normalMesh.GetVertexArray()[index].SetNormal( normalVec.GetFloatX(), normalVec.GetFloatY(), normalVec.GetFloatZ() );

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
					polyRingMesh.GetVertexArray()[index] = normalMesh.GetVertexArray()[index];
				}
				else
				{
					//simply copy the computed normal values from the initial ring stack
					polyRingMesh.GetVertexArray()[index].SetNormal( normalMesh.GetVertexArray()[index].GetNormal().m_x, 
						normalMesh.GetVertexArray()[index].GetNormal().m_y, 
						normalMesh.GetVertexArray()[index].GetNormal().m_z );

					polyRingMesh.GetVertexArray()[index].SetBiNormal( normalMesh.GetVertexArray()[index].GetBiNormal().m_x, 
						normalMesh.GetVertexArray()[index].GetBiNormal().m_y, 
						normalMesh.GetVertexArray()[index].GetBiNormal().m_z );

					polyRingMesh.GetVertexArray()[index].SetTangent( normalMesh.GetVertexArray()[index].GetTangent().m_x, 
						normalMesh.GetVertexArray()[index].GetTangent().m_y, 
						normalMesh.GetVertexArray()[index].GetTangent().m_z );
				}				

				//apply the offset to the array element
				mesh.GetVertexArray()[index + indexStackOffset] = polyRingMesh.GetVertexArray()[index];	

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			}//end for loop

			computedYOffset += this->m_yOffset;
			computedRadius -= this->m_radiusOffset;			

		}//end for loop
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//delete the vertices from the heap memory
		polyFanMesh.DeleteVertexArray();
		polyRingMesh.DeleteVertexArray();
		normalMesh.DeleteVertexArray();
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
	void ConeBuilder::LoadGeometryVerticesSubFuncLessVtx( Mesh & mesh, 
		const GLfloat radius, const GLuint slices, const GLuint stacks, 
		const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		PolygonBuilder	polyFanBuilder;
		Mesh			polyFanMesh;
		PolygonBuilder	polyRingBuilder;
		Mesh			polyRingMesh;

		//allocate the vertex array in the memory heap
		if ( stacks == 1 )
		{
			//base fan + point tip
			//this->m_numberOfVertices = (this->m_slices + 1) + 1;
			mesh.SetNumberOfVertices( ( slices + 1 ) + 1 );
		}
		else
		{
			//base and top fans + rings
			mesh.SetNumberOfVertices( ( ( slices + 1 ) * 2 ) + ( slices * ( stacks - 2 ) ) );
		}
		
		mesh.InstantiateVertexArray( mesh.GetNumberOfVertices() );
		
		//generate the bottom base			
		polyFanBuilder.LoadGeometryVertices( polyFanMesh, radius, slices, -this->m_yLimit, GL_TRUE, -this->m_yLimit, red, green, blue, alpha );

		for ( GLuint index = 0; index < polyFanMesh.GetNumberOfVertices(); ++index )
		{
			mesh.GetVertexArray()[index] = polyFanMesh.GetVertexArray()[index];

			//on the first iteration, if there is only cone one stack, generate its tip
			if ( index + 1 == polyFanMesh.GetNumberOfVertices() && stacks == 1 )
			{
				Vertex tipVertex;
				tipVertex.m_point.m_x = 0.0F;
				tipVertex.m_point.m_y = this->m_yLimit;
				tipVertex.m_point.m_z = 0.0F;

				//set the color values
				tipVertex.m_color.m_r = red;
				tipVertex.m_color.m_g = green;
				tipVertex.m_color.m_b = blue;
				tipVertex.m_color.m_a = alpha;

				mesh.GetVertexArray()[index + 1] = tipVertex;
			}
		}//end for loop


		//generate the subsequent rings of the cone if there is more than one stack
		if ( stacks > 1 )		
		{
			GLfloat computedRadius = radius;	
			GLfloat computedYOffset = -this->m_yLimit;

			//loop through each stack with the starting index offset from the initial base
			GLuint indexStackOffset = 0;			
			GLuint stackLimit = stacks - 1;

			for (GLuint indexStack = 0; indexStack < stackLimit; ++indexStack)
			{	
				computedYOffset += this->m_yOffset;
				computedRadius -= this->m_radiusOffset;

				//delete the vertices from the heap memory before creating another mesh
				polyRingMesh.DeleteVertexArray();

				//generate the ring of the cone starting from the vertical offset
				polyRingBuilder.LoadGeometryVertices( polyRingMesh, computedRadius, slices, computedYOffset, GL_FALSE, computedYOffset, red, green, blue, alpha );

				//on the first iteration
				if ( indexStack == 0 )
				{
					indexStackOffset = polyFanMesh.GetNumberOfVertices();
				}
				else
				{
					indexStackOffset += polyRingMesh.GetNumberOfVertices();
				}

				//on the last iteration, generate the top polygon fan to close the cone
				if ( indexStack + 1 == stackLimit )
				{
					//delete the vertices from the heap memory before creating another mesh
					polyFanMesh.DeleteVertexArray();

					//generate the top						
					polyFanBuilder.LoadGeometryVertices( polyFanMesh, computedRadius, slices, computedYOffset, GL_TRUE, computedYOffset + this->m_yOffset, red, green, blue, alpha );

					//loop through each vertex in the polygon fan
					for ( GLuint index = 0; index < polyFanMesh.GetNumberOfVertices(); ++index )
					{
						//apply the offset to the array element
						mesh.GetVertexArray()[index + indexStackOffset] = polyFanMesh.GetVertexArray()[index];
					}//end for loop
				}
				else
				{
					//loop through each vertex in the polygon ring
					for ( GLuint index = 0; index < polyRingMesh.GetNumberOfVertices(); ++index )
					{
						//apply the offset to the array element
						mesh.GetVertexArray()[index + indexStackOffset] = polyRingMesh.GetVertexArray()[index];
					}//end for loop
				}
		
			}//end for loop
		}

		//delete the vertices from the heap memory
		polyFanMesh.DeleteVertexArray();
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
	void ConeBuilder::GenerateGeometryIndices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values
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
	\param slices
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
	\return
	*/
	/******************************************************************************/
	void ConeBuilder::GenerateGeometryIndices( Mesh & mesh, const GLuint slices, const GLuint stacks )
	{
		//validate the values
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
	\param slices
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
	\return
	*/
	/******************************************************************************/
	void ConeBuilder::GenerateGeometryIndicesSubFunc( Mesh & mesh, const GLuint slices, const GLuint stacks )
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
		mesh.SetNumberOfIndices( ( polyFanMesh.GetNumberOfIndices() * 1 ) + ( 4 * slices * stacks) );
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
	\param slices
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
	\return
	*/
	/******************************************************************************/
	void ConeBuilder::GenerateGeometryIndicesSubFuncLessIdx( Mesh & mesh, const GLuint slices, const GLuint stacks )
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
		mesh.SetNumberOfIndices( ( polyFanMesh.GetNumberOfIndices() * 2 ) + ( 4 * slices * ( stacks - 1 ) ) );
		mesh.InstantiateIndexArray( mesh.GetNumberOfIndices() );


		//generate indices for the bottom base			
		for ( GLuint index = 0; index < polyFanMesh.GetNumberOfIndices(); ++index )
		{			
			//logic to invert the normals by tracing the indices clockwise
			//0 1 2 3 4 1 -> 0 4 3 2 1 4
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
				mesh.GetIndexArray()[index] = polyFanMesh.GetIndexArray()[polyFanMesh.GetNumberOfIndices() - (index + 1)];
			}

			//if there is only one stack, generate the indices for the tip
			if ( stacks == 1 )
			{
				//on the first iteration
				if ( index == 0 )
				{
					//set the index for the vertex tip element (the new origin center point)
					mesh.GetIndexArray()[index + polyFanMesh.GetNumberOfIndices()] = static_cast<GLushort>( slices + 1 );
				}
				else
				{
					//get the subsequent vertex element from the original fan (exclude the old origin center point)
					mesh.GetIndexArray()[index + polyFanMesh.GetNumberOfIndices()] = polyFanMesh.GetIndexArray()[index];
				}
			}

		}//end for loop	
			

		if ( stacks > 1 )
		{
			GLuint stackLimit = stacks - 1;

			for ( GLuint indexStack = 0; indexStack < stackLimit; ++indexStack )
			{
				elementValOffset = indexStack * slices;

				//on the first iteration
				if ( indexStack == 0 )
				{
					indexOffset = polyFanMesh.GetNumberOfIndices();
				}

				//generate the indices for the body of the cone
				for ( GLuint indexSlice = 0; indexSlice < slices; ++indexSlice )
				{
					//check if it is the last slice iteration to complete the cone body ring
					if ( indexSlice + 1 == slices )
					{
						//on the last stack iteration generate the indices for the body of the cone to link with the top base
						if ( indexStack + 1 == stackLimit )
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
						//on the last stack iteration generate the indices for the body of the cone to link with the top base
						if ( indexStack + 1 == stackLimit )
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


				//on the last iteration, generate the indices for the top polygon fan to close the cone
				if ( indexStack + 1 == stackLimit )
				{
					//generate indices for the top base		
					for ( GLuint index = 0; index < polyFanMesh.GetNumberOfIndices(); ++index )
					{
						mesh.GetIndexArray()[index + indexOffset] = static_cast<GLushort>( polyFanMesh.GetIndexArray()[index] + ( slices * stackLimit + 1) );
					}//end for loop
				}
	
			}//end for loop
		}

		//delete the indices from the heap memory
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
	void ConeBuilder::DrawGeometry( const GLuint VAO ) const
	{
		// Render object
		glBindVertexArray( VAO );

		GLuint offSetVal = 0;
		//the number of quad faces on each side plus the bottom face
		GLuint numOfFaces = this->m_slices * this->m_stacks + 1;
		//there are two additional indices: one for the point of origin and the other one to close the fan
		GLuint numOfPolyFanIndices = this->m_slices + 2;

		for ( GLuint index = 0; index < numOfFaces; ++index )
		{
			//if first iteration
			if ( index == 0 )
			{
				//draw bottom
				glDrawElements(
					GL_TRIANGLE_FAN, 
					numOfPolyFanIndices,
					GL_UNSIGNED_SHORT, 
					(GLvoid*)offSetVal);

				offSetVal += numOfPolyFanIndices * sizeof(GLushort);
			}
			else
			{
				//draw each quad face around cone body
				glDrawElements(
					GL_TRIANGLE_STRIP, 
					4,
					GL_UNSIGNED_SHORT, 
					(GLvoid*)offSetVal);

				offSetVal += 4 * sizeof(GLushort);
			}		
		}//end for loop		
	}
	/*
	void ConeBuilder::DrawGeometry( const GLuint VAO ) const
	{
		// Render object
		glBindVertexArray( VAO );

		GLuint offSetVal = 0;
		GLuint numOfFaces = this->m_slices * ( this->m_stacks - 1 ) + 2;
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
				//draw each quad face around cone body
				glDrawElements(
					GL_TRIANGLE_STRIP, 
					4,
					GL_UNSIGNED_SHORT, 
					(GLvoid*)offSetVal);

				offSetVal += 4 * sizeof(GLushort);
			}		
		}//end for loop		
	}
	*/


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
	void ConeBuilder::DrawGeometry( const GLuint VAO, const GLuint textureId ) const
	{
		// bind the texture name to the texture target
		glBindTexture( GL_TEXTURE_2D, textureId );

		//draw/render the geometry through the VAO
		this->DrawGeometry( VAO );
	}


} // namespace GraphicsFramework