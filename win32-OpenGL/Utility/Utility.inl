/******************************************************************************/
/*!
\file Utility.inl
\author Oliver Ryan Chong
\par email: oliver.chong\@digipen.edu
\par oliver.chong 900863
\par Course: CS1250
\par Project #01
\date 12/12/2011
\brief
This contains utility functions that can be used throughout the application

Copyright (C) 2011 DigiPen Institute of Technology Singapore
*/
/******************************************************************************/

namespace Utility
{
	/******************************************************************************/
	/*!
	Performs a deep copy of the contents of the source array to the destination array based on the offset
	\param sourceArray
	the source array to be copied from
	\param srcArrSize
	the source array size
	\param destinationArray
	the destination array that will store the copied data
	\param destArrSize
	the destination array size
	\param offsetVal
	the offset value of the destination array index
	\return
	*/
	/******************************************************************************/
	template <typename T>
	void CopyArrayBasedOnOffset (const T * sourceArray, const unsigned srcArrSize, 
		T * destinationArray, const unsigned destArrSize, const unsigned offsetVal)
	{
		unsigned indexWithOffset = 0;

		for (unsigned index = 0; index < destArrSize; ++index)
		{
			indexWithOffset = index + offsetVal;

			//validate if the index is within bounds of the destination array after applying the offset
			//also check if the index is within bounds of the source array
			if (indexWithOffset < destArrSize && index < srcArrSize)
			{
				destinationArray[indexWithOffset] = sourceArray[index];	
			}
			else
			{
				break;
			}
		}//end for loop
	}

} //end namespace Utility