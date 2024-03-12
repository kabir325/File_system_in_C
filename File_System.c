##FINAL


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LENGTH 20
#define MAX_PATH_LENGTH 500
#define MAX_NO_OF_FOLDERS 20
#define MAX_NO_OF_FILES 20
#define MAX_CONTENT_LENGTH 1000

struct Metadata {
    char name[MAX_NAME_LENGTH];
    char path[MAX_PATH_LENGTH];
    int size;
    char creation_date[20];
    char modification_date[20];
    char content[MAX_CONTENT_LENGTH];
};
struct Directory{
    int files;
    int folders;
    char name[MAX_NAME_LENGTH];
    char Directory_path[20][20];
    struct Metadata *file[MAX_NO_OF_FILES];

    struct Directory *prev;
    struct Directory *next[MAX_NO_OF_FOLDERS];
};

struct Directory *Create(){
    struct Directory D=(struct Directory)malloc(sizeof(struct Directory));
    D->prev=NULL;
    D->files=0;
    D->folders=0;
    struct Directory *temp=D;
    int i=0;
    while(temp!=NULL && i < 20){
        strcpy(D->Directory_path[i], temp->name);
        temp=temp->prev;
        i++;
    }
    strcpy(D->name,"C");
    return D;
}

struct Directory* createDirectory(char name[MAX_NAME_LENGTH], struct Directory* currentDir) {
    struct Directory* newDir = (struct Directory*)malloc(sizeof(struct Directory));
    strcpy(newDir->name, name);
    newDir->files = 0;
    newDir->folders = 0;
    newDir->prev = currentDir;
    currentDir->next[currentDir->folders++] = newDir;
    return newDir;
}



void createFile(char name[MAX_NAME_LENGTH], int size, struct Directory *currentDir, char content[MAX_CONTENT_LENGTH]) {
    if (currentDir->files < MAX_NO_OF_FILES) {
        struct Metadata *newFile = (struct Metadata *)malloc(sizeof(struct Metadata));
        strcpy(newFile->name, name);

        sprintf(newFile->path, "%s/%s", currentDir->Directory_path, name);

        newFile->size = size;

        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);

        strftime(newFile->creation_date, sizeof(newFile->creation_date), "%Y-%m-%d %H:%M:%S", tm_info);
        strcpy(newFile->modification_date, newFile->creation_date);

        strncpy(newFile->content, content, MAX_CONTENT_LENGTH - 1);
        newFile->content[MAX_CONTENT_LENGTH - 1] = '\0';

        currentDir->file[currentDir->files++] = newFile;
    } else {
        printf("Max number of files reached in this directory.\n");
    }
}

struct Directory* changeDirectory(struct Directory* currentDir) {
    printf("Enter the name of the directory to move into (or '..' to go back): ");
    char newDir[MAX_NAME_LENGTH];
    scanf("%s", newDir);

    if (strcmp(newDir, "..") == 0) {
        if (currentDir->prev != NULL) {
            return currentDir->prev;
        } else {
            printf("Already in the root directory.\n");
            return currentDir;
        }
    }

    for (int i = 0; i < currentDir->folders; ++i) {
        if (strcmp(currentDir->next[i]->name, newDir) == 0) {
            return currentDir->next[i];
        }
    }

    printf("Directory not found.\n");
    return currentDir;
}


void viewCurrentDirectory(struct Directory* currentDir) {
    printf("Files in the current directory:\n");
    for (int i = 0; i < currentDir->files; ++i) {
        printf("- %s\n", currentDir->file[i]->name);
    }
    printf("\nSubdirectories in the current directory:\n");
    for (int i = 0; i < currentDir->folders; ++i) {
        printf("- %s\n", currentDir->next[i]->name);
    }
}

