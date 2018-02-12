/******************************************************************************/
/*!
\file ComplexObjBuilder.h
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

////////////////////////////////////////////////////////////////////////////////
#ifndef COMPLEX_OBJ_BUILDER_H
#define COMPLEX_OBJ_BUILDER_H
////////////////////////////////////////////////////////////////////////////////

#include "BaseGeometryBuilder.h"
#include "../Utility/MatrixStack.h"
#include "../Graphics/GraphicsObj.h"
#include <unordered_map>
#include <hash_map>


namespace GraphicsFramework
{
	typedef std::unordered_map< const unsigned, GraphicsObject > GraphicsObjectMap;
	typedef std::unordered_map< const unsigned, BaseGeometryBuilder * > BaseGeometryBuilderMap;


	class ComplexObjBuilder : public BaseGeometryBuilder
	{
	public:
		ComplexObjBuilder( Utility::MatrixStack & matrixStack, const GraphicsObjectMap graphicsObjMap, const BaseGeometryBuilderMap	baseGeometryBuilderMap );
		virtual ~ComplexObjBuilder( void );

		//copy constructor
		ComplexObjBuilder( const ComplexObjBuilder & rhsComplexObjBuilder );
		//overloaded assignment operator
		ComplexObjBuilder & operator=( const ComplexObjBuilder & rhsComplexObjBuilder );

		virtual void DrawGeometry( const GLuint VAO ) const;
		virtual void DrawGeometry( const GLuint VAO, const GLuint textureId ) const;

		virtual void ComputeGeometryBoundaryAndOffset( const MeshParameterContainer & meshParameterContainer );
		virtual void LoadGeometryVertices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer );
		virtual void GenerateGeometryIndices( Mesh & mesh, const MeshParameterContainer & meshParameterContainer );
		
		virtual void UpdateBehavior( float dt ) const;

		void SetObjectType( const unsigned objectType );
		void SetObjectType( const unsigned objectType, const Math::Mtx44 & parentLocalTransform );
		void AddChild( const ComplexObjBuilder * const complexObjBuilderPtr );
		void AddChild( const ComplexObjBuilder * const complexObjBuilderPtr, const Math::Mtx44 & parentGlobalCascadeTransform );

		void SetCascadeTransformForAnimation( const Math::Mtx44 & parentGlobalCascadeTransformForAnimation );
		void SetLocalTransformForAnimation( const Math::Mtx44 & parentLocalTransformForAnimation );		

	protected:
		GraphicsObjectMap							m_graphicsObjMap;
		BaseGeometryBuilderMap						m_baseGeometryBuilderMap;			

		unsigned									m_objectType;
		GLuint										m_VAO;
		GLuint										m_textureId;
		BaseGeometryBuilder *						m_baseGeometryBuilderPtr;
		std::vector< const ComplexObjBuilder * >	m_children;

		Utility::MatrixStack &						m_matrixStack;
		Math::Mtx44									m_parentGlobalCascadeTransform;
		Math::Mtx44									m_parentLocalTransform;
		Math::Mtx44									m_parentGlobalCascadeTransformForAnimation;
		Math::Mtx44									m_parentLocalTransformForAnimation;
	};

} // namespace GraphicsFramework

#endif
////////////////////////////////////////////////////////////////////////////////