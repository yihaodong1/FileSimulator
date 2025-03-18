#include "FileSystem.h"

FileSystem::FileSystem(const string& username, const uint64_t& inode)
    : root(new Directory("", username, inode, nullptr)), cur(root), username(username) {
    // no change
    users.insert(username);
}

// Navigation
bool FileSystem::changeDir(const uint64_t& inode) {
    // TODO: Change current directory using inode directly, return true if change successfully, otherwise false
    // note 1: check if the inode exists in children [or parent] and if target is directory
    // note 2: update current directory pointer
    
    fprintf(stderr, "Error: FileSystem::changeDir() is not implemented yet!\n");
    assert(0);  
    return false;
}

// File operation "local"
File* FileSystem::createFile(const string& name) {
    // TODO: Create a new file in current directory, return File* if create successfully, otherwise nullptr
    // note 1: check if name already exists
    // note 2: generate new inode via InodeFactory, and update config_table
    string fullname = cur->getPath()+name;
    if(config_table.find(fullname) != config_table.end()){
        return nullptr;
    }
    /*std::vector<FileObj *> v = cur->getAll();*/
    /*for(auto it = v.begin(); it != v.end(); it++){*/
    /*    if((*it)->getName() == name){*/
    /*        return nullptr;*/
    /*    }*/
    /*}*/
    uint64_t i = search(name, "file");
    if(i)
        return nullptr;
    i = InodeFactory::generateInode();
    File *f = new File(name, "file", username, i, cur);
    if(cur->add(f)){
        config_table.insert(std::pair(f->getPath(), i));
        return f;
    }
    delete f;
    return nullptr;
}

bool FileSystem::deleteFile(const string& name, const string& user){
    // TODO: Delete file with given inode from current directory, return true if delete successfully, otherwise false
    // note 1: check if the inode exists and if target is a file, and check permission via user and file owner
    // note 2: update config_table

    uint64_t i = search(name, "file");
    if(i==0)
        return false;
    FileObj* f = cur->getChild(i);
    if(f->getOwner() == username){
        if(cur->remove(i)){
            config_table.erase(f->getPath());
            return true;
        }
    }
    return false;
}

// Dir operation "local"
Directory* FileSystem::createDir(const string& name) {
    // TODO: Create a new directory in current directory, return Directory* if create successfully, otherwise nullptr
    // note 1: check if name already exists
    // note 2: generate new inode via InodeFactory, and update config_table

    uint64_t i = search(name, "directory");
    if(i)
        return nullptr;
    i = InodeFactory::generateInode();
    Directory *d = new Directory(name, username, i, cur);
    if(cur->add(d)){
        config_table.insert(std::pair(d->getPath(), i));
        return d;
    }
    delete d;
    return nullptr;
}

bool FileSystem::deleteDir(const string& name,const string& user, bool recursive){
    // TODO: Delete directory with given name from current directory, return true if delete target successfully, otherwise false 
    // note 1: if recursive is true, delete all contents and their config_table entries, and check permission via user and directory owner
    // note 2: if recursive is false, only delete if empty

    uint64_t i = search(name, "directory");
    if(i == 0)
        return false;
    FileObj* f = cur->getChild(i);
    if(f->getOwner() == username){
        if(recursive){
            std::vector<FileObj*> v = dynamic_cast<Directory *>(f)->getAll();
            for(auto &it: v){
                if(it->getType() == "file"){
                    std::cout<<name+"/"+it->getName()<<std::endl;
                    deleteFile(name + "/"+ it->getName(), user);
                }else{
                    deleteDir(name + "/" + it->getName() + "/", user, recursive);
                }
            }
            if(cur->removeDir(i)){
                config_table.erase(f->getPath());
                return true;
            }
        }else{
            Directory* d = dynamic_cast<Directory *>(f);
            if(d->isEmpty() && cur->removeDir(i)){
                config_table.erase(f->getPath());
                return true;
            }
        }
    }
    return false;
}

// File and Dir operation "Global"
uint64_t FileSystem::search(const string& name, const string& type) {
    // TODO: Search name in config_table, return inode if found in config_table, 0 if not found
    // note 1: try to find relative path (current path + name) in config_table
    // note 2: try to find absolute path (from root) in config_table first
    
    string fullname = cur->getPath()+name;
    if(type == "directory")
        fullname += "/";
    if(config_table.find(fullname) == config_table.end()){
        return 0;
    }
    uint64_t i = config_table.find(fullname)->second;
    if(cur->getChild(i)->getType() == type)
        return i;
    return 0;

}

// Getters
string FileSystem::getCurrentPath() const{
    // TODO: Get the full path of current directory
    // note 1: combine path from root to current directory
    // note 2: handle special case when at root

    return cur->getPath();
}

string FileSystem::getUserName() const {
    // TODO: Get current username

    return username;
}

// Setters
bool FileSystem::setUser(const string& username) {
    // TODO: Set new User to use FileSystem
    // note 1: check if the user is in set of users
    // note 2: update current user

    if(users.find(username) != users.end()){
        this->username = username;
        return true;
    }
    return false;
}

bool FileSystem::setCurrentDir(Directory* newDir){
    // TODO: Set new current dir in FileSystem, return true if set successfully, otherwise false

    if(newDir->getType() == "directory"){
        cur = newDir;
        return true;
    }
    return false;
}

// User management methods
bool FileSystem::hasUser(const string& username) const {
    // TODO: Check if user exists in users set, returns true if username exists, otherwise false
    if(users.find(username) != users.end())
        return true;
    return false;
}

bool FileSystem::registerUser(const string& username) {
    // TODO： Check if user exists in users set, return true if register successfully, otherwise false

    if(users.find(username) == users.end()){
        users.insert(username);
        return true;
    }
    return false;
}

// helper function
FileObj* FileSystem::resolvePath(const string& path) {
    // TODO: resolve path, you can use strtok() in c library or istringstream with getline() in c++
    // return target of FileObj* if resolve successfully, otherwise nullptr

    FileObj *tmp = nullptr;
    if(path[0] == '/')
        tmp = root;
    else
        tmp = cur;
    std::istringstream iss(path);
    string buffer;
    std::vector<string> v;
    while(getline(iss, buffer, '/') && tmp)
    {
         if(buffer == "."){
            tmp = tmp;
         }else if(buffer == ".."){
            tmp = tmp->getParent();
         }else{
            string fullname = tmp->getPath()+buffer+"/";
            if(config_table.find(fullname) == config_table.end()){
                return nullptr;
            }
            uint64_t i = config_table.find(fullname)->second;
            tmp = dynamic_cast<Directory *>(tmp)->getChild(i);
        }
    }
    return tmp;
}

void FileSystem::display(){
    std::cout << "[FileSystem: ]" << std::endl;
    for (const auto& pair : this->config_table) {
        std::cout << "- " << pair.first << ": " 
                 << pair.second << std::endl;
    }
}
