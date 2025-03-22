#include "File.h"

File::File(const string& name, const string& type, const string& owner, const uint64_t& inode, FileObj* parent)
    :FileObj(name, (parent ? parent->getPath() + name : "/" + name), type, owner, inode, parent), content("") {
}

// read and write
string File::read() const {
    // TODO: return file content
    // note 1: you can choose to printf content into stdout in this function or not (Optional)
    return content;
}

bool File::write(const string &data) { 
    //TODO: write data into file content, return true if write successfully, otherwise false
    // note 1: replace "\\n" into new line "\n"
    // for example, when you wrote "Hello PA-1\n" in command line, data will be "Hello PA-1\\n"
    size_t pos = content.size();
    content += data;
    while ((pos = content.find("\\\\n", pos)) != std::string::npos) {
        content.replace(pos, 3, "\n");
        pos += 2; // 移动到"\n"之后
    }
    return true;
}

string File::getContent() const {
    // TODO: retun file content
    return content;
}

// helper function
void File::display() const {
    std::cout << "[File: " << getName() << "] Size: " << content.length() << " bytes" << std::endl;
}
