/******************************************************************************/
/*!
\file MatrixStack.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
The matrix stack that manages the matrix transformations

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include "../Math/Mtx44.h"

namespace Utility
{
	enum MatrixModeEnum {
		MODELVIEW,
		PROJECTION,
		NUMBER_OF_STACKS
	};

	class MatrixStack
	{
	public:
		MatrixStack (void);
		
		void MatrixMode (const MatrixModeEnum matrixMode);
		void Push (void);
		void Pop (void);
		void LoadMatrix (const Math::Mtx44 & matrix);
		void MultMatrix (const Math::Mtx44 & matrix);
		bool IsEmpty (void) const;		
		const Math::Mtx44 & Top (void) const;
	
	private:
		//a matrix stack which in turn contains matrix objects
		std::vector<Math::Mtx44> m_matrixStack[NUMBER_OF_STACKS];
		MatrixModeEnum m_currentMatrixMode;
	};
} //end namespace Utility

#endif
////////////////////////////////////////////////////////////////////////////////