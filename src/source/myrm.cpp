//
// @author Charles hau
// 
// delete a file
//

#include "../header/my.h"

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		throw std::runtime_error(std::string("Error: rm: argument error."));
	}
	else
	{
		for(int i = 1; i < argc; i++)
		{
			File f = File(argv[i]);
			f.remove();
		}
		return 0;
	}
}