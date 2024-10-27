

#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;
struct NODE* lastNode;
char* path;

struct NODE* nodeSearch(struct NODE* node, char* targetName, char* grandpaName){
    if(node == NULL){
        return NULL;
    }
    if(strcmp(node->name, targetName) == 0 && strcmp(node->parentPtr->name, grandpaName) == 0){
        return node;
    }
    struct NODE* foundNode = nodeSearch(node->siblingPtr, targetName, grandpaName);
    if(foundNode != NULL){
        return foundNode;
    }
    return nodeSearch(node->childPtr, targetName, grandpaName);
    
}
//make directory
void mkdir(char pathName[]){

    // TO BE IMPLEMENTED
    //
    // YOUR CODE TO REPLACE THE PRINTF FUNCTION BELOW
    path = malloc(100);
    if(strcmp(pathName, "/") == 0){
        printf("MKDIR ERROR: no path provided\n");
        return;
    }
    char* baseName = malloc(100);
    char* dirName = malloc(100); 
    struct NODE* targetNode = splitPath(pathName, baseName, dirName);
    if(targetNode == NULL){
        char* token = strtok(path, "/");
        struct NODE* checkNode = nodeSearch(root, token, "/");
        while(token != NULL){
            if(checkNode == NULL){
                break;
            }
            token = strtok(NULL, "/");
            checkNode = nodeSearch(root, token, checkNode->name);
        }
        printf("ERROR: Directory %s does not exist\n", path);
        return;
    }
    // check if target directory already in current directoy
    if(nodeSearch(root, baseName, targetNode->name) != NULL){
        printf("MKDIR ERROR: Directory %s already exists\n", path);
        return;
    }
    struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));
    newNode->fileType = 'D';
    newNode->childPtr = NULL;
    newNode->siblingPtr = NULL;
    newNode->parentPtr = targetNode;
    strcpy(newNode->name, baseName);
    if(targetNode->childPtr == NULL){
        targetNode->childPtr = newNode;
    } else {
        lastNode = targetNode->childPtr;
        while(1){
            if(lastNode->siblingPtr == NULL) {
                lastNode->siblingPtr = newNode;
                break;
            }
            lastNode = lastNode->siblingPtr;
        }
    }
    printf("MKDIR SUCCESS: node %s successfully created\n", path);
    return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){

    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HERE
    //
    strcpy(path, pathName);
    if(strcmp(pathName, "/") == 0){
        strcpy(baseName,pathName);
        strcpy(dirName, "");
        return root;
    }
    char* lastSlash = strrchr(pathName, '/');
    char* targetName = malloc(100);
    char* grandpaName = malloc(100);
    if(lastSlash == NULL){
        strcpy(baseName,pathName);
        strcpy(dirName, "");
        return cwd;
    } else {
        strcpy(baseName,lastSlash + 1);
        *lastSlash = '\0';
        baseName = strcpy(dirName, pathName);
        lastSlash = strrchr(pathName, '/');
        if(lastSlash == NULL){
            strcpy(targetName, pathName);
            strcpy(grandpaName, "/");
        } else {
            strcpy(targetName, lastSlash + 1);
            *lastSlash = '\0';
            lastSlash = strrchr(pathName, '/');
            strcpy(grandpaName, pathName);
            if(lastSlash != NULL) {
                strcpy(grandpaName, lastSlash + 1);
            }
         
    
        }

    }
    strcpy(pathName, path);
    return nodeSearch(root, targetName, grandpaName);
}
