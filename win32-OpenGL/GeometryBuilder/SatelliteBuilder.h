/******************************************************************************/
/*!
\file SatelliteBuilder.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 02/01/2012
\brief
This file will create the animated satellite complex object

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
#ifndef SATELLITE_BUILDER_H
#define SATELLITE_BUILDER_H
////////////////////////////////////////////////////////////////////////////////

#include "ComplexObjBuilder.h"
#include <hash_map>


namespace GraphicsFramework
{
	typedef std::hash_map< const std::string, ComplexObjBuilder * > ComplexObjBuilderMap;

	class SatelliteBuilder : public ComplexObjBuilder
	{
	public:
		SatelliteBuilder( Utility::MatrixStack & matrixStack, const GraphicsObjectMap graphicsObjMap, const BaseGeometryBuilderMap baseGeometryBuilderMap );
		virtual ~SatelliteBuilder( void );

		virtual void UpdateBehavior( float dt ) const;

	private:	
		ComplexObjBuilderMap m_complexObjBuilderMap;

		void DeclareComponents( void );
		void AssembleComponents( void );
		void DeleteComponents( void );

		void CreateComponent( const std::string strComponentName );
		ComplexObjBuilder * const GetComponent( const std::string strComponentName ) const;
	};

} // namespace GraphicsFramework


#endif
////////////////////////////////////////////////////////////////////////////////