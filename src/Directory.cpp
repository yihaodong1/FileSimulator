#include "Directory.h"

Directory::Directory(const string& name, const string& owner, const uint64_t& inode, FileObj* parent)
    :FileObj(name, (parent ? parent->getPath() + name + "/" : "/"), "directory", owner, inode, parent){

}

// add, remove
bool Directory::add(FileObj* child) {
    // TODO: add a FileObj to current Directory, return true if add successfully, otherwise false
    // note 1: you can't add a nullptr 
    // note 2: set child's parent pointer
    if(child){
        std::pair<std::unordered_map<uint64_t, FileObj *>::iterator, bool>flag = children.insert(std::pair(child->getInode(), child));
        if(flag.second){
            child->setParent(this);
            return true;
        }else
            return false;
    }else {
        return false;
    }
}

bool Directory::remove(uint64_t inode) {
    // TODO: Remove child object by inode, return true if remove successfully, otherwise false
    // note 1: free memory if child object need to be removed
    // note 2: only remove files, not directories (use removeDir for directories)
    FileObj *f = getChild(inode);
    if(f == nullptr)
        return false;
    if(f->getType() == "file"){
        if(children.erase(inode)){
            delete f;
            return true;
        }
    }
    return false;
}

bool Directory::removeDir(uint64_t inode){
    // TODO: Remove directory object by inode, return true if remove successfully, otherwise false
    // note 1: free memory of the directory and all its children recursively
    // note 2: return false if inode not in current directory or target is not a directory
    // note 3: use dynamic_cast to safely convert FileObj* to Directory*
    // note 4: recursively remove all children before removing the directory itself
    Directory *dir = dynamic_cast<Directory *>(getChild(inode));
    if(dir == nullptr)
        return false;
    if(dir->getType() != "directory")
        return false;
    if(dir){
        std::vector<FileObj*> objv = dir->getAll();
        size_t len = dir->getCount();
        for(size_t i = 0; i < len; i++){
            if(objv[i]->getType() == "file"){
                if(!dir->remove(objv[i]->getInode()))
                    return false;
            }else if(objv[i]->getType() == "directory"){
                if(!dir->removeDir(objv[i]->getInode()))
                    return false;
            }else
                assert(0);
        }
        if(children.erase(inode)){
            delete dir;
            return true;
        }else
            return false;
    }else
        assert(0);
}

// Getters
FileObj* Directory::getChild(uint64_t inode) {
    // TODO: Get child object by inode if found, otherwise nullptr
    auto it = children.find(inode);
    if(it != children.end()){
        return it->second;
    }
    return nullptr;
}

std::vector<FileObj*> Directory::getAll() const {
    // TODO: Get all child objects in vector, may be empty
    
    std::vector<FileObj*> objv;
    for(auto it = children.begin(); it != children.end(); it++){
        objv.push_back(it->second);
    }
    return objv;
}

size_t Directory::getCount() const {
    // TODO: Get number of children
    return children.size();
}

// helper function
bool Directory::isEmpty() const {
    // TODO: return true if directory is empty, otherwise flase
    return children.empty();
}

// helper function
void Directory::display() const {
    std::cout << "[Directory: " << getName() << "]" << std::endl;
    for (const auto& pair : this->children) {
        std::cout << "- " << pair.second->getType() << ": " 
                 << pair.second->getName() << " with owner: " << pair.second->getOwner() << std::endl;
    }
}
