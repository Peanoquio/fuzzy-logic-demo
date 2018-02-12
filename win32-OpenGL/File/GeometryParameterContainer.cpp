/******************************************************************************/
/*!
\file GeometryParameterContainer.cpp
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
This file will contain the parameters for creating geometries

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


#include "GeometryParameterContainer.h"


namespace File
{
	/******************************************************************************/
	/*!
	The constructor for the GeometryParameterContainer class
	\param
	\return
	*/
	/******************************************************************************/
	GeometryParameterContainer::GeometryParameterContainer (void)
		: m_slices(0), m_stacks(0), m_xSubdivisions(0), m_ySubdivisions(0), m_width(0.0F), m_height(0.0F),	
		m_radius(0.0F), m_verticalPos(0.0F), m_centerVerticalPos(0.0F), m_hasCenterPoint(GL_TRUE),
		m_red(0), m_green(0), m_blue(0), m_alpha(255)
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	The destructor for the GeometryParameterContainer class
	\param
	\return
	*/
	/******************************************************************************/
	GeometryParameterContainer::~GeometryParameterContainer (void)
	{
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the number of slices of the mesh
	\param
	\return GLuint
	the number of slices of the mesh
	*/
	/******************************************************************************/
	const GLuint GeometryParameterContainer::GetSlices (void) const
	{
		return this->m_slices;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the number of stacks of the mesh
	\param
	\return GLuint
	the number of stacks of the mesh
	*/
	/******************************************************************************/
	const GLuint GeometryParameterContainer::GetStacks (void) const
	{
		return this->m_stacks;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the number of X subdivisions of the mesh
	\param
	\return GLuint
	the number of X subdivisions of the mesh
	*/
	/******************************************************************************/
	const GLuint GeometryParameterContainer::GetXSubdivisions (void) const
	{
		return this->m_xSubdivisions;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the number of Y subdivisions of the mesh
	\param
	\return GLuint
	the number of Y subdivisions of the mesh
	*/
	/******************************************************************************/
	const GLuint GeometryParameterContainer::GetYSubdivisions (void) const
	{
		return this->m_ySubdivisions;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the width of the mesh
	\param
	\return GLfloat
	the width of the mesh
	*/
	/******************************************************************************/
	const GLfloat GeometryParameterContainer::GetWidth (void) const
	{
		return this->m_width;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the height of the mesh
	\param
	\return GLfloat
	the height of the mesh
	*/
	/******************************************************************************/
	const GLfloat GeometryParameterContainer::GetHeight (void) const
	{
		return this->m_height;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the radius of the mesh
	\param
	\return GLfloat
	the radius of the mesh
	*/
	/******************************************************************************/
	const GLfloat GeometryParameterContainer::GetRadius (void) const
	{
		return this->m_radius;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the vertical position of the vertices that rings around the mesh
	\param
	\return GLfloat
	the vertical position of the vertices that rings around the mesh
	*/
	/******************************************************************************/
	const GLfloat GeometryParameterContainer::GetVerticalPosition (void) const
	{
		return this->m_verticalPos;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the vertical position of the central vertices of the mesh
	\param
	\return GLfloat
	the vertical position of the central vertices of the mesh
	*/
	/******************************************************************************/
	const GLfloat GeometryParameterContainer::GetCenterVerticalPosition (void) const
	{
		return this->m_centerVerticalPos;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Indicates whether the geometry has a central point on its base
	\param
	\return GLboolean
	the indicator whether the geometry has a central point on its base
	*/
	/******************************************************************************/
	const GLboolean GeometryParameterContainer::GetHasCenterPoint (void) const
	{
		return this->m_hasCenterPoint;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Indicates whether the geometry plane normal will be inverted
	\param
	\return GLboolean
	the indicator whether the geometry plane normal will be inverted
	*/
	/******************************************************************************/
	const GLboolean GeometryParameterContainer::GetInvertPlaneNormal (void) const
	{
		return this->m_invertPlaneNormal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the red color value of the mesh
	\param
	\return GLubyte
	the red color value of the mesh
	*/
	/******************************************************************************/
	const GLubyte GeometryParameterContainer::GetRed ( void ) const
	{
		return this->m_red;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the green color value of the mesh
	\param
	\return GLubyte
	the green color value of the mesh
	*/
	/******************************************************************************/
	const GLubyte GeometryParameterContainer::GetGreen ( void ) const
	{
		return this->m_green;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the blue color value of the mesh
	\param
	\return GLubyte
	the blue color value of the mesh
	*/
	/******************************************************************************/
	const GLubyte GeometryParameterContainer::GetBlue ( void ) const
	{
		return this->m_blue;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Gets the alpha transparency value of the mesh
	\param
	\return GLubyte
	the alpha transparency value of the mesh
	*/
	/******************************************************************************/
	const GLubyte GeometryParameterContainer::GetAlpha ( void ) const
	{
		return this->m_alpha;
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the number of slices of the mesh
	\param GLuint
	the number of slices of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetSlices ( const GLuint slices )
	{
		this->m_slices = slices;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the number of stacks of the mesh
	\param GLuint
	the number of stacks of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetStacks ( const GLuint stacks )
	{
		this->m_stacks = stacks;
	}

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the number of X subdivisions of the mesh
	\param GLuint
	the number of X subdivisions of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetXSubdivisions ( const GLuint xSubdivisions )
	{
		this->m_xSubdivisions = xSubdivisions;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the number of Y subdivisions of the mesh
	\param GLuint
	the number of Y subdivisions of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetYSubdivisions ( const GLuint ySubdivisions )
	{
		this->m_ySubdivisions = ySubdivisions;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the width of the mesh
	\param GLfloat
	the width of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetWidth ( const GLfloat width )
	{
		this->m_width = width;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the height of the mesh
	\param GLfloat
	the height of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetHeight ( const GLfloat height )
	{
		this->m_height = height;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the radius of the mesh
	\param GLfloat
	the radius of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetRadius ( const GLfloat radius )
	{
		this->m_radius = radius;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the vertical position of the vertices that rings around the mesh
	\param GLfloat
	the vertical position of the vertices that rings around the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetVerticalPosition ( const GLfloat verticalPosition )
	{
		this->m_verticalPos = verticalPosition;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the vertical position of the central vertices of the mesh
	\param GLfloat
	the vertical position of the central vertices of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetCenterVerticalPosition ( const GLfloat centerVerticalPosition )
	{
		this->m_centerVerticalPos = centerVerticalPosition;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the indicator whether the geometry has a central point on its base
	\param GLboolean
	the indicator whether the geometry has a central point on its base
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetHasCenterPoint ( const GLboolean hasCenterPoint )
	{
		this->m_hasCenterPoint = hasCenterPoint;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the indicator whether the geometry plane normal will be inverted
	\param GLboolean
	the indicator whether the geometry plane normal will be inverted
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetInvertPlaneNormal ( const GLboolean invertPlaneNormal )
	{
		this->m_invertPlaneNormal = invertPlaneNormal;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the red color value of the mesh
	\param GLubyte
	the red color value of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetRed ( const GLubyte red )
	{
		this->m_red = red;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the green color value of the mesh
	\param GLubyte
	the green color value of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetGreen ( const GLubyte green )
	{
		this->m_green = green;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the blue color value of the mesh
	\param GLubyte
	the blue color value of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetBlue ( const GLubyte blue )
	{
		this->m_blue = blue;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*!
	Sets the alpha transparency value of the mesh
	\param GLubyte
	the alpha transparency value of the mesh
	\return
	*/
	/******************************************************************************/
	void GeometryParameterContainer::SetAlpha ( const GLubyte alpha )
	{
		this->m_alpha = alpha;
	}


} //end namespace File