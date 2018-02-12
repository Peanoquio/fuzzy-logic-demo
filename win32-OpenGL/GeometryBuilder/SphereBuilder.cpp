/******************************************************************************/
/*!
\file SphereBuilder.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 20/12/2011
\brief
This is the sphere builder that will generate the mesh for the sphere.

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "SphereBuilder.h"
#include "../Math/MyMath.h"
#include "../Math/Vector4.h"


namespace GraphicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The default constructor for the SphereBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	SphereBuilder::SphereBuilder( void )
		: m_radius ( 0.01F ),
		m_slices ( 3 ),
		m_stacks ( 2 ),
		m_height ( 1.0F ),
		m_yLimit ( m_height / 2.0F ),
		m_yOffset ( m_height / m_stacks),
		m_radiusOffset ( m_radius / m_stacks)
	{		
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the SphereBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	SphereBuilder::~SphereBuilder (void)
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
	void SphereBuilder::ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values being passed
		this->m_radius = ( meshParameterContainer.m_radius < 0.0F ) ? 0.05F : meshParameterContainer.m_radius;
		this->m_height = ( meshParameterContainer.m_height < 0.0F ) ? 0.1F : meshParameterContainer.m_height;
		this->m_slices = ( meshParameterContainer.m_slices < 3 ) ? 3 : meshParameterContainer.m_slices;
		this->m_stacks = ( meshParameterContainer.m_stacks < 2 ) ? 2 : meshParameterContainer.m_stacks;

		//invoke the subfunction
		this->ComputeGeometryBoundaryAndOffsetSubFunc( this->m_stacks, this->m_radius, this->m_height );
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This computes the boundary and offset values used to create the geometry
	\param slices
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
	\param radius
	the radius of the geometry
	\param height
	the height of the geometry
	\return
	*/
	/******************************************************************************/
	void SphereBuilder::ComputeGeometryBoundaryAndOffset( const GLuint slices, const GLuint stacks, const GLfloat radius, const GLfloat height )
	{
		//validate the values being passed
		this->m_radius = ( radius < 0.0F ) ? 0.05F : radius;
		this->m_height = ( height < 0.0F ) ? 0.1F : height;
		this->m_slices = ( slices < 3 ) ? 3 : slices;
		this->m_stacks = ( stacks < 2 ) ? 2 : stacks;

		//invoke the subfunction
		this->ComputeGeometryBoundaryAndOffsetSubFunc( this->m_stacks, this->m_radius, this->m_height );
	}	
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	This computes the boundary and offset values used to create the geometry (subfunction)
	\param stacks
	the number of stacks in the geometry
	\param radius
	the radius of the geometry
	\param height
	the height of the geometry
	\return
	*/
	/******************************************************************************/
	void SphereBuilder::ComputeGeometryBoundaryAndOffsetSubFunc( const GLuint stacks, const GLfloat radius, const GLfloat height )
	{
		this->m_yLimit = height / 2.0F;
		this->m_yOffset = height / stacks;
		this->m_radiusOffset = radius / stacks;

		this->m_sTextureOffset = 1.0F / this->m_slices;
		this->m_tTextureOffset = 1.0F / this->m_stacks;
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
	void SphereBuilder::LoadGeometryVertices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values being passed
		this->m_radius = ( meshParameterContainer.m_radius < 0.0F ) ? 0.01F : meshParameterContainer.m_radius;
		this->m_slices = ( meshParameterContainer.m_slices < 3 ) ? 3 : meshParameterContainer.m_slices;
		this->m_stacks = ( meshParameterContainer.m_stacks < 2) ? 2 : meshParameterContainer.m_stacks;

		//invoke the sub function
		this->LoadGeometryVerticesSubFunc( mesh, this->m_radius, this->m_slices, this->m_stacks, this->m_yLimit, 
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
	\param verticalPos
	the vertical position of the central point of the tip of the sphere
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
	void SphereBuilder::LoadGeometryVertices( Mesh & mesh,
		const GLfloat radius, const GLuint slices, const GLuint stacks, const GLfloat verticalPos, 
		const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		//validate the values being passed
		this->m_radius = ( radius < 0.0F ) ? 0.01F : radius;
		this->m_slices = ( slices < 3 ) ? 3 : slices;
		this->m_stacks = ( stacks < 2 ) ? 2 : stacks;

		//invoke the sub function
		this->LoadGeometryVerticesSubFunc( mesh, this->m_radius, this->m_slices, this->m_stacks, verticalPos, 
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
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
	\param verticalPos
	the vertical position of the central point of the tip of the sphere
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
	void SphereBuilder::LoadGeometryVerticesSubFuncLessVtx( Mesh & mesh,
		const GLfloat radius, const GLuint slices, const GLuint stacks, const GLfloat verticalPos, 
		const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		//there is an additional vertex for the top and bottom sphere caps: one for the point of origin 
		//plus the stacks times the number of slices (excluding the top and bottom caps)
		mesh.SetNumberOfVertices( (slices + 2) + ((stacks - 2) * slices) );
		
		//allocate the vertex array of the mesh in the heap
		mesh.InstantiateVertexArray( mesh.GetNumberOfVertices() );

		//get the degrees per angle based on the number of slices and stacks
		GLfloat inclinationDegreesPerAngle = (Math::REVOLUTION_DEGREES / 2.0F) / stacks;	
		GLfloat azimuthDegreesPerAngle = Math::REVOLUTION_DEGREES / slices;	
		//compute for the corresponding radian value of the degree angle
		GLfloat inclinationRadianVal = Math::DegreeToRadian(inclinationDegreesPerAngle);
		GLfloat azimuthRadianVal = Math::DegreeToRadian(azimuthDegreesPerAngle);
		GLfloat inclinationRadianValTemp = Math::DegreeToRadian(Math::REVOLUTION_DEGREES / 2.0F) - inclinationRadianVal;
		GLfloat azimuthRadianValTemp = azimuthRadianVal;

		GLuint index = 0;

		for (GLuint indexStack = 0; indexStack < stacks; ++indexStack)
		{	
			//on the first iteration
			if (indexStack == 0)
			{				
				//create the point of origin
				mesh.GetVertexArray()[index].SetPointX( 0.0F );
				mesh.GetVertexArray()[index].SetPointY( -verticalPos );
				mesh.GetVertexArray()[index].SetPointZ( 0.0F );

				//set the color values
				mesh.GetVertexArray()[index].SetColor( red, green, blue, alpha );

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

				++index;
			}			
			//on subsequent iterations
			else
			{
				for (GLuint indexSlice = 0; indexSlice < slices; ++indexSlice)
				{
					//convert 2D coordinates into an index to be used in a one-dimensional array
					//index = (indexStack * slices) + indexSlice;
					//formula for the spherical Cartesian coordinates
					mesh.GetVertexArray()[index].SetPointX( radius * sin(inclinationRadianValTemp) * sin(azimuthRadianValTemp) );
					mesh.GetVertexArray()[index].SetPointY( radius * cos(inclinationRadianValTemp) );
					mesh.GetVertexArray()[index].SetPointZ( radius * sin(inclinationRadianValTemp) * cos(azimuthRadianValTemp) );

					//set the color values
					mesh.GetVertexArray()[index].SetColor( red, green, blue, alpha );

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

					++index;

					//increment the degree of the angle
					azimuthRadianValTemp += azimuthRadianVal;
				}//end for loop

				//decrement the degree of the angle
				inclinationRadianValTemp -= inclinationRadianVal;

				//on the last iteration
				if (indexStack + 1 == stacks)
				{
					//create the point of origin
					mesh.GetVertexArray()[index].SetPointX( 0.0F );
					mesh.GetVertexArray()[index].SetPointY( verticalPos );
					mesh.GetVertexArray()[index].SetPointZ( 0.0F );

					//set the color values
					mesh.GetVertexArray()[index].SetColor( red, green, blue, alpha );

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
			}			

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
	the number of slices in the geometry
	\param stacks
	the number of stacks in the geometry
	\param verticalPos
	the vertical position of the central point of the tip of the sphere
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
	void SphereBuilder::LoadGeometryVerticesSubFunc( Mesh & mesh,
		const GLfloat radius, const GLuint slices, const GLuint stacks, const GLfloat verticalPos, 
		const GLubyte red, const GLubyte green, const GLubyte blue, const GLubyte alpha )
	{
		//the stacks times the number of slices (including the top and bottom caps)
		//the additional slices is to close the ring which is needed for texturing
		GLuint stacksAdjusted = stacks + 1;
		GLuint slicesAdjusted = slices + 1;
		mesh.SetNumberOfVertices( slicesAdjusted * stacksAdjusted );
		
		//allocate the vertex array of the mesh in the heap
		mesh.InstantiateVertexArray( mesh.GetNumberOfVertices() );

		//get the degrees per angle based on the number of slices and stacks
		GLfloat inclinationDegreesPerAngle = ( Math::REVOLUTION_DEGREES / 2.0F ) / stacks;	
		//for the azimuth degrees per angle, we won't be using the adjusted number of slices since the last vertex of the ring will repeat the coordinates of the first vertex
		GLfloat azimuthDegreesPerAngle = Math::REVOLUTION_DEGREES / slices;	
		//compute for the corresponding radian value of the degree angle
		GLfloat inclinationRadianVal = Math::DegreeToRadian( inclinationDegreesPerAngle );
		GLfloat azimuthRadianVal = Math::DegreeToRadian( azimuthDegreesPerAngle );
		//GLfloat inclinationRadianValTemp = Math::DegreeToRadian( Math::REVOLUTION_DEGREES / 2.0F ) - inclinationRadianVal;
		GLfloat inclinationRadianValTemp = Math::DegreeToRadian( Math::REVOLUTION_DEGREES / 2.0F );
		GLfloat azimuthRadianValTemp = azimuthRadianVal;

		GLuint index = 0;
		GLfloat sTexCoord = 0.0F;
		GLfloat tTexCoord = 0.0F;
			
		//loop through the stacks
		for ( GLuint indexStack = 0; indexStack < stacksAdjusted; ++indexStack )
		{
			//loop through the slices
			//the additional slices is to close the ring needed for texturing
			for ( GLuint indexSlice = 0; indexSlice < slicesAdjusted; ++indexSlice )
			{
				//on the first stack iteration, get the starting coordinates				
				if ( indexStack == 0 )
				{
					//create the point of origin
					mesh.GetVertexArray()[index].SetPointX( 0.0F );
					mesh.GetVertexArray()[index].SetPointY( -verticalPos );
					mesh.GetVertexArray()[index].SetPointZ( 0.0F );
				}
				//on the last stack iteration
				else if ( indexStack + 1 == stacksAdjusted )
				{
					//create the point of origin
					mesh.GetVertexArray()[index].SetPointX( 0.0F );
					mesh.GetVertexArray()[index].SetPointY( verticalPos );
					mesh.GetVertexArray()[index].SetPointZ( 0.0F );
				}
				//on subsequent stacks iterations
				else
				{
					//on the last slice iteration
					if ( indexSlice + 1 == slicesAdjusted )
					{
						//reset the degree of the angle
						//since we want the starting and closing vertices of the ring slice to have the same coordinates
						azimuthRadianValTemp = azimuthRadianVal;
					}

					//formula for the spherical Cartesian coordinates
					mesh.GetVertexArray()[index].SetPointX( radius * sin( inclinationRadianValTemp ) * sin( azimuthRadianValTemp ) );
					mesh.GetVertexArray()[index].SetPointY( radius * cos( inclinationRadianValTemp ) );
					mesh.GetVertexArray()[index].SetPointZ( radius * sin( inclinationRadianValTemp ) * cos( azimuthRadianValTemp ) );	

					//on the last slice iteration
					if ( indexSlice + 1 == slicesAdjusted )
					{
					}
					//on subsequent slice iterations
					else
					{
						//increment the degree of the angle
						azimuthRadianValTemp += azimuthRadianVal;
					}
				}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//on the first iteration, get the coordinate
				if ( indexSlice == 0 )
				{
					sTexCoord = 0.0F;
				}
				//on the last iteration
				else if ( indexSlice + 1 == slicesAdjusted )
				{
					sTexCoord = 1.0F;
				}
				//on subsequent iterations, apply the offset to the coordinate
				else
				{
					sTexCoord += this->m_sTextureOffset;
				}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//set the color values
				mesh.GetVertexArray()[index].SetColor( red, green, blue, alpha );

				//set the texture coordinates
				mesh.GetVertexArray()[index].SetTextureCoord( sTexCoord, tTexCoord );

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

				++index;				

			}//end for loop			

			//on the last stack iteration
			if ( indexStack + 1 == stacksAdjusted )
			{
				tTexCoord = 1.0F;
			}
			//on subsequent stack iterations
			else
			{
				//apply the offset to the coordinate
				tTexCoord += this->m_tTextureOffset;	

				//decrement the degree of the angle
				inclinationRadianValTemp -= inclinationRadianVal;
				//reset the azimuth angle
				azimuthRadianValTemp = azimuthRadianVal;
			}				
		
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
	void SphereBuilder::GenerateGeometryIndices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer )
	{
		//validate the values being passed
		this->m_slices = ( meshParameterContainer.m_slices < 3 ) ? 3 : meshParameterContainer.m_slices;
		this->m_stacks = ( meshParameterContainer.m_stacks < 2 ) ? 2 : meshParameterContainer.m_stacks;

		//invoke the sub function
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
	void SphereBuilder::GenerateGeometryIndices( Mesh & mesh,
		const GLuint slices, const GLuint stacks )
	{
		//validate the values being passed
		this->m_slices = ( slices < 3 ) ? 3 : slices;
		this->m_stacks = ( stacks < 2 ) ? 2 : stacks;

		//invoke the sub function
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
	void SphereBuilder::GenerateGeometryIndicesSubFunc( Mesh & mesh,
		const GLuint slices, const GLuint stacks )
	{
		GLuint indexOffset = 0;
		GLuint elementValOffset = 0;

		//algorithm for the index values of the quad in each stack
		GLuint startVertex = ( slices * 2 ) + 1;
		GLuint secondVertex = startVertex - 1;
		GLuint thirdVertex = slices;
		GLuint endVertex = thirdVertex - 1;

		GLuint numberOfIndicesPerBodyStack = slices * 4;
		//allocate the index array in the memory heap
		mesh.SetNumberOfIndices( stacks * numberOfIndicesPerBodyStack );
		mesh.InstantiateIndexArray( mesh.GetNumberOfIndices() );


		for (GLuint indexStack = 0; indexStack < stacks; ++indexStack)
		{
			elementValOffset = indexStack * ( slices + 1 );

			//generate the indices for the body of the sphere
			for (GLuint indexSlice = 0; indexSlice < slices; ++indexSlice)
			{
				mesh.GetIndexArray()[0 + indexOffset] = static_cast<GLushort>( startVertex + elementValOffset - indexSlice );
				mesh.GetIndexArray()[1 + indexOffset] = static_cast<GLushort>( secondVertex + elementValOffset - indexSlice );				
				mesh.GetIndexArray()[2 + indexOffset] = static_cast<GLushort>( thirdVertex + elementValOffset - indexSlice );
				mesh.GetIndexArray()[3 + indexOffset] = static_cast<GLushort>( endVertex + elementValOffset - indexSlice );

				indexOffset += 4;

			}//end for loop		
		}//end for loop
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
	void SphereBuilder::GenerateGeometryIndicesSubFuncLessIdx( Mesh & mesh,
		const GLuint slices, const GLuint stacks )
	{
		GLuint indexOffset = 0;
		GLuint elementValOffset = 0;

		//algorithm for the index values of the quad in each stack
		GLuint startVertex = slices * 2;
		GLuint secondVertex = startVertex - 1;
		GLuint thirdVertex = startVertex - slices;
		GLuint endVertex = (startVertex - 1) - slices;

		//algorithm for the index values of the last quad in the stack
		GLuint closingStartVertex = slices + 1;
		GLuint closingSecondVertex = slices * 2;
		GLuint closingThirdVertex = 1;
		GLuint closingEndVertex = slices;

		GLuint numberOfIndicesPerFan = slices + 2;
		GLuint numberOfIndicesPerBodyStack = slices * 4;
		//allocate the index array in the memory heap
		mesh.SetNumberOfIndices( (2 * numberOfIndicesPerFan) + ((stacks - 2) * numberOfIndicesPerBodyStack) );
		mesh.InstantiateIndexArray( mesh.GetNumberOfIndices() );


		//on the first iteration, generate the indices in reverse order for the bottom polygon fan to close the sphere
		//generate indices for the bottom base (reverse normals)	
		for (GLuint index = 0; index < numberOfIndicesPerFan; ++index)
		{			
			//on the first iteration
			if (index == 0)
			{
				mesh.GetIndexArray()[index] = static_cast<GLushort>(index);
			}
			//on the last iteration, close the fan
			else if (index + 1 == numberOfIndicesPerFan)
			{
				mesh.GetIndexArray()[index] = static_cast<GLushort>(this->m_slices);
			}
			//on subsequent iterations
			else
			{
				//copy starting from the second to the last element in reverse order (excludes the old closing vertex element)
				mesh.GetIndexArray()[index] = static_cast<GLushort>(numberOfIndicesPerFan - (index + 1));
			}			
		}//end for loop

		indexOffset += numberOfIndicesPerFan;			

		if (stacks > 2)
		{
			GLuint stackLimit = stacks - 2;

			for (GLuint indexStack = 0; indexStack < stackLimit; ++indexStack)
			{
				elementValOffset = indexStack * slices;

				//generate the indices for the body of the sphere
				for (GLuint indexSlice = 0; indexSlice < slices; ++indexSlice)
				{
					//check if it is the last slice iteration to complete the sphere body ring
					if (indexSlice + 1 == slices)
					{
						mesh.GetIndexArray()[0 + indexOffset] = static_cast<GLushort>(closingStartVertex + elementValOffset);
						mesh.GetIndexArray()[1 + indexOffset] = static_cast<GLushort>(closingSecondVertex + elementValOffset);					
						mesh.GetIndexArray()[2 + indexOffset] = static_cast<GLushort>(closingThirdVertex + elementValOffset);
						mesh.GetIndexArray()[3 + indexOffset] = static_cast<GLushort>(closingEndVertex + elementValOffset);
					}
					else
					{
						mesh.GetIndexArray()[0 + indexOffset] = static_cast<GLushort>(startVertex + elementValOffset - indexSlice);
						mesh.GetIndexArray()[1 + indexOffset] = static_cast<GLushort>(secondVertex + elementValOffset - indexSlice);				
						mesh.GetIndexArray()[2 + indexOffset] = static_cast<GLushort>(thirdVertex + elementValOffset - indexSlice);
						mesh.GetIndexArray()[3 + indexOffset] = static_cast<GLushort>(endVertex + elementValOffset - indexSlice);
					}

					indexOffset += 4;

				}//end for loop		
			}//end for loop
		}


		//generate indices for the top base			
		for (GLuint index = 0; index < numberOfIndicesPerFan; ++index)
		{			
			//on the first iteration
			if (index == 0)
			{
				mesh.GetIndexArray()[index + indexOffset] = static_cast<GLushort>(mesh.GetNumberOfVertices() - 1);
			}
			//on the last iteration, close the fan
			else if (index + 1 == numberOfIndicesPerFan)
			{
				mesh.GetIndexArray()[index + indexOffset] = static_cast<GLushort>((mesh.GetNumberOfVertices() - 1) - this->m_slices);
			}
			//on subsequent iterations
			else
			{
				mesh.GetIndexArray()[index + indexOffset] = static_cast<GLushort>(((mesh.GetNumberOfVertices() - 1) - this->m_slices) + (index - 1));
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
	void SphereBuilder::DrawGeometry( const GLuint VAO ) const
	{
		// Render object
		glBindVertexArray( VAO );

		GLuint offSetVal = 0;
		GLuint numOfFaces = this->m_slices * this->m_stacks;

		for (GLuint index = 0; index < numOfFaces; ++index)
		{
			//draw each quad face around sphere body
			glDrawElements(
				GL_TRIANGLE_STRIP, 
				4,
				GL_UNSIGNED_SHORT, 
				(GLvoid*)offSetVal);

			offSetVal += 4 * sizeof(GLushort);
		}//end for loop		
	}
	/*
	void SphereBuilder::DrawGeometry( const GLuint VAO ) const
	{
		// Render object
		glBindVertexArray( VAO );

		GLuint offSetVal = 0;
		GLuint numOfFaces = this->m_slices * (this->m_stacks - 2) + 2;
		GLuint numberOfIndicesPerFan = this->m_slices + 2;

		for (GLuint index = 0; index < numOfFaces; ++index)
		{
			//if first or last iteration
			if (index == 0 || index + 1 == numOfFaces)
			{
				//draw top and bottom
				glDrawElements(
					GL_TRIANGLE_FAN, 
					numberOfIndicesPerFan, 
					GL_UNSIGNED_SHORT, 
					(GLvoid*)offSetVal);

				offSetVal += numberOfIndicesPerFan * sizeof(GLushort);
			}
			else
			{
				//draw each quad face around sphere body
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
	void SphereBuilder::DrawGeometry( const GLuint VAO, const GLuint textureId ) const
	{
		// bind the texture name to the texture target
		glBindTexture( GL_TEXTURE_2D, textureId );

		//draw/render the geometry through the VAO
		this->DrawGeometry( VAO );
	}
	
} //end namespace GraphicsFramework