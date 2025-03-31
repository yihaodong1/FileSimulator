#include "ClientInterface.h"

ClientInterface::ClientInterface(const string& username, FileSystem* filesystem)
    : filesystem(filesystem), username(username) {
    // no change
}

std::vector<string> ClientInterface::parseCommand(const string& cmdLine) {
    // TODO: Parse command line into vector of arguments, returns vector of parsed arguments
    // note 1: split by whitespace, you can use strtok() in c or istringstream in c++ to get tokens
    // note 2: handle quote string in two bounds for per token

    size_t index = cmdLine.find('\"');
    string buffer;
    std::vector<string> v;
    if(index != string::npos){ // this cmdLine is write
        string s;
        s.assign(cmdLine, 0, index - 1);
        std::istringstream iss(s);
        while(getline(iss, buffer, ' '))
        {
            v.push_back(buffer);
        }
        s.assign(cmdLine, index, cmdLine.length());
        v.push_back(s);
    }else{
        std::istringstream iss(cmdLine);
        while(getline(iss, buffer, ' '))
        {
            v.push_back(buffer);
        }
    }
    return v;
}

bool ClientInterface::execueCommand(const std::vector<string>& cmd) {
    // TODO: Execute parsed command, returns true if command executed successfully
    // note 1: check first argument for command type
    // note 2: validate number of arguments
    // note 3: call corresponding operation method

    if(cmd[0] =="create"){
        int len = cmd.size();
        for(int i = 1; i < len; i++){
            if(!createFile(cmd[i])){
                fprintf(stderr, "ClientInterface::createFile failed\n");
            }
        }
        /*filesystem->display();*/
    }else if(cmd[0] == "delete"){
        size_t len = cmd.size();
        for(size_t i = 1; i < len; i++){
            if(!deleteFile(cmd[i])){
                fprintf(stderr, "ClientInterface::deleteFile failed\n");
            }
        }
    }else if(cmd[0] == "read"){
        size_t len = cmd.size();
        for(size_t i = 1; i < len; i++){
            std::cout<<"=== " + cmd[i] + " ==="<<std::endl;
            std::cout<<readFile(cmd[i])<<std::endl;
        }
    }else if(cmd[0] == "write"){
        writeFile(cmd[1], cmd[2]);
    }else if(cmd[0] == "mkdir"){
        if(!createDir(cmd[1])){
            fprintf(stderr, "ClientInterface::createDir failed\n");
        }
    }else if(cmd[0] == "rmdir"){
        int res;
        if(cmd[1] == "-r")
            res = deleteDir(cmd[2], true);
        else
            res = deleteDir(cmd[1], false);
        if(!res){
            fprintf(stderr, "ClientInterface::deleteDir failed\n");
        }
    }else if(cmd[0] == "cd"){
        if(!changeDir(cmd[1])){
            fprintf(stderr, "ClientInterface::changeDir failed\n");
        }
    }else if(cmd[0] == "ls"){
        listCurrentDir();
    }else if(cmd[0] == "pwd"){
        std::cout<<getCurrentPath()<<std::endl;
    }else if(cmd[0] == "whoami"){
        std::cout<<username<<std::endl;
    }else if(cmd[0] == "clear"){
        //TODO:
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }else if(cmd[0] == "help"){
        showHelp();
    }else{// exit and quit was handled in VFS
        std::cout<<"Invalid argument\n";
        return true;// if return false, the program would exits
    }
    filesystem->display();
    return true;
}

void ClientInterface::processCommand(const string& cmdLine) {
    // TODO: Process user input command line, no return value
    // note 1: parse command line
    // note 2: execute command
    // note 3: handle exceptions
    std::vector<string> v = parseCommand(cmdLine);
    if(execueCommand(v)){
        return;
    }else{
        std::cout<<"error"<<std::endl;
        assert(0);
    }
    
}

