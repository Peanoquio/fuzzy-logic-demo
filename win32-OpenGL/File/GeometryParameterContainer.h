/******************************************************************************/
/*!
\file GeometryParameterContainer.h
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


////////////////////////////////////////////////////////////////////////////////
#ifndef GEOMETRYPARAMETERCONTAINER_H
#define GEOMETRYPARAMETERCONTAINER_H
////////////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>

namespace File
{
	class GeometryParameterContainer
	{
	public:
		GeometryParameterContainer (void);
		~GeometryParameterContainer (void);

		const GLuint GetSlices (void) const;
		const GLuint GetStacks (void) const;
		const GLuint GetXSubdivisions (void) const;
		const GLuint GetYSubdivisions (void) const;
		const GLfloat GetWidth (void) const;
		const GLfloat GetHeight (void) const;
		const GLfloat GetRadius (void) const;
		const GLfloat GetVerticalPosition (void) const;
		const GLfloat GetCenterVerticalPosition (void) const;
		const GLboolean GetHasCenterPoint (void) const;
		const GLboolean GetInvertPlaneNormal (void) const;
		const GLubyte GetRed ( void ) const;
		const GLubyte GetGreen ( void ) const;
		const GLubyte GetBlue ( void ) const;
		const GLubyte GetAlpha ( void ) const;

		void SetSlices ( const GLuint slices );
		void SetStacks ( const GLuint stacks );
		void SetXSubdivisions ( const GLuint xSubdivisions );
		void SetYSubdivisions ( const GLuint ySubdivisions );
		void SetWidth ( const GLfloat width );
		void SetHeight ( const GLfloat height );
		void SetRadius ( const GLfloat radius );
		void SetVerticalPosition ( const GLfloat verticalPosition );
		void SetCenterVerticalPosition ( const GLfloat centerVerticalPosition );
		void SetHasCenterPoint ( const GLboolean hasCenterPoint );
		void SetInvertPlaneNormal ( const GLboolean invertPlaneNormal );
		void SetRed ( const GLubyte red );
		void SetGreen ( const GLubyte green );
		void SetBlue ( const GLubyte blue );
		void SetAlpha ( const GLubyte alpha );

	private:
		GLuint m_slices;
		GLuint m_stacks;
		GLuint m_xSubdivisions;
		GLuint m_ySubdivisions;
		GLfloat m_width;
		GLfloat m_height;	
		GLfloat m_radius;
		GLfloat m_verticalPos;
		GLfloat m_centerVerticalPos;
		GLboolean m_hasCenterPoint;
		GLboolean m_invertPlaneNormal;
		GLubyte m_red;
		GLubyte m_green;
		GLubyte m_blue;
		GLubyte m_alpha;
	};

} //end namespace File


#endif
////////////////////////////////////////////////////////////////////////////////