void deleteDirectory(char dirToDelete[MAX_NAME_LENGTH], struct Directory* currentDir) {
    int found = 0;
    for (int i = 0; i < currentDir->folders; ++i) {
        if (strcmp(currentDir->next[i]->name, dirToDelete) == 0) {
            free(currentDir->next[i]);
            for (int j = i; j < currentDir->folders - 1; ++j) {
                currentDir->next[j] = currentDir->next[j + 1];
            }
            currentDir->folders--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Directory not found.\n");
    }
}

void deleteFile(char fileToDelete[MAX_NAME_LENGTH], struct Directory* currentDir) {
    int found = 0;
    for (int i = 0; i < currentDir->files; ++i) {
        if (strcmp(currentDir->file[i]->name, fileToDelete) == 0) {
            free(currentDir->file[i]);
            for (int j = i; j < currentDir->files - 1; ++j) {
                currentDir->file[j] = currentDir->file[j + 1];
            }
            currentDir->files--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("File not found.\n");
    }
}

void display_Directory(struct Directory *D) {
    char fullPath[MAX_PATH_LENGTH];
    fullPath[0] = '\0';

    while (D != NULL) {
        char temp[MAX_PATH_LENGTH];
        sprintf(temp, "%s/%s", D->name, fullPath);
        strcpy(fullPath, temp);
        D = D->prev;
    }

    printf("%s", fullPath);
}

void displayMetadata(struct Metadata *metadata) {
    printf("Name: %s\n", metadata->name);
    printf("Path: %s\n", metadata->path);
    printf("Size: %d\n", metadata->size);
    printf("Creation Date: %s\n", metadata->creation_date);
    printf("Modification Date: %s\n", metadata->modification_date);
    printf("\n");
}

void displayFileMetadata(struct Metadata *fileMetadata) {
    printf("File Metadata:\n");
    displayMetadata(fileMetadata);
}

void displayDirectoryMetadata(struct Directory *directory) {
    printf("Directory Metadata:\n");
    printf("Name: %s\n", directory->name);
    printf("Path: %s\n", directory->Directory_path);
    printf("Number of Files: %d\n", directory->files);
    printf("Number of Subdirectories: %d\n", directory->folders);
    printf("\n");
}


int main() {
    struct Directory *mainDir = Create();
    struct Directory *currentDir = mainDir;
    int choice;

    while (1) {
        printf("\nCurrent Directory: ");
        display_Directory(currentDir);
        printf("\n");

        printf("Enter 1 to view current directory elements\n");
        printf("Enter 2 to create a directory in the current directory\n");
        printf("Enter 3 to delete a directory\n");
        printf("Enter 4 to create a file\n");
        printf("Enter 5 to delete a file\n");
        printf("Enter 6 to change directory\n");
        printf("Enter 7 to display file metadata\n");
        printf("Enter 8 to display directory metadata\n");
        printf("Enter 0 to exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 0:
                return 0;

            case 1:
                viewCurrentDirectory(currentDir);
                break;

            case 2: {
                char dirName[MAX_NAME_LENGTH];
                printf("Enter the name of the new directory: ");
                scanf("%s", dirName);
                createDirectory(dirName, currentDir);
                break;
            }

            case 3: {
                char dirToDelete[MAX_NAME_LENGTH];
                printf("Enter the name of the directory to delete: ");
                scanf("%s", dirToDelete);
                deleteDirectory(dirToDelete, currentDir);
                break;
            }

            case 4: {
                char fileName[MAX_NAME_LENGTH];
                int fileSize;
                char fileContent[MAX_CONTENT_LENGTH];

                printf("Enter the name of the new file: ");
                scanf("%s", fileName);

                printf("Enter the size of the new file: ");
                scanf("%d", &fileSize);

                printf("Enter the content of the new file (up to %d characters): ", MAX_CONTENT_LENGTH - 1);
                scanf(" %[^\n]s", fileContent);

                createFile(fileName, fileSize, currentDir, fileContent);
                break;
            }
            case 5: {
                char fileToDelete[MAX_NAME_LENGTH];
                printf("Enter the name of the file to delete: ");
                scanf("%s", fileToDelete);
                deleteFile(fileToDelete, currentDir);
                break;
            }

            case 6: {
                currentDir = changeDirectory(currentDir);
                break;
            }

            case 7:
                displayFileMetadata(currentDir->file[currentDir->files - 1]);
                break;

            case 8:
                displayDirectoryMetadata(currentDir);
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
  return 0;
}
