//
// @author Charles Hau
//
// print bunches of files on the screen.
// 
// If param is a DIR, print "xxx Is a directory"
//

#include "../header/my.h"

int main(int argc, char *argv[])
{
	if(argc <= 1)
	{
		throw std::runtime_error(std::string("Error: cat: argument error."));
	}
	else
	{
		for(unsigned long i = 1; i < argc; i++)
		{
			File f = File(argv[i]);
			if(S_ISDIR(f.type))
				std::cout << "cat: " << f.name << ": " << "Is a directory" << std::endl;
			else if(S_ISREG(f.type))
				std::cout << f.text() << std::endl;
		}


	}
}
