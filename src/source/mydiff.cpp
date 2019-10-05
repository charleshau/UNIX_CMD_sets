//
// @author Charles hau
// 
// check whether two files are the same.
//

#include "../header/my.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		throw std::runtime_error(std::string("Error: rm: argument error."));
	}
	else
	{
		File f = File(argv[1]);
		File g = File(argv[2]);
		if(S_ISREG(f.type)&&S_ISREG(g.type))
		{
			if(f.compare(g))
				std::cout << "same";
			else
				std::cout << "different";
		} else {
			throw std::runtime_error(std::string("Error: diff: File Incomparable."));
		}
	}
}