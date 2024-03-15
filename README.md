# File_system_in_C

This is a sort of simulation of a file explorer using tree data structure.

The tree structure used is a multilevel tree which has option to treverse up and down both using pointers.

Metadata structure represents a file wich has a name, path, content and other details about it.
```
struct Metadata {
    char name[MAX_NAME_LENGTH];
    char path[MAX_PATH_LENGTH];
    int size;
    char creation_date[20];
    char modification_date[20];
    char content[MAX_CONTENT_LENGTH];
};
```

Directory structure represents a Folder which has the 
```
struct Directory{
    int files;
    int folders;
    char name[MAX_NAME_LENGTH];
    char Directory_path[20][20];
    struct Metadata *file[MAX_NO_OF_FILES];

    struct Directory *prev;
    struct Directory *next[MAX_NO_OF_FOLDERS];
};
```

##Project constrains
- MAX_NAME_LENGTH 20
- MAX_PATH_LENGTH 500
- MAX_NO_OF_FOLDERS 20
- MAX_NO_OF_FILES 20
- MAX_CONTENT_LENGTH 1000
