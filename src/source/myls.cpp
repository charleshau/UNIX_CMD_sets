//
// @author Charles hau
// 
// list the target's info. Allowed -l
//

#include "../header/my.h"
typedef std::pair<File, std::string> p;

// for more info about file type, see README - File Type.

int sub(int argc, char *argv[])
{
	if(argc == 1)
	{
		char path[4028];
		getcwd(path, sizeof path);
		File f = File(std::string(path, strlen(path)));
		if ( S_ISDIR(f.type))
			for ( auto &s:f.children )
			{
				std::cout << s.second << " ";
			}
		else
			std::cout << f.name;
		std::cout << std::endl;
	}
	else if(argc == 2 && strcmp(argv[1],"-l") != 0)
	{
		File f = File(argv[1]);
		if ( S_ISDIR(f.type))
			for ( auto &s:f.children )
			{
				std::cout << s.second << " ";
			}
		else
			std::cout << f.name;
		std::cout << std::endl;
	}

	else if(argc == 2 && strcmp(argv[1],"-l") == 0)
	{
		std::vector<p> temp; // store the kids which is DIR
		char path[4028]; // store the whole path of current DIR
		getcwd(path, sizeof path); // get path
		File f = File(std::string(path, strlen(path))); // created current file.
		if ( S_ISDIR(f.type))
		{
			for ( auto &s:f.children )
			{
				if ( S_ISDIR(s.first.type)) // if there is a kid which is DIR
					temp.push_back(s); // store it.
				std::cout << s.second << " ";
			}
			std::cout << std::endl;
			for(auto &s:temp)
			{
				std::cout << s.second << ":" << std::endl;
				char* arg [2];
				arg[0] = "myls";
				char cstr[s.second.size() + 1]; strcpy(cstr, s.second.c_str());
				arg[1] = cstr;
				sub(2, arg);
			}
		}
		else
			std::cout << f.name;
		std::cout << std::endl;
	}
	else if(argc == 3 && strcmp(argv[2],"-l") == 0)
	{
		std::vector<p> temp; // store the kids which is DIR
		File f = File(argv[1]); // created current file.
		if ( S_ISDIR(f.type))
		{
			for ( auto &s:f.children )
			{
				if ( S_ISDIR(s.first.type)) // if there is a kid which is DIR
					temp.push_back(s); // store it.
				std::cout << s.second << " ";
			}
			std::cout << std::endl;
			for(auto &s:temp)
			{
				std::cout << s.second << ":" << std::endl;
				char* arg [2];
				arg[0] = "myls";
				char cstr[s.second.size() + 1]; strcpy(cstr, s.first.name.c_str());
				arg[1] = cstr;
				sub(2, arg);
			}
		}
		else
			std::cout << f.name;
		std::cout << std::endl;
	}
	else
	{
		throw std::runtime_error(std::string("Error: ls: argument error."));
	}
}
int main(int argc, char *argv[])
{
	sub(argc, argv);

}