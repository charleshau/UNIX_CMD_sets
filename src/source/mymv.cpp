//
// @author Charles hau
// 
// move a file
//

#include "../header/my.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		throw std::runtime_error(std::string("Error: mv: argument error."));
		exit(1);
	}
	else
	{
		File f = File(argv[1]);
		const char * target = argv[2];
		try{
			f.rename(target);
			return 0;
		} catch (...)
		{
			char * text = f.text();
			f.dump(target, text);
			f.remove();
			return 0;
		}
	}
}