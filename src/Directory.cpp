#include "Directory.h"

Directory::Directory(const string& name, const string& owner, const uint64_t& inode, FileObj* parent)
    :FileObj("", "", "", "", 0, nullptr) { 
    // TODO: finish construction function like File class
    fprintf(stderr, "Error: Directory::Directory() is not implemented yet!\n");
    assert(0);
}

// add, remove
bool Directory::add(FileObj* child) {
    // TODO: add a FileObj to current Directory, return true if add successfully, otherwise false
    // note 1: you can't add a nullptr 
    // note 2: set child's parent pointer
    fprintf(stderr, "Error: Directory::add() is not implemented yet!\n");
    assert(0);
    return true;
}

bool Directory::remove(uint64_t inode) {
    // TODO: Remove child object by inode, return true if remove successfully, otherwise false
    // note 1: free memory if child object need to be removed
    // note 2: only remove files, not directories (use removeDir for directories)
    fprintf(stderr, "Error: Directory::remove() is not implemented yet!\n");
    assert(0);  
    return true;
}

bool Directory::removeDir(uint64_t inode){
    // TODO: Remove directory object by inode, return true if remove successfully, otherwise false
    // note 1: free memory of the directory and all its children recursively
    // note 2: return false if inode not in current directory or target is not a directory
    // note 3: use dynamic_cast to safely convert FileObj* to Directory*
    // note 4: recursively remove all children before removing the directory itself
    fprintf(stderr, "Error: Directory::removeDir() is not implemented yet!\n");
    assert(0);  
    return true;
}

// Getters
FileObj* Directory::getChild(uint64_t inode) {
    // TODO: Get child object by inode if found, otherwise nullptr
    fprintf(stderr, "Error: Directory::getChild() is not implemented yet!\n");
    assert(0);  
    return nullptr;
}

std::vector<FileObj*> Directory::getAll() const {
    // TODO: Get all child objects in vector, may be empty
    fprintf(stderr, "Error: Directory::getAll() is not implemented yet!\n");
    assert(0);  
    return std::vector<FileObj*>();
}

size_t Directory::getCount() const {
    // TODO: Get number of children
    fprintf(stderr, "Error: Directory::getCount() is not implemented yet!\n");
    assert(0);  
    return 0;
}

// helper function
bool Directory::isEmpty() const {
    // TODO: return true if directory is empty, otherwise flase
    fprintf(stderr, "Error: Directory::isEmpty() is not implemented yet!\n");
    assert(0);  
    return false;
}

// helper function
void Directory::display() const {
    std::cout << "[Directory: " << getName() << "]" << std::endl;
    for (const auto& pair : this->children) {
        std::cout << "- " << pair.second->getType() << ": " 
                 << pair.second->getName() << " with owner: " << pair.second->getOwner() << std::endl;
    }
}