void ClientInterface::showHelp() const {
    // Show help message with all available commands and their usage, no return value
    std::cout << "Available commands:\n"
         << "  create <filename...>      - Create one or more new files\n"
         << "  delete <filename...>      - Delete one or more files\n"
         << "  read <filename...>        - Read content from one or more files\n"
         << "  write <filename> <text>   - Write text to file (supports '\\n' for newline)\n"
         << "  mkdir <dirname>           - Create a new directory\n"
         << "  rmdir [-r] <dirname>      - Remove directory (-r for recursive deletion)\n"
         << "  cd <path>                - Change directory (supports relative/absolute paths)\n"
         << "  ls                       - List current directory contents\n"
         << "  pwd                      - Show current working directory\n"
         << "  whoami                   - Show current user name\n"
         << "  clear                    - clear current command line\n"
         << "  help                     - Show this help message\n"
         << "  exit                     - Logout current user\n"
         << "  quit                     - Exit program\n" << std::endl;
}


bool ClientInterface::createFile(const string& name) {
    // TODO: Create new file with given name, returns true if file created successfully
    // note 1: validate file name
    // note 2: use filesystem to create file

    if(filesystem->createFile(name))
        return true;
    return false;
}

bool ClientInterface::deleteFile(const string& name) {
    // TODO: Delete file with given name, returns true if file deleted successfully
    // note 1: use filesystem to delete file

    return filesystem->deleteFile(name, username);
}

string ClientInterface::readFile(const string& name) {
    // TODO: Read content from file with given name, returns file content as string
    // note 1: search file by name
    // note 2: cast to File type and read content
    uint64_t i = filesystem->search(name, "file");
    File *f = dynamic_cast<File*>(filesystem->getCurrentDir()->getChild(i));
    if(f)
        return f->read();
    else
        assert(0);

}

bool ClientInterface::writeFile(const string& name, const string& data) {
    // TODO: Write data to file with given name, returns true if write successful
    // note 1: search file by name
    // note 2: process quoted strings
    // note 3: cast to File type and write content

    uint64_t i = filesystem->search(name, "file");
    File *f = dynamic_cast<File*>(filesystem->getCurrentDir()->getChild(i));
    if(f){
        string s;
        s.assign(data.begin() + 1, data.end() - 1);
        f->write(s);
        return true;
    }
    return false;
}

bool ClientInterface::createDir(const string& name) {
    // TODO: Create new directory with given name, returns true if directory created successfully
    // note 1: use filesystem to create directory

    if(filesystem->createDir(name))
        return true;
    return false;
}

bool ClientInterface::deleteDir(const string& name, bool recursive) {
    // TODO: Delete directory with given name, returns true if directory deleted successfully
    // note 1: use filesystem to delete directory with recursive flag

    return filesystem->deleteDir(name, username, recursive);
}

bool ClientInterface::changeDir(const string& path) {
    // TODO: Change current directory to given path, returns true if directory changed successfully
    // note 1: resolve path to get target directory
    // note 2: validate target is directory type to set

    FileObj *f = filesystem->resolvePath(path);
    if(f){
        if(f->getType() == "directory"){
            filesystem->setCurrentDir(dynamic_cast<Directory *>(f));
            return true;
        }
    }
    std::cout<< "Path does not exit\n";
    return false;
}

void ClientInterface::listCurrentDir() {
    // TODO: List all contents in current directory, no return value
    // note 1: print each child's name in current directory per line

    std::vector<FileObj*>v = filesystem->getCurrentDir()->getAll();
    for(auto &it: v){
        std::cout<<it->getName()<<std::endl;
    }
}

string ClientInterface::getCurrentPath() const {
    // TODO: Get current working directory path, returns current path as string
    // note 1: use filesystem to get current path

    return filesystem->getCurrentPath();
}

string ClientInterface::search(const string& name, const string& type) {
    // TODO: Search file or directory by name, returns formatted result string
    // note 1: use filesystem to search by name

    uint64_t i = filesystem->search(name, type);
    return "";
}
