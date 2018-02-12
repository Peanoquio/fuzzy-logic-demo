/******************************************************************************/
/*!
\file FileIO.h
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
Opens and reads the contents of the file while storing it data in a container

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
#ifndef FILEIO_H
#define FILEIO_H
////////////////////////////////////////////////////////////////////////////////

#include "GeometryParameterContainer.h"
#include <unordered_map>

//define the typedef ContainerType
typedef File::GeometryParameterContainer ContainerType;
typedef std::unordered_map< std::string, ContainerType> FileDataMap;


namespace File
{
	class File
	{
	public:
		void OpenFile (const char* fileName, ContainerType& container);
		const FileDataMap & GetFileDataMap (void) const;
	private:
		FileDataMap m_fileDataMap;
	};
}

#endif
////////////////////////////////////////////////////////////////////////////////