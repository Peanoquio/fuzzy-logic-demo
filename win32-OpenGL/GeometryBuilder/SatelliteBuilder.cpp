/******************************************************************************/
/*!
\file SatelliteBuilder.cpp
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

#include "SatelliteBuilder.h"
#include "../MyGeometryOM.h"


namespace GraphicsFramework
{
	/******************************************************************************/
	/*!
	The constructor for the SatelliteBuilder class
	\param matrixStack
	the matrix stack that will contain the transformation
	\param graphicsObjMap
	contains a map of graphics objects
	\param baseGeometryBuilderMap
	contains a mpa of pointers to base geometry builders
	\return
	*/
	/******************************************************************************/
	SatelliteBuilder::SatelliteBuilder( Utility::MatrixStack & matrixStack, 
		const GraphicsObjectMap graphicsObjMap, const BaseGeometryBuilderMap baseGeometryBuilderMap )
		: ComplexObjBuilder( matrixStack, graphicsObjMap, baseGeometryBuilderMap ),
		m_complexObjBuilderMap()
	{
		//declare and assemble the components of the complex object
		this->DeclareComponents();
		this->AssembleComponents();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the SatelliteBuilder class
	\param
	\return
	*/
	/******************************************************************************/
	SatelliteBuilder::~SatelliteBuilder (void)
	{
		this->DeleteComponents();
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Deallocates the components used to construct the complex object
	\param
	\return
	*/
	/******************************************************************************/
	void SatelliteBuilder::DeleteComponents( void )
	{
		ComplexObjBuilderMap::iterator itor = this->m_complexObjBuilderMap.begin();
		ComplexObjBuilderMap::iterator end = this->m_complexObjBuilderMap.end();

		//delete all the complex object builders used to construct the complex object
		//loop through each complex object builder pointer and delete it from the heap memory
		while ( itor != end )
		{			
			delete itor->second;
			itor->second = 0;
			++itor;
		}//end while loop

		this->m_complexObjBuilderMap.clear();		

		//clear the children
		this->m_children.clear();		
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Creates the component used to construct the complex object
	\param strComponentName
	the name of the component
	\return
	*/
	/******************************************************************************/
	void SatelliteBuilder::CreateComponent( const std::string strComponentName )
	{
		ComplexObjBuilder * complexObjBuilder = new ComplexObjBuilder( this->m_matrixStack, this->m_graphicsObjMap, this->m_baseGeometryBuilderMap );
		this->m_complexObjBuilderMap.insert( std::make_pair( strComponentName, complexObjBuilder ) );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the component used to construct the complex object
	\param strComponentName
	the name of the component
	\return ComplexObjBuilder *
	the pointer to the complex object builder
	*/
	/******************************************************************************/
	ComplexObjBuilder * const SatelliteBuilder::GetComponent( const std::string strComponentName ) const
	{
		return this->m_complexObjBuilderMap.find( strComponentName )->second;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Declares the complex objects that will constitute the main complex object
	\param
	\return
	*/
	/******************************************************************************/
	void SatelliteBuilder::DeclareComponents( void )
	{
		this->CreateComponent( "planet" );

		this->CreateComponent( "satelliteBody" );

		this->CreateComponent( "solarPanelMain" );
		this->CreateComponent( "solarPanelTop" );
		this->CreateComponent( "solarPanelBottom" );
		this->CreateComponent( "solarPanelShaftBeg" );
		this->CreateComponent( "solarPanelShaftMid" );
		this->CreateComponent( "solarPanelShaftEnd" );
		this->CreateComponent( "solarPanelBarBeg" );
		this->CreateComponent( "solarPanelBarMid" );
		this->CreateComponent( "solarPanelBarEnd" );
		this->CreateComponent( "solarPanelBarEnd2" );

		this->CreateComponent( "radarReceiver" );
		this->CreateComponent( "radarAntenna" );
		this->CreateComponent( "radarDish" );
		this->CreateComponent( "radarShaft1" );
		this->CreateComponent( "radarShaft2" );
		this->CreateComponent( "radarJoint1" );
		this->CreateComponent( "radarJoint2" );
		this->CreateComponent( "radarBase" );

		this->CreateComponent( "thruster" );
		this->CreateComponent( "thrusterCap1" );
		this->CreateComponent( "thrusterCap2" );
		this->CreateComponent( "thrusterCap3" );
		this->CreateComponent( "thrusterCap4" );

		this->CreateComponent( "hatch" );
		this->CreateComponent( "hatchFrame1" );
		this->CreateComponent( "hatchFrame2" );
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Updates the behavior of the geometries for animation
	\param
	\return
	*/
	/******************************************************************************/
	void SatelliteBuilder::UpdateBehavior( float dt ) const
	{
		Math::Mtx44 rotateMtx;
		Math::Mtx44 rotateMtx2;
		Math::Mtx44 rotateMtx3;

		static float spin = 0.0F;
		static float spin2 = 360.0F;
		static float swing = 0.0F;	
		static bool swingBool = true;

		const float speed = 5.0F;
		const float speed2 = 30.0F;

		//spin CW
		spin += speed * dt;
		if (spin > 360.0F )
		{
			spin -= 360.0F;
		}	

		//spin CCW
		spin2 -= speed2 * dt;
		if (spin2 < 0.0F )
		{
			spin2 += 360.0F;
		}

		//swing back and forth
		if (swing >= 45.0F )
		{
			swingBool = false;
		} 
		else if (swing  <= -45.0F )
		{
			swingBool = true;
		}		
		
		if (swingBool == true)
		{
			swing += speed2 * dt;
		}
		else
		{
			swing -= speed2 * dt;
		}

		//PLANET		
		rotateMtx.SetToRotationDegreesY( spin );
		rotateMtx2.SetToRotationDegreesX( spin );
		rotateMtx3.SetToRotationDegreesZ( spin );
		this->GetComponent( "planet" )->SetCascadeTransformForAnimation( rotateMtx3 * rotateMtx2 * rotateMtx );	

		//SATELLITE
		rotateMtx.SetToRotationDegreesY( spin2 );
		this->GetComponent( "satelliteBody" )->SetCascadeTransformForAnimation( rotateMtx );

		//SOLAR PANEL BAR END
		rotateMtx.SetToRotationDegreesX( spin2 );
		this->GetComponent( "solarPanelBarEnd" )->SetCascadeTransformForAnimation( rotateMtx );

		//SOLAR PANEL BAR END 2
		rotateMtx.SetToRotationDegreesX( spin2 );
		this->GetComponent( "solarPanelBarEnd2" )->SetCascadeTransformForAnimation (rotateMtx);

		//RADAR JOINT 1
		rotateMtx.SetToRotationDegreesX( swing );
		this->GetComponent( "radarJoint1" )->SetCascadeTransformForAnimation( rotateMtx );

		//RADAR JOINT 2
		rotateMtx.SetToRotationDegreesX( -swing );
		this->GetComponent( "radarJoint2" )->SetCascadeTransformForAnimation( rotateMtx );
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Assembles the complex objects that will constitute the main complex object
	\param
	\return
	*/
	/******************************************************************************/
	void SatelliteBuilder::AssembleComponents( void )
	{
		Math::Mtx44 parentLocalMatrix;
		parentLocalMatrix.SetToIdentity();
		Math::Mtx44 parentCascadeMatrix;
		parentCascadeMatrix.SetToIdentity();

		Math::Mtx44 translateMtx;
		Math::Mtx44 rotateMtx;
		Math::Mtx44 rotateMtx2;
		Math::Mtx44 scaleMtx;		


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//RADAR RECEIVER
		//parent
		scaleMtx.SetToScale ( 0.15F, 0.15F, 0.15F );
		parentLocalMatrix = scaleMtx;
		this->GetComponent( "radarReceiver" )->SetObjectType( MyGeometryGame::SPHERE3_OBJTYPE, parentLocalMatrix );

		//RADAR ANTENNA
		//parent
		scaleMtx.SetToScale ( 0.15F, 0.65F, 0.15F );
		parentLocalMatrix = scaleMtx;
		this->GetComponent( "radarAntenna" )->SetObjectType( MyGeometryGame::CONE_OBJTYPE, parentLocalMatrix );
		//child
		translateMtx.SetToTranslation ( 0.0F, 0.35F, 0.0F );
		this->GetComponent( "radarAntenna" )->AddChild( this->GetComponent( "radarReceiver" ), translateMtx );

		//RADAR DISH
		//parent
		scaleMtx.SetToScale ( 1.25F, 0.1F, 1.25F );
		parentLocalMatrix = scaleMtx;
		this->GetComponent( "radarDish" )->SetObjectType( MyGeometryGame::SPHERE3_OBJTYPE, parentLocalMatrix );
		//child
		this->GetComponent( "radarDish" )->AddChild( this->GetComponent( "radarAntenna" ) );

		//RADAR JOINT 1
		//parent
		scaleMtx.SetToScale ( 0.35F, 0.35F, 0.35F );
		parentLocalMatrix = scaleMtx;
		this->GetComponent( "radarJoint1" )->SetObjectType( MyGeometryGame::SPHERE2_OBJTYPE, parentLocalMatrix );
		//child
		translateMtx.SetToTranslation ( 0.0F, 0.4F, 0.0F );
		this->GetComponent( "radarJoint1" )->AddChild( this->GetComponent( "radarDish" ), translateMtx );

		//RADAR SHAFT 1
		//parent
		scaleMtx.SetToScale ( 0.15F, 0.5F, 0.15F );
		parentLocalMatrix = scaleMtx;
		this->GetComponent( "radarShaft1" )->SetObjectType( MyGeometryGame::CYLINDER2_OBJTYPE, parentLocalMatrix );
		//child	
		translateMtx.SetToTranslation ( 0.0F, 0.35F, 0.0F );
		this->GetComponent( "radarShaft1" )->AddChild( this->GetComponent( "radarJoint1" ), translateMtx );

		//RADAR JOINT 2
		//parent
		scaleMtx.SetToScale ( 0.25F, 0.25F, 0.25F );
		parentLocalMatrix = scaleMtx;
		this->GetComponent( "radarJoint2" )->SetObjectType( MyGeometryGame::SPHERE2_OBJTYPE, parentLocalMatrix );
		//child
		rotateMtx.SetToRotationDegreesX ( 45.0F );
		translateMtx.SetToTranslation ( 0.0F, 0.35F, 0.0F );
		parentCascadeMatrix = translateMtx * rotateMtx;
		this->GetComponent( "radarJoint2" )->AddChild( this->GetComponent( "radarShaft1" ), parentCascadeMatrix );

		//RADAR SHAFT 2
		//parent
		scaleMtx.SetToScale ( 0.15F, 0.5F, 0.15F );
		parentLocalMatrix = scaleMtx;
		this->GetComponent( "radarShaft2" )->SetObjectType( MyGeometryGame::CYLINDER2_OBJTYPE, parentLocalMatrix );
		//child	
		translateMtx.SetToTranslation ( 0.0F, 0.4F, 0.0F );
		this->GetComponent( "radarShaft2" )->AddChild( this->GetComponent( "radarJoint2" ), translateMtx );

		//RADAR BASE
		//parent
		scaleMtx.SetToScale ( 0.5F, 0.5F, 0.5F );
		parentLocalMatrix = scaleMtx;
		this->GetComponent( "radarBase" )->SetObjectType( MyGeometryGame::SPHERE3_OBJTYPE, parentLocalMatrix );
		//child
		translateMtx.SetToTranslation ( 0.0F, 1.0F, 0.0F );
		this->GetComponent( "radarBase" )->AddChild( this->GetComponent( "radarShaft2" ), translateMtx );


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//SOLAR PANEL TOP
		//parent
		scaleMtx.SetToScale ( 0.05F, 1.0F, 1.0F );
		rotateMtx.SetToRotationDegreesZ ( 40.0F );
		translateMtx.SetToTranslation ( -0.32F, 1.0F, 0.0F );
		parentLocalMatrix = translateMtx * rotateMtx * scaleMtx;
		this->GetComponent( "solarPanelTop" )->SetObjectType( MyGeometryGame::CUBE2_OBJTYPE, parentLocalMatrix );

		//SOLAR PANEL BOTTOM
		//parent
		scaleMtx.SetToScale ( 0.05F, 1.0F, 1.0F );
		rotateMtx.SetToRotationDegreesZ ( -40.0F );
		translateMtx.SetToTranslation ( -0.32F, -1.0F, 0.0F );
		parentLocalMatrix = translateMtx * rotateMtx * scaleMtx;
		this->GetComponent( "solarPanelBottom" )->SetObjectType( MyGeometryGame::CUBE2_OBJTYPE, parentLocalMatrix );

		//SOLAR PANEL MAIN
		//parent
		scaleMtx.SetToScale ( 0.05F, 1.25F, 1.0F );
		parentLocalMatrix = scaleMtx;
		this->GetComponent( "solarPanelMain" )->SetObjectType( MyGeometryGame::CUBE2_OBJTYPE, parentLocalMatrix );
		//child
		this->GetComponent( "solarPanelMain" )->AddChild( this->GetComponent( "solarPanelTop" ) );
		this->GetComponent( "solarPanelMain" )->AddChild( this->GetComponent( "solarPanelBottom" ) );

		//SOLAR PANEL SHAFT BEGIN
		//parent
		scaleMtx.SetToScale ( 0.25F, 0.4F, 0.25F );
		translateMtx.SetToTranslation ( 0.0F, 0.65F, 0.0F );		
		parentLocalMatrix = translateMtx * scaleMtx;
		this->GetComponent( "solarPanelShaftBeg" )->SetObjectType( MyGeometryGame::CYLINDER3_OBJTYPE, parentLocalMatrix );
		//child
		this->GetComponent( "solarPanelShaftBeg" )->AddChild( this->GetComponent( "solarPanelMain" ) );

		//SOLAR PANEL SHAFT MID
		//parent
		scaleMtx.SetToScale ( 0.15F, 1.0F, 0.15F );
		translateMtx.SetToTranslation ( 0.0F, 0.0F, 0.0F );		
		parentLocalMatrix = translateMtx * scaleMtx;
		this->GetComponent( "solarPanelShaftMid" )->SetObjectType( MyGeometryGame::CYLINDER2_OBJTYPE, parentLocalMatrix );
		//child
		this->GetComponent( "solarPanelShaftMid" )->AddChild( this->GetComponent( "solarPanelShaftBeg" ) );

		//SOLAR PANEL SHAFT END
		//parent
		scaleMtx.SetToScale ( 0.25F, 0.4F, 0.25F );
		translateMtx.SetToTranslation ( 0.0F, -0.65F, 0.0F );		
		parentLocalMatrix = translateMtx * scaleMtx;
		this->GetComponent( "solarPanelShaftEnd" )->SetObjectType( MyGeometryGame::CYLINDER3_OBJTYPE, parentLocalMatrix );
		//child
		this->GetComponent( "solarPanelShaftEnd" )->AddChild( this->GetComponent( "solarPanelShaftMid" ) );

		//SOLAR PANEL BAR BEGIN
		//parent
		scaleMtx.SetToScale ( 0.25F, 0.4F, 0.25F );
		rotateMtx.SetToRotationDegreesZ ( 90.0F );
		translateMtx.SetToTranslation ( 0.05F, 0.0F, 0.0F );		
		parentLocalMatrix = translateMtx * rotateMtx * scaleMtx;
		this->GetComponent( "solarPanelBarBeg" )->SetObjectType( MyGeometryGame::CYLINDER3_OBJTYPE, parentLocalMatrix );
		//child
		this->GetComponent( "solarPanelBarBeg" )->AddChild( this->GetComponent( "solarPanelShaftEnd" ) );

		//SOLAR PANEL BAR MID
		//parent
		scaleMtx.SetToScale ( 0.15F, 1.0F, 0.15F );
		rotateMtx.SetToRotationDegreesZ ( 90.0F );
		translateMtx.SetToTranslation ( 0.5F, 0.0F, 0.0F );		
		parentLocalMatrix = translateMtx * rotateMtx * scaleMtx;
		this->GetComponent( "solarPanelBarMid" )->SetObjectType( MyGeometryGame::CYLINDER2_OBJTYPE, parentLocalMatrix );
		//child
		this->GetComponent( "solarPanelBarMid" )->AddChild( this->GetComponent( "solarPanelBarBeg" ) );

		//SOLAR PANEL BAR END
		//parent
		scaleMtx.SetToScale ( 0.25F, 0.4F, 0.25F );
		rotateMtx.SetToRotationDegreesZ ( 90.0F );
		translateMtx.SetToTranslation ( 1.0F, 0.0F, 0.0F );
		parentLocalMatrix = translateMtx * rotateMtx * scaleMtx;
		this->GetComponent( "solarPanelBarEnd" )->SetObjectType( MyGeometryGame::CYLINDER3_OBJTYPE, parentLocalMatrix );
		//child
		translateMtx.SetToTranslation ( -1.75F, 0.0F, 0.0F );
		parentCascadeMatrix = translateMtx;
		this->GetComponent( "solarPanelBarEnd" )->AddChild( this->GetComponent( "solarPanelBarMid" ), parentCascadeMatrix );

		//SOLAR PANEL BAR END 2
		//parent
		scaleMtx.SetToScale ( 0.25F, 0.4F, 0.25F );
		rotateMtx.SetToRotationDegreesZ ( 90.0F );
		translateMtx.SetToTranslation ( 1.0F, 0.0F, 0.0F );
		parentLocalMatrix = translateMtx * rotateMtx * scaleMtx;
		this->GetComponent( "solarPanelBarEnd2" )->SetObjectType( MyGeometryGame::CYLINDER3_OBJTYPE, parentLocalMatrix );
		//child
		rotateMtx.SetToRotationDegreesY ( 180.0F );
		translateMtx.SetToTranslation ( 1.75F, 0.0F, 0.0F );
		parentCascadeMatrix = translateMtx * rotateMtx;
		this->GetComponent( "solarPanelBarEnd2" )->AddChild( this->GetComponent( "solarPanelBarMid" ), parentCascadeMatrix );


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//get the degrees per angle based on the number of thrusters
		GLfloat degreesPerAngle = Math::REVOLUTION_DEGREES / 4;	
		//compute for the corresponding radian value of the degree angle
		GLfloat radianVal = Math::DegreeToRadian(degreesPerAngle);
		GLfloat tempRadianVal = 0.0F;
		GLfloat radius = 0.3F;

		//THRUSTER
		//parent
		scaleMtx.SetToScale ( 0.25F, 0.25F, 0.25F );
		translateMtx.SetToTranslation ( 0.0F, -0.35F, 0.0F );
		parentLocalMatrix = translateMtx * scaleMtx;
		this->GetComponent( "thruster" )->SetObjectType( MyGeometryGame::CYLINDER3_OBJTYPE, parentLocalMatrix );

		//THRUSTER CAP 1
		//parent
		scaleMtx.SetToScale ( 0.65F, 0.65F, 0.65F );
		this->GetComponent( "thrusterCap1" )->SetObjectType( MyGeometryGame::CONE_OBJTYPE, scaleMtx );
		//child
		rotateMtx.SetToRotationDegreesZ ( 45.0F );
		rotateMtx2.SetToRotationDegreesY ( 315.0F );
		translateMtx.SetToTranslation( (sin(tempRadianVal) * radius), -0.75F, (cos(tempRadianVal) * radius));
		parentCascadeMatrix = translateMtx * rotateMtx2 * rotateMtx;
		this->GetComponent( "thrusterCap1" )->AddChild( this->GetComponent( "thruster" ), parentCascadeMatrix );

		//increment the degree of the angle
		tempRadianVal += radianVal;	

		//THRUSTER CAP 2
		//parent
		scaleMtx.SetToScale ( 0.65F, 0.65F, 0.65F );
		this->GetComponent( "thrusterCap2" )->SetObjectType( MyGeometryGame::CONE_OBJTYPE, scaleMtx );
		//child
		rotateMtx.SetToRotationDegreesZ ( 45.0F );
		rotateMtx2.SetToRotationDegreesY ( 45.0F );
		translateMtx.SetToTranslation( (sin(tempRadianVal) * radius), -0.75F, (cos(tempRadianVal) * radius));
		parentCascadeMatrix = translateMtx * rotateMtx2 * rotateMtx;
		this->GetComponent( "thrusterCap2" )->AddChild( this->GetComponent( "thruster" ), parentCascadeMatrix );

		//increment the degree of the angle
		tempRadianVal += radianVal;

		//THRUSTER CAP 3
		//parent
		scaleMtx.SetToScale ( 0.65F, 0.65F, 0.65F );
		this->GetComponent( "thrusterCap3" )->SetObjectType( MyGeometryGame::CONE_OBJTYPE, scaleMtx );
		//child
		rotateMtx.SetToRotationDegreesZ ( 45.0F );
		rotateMtx2.SetToRotationDegreesY ( 135.0F );
		translateMtx.SetToTranslation( (sin(tempRadianVal) * radius), -0.75F, (cos(tempRadianVal) * radius));
		parentCascadeMatrix = translateMtx * rotateMtx2 * rotateMtx;
		this->GetComponent( "thrusterCap3" )->AddChild( this->GetComponent( "thruster" ), parentCascadeMatrix );

		//increment the degree of the angle
		tempRadianVal += radianVal;

		//THRUSTER CAP 4
		//parent
		scaleMtx.SetToScale ( 0.65F, 0.65F, 0.65F );
		this->GetComponent( "thrusterCap4" )->SetObjectType( MyGeometryGame::CONE_OBJTYPE, scaleMtx );
		//child
		rotateMtx.SetToRotationDegreesZ ( 45.0F );
		rotateMtx2.SetToRotationDegreesY ( 225.0F );
		translateMtx.SetToTranslation( (sin(tempRadianVal) * radius), -0.75F, (cos(tempRadianVal) * radius));
		parentCascadeMatrix = translateMtx * rotateMtx2 * rotateMtx;
		this->GetComponent( "thrusterCap4" )->AddChild( this->GetComponent( "thruster" ), parentCascadeMatrix );
		

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//HATCH
		//parent
		scaleMtx.SetToScale ( 0.5F, 0.5F, 0.5F );
		translateMtx.SetToTranslation ( 0.0F, 0.0F, 0.25F );
		parentLocalMatrix = translateMtx * scaleMtx;
		this->GetComponent( "hatch" )->SetObjectType( MyGeometryGame::SPHERE3_OBJTYPE, parentLocalMatrix );

		//HATCH FRAME 1
		//parent
		scaleMtx.SetToScale ( 0.65F, 1.0F, 0.65F );
		parentLocalMatrix = scaleMtx;
		this->GetComponent( "hatchFrame1" )->SetObjectType( MyGeometryGame::CYLINDER3_OBJTYPE, parentLocalMatrix );
		//child
		translateMtx.SetToTranslation ( 0.0F, 0.0F, 0.75F );
		//hatchFrame1->AddChildObject (hatch, translateMtx);
		this->GetComponent( "hatchFrame1" )->AddChild( this->GetComponent( "hatch" ), translateMtx );

		//HATCH FRAME 2
		//parent
		scaleMtx.SetToScale ( 0.65F, 1.0F, 0.65F );
		parentLocalMatrix = scaleMtx;
		this->GetComponent( "hatchFrame2" )->SetObjectType( MyGeometryGame::CYLINDER3_OBJTYPE, parentLocalMatrix );
		//child
		rotateMtx.SetToRotationDegreesY ( 180.0F );
		translateMtx.SetToTranslation ( 0.0F, 0.0F, -0.75F );
		parentCascadeMatrix = translateMtx * rotateMtx;
		this->GetComponent( "hatchFrame2" )->AddChild( this->GetComponent( "hatch" ), parentCascadeMatrix );


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//SATELLITE BODY
		//parent
		scaleMtx.SetToScale ( 1.5F, 2.0F, 1.5F );		
		this->GetComponent( "satelliteBody" )->SetObjectType( MyGeometryGame::HEXASPHERE_OBJTYPE, scaleMtx );
		//child
		scaleMtx.SetToScale ( 0.5F, 0.5F, 0.5F );
		translateMtx.SetToTranslation ( 2.5F, 0.0F, 0.0F );
		parentCascadeMatrix = translateMtx * scaleMtx;
		this->GetComponent( "satelliteBody" )->AddChild( this->GetComponent( "solarPanelBarEnd" ), parentCascadeMatrix );
		this->GetComponent( "satelliteBody" )->AddChild( this->GetComponent( "solarPanelBarEnd2" ) );
		this->GetComponent( "satelliteBody" )->AddChild( this->GetComponent( "radarBase" ) );
		this->GetComponent( "satelliteBody" )->AddChild( this->GetComponent( "thrusterCap1" ) );
		this->GetComponent( "satelliteBody" )->AddChild( this->GetComponent( "thrusterCap2" ) );
		this->GetComponent( "satelliteBody" )->AddChild( this->GetComponent( "thrusterCap3" ) );
		this->GetComponent( "satelliteBody" )->AddChild( this->GetComponent( "thrusterCap4" ) );
		this->GetComponent( "satelliteBody" )->AddChild( this->GetComponent( "hatchFrame1" ) );
		this->GetComponent( "satelliteBody" )->AddChild( this->GetComponent( "hatchFrame2" ) );

		//PLANET
		//parent
		scaleMtx.SetToScale ( 1.5F, 1.5F, 1.5F );
		this->GetComponent( "planet" )->SetObjectType( MyGeometryGame::SPHERE_OBJTYPE, scaleMtx );
		//child		
		this->GetComponent( "planet" )->AddChild( this->GetComponent( "satelliteBody" ) );


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		this->m_objectType = MyGeometryGame::SATELLITE_OBJTYPE;
		//this->m_baseGeometryBuilderPtr = this;
		this->AddChild( this->GetComponent( "planet" ) );
	}	

} //end namespace GraphicsFramework