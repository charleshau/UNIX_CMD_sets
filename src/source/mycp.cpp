
//
// @author Charles hau
// 
// copy a file from one place to another.
//

#include "../header/my.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		throw std::runtime_error(std::string("Error: cp: argument error."));
	}
	else
	{
		File f = File(argv[1]);
		const char * target = argv[2];
		try{
			char * text = f.text();
			f.dump(target, text);
			return 0;
		} catch (...)
		{
			char * text = f.text();
			f.dump(target, text);
			return 0;
		}
	}
}