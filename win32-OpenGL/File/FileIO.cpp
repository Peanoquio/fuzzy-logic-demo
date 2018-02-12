/******************************************************************************/
/*!
\file FileIO.cpp
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

#include "FileIO.h"
#include <fstream>
#include <iostream>
#include <string>

namespace File
{
	/******************************************************************************/
	/*! 
	\brief 
	Returns a container with the data read from the file

	\param
	\return FileDataMap
	a container with the data read from the file
	*/
	/******************************************************************************/
	const FileDataMap & File::GetFileDataMap (void) const
	{
		return this->m_fileDataMap;
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/******************************************************************************/
	/*! 
	\brief 
	Opens a file for reading

	\param fileName
	the name of the file to open
	\param container
	a reference to the container to fill
	*/
	/******************************************************************************/
	void File::OpenFile (const char* fileName, ContainerType& container)
	{
		//Open the file
		std::ifstream infile;
		infile.open ( fileName );

		//check if the file is open, if it couldn't be opened, Report error to cout
		if ( !infile.is_open() )
		{
			std::cout << "Cannot open the file : " << fileName << std::endl;	
		}
		else
		{
			std::pair<std::string, ContainerType> myPair;
			std::string strKey;
			std::string strConfig;			
			GLuint uintVal;
			GLfloat floatVal;
			int startingIndex = 0;

			//loop until the end of the file
			while ( !infile.eof() )
			{				
				//get the details from the file
				
				//define the key
				if (std::getline(infile, strConfig))
				{
					//check if the first element of the string begins with [
					if (strConfig.substr( 0,1 ).compare(";") != 0 && strConfig.substr( 0,1 ).compare("[") == 0)
					{
						//strKey will store the key value for the map
						//[sampleKey] -> the key name will be sampleKey exclucding the [] characters
						strKey = strConfig.substr( 1, strConfig.length() - 2 );
					}
					//break;
				}

				//Fill in the container with the data
				if (std::getline(infile, strConfig))
				{
					//ignore lines that start with the character ;
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						//start parsing the line after the character :
						startingIndex = strConfig.find(":") + 1;
						uintVal = std::atoi(strConfig.substr(startingIndex).c_str());
						container.SetRed( static_cast<GLubyte>(uintVal) );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						uintVal = std::atoi(strConfig.substr(startingIndex).c_str());
						container.SetGreen( static_cast<GLubyte>(uintVal) );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						uintVal = std::atoi(strConfig.substr(startingIndex).c_str());
						container.SetBlue( static_cast<GLubyte>(uintVal) );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						uintVal = std::atoi(strConfig.substr(startingIndex).c_str());
						container.SetAlpha( static_cast<GLubyte>(uintVal) );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						uintVal = static_cast<GLuint>( std::atoi(strConfig.substr(startingIndex).c_str()) );
						container.SetSlices( uintVal );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						uintVal = static_cast<GLuint>( std::atoi(strConfig.substr(startingIndex).c_str()) );
						container.SetStacks( uintVal );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						uintVal = static_cast<GLuint>( std::atoi(strConfig.substr(startingIndex).c_str()) );
						container.SetXSubdivisions( uintVal );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						uintVal = static_cast<GLuint>( std::atoi(strConfig.substr(startingIndex).c_str()) );
						container.SetYSubdivisions( uintVal );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						floatVal = static_cast<GLfloat>( std::atof(strConfig.substr(startingIndex).c_str()) );
						container.SetWidth( floatVal );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						floatVal = static_cast<GLfloat>( std::atof(strConfig.substr(startingIndex).c_str()) );
						container.SetHeight( floatVal );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						floatVal = static_cast<GLfloat>( std::atof(strConfig.substr(startingIndex).c_str()) );
						container.SetRadius( floatVal );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						floatVal = static_cast<GLfloat>( std::atof(strConfig.substr(startingIndex).c_str()) );
						container.SetVerticalPosition( floatVal );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						floatVal = static_cast<GLfloat>( std::atof(strConfig.substr(startingIndex).c_str()) );
						container.SetCenterVerticalPosition( floatVal );
					}
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						GLboolean hasCenterPoint = GL_FALSE;
						if (strConfig.substr(startingIndex).compare("true") == 0)
							hasCenterPoint = GL_TRUE;

						container.SetHasCenterPoint( hasCenterPoint );
					}

					//push the contact to the container
					//container.push_back( container );
					//break;
				}

				if (std::getline(infile, strConfig))
				{
					if (strConfig.substr( 0,1 ).compare(";") != 0)
					{
						startingIndex = strConfig.find(":") + 1;
						GLboolean invertPlaneNormal = GL_FALSE;
						if (strConfig.substr(startingIndex).compare("true") == 0)
							invertPlaneNormal = GL_TRUE;

						container.SetInvertPlaneNormal( invertPlaneNormal );
					}

					//push the contact to the container
					//container.push_back( container );
					//break;
				}

				//push the contact to the container
				//container.push_back( container );

				//construct the key-data pair for the map
				myPair = std::make_pair( strKey, container );
				//insert the pair to the map
				this->m_fileDataMap.insert( myPair );

			}//end while loop
		}		

		//make sure to close the file if it was opened
		infile.close();
	}
}