#include "tools.h"

std::string tools::BoolToString(bool i)
{
	{
		if (i = true)
		{
			return "True";
		}
		else
		{
			return "False";
		}
	}
}

ImVec4 tools::GetBoolColor(bool i)
{
	if (i = true)
	{
		return ImVec4(255,0,0,255);
	}
	else
	{
		return ImVec4(0, 255, 0, 255);
	}
	
}
