//
// @author Charles hau
// 
// print information of a target
//

#include "../header/my.h"

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		throw std::runtime_error(std::string("Error: stat: argument error."));
	} else {
		File f = File(argv[1]);
		std::cout << f.name << std::endl;
		std::cout << "========================" << std::endl;
		std::cout << f.getSize() << std::endl;
		std::cout << f.getTypeInfo() << std::endl;
		std::cout << f.getPermission() << std::endl;
		std::cout << "Last open: "<< f.getAccessTime();
		std::cout << "Last change: "<< f.getChangeTime();
		std::cout << "Last modify: "<< f.getModifyTime();
		std::cout << "group: " << f.getGroup() << std::endl;
		std::cout << "owned by: " << f.getOwner() << std::endl;
	}
}