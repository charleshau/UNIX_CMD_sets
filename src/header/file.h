// @author Mu He, 250995508
// the header of file.cpp
// 
// For any detail, see README - Implementation Details - File
//

#ifndef CS3307_1_FILE_H
#define CS3307_1_FILE_H

#include <iostream>
#include <utility>
#include <vector>
#include <bitset>
#include <ctime>
#include <cerrno>
#include <dirent.h>
#include <cstdio>
#include <cstring>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h> // for passwd and getpwuid();
#include <grp.h> // for group and getgrgid();
#include <fstream>
class File
{
public:
	std::string name;
	mode_t type;
	std::string str_type;
	off_t size;
	std::string owner;
	std::string group;
	std::string permission;
	std::string access_time;
	std::string modify_time;
	std::string change_time;
	int block_size;
	std::vector<std::pair<File, std::string> > children;
	int error_number;

	//----- constructor & destructor. View README to see the idea of design
	explicit File ( std::string n );

	~File () = default;

	//----- error getters
	void error_maker ( const std::string &pre_info );

	int getError () const;

	static std::string getErrorInfo ( int error );

	//----- aux functions. View README to see the idea of design
	void dump ( std::fstream& s );

	void dump ( const char * new_name);

	void dump ( const char * new_name, const char * buffer);

	char * text ();

	void rename ( const std::string &new_name );

	void remove ();

	bool compare ( File f );

	void expand (); // see README

	//------ Getters & Setters
	const std::string &getName () const;

	const ::mode_t &getType () const;

	int getSize () const;

	const std::string &getOwner () const;

	const std::string &getGroup () const;

	const std::string &getPermission () const;

	const std::string &getAccessTime () const;

	const std::string &getModifyTime () const;

	const std::string &getChangeTime () const;

	int getBlockSize () const;

	const std::vector<std::pair<File,std::string> > &getChildren () const;

	std::string getTypeInfo () const;

	struct stat sb; // stat buff
private:
	static std::string to_rwx ( std::string temp ); // for transfer from binary 001110001 to r-w-x format
};


#endif //CS3307_1_FILE_H
