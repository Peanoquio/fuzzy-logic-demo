#include "GraphicsContainer.h"


namespace GraphicsFramework
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The constructor for the GraphicsContainer class
	\param
	\return
	*/
	/******************************************************************************/
	GraphicsContainer::GraphicsContainer( void )
		: m_graphicsObj(), m_mesh(), m_baseGeometryBuilderPtr( 0 )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the GraphicsContainer class
	\param
	\return
	*/
	/******************************************************************************/
	GraphicsContainer::~GraphicsContainer( void )
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the graphics obects
	\param
	\return GraphicsObject
	the graphics object
	*/
	/******************************************************************************/
	GraphicsObject GraphicsContainer::GetGraphicsObj( void ) const
	{
		return this->m_graphicsObj;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the mesh
	\param
	\return Mesh
	the mesh
	*/
	/******************************************************************************/
	Mesh GraphicsContainer::GetMesh( void ) const
	{
		return this->m_mesh;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Get the pointer to the BaseGeometryBuilder
	\param
	\return BaseGeometryBuilder*
	the pointer to the BaseGeometryBuilder
	*/
	/******************************************************************************/
	const BaseGeometryBuilder* GraphicsContainer::GetBaseGeometryBuilder( void ) const
	{
		return this->m_baseGeometryBuilderPtr;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the graphics object
	\param graphicsObj
	the graphics object
	\return 	
	*/
	/******************************************************************************/
	void GraphicsContainer::SetGraphicsObj( const GraphicsObject & graphicsObj )
	{
		this->m_graphicsObj = graphicsObj;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the mesh
	\param mesh
	the mesh
	\return 	
	*/
	/******************************************************************************/
	void GraphicsContainer::SetMesh( const Mesh & mesh )
	{
		this->m_mesh = mesh;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Set the pointer to the BaseGeometryBuilder
	\param baseGeometryBuilderPtr
	the pointer to the BaseGeometryBuilder
	\return 	
	*/
	/******************************************************************************/
	void GraphicsContainer::SetBaseGeometryBuilder( const BaseGeometryBuilder* const baseGeometryBuilderPtr )
	{
		this->m_baseGeometryBuilderPtr = baseGeometryBuilderPtr;
	}

} //end namespace GraphicsFramework