# Readme

@ author: Charles Hau
@ date: Thu 3 Oct 2019 19:51:38 EDT

## Install

Download the source code. In the home folder of the project(also where Makefile located), run ```make A``` to compile, where A is one of these: ```cat cp diff ls mv rm stat```

The binary file will be stored in ```/bin```. I also put some sample files and directories for test. The source code is in  ```src/source``` and ```src/header```

Run ```./myA``` to run the command, where A is same thing above.

All the programs has been run on ```Linux raspberry 4.19.0-6-686 #1 SMP Debian 4.19.67-2+deb10u1 (2019-09-20) i686 GNU/Linux```, with compiler ```g++ 8.3.0```.

Feel free to email me and have fun!

## Background

The key point of this program, is to encapsulate a buildin file management kit into a class called ```File```. 

The properties of ```File``` is mainly from  ```stat()```:

```c
struct stat {
    dev_t     st_dev;         /* ID of device containing file */
    ino_t     st_ino;         /* inode number */
    mode_t    st_mode;        /* file type and mode */
    nlink_t   st_nlink;       /* number of hard links */
    uid_t     st_uid;         /* user ID of owner */
    gid_t     st_gid;         /* group ID of owner */
    dev_t     st_rdev;        /* device ID (if special file) */
    off_t     st_size;        /* total size, in bytes */
    blksize_t st_blksize;     /* blocksize for filesystem I/O */
    blkcnt_t  st_blocks;      /* number of 512B blocks allocated */
    /* Since Linux 2.6, the kernel supports nanosecond
       precision for the following timestamp fields.
       For the details before Linux 2.6, see NOTES. */
    struct timespec st_atim;  /* time of last access */
    struct timespec st_mtim;  /* time of last modification */
    struct timespec st_ctim;  /* time of last status change */
#define st_atime st_atim.tv_sec      /* Backward compatibility */
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};
```

(reference: https://manpages.debian.org/stretch/manpages-dev/stat.2.en.html)

About ```mode_t``` and how to check file type, see ```Appendix I```

Besides, ```struct passwd``` and ```struct group``` are also used.
```
struct group {
    char   *gr_name;        /* group name */
    char   *gr_passwd;      /* group password */
    gid_t   gr_gid;         /* group ID */
    char  **gr_mem;         /* NULL-terminated array of pointers
                       to names of group members */
};

struct passwd {
    char   *pw_name;       // username
	char   *pw_passwd;     // user password
	uid_t   pw_uid;        // user ID
	gid_t   pw_gid;        // group ID
	char   *pw_gecos;      // user information
	char   *pw_dir;        // home directory
	char   *pw_shell;      // shell program
	};
```

(reference https://manpages.debian.org/stretch/manpages-dev/getpwuid.3.en.html)

In the program, we mainly use ```passwd getpwuid(st_uid)``` and ```group getgrgid(st_gid)``` to get user's group and owner.

## Implementation Details

### ```File.permission```

- Firstly use type ```bitset```, transfer from int to binary, then to string.
- Then use function ```string to_rwx(int)``` switch to string.

```c
std::bitset<9> res (sb.st_mode); // new a bitset res
string s_res = res.to_string('-','*'));
to_rwx(s_res)
```

### ```File.access_time``` and other time

A string with formatted date.
```
ctime(&sb.st_atime)
```

```ctime``` is a classical function from ```time.h```, which take ```const *t_time``` as a param and return a string

Also, ```st_atime``` is from

``` c
#define st_atime st_atim.tv_sec 
```

and ```tv_sec``` actually is ```t_time```

The _Status Change Time_ and _Modification Time_ is the same principle


###  ```File.error_maker(string pre_info)```

print the error, with the format

```$xslt
pre-information, error number, error information
```

###  ```File.text()```

If a file is a context, read from it and return a string storing it.

It will have two errors: 1. size; 2. existence; 

###  ```File.children & File.expand()```

The instance variable ```children``` is made by ```pair<File, string>```

The second string store a brief name of a file. Because in ```File.name```, you have to store the whole path, so, in case of ```ls```, it could be super inconvenient.

In ```File.expand()```, we use two builtin class, ```dirent``` and ```DIR```, referring to files and directories in file system.

What's noticeable is, in ```File.expand()```, the ```File.name``` keeps increasing, from ```/f``` to ```/f/ff``` to ```/f/ff/fff```, but we always keep its original name ```fff``` in ```pair<File, string>```.  

### ```File.dump()```

I use three versions of ```dump``` here. It will copy from a file, and store it in file or stream or char buffer.


## Appendix I. File Type

There is bunches of system types built-in. It will mainly be used in class and ```myls```. 
```
           S_IFMT     0170000   bit mask for the file type bit field
           S_IFSOCK   0140000   socket
           S_IFLNK    0120000   symbolic link
           S_IFREG    0100000   regular file
           S_IFBLK    0060000   block device
           S_IFDIR    0040000   directory
           S_IFCHR    0020000   character device
           S_IFIFO    0010000   FIFO
```

Compare the above things with ```st_mode``` is illegal. You have to call those functions:

```c
           S_ISREG(m)  is it a regular file?
           S_ISDIR(m)  directory?
           S_ISCHR(m)  character device?
           S_ISBLK(m)  block device?
           S_ISFIFO(m) FIFO (named pipe)?
           S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
           S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)
```