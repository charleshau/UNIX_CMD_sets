// author Mu He, 250995508
// file is a class providing an abstract file class ADT in the program
//
// For any detail, see README - Implementation Details - File
//

#include "../header/file.h"
using namespace std;

File::File ( string n ) : name(std::move(n))
{
	error_number = 0;
	if ( stat(name.c_str(), &sb) != -1 )
	{
		type = sb.st_mode;
		size = sb.st_size;
		owner = *getpwuid(sb.st_uid)->pw_name; // in struct passwd: char *pw_name; /* username */
		group = *getgrgid(sb.st_gid)->gr_name; // same as above
		permission = to_rwx(bitset<9>(sb.st_mode).to_string('-', '*')); // or you can do it by two steps. See README
		access_time = ctime(&sb.st_atime); // see README
		modify_time = ctime(&sb.st_mtime);
		change_time = ctime(&sb.st_ctime);
		block_size = sb.st_blksize;
		if ( S_ISDIR(sb.st_mode))
		{
			str_type = "directory";
			expand();
		}
		else if ( S_ISREG(sb.st_mode))
			str_type = "regular file";
		else if ( S_ISLNK(sb.st_mode))
			str_type = "link";
		else
			str_type = "other type";
	} else
	{
		error_number = errno;
		error_maker("File: constructor ERR");
	}

}

void File::error_maker ( const string &pre_info )
{
	cout << pre_info << " " << error_number << ": " << strerror(error_number) << endl;
	exit(1);
}

char * File::text()
{
	ifstream s(name, std::ifstream::binary);
	if ( s )
	{
		char * buffer = new char[size + 10];
		s.read(buffer, size);
		if ( !s )
		{
			delete[] buffer;
			error_number = EFBIG; // the file is too big
			error_maker("File.text: ERR");
		} else
		{
			return buffer;
		}
	} else
	{
		error_number = ENOTSUP;
		error_maker("File.text: ERR");
	}

	return nullptr;
}

void File::rename ( const string &new_name )
{
	if ( ::rename(name.c_str(), new_name.c_str()))
	{
		error_number = errno;
		error_maker("File.rename: ERR");
	}
	name = new_name;
}

void File::remove ()
{
	if ( ::unlink(name.c_str()))
	{
		error_number = errno;
		error_maker("File.remove: ERR");
	}
}

bool File::compare ( File f )
{
	try
	{
		if(f.size!=this->size || f.size >= this->size + 3 || f.size <= this->size - 3)
			return false;
		for ( int i = 0; i < f.size; i++ )
		{
			if ( text()[i] != f.text()[i] )
				return false;
		}
		return true;
	} catch ( ... )
	{
		error_number = errno;
		error_maker("File.compare: ERR");
	}
	return false;
}

void File::expand ()
{
	DIR * dir;
	vector<string> res; // for test. Delete
	if (( dir = opendir(name.c_str())) == nullptr )
	{
		error_number = ENOTSUP;
		error_maker("File.expand: ERR");
	} else
	{
		struct dirent * dp;
		while (( dp = readdir(dir)) != nullptr )
		{
			if ( dp->d_name[0] != '.' )
			{
				try
				{
					string temp = name; temp.append("/");
					File f = File(temp.append(dp->d_name, strlen(dp->d_name)));
					children.push_back(pair<File,string>(f,dp->d_name));
					res.push_back(dp->d_name);
				} catch ( ... )
				{
					error_number = ENOTSUP;
					error_maker("File.expand: ERR");
				}
			}
		}
	}
	//		for(auto &s:res)
	//		{
	//			cout << "file is:" << s << endl;
	//		}
	//		cout << children.size() << endl;
}

const string &File::getName () const
{
	return name;
}

const mode_t &File::getType () const
{
	return type;
}

int File::getSize () const
{
	return size;
}

const string &File::getOwner () const
{
	return owner;
}

const string &File::getGroup () const
{
	return group;
}

const string &File::getPermission () const
{
	return permission;
}

const string &File::getAccessTime () const
{
	return access_time;
}

const string &File::getModifyTime () const
{
	return modify_time;
}

const string &File::getChangeTime () const
{
	return change_time;
}

int File::getBlockSize () const
{
	return block_size;
}

const vector<pair<File,string> > &File::getChildren () const
{
	return children;
}

int File::getError () const
{
	return error_number;
}

string File::getTypeInfo () const
{
	return str_type;
}

string File::getErrorInfo ( int error )
{
	return strerror(error);
}

string File::to_rwx ( string temp )
{
	for ( int i = 0; i < 9; i++ )
	{
		if ( temp[i] == '*' )
		{
			switch ( i % 3 )
			{
				case 0:
					temp[i] = 'r';
					break;
				case 1:
					temp[i] = 'w';
					break;
				case 2:
					temp[i] = 'x';
					break;
				default:
					break;
			}
		}
	}
	return temp;
}

void File::dump ( fstream & s )
{
	fstream out(name, ios::in|ios::out|ios::binary);
	if ( out )
	{
		char * buffer = new char[size + 10];
		s.read(buffer, size);
		if (!s )
		{
			delete[] buffer;
			error_number = EFBIG; // the file is too big
			error_maker("File.dump: ERR");
		} else
		{
			out.write(buffer, size);
			delete[] buffer;
		}
	} else
	{
		error_number = ENOTSUP;
		error_maker("File.dump: ERR");
		exit(1);
	}
}

void File::dump( const char * new_name)
{
	std::ofstream f (new_name);
	f << this->File::text();
	f.close();
}

void File::dump ( const char * new_name, const char * buffer)
{
	std::ofstream f (new_name);
	f << buffer;
	f.close();
}

//int main ()
//{
//	File f = File("123.cpp");
//	f.dump("hellooo");
//}
