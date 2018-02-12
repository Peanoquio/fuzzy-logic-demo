//This is the flow of how to expand the current state

/*
bool ExpandCurrentState()
{
	//read the hole index
	
	if(hole index is on the right side)
	{
		if(hole index is on the top row)
		{
			//2 possible moves
			CheckPossibleMove(left side);
			CheckPossibleMove(down side);
		}
		else if(hole index is on the bottom row)
		{
			//2 possible moves
			CheckPossibleMove(down side);
			CheckPossibleMove(up side);			
		}
		else
		{
			//3 possible moves
			CheckPossibleMove(left side);
			CheckPossibleMove(top side);
			CheckPossibleMove(down side);
		}
	}
	else if(hole index is on the left side)
	{
		if(hole index is on the top row)
		{
			//2 possible moves
			CheckPossibleMove(right side);
			CheckPossibleMove(down side);				
		}
		else if(hole index is on the bottom row)
		{
			//2 possible moves
			CheckPossibleMove(right side);
			CheckPossibleMove(up side);
		}
		else
		{
			//3 possible moves
			CheckPossibleMove(right side);
			CheckPossibleMove(up side);
			CheckPossibleMove(down side);
		}
	}
	else if(hole index is on the top row)
	{
		//3 possible moves
		CheckPossibleMove(down side);
		CheckPossibleMove(left side);
		CheckPossibleMove(right side);		
	}
	else if(hole index is on the bottom row)
	{
		//3 possible moves
		CheckPossibleMove(up side);
		CheckPossibleMove(left side);
		CheckPossibleMove(right side);		
	}
	else//the hole is not on a border
	{
		//4 possible moves
		CheckPossibleMove(down side);
		CheckPossibleMove(up side);
		CheckPossibleMove(left side);
		CheckPossibleMove(right side);		
	}
}
*/