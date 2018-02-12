/******************************************************************************/
/*!
\file ComplexObjBuilder.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 01/01/2012
\brief
This will serve as the base class for the complex object builder.
It contains functions that will construct a hierarchical model.
It also contains functions to perform transformations for animation.

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

#include "ComplexObjBuilder.h"


namespace GraphicsFramework
{
	/******************************************************************************/
	/*!
	The constructor for the ComplexObjBuilder class
	\param matrixStack
	the matrixStack that contains the transformations
	\param graphicsObjMap
	contains a map of graphics objects
	\param baseGeometryBuilderMap
	contains a mpa of pointers to base geometry builders
	\return
	*/
	/******************************************************************************/
	ComplexObjBuilder::ComplexObjBuilder( Utility::MatrixStack & matrixStack, 
		const GraphicsObjectMap graphicsObjMap, const BaseGeometryBuilderMap baseGeometryBuilderMap )
		: m_graphicsObjMap( graphicsObjMap ),
		m_baseGeometryBuilderMap( baseGeometryBuilderMap ),
		m_objectType( 0 ),
		m_VAO( 0 ),
		m_textureId( 0 ),
		m_baseGeometryBuilderPtr( 0 ),
		m_children(),
		m_matrixStack( matrixStack ),
		m_parentGlobalCascadeTransform(),
		m_parentLocalTransform(),
		m_parentGlobalCascadeTransformForAnimation(),
		m_parentLocalTransformForAnimation()
	{
		//initialize into identity matrix
		this->m_parentGlobalCascadeTransform.SetToIdentity();
		this->m_parentLocalTransform.SetToIdentity();

		this->m_parentGlobalCascadeTransformForAnimation.SetToIdentity();
		this->m_parentLocalTransformForAnimation.SetToIdentity();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the ComplexObjBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	ComplexObjBuilder::~ComplexObjBuilder (void)
	{		
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The copy constructor for the ComplexObjBuilder class
	\param rhsComplexObjBuilder
	the complex object builder to be copied
	\return
	*/
	/******************************************************************************/
	ComplexObjBuilder::ComplexObjBuilder( const ComplexObjBuilder & rhsComplexObjBuilder )
		: m_graphicsObjMap( rhsComplexObjBuilder.m_graphicsObjMap ),
		m_baseGeometryBuilderMap( rhsComplexObjBuilder.m_baseGeometryBuilderMap ),
		m_objectType( rhsComplexObjBuilder.m_objectType ),
		m_VAO( rhsComplexObjBuilder.m_VAO ),
		m_textureId( rhsComplexObjBuilder.m_textureId ),
		m_baseGeometryBuilderPtr( rhsComplexObjBuilder.m_baseGeometryBuilderPtr ),
		m_children( rhsComplexObjBuilder.m_children ),
		m_matrixStack( rhsComplexObjBuilder.m_matrixStack ),
		m_parentGlobalCascadeTransform( rhsComplexObjBuilder.m_parentGlobalCascadeTransform ),
		m_parentLocalTransform( rhsComplexObjBuilder.m_parentLocalTransform ),
		m_parentGlobalCascadeTransformForAnimation( rhsComplexObjBuilder.m_parentGlobalCascadeTransformForAnimation ),
		m_parentLocalTransformForAnimation( rhsComplexObjBuilder.m_parentLocalTransformForAnimation )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The overloaded assignment operator for the ComplexObjBuilder class
	\param rhsComplexObjBuilder
	the complex object builder to be copied
	\return
	*/
	/******************************************************************************/
	ComplexObjBuilder & ComplexObjBuilder::operator=(const ComplexObjBuilder & rhsComplexObjBuilder )
	{
		//check for self-assignment
		if ( this != &rhsComplexObjBuilder )
		{
			//clear the vector containing the children
			this->m_children.clear();

			//copy the values
			this->m_graphicsObjMap = rhsComplexObjBuilder.m_graphicsObjMap;
			this->m_baseGeometryBuilderMap = rhsComplexObjBuilder.m_baseGeometryBuilderMap;

			this->m_objectType = rhsComplexObjBuilder.m_objectType;
			this->m_VAO = rhsComplexObjBuilder.m_VAO;
			this->m_textureId = rhsComplexObjBuilder.m_textureId;
			this->m_baseGeometryBuilderPtr = rhsComplexObjBuilder.m_baseGeometryBuilderPtr;
			this->m_children = rhsComplexObjBuilder.m_children;

			this->m_matrixStack = rhsComplexObjBuilder.m_matrixStack;
			this->m_parentGlobalCascadeTransform = rhsComplexObjBuilder.m_parentGlobalCascadeTransform;
			this->m_parentLocalTransform = rhsComplexObjBuilder.m_parentLocalTransform;
			this->m_parentGlobalCascadeTransformForAnimation = rhsComplexObjBuilder.m_parentGlobalCascadeTransformForAnimation;
			this->m_parentLocalTransformForAnimation = rhsComplexObjBuilder.m_parentLocalTransformForAnimation;
		}

		return *this;
	}	


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the object type of the parent
	\param objectType
	the object type
	\return
	*/
	/******************************************************************************/
	void ComplexObjBuilder::SetObjectType( const unsigned objectType )
	{
		//store the object type
		this->m_objectType = objectType;

		//set the VAO based on the object type
		this->m_VAO = this->m_graphicsObjMap.find( this->m_objectType )->second.GetNameOfVAO();
		//set the texture id
		this->m_textureId = this->m_graphicsObjMap.find( this->m_objectType )->second.GetTextureId( 0 );
		//set the base geoemetry pointer based on the object type
		this->m_baseGeometryBuilderPtr = this->m_baseGeometryBuilderMap.find( this->m_objectType )->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the object type of the parent and apply a local transform
	\param objectType
	the object type
	\param parentLocalTransform
	the local transformation that will apply to the parent
	\return
	*/
	/******************************************************************************/
	void ComplexObjBuilder::SetObjectType( const unsigned objectType, const Math::Mtx44 & parentLocalTransform )
	{
		//store the object type
		this->m_objectType = objectType;
		//store the matrix transforms
		this->m_parentLocalTransform = parentLocalTransform;

		//set the VAO based on the object type
		this->m_VAO = this->m_graphicsObjMap.find( this->m_objectType )->second.GetNameOfVAO();
		//set the texture id
		this->m_textureId = this->m_graphicsObjMap.find( this->m_objectType )->second.GetTextureId( 0 );
		//set the base geoemetry pointer based on the object type
		this->m_baseGeometryBuilderPtr = this->m_baseGeometryBuilderMap.find( this->m_objectType )->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Adds the child in the hierarchy
	\param complexObjBuilderPtr
	the child
	\return
	*/
	/******************************************************************************/
	void ComplexObjBuilder::AddChild( const ComplexObjBuilder * const complexObjBuilderPtr )
	{
		//store the child
		this->m_children.push_back( complexObjBuilderPtr );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Adds the child in the hierarchy and apply a transform that applies to the parent and cascades to the children
	\param complexObjBuilderPtr
	the child
	\param parentGlobalCascadeTransform
	the transformation that will apply to the parent and cascade to the children
	\return
	*/
	/******************************************************************************/
	void ComplexObjBuilder::AddChild( const ComplexObjBuilder * const complexObjBuilderPtr, const Math::Mtx44 & parentGlobalCascadeTransform )
	{
		//store the child
		this->m_children.push_back( complexObjBuilderPtr );	
		//store the matrix transforms
		this->m_parentGlobalCascadeTransform = parentGlobalCascadeTransform;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the transformation that applies to the parent and cascades to the children
	\param parentGlobalCascadeTransformForAnimation
	the transformation that will apply to the parent and cascade to the children
	\return
	*/
	/******************************************************************************/
	void ComplexObjBuilder::SetCascadeTransformForAnimation( const Math::Mtx44 & parentGlobalCascadeTransformForAnimation )
	{
		this->m_parentGlobalCascadeTransformForAnimation = parentGlobalCascadeTransformForAnimation;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the local transformation that applies to the parent
	\param parentLocalTransformForAnimation
	the local transformation that will apply to the parent
	\return
	*/
	/******************************************************************************/
	void ComplexObjBuilder::SetLocalTransformForAnimation( const Math::Mtx44 & parentLocalTransformForAnimation )
	{
		this->m_parentLocalTransformForAnimation = parentLocalTransformForAnimation;
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
	void ComplexObjBuilder::ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & /*meshParameterContainer*/ )
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
	void ComplexObjBuilder::LoadGeometryVertices( Mesh & /*mesh*/, const MeshParameterContainer & /*meshParameterContainer*/ )
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
	void ComplexObjBuilder::GenerateGeometryIndices( Mesh & /*mesh*/, const MeshParameterContainer & /*meshParameterContainer*/ )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Updates the behavior of the geometry for animation
	\param
	\return
	*/
	/******************************************************************************/
	void ComplexObjBuilder::UpdateBehavior( float /*dt*/ ) const
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Draws/renders the complex object by traversing through the hierarchy and performing the transformations
	\param VAO
	the Vertex Array Object
	\return
	*/
	/******************************************************************************/
	void ComplexObjBuilder::DrawGeometry( const GLuint /*VAO*/ ) const
	{
		//explicitly call OpenGL function
		glMatrixMode( GL_MODELVIEW );
		
		//set the matrix mode through the matrix stack
		this->m_matrixStack.MatrixMode( Utility::MODELVIEW );

		this->m_matrixStack.Push();

			//validate if there are children
			if ( this->m_children.size() > 0 )
			{
				//apply the parent transform that cascades to the children
				this->m_matrixStack.MultMatrix( this->m_parentGlobalCascadeTransform );
				this->m_matrixStack.MultMatrix( this->m_parentGlobalCascadeTransformForAnimation );

				//explicitly call OpenGL function to load the concatenated matrix
				glLoadMatrixf( this->m_matrixStack.Top().GetMatrixArr() );

				//loop through the child objects
				for ( GLuint index = 0; index < this->m_children.size(); ++index )
				{
					//render the child
					this->m_children[index]->DrawGeometry( this->m_children[index]->m_VAO );
					//this->m_children[index]->m_baseGeometryBuilderPtr->DrawGeometry( this->m_children[index]->m_VAO );

				}//end for loop
			}
			
			if ( this->m_baseGeometryBuilderPtr != NULL )
			{
				//this will perform the parent local transform before the cascade transform 
				//apply the parent transform locally
				this->m_matrixStack.MultMatrix( this->m_parentLocalTransform );
				this->m_matrixStack.MultMatrix( this->m_parentLocalTransformForAnimation );

				//explicitly call OpenGL function to load the concatenated matrix
				glLoadMatrixf( this->m_matrixStack.Top().GetMatrixArr() );

				//render the parent
				//this->DrawGeometry( this->m_VAO );	
				this->m_baseGeometryBuilderPtr->DrawGeometry( this->m_VAO );
			}

		this->m_matrixStack.Pop();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Draws/renders the complex object by traversing through the hierarchy and performing the transformations
	\param VAO
	the Vertex Array Object
	\param texture Id
	the texture Id
	\return
	*/
	/******************************************************************************/
	void ComplexObjBuilder::DrawGeometry( const GLuint /*VAO*/, const GLuint /*textureId*/ ) const
	{
		//explicitly call OpenGL function
		glMatrixMode( GL_MODELVIEW );
		
		//set the matrix mode through the matrix stack
		this->m_matrixStack.MatrixMode( Utility::MODELVIEW );

		this->m_matrixStack.Push();

			//validate if there are children
			if ( this->m_children.size() > 0 )
			{
				//apply the parent transform that cascades to the children
				this->m_matrixStack.MultMatrix( this->m_parentGlobalCascadeTransform );
				this->m_matrixStack.MultMatrix( this->m_parentGlobalCascadeTransformForAnimation );

				//explicitly call OpenGL function to load the concatenated matrix
				glLoadMatrixf( this->m_matrixStack.Top().GetMatrixArr() );

				//loop through the child objects
				for ( GLuint index = 0; index < this->m_children.size(); ++index )
				{
					//render the child
					this->m_children[index]->DrawGeometry( this->m_children[index]->m_VAO, this->m_children[index]->m_textureId );
					//this->m_children[index]->m_baseGeometryBuilderPtr->DrawGeometry( this->m_children[index]->m_VAO );

				}//end for loop
			}
			
			if ( this->m_baseGeometryBuilderPtr != NULL )
			{
				//this will perform the parent local transform before the cascade transform 
				//apply the parent transform locally
				this->m_matrixStack.MultMatrix( this->m_parentLocalTransform );
				this->m_matrixStack.MultMatrix( this->m_parentLocalTransformForAnimation );

				//explicitly call OpenGL function to load the concatenated matrix
				glLoadMatrixf( this->m_matrixStack.Top().GetMatrixArr() );

				//render the parent
				//this->DrawGeometry( this->m_VAO );	
				this->m_baseGeometryBuilderPtr->DrawGeometry( this->m_VAO, this->m_textureId );
			}

		this->m_matrixStack.Pop();
	}

} // namespace GraphicsFramework