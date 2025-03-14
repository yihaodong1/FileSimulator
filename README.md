<div align="center">
  <h1 style="font-size: 2.5em;">欢迎开启 PA-1 学习之旅! 🚀</h1>

 👋 欢迎来到《高级程序设计》2025年春季课程PA-1项目!
 😊 本文档作为实验手册，希望能帮助你顺利完成本次PA项目。
 😎 通过本次 PA 课程的学习，你将了解并掌握以下内容：

  <ul style="font-size: 1.5em; list-style-type: none; padding: 0;">
    <li>🎯 深入理解 <strong>面向对象</strong> 编程思想</li>
    <li>💡 掌握 C++ 类的设计与实现</li>
    <li>🔧 学会构建完整的软件系统</li>
  </ul>

  <p style="font-size: 1.5em;">🎉 Let's Start now!</p>
</div>

<div align="center">
  <h1>PA-1: 虚拟文件系统</h1>
  <h2>Virtual File System with Command Line Interface (VFS) 🌐</h2>
</div>

<div style="display: flex; justify-content: center; gap: 10px;">
  <img src="https://img.shields.io/badge/C++-17-blue?logo=cplusplus" alt="C++17">
  <img src="https://img.shields.io/badge/CMake-3.10+-brightgreen?logo=cmake" alt="CMake">
  <img src="https://img.shields.io/badge/License-MIT-green" alt="License">
</div>

## 🎯 1. 背景介绍

相信大家都使用过文件管理系统，不论是创建文件和删除文件，我们本次PA项目就是构建一个虚拟文件系统(**VFS**),通过维护 **FileSystem** 类来实现文件管理功能。另外，我还为大家设计了 **ClientInterface** 类，用来模拟用户的命令行操作，从而实现接口设计的可视化信息。

*虚拟文件系统（**VFS**）是一个模拟真实文件系统的软件实现。通过面向对象的设计方法，**VFS**提供了文件和目录的基本管理功能，帮助理解文件系统的核心概念和面向对象编程思想。*

🔧 **VFS工作原理**：
1. **文件抽象**：将文件和目录统一抽象为类 `File`, `Directory`，通过 `FileObj` 基类实现继承和多态
2. **目录组织**：使用 `FileSystem` 类组织文件和目录，支持灵活的路径导航
3. **用户交互**：通过 `ClientInterface` 提供命令行界面，支持类Unix风格的文件操作命令
4. **系统集成**： 通过 `VFS` 实现对 `FileSystem` 和 `ClientInterface` 的集成统一管理。

🔄 **系统流程图**：
```mermaid
 graph LR
     A[用户命令] --> B[ClientInterface]
     B --> C[命令解析]
     C --> D[调用FileSystem]
 ```
 ```mermaid
 graph LR
     D[调用FileSystem] --> E[文件/目录操作]
     E --> F[更新系统状态]
     F --> G[返回结果]
 ```
> 💡 **核心组件说明**
> - **ClientInterface**：命令解析与用户交互
> - **FileSystem**：文件系统核心逻辑
> - **FileObj及其派生类**：文件/目录的面向对象实现
> - **VFS**: 集成管理上述所有类

<div style="background-color: #ffe6e6; border-left: 4px solid #f44336; padding: 15px; margin: 20px 0; border-radius: 4px;">
<span style="font-size: 20px;">💡 <strong>划重点！</strong></span><br>
<strong>本次PA项目待完成的组件及其功能描述：

| 组件 | 功能描述 |
|:------:|:----------:|
| `ClientInterface` | 负责命令解析和用户交互 |
| `FileSystem` | 实现文件和目录的管理功能 |
| `FileObj及派生类` | 提供文件和目录的具体实现 |
</strong>

项目任务：使用**面向对象**方法实现这三个核心组件，构建完整的**VFS**系统。
</div>

</div>
</div>

## 🚀 2. 学习目标

| 目标类型 | 具体内容 |
|---------|----------|
| 📚 **类设计** | 掌握C++类的设计与实现 |
| 🧩 **继承多态** | 理解并应用继承与多态 |
| 🧠 **系统构建** | 使用组合与嵌套类构建复杂系统 |
| 🔒 **封装原则** | 实现访问控制与封装 |

## 🌈 3. 前瞻学习

建议在实现PA-1前或过程中了解以下内容：
- **数组**: `vector<T>` 及其 `push(T)` `pop()`方法
- **字典**: `unordered_map<key, value>` 以及 增删改查 操作
- **集合**: `set<T>` 及其 `find(T)` `insert(T)` 方法
- **数据类型**：`enum`，`size_t`
- **字符串**： `string`
- **输入输出流** `isstringstream`
- **OOP原则**：继承、多态、封装、抽象
- (在PA不同设计过程中一定要注意**抽象一个level**!)


## 👏 4. 项目树框架

<div style="background-color:rgb(46, 38, 38); border-radius: 8px; padding: 20px; margin: 20px 0; font-family: 'Consolas', monospace;">
  <div style="color: #569cd6; margin-bottom: 10px;">FileSimulator/</div>
  <div style="color: #dcdcaa; margin-left: 20px;">├── <span style="color: #c586c0;">CMakeLists.txt</span></div>
  <div style="color: #dcdcaa; margin-left: 20px;">├── <span style="color: #4ec9b0;">include/</span></div>
  <div style="color: #dcdcaa; margin-left: 40px;">├── <span style="color: #9cdcfe;">FileObj.h</span></div>
  <div style="color: #dcdcaa; margin-left: 40px;">├── <span style="color: #9cdcfe;">Directory.h</span></div>
  <div style="color: #dcdcaa; margin-left: 40px;">├── <span style="color: #9cdcfe;">FileSystem.h</span></div>
  <div style="color: #dcdcaa; margin-left: 40px;">├── <span style="color: #9cdcfe;">VFS.h</span></div>
  <div style="color: #dcdcaa; margin-left: 40px;">└── <span style="color: #9cdcfe;">ClientInterface.h</span></div>
  <div style="color: #dcdcaa; margin-left: 20px;">├── <span style="color: #4ec9b0;">src/</span></div>
  <div style="color: #dcdcaa; margin-left: 40px;">├── <span style="color: #ce9178;">main.cpp</span></div>
  <div style="color: #dcdcaa; margin-left: 40px;">├── <span style="color: #ce9178;">FileObj.cpp</span></div>
  <div style="color: #dcdcaa; margin-left: 40px;">├── <span style="color: #ce9178;">Directory.cpp</span></div>
  <div style="color: #dcdcaa; margin-left: 40px;">├── <span style="color: #ce9178;">FileSystem.cpp</span></div>
  <div style="color: #dcdcaa; margin-left: 40px;">├── <span style="color: #ce9178;">VFS.cpp</span></div>
  <div style="color: #dcdcaa; margin-left: 40px;">└── <span style="color: #ce9178;">ClientInterface.cpp</span></div>
  <div style="color: #dcdcaa; margin-left: 20px;">└── <span style="color: #c586c0;">README.md</span></div>
</div>

## ✨ 5. 实验指南

<div style="background-color: #f8f9fa; border-left: 4px solid #6c757d; padding: 15px; margin: 20px 0; border-radius: 4px;">
<h3 style="color: #2c3e50; margin-top: 0;">5-0. InodeFactory 类 (include/InodeFactory.h)</h3>

```cpp
class InodeFactory{
public:
    static uint64_t generateInode(){
        static uint64_t nextInode = 1;
        return nextInode++;
    }
};
```
在VFS中， 所有的系统对象（File\Directory）都会拥有唯一的inode标识，类型为uint64_t(which is unsigned long long)。

对于这一全局标识变量的设计，我们已经为你提供了generateInode()这一接口实现，你可以尽情调用这一API接口，默认情况下，FileSystem初始化的根目录"/"具有inode = 1。

所以理论上讲，任意新建文件或文件夹都具有 inode >= 2(我们的VFS并没有设计inode回收机制，所以每次调用新的inode，它都只会变大，且不会出现两次相同的inode)
</div>

<div style="background-color: #f8f9fa; border-left: 4px solid #6c757d; padding: 15px; margin: 20px 0; border-radius: 4px;">
<h3 style="color: #2c3e50; margin-top: 0;">5-1. FileObj（Base class）</h3>

```cpp
class FileObj {
    string name;     // 文件/目录名
    string path;     // 绝对路径
    string type;     // "file"或"directory"
    string owner;    // 所有者
    uint64_t inode;  // 唯一标识符
    FileObj* parent; // 父目录
}
```
对于FileObj，各个属性的含义如上注释所说，其中，inode来自于上述所说的InodeFactory类，而parent可以理解为是*当前文件/文件夹的父目录*，对于'/'根目录，它的parent为nullptr。

另外，我们已经为你实现了对应的API接口与File类的构造函数，你可以学习File和FileObj的构造函数中path属性的设置方法，你可以依照此完成其他类的构造函数。
</div>

<div style="background-color: #f8f9fa; border-left: 4px solid #6c757d; padding: 15px; margin: 20px 0; border-radius: 4px;">
<h3 style="color: #2c3e50; margin-top: 0;">5-2. File class</h3>

```cpp
(include/File.h)
class File: public FileObj{
protected:
    string content; // content of the file
}
```
File类只在FileObj的基础上新增了content这一属性。
```cpp
(src/File.cpp) 
- File(const string& name, const string& type, const string& owner,
       const uint64_t& inode, FileObj* parent);

- virtual string read() const;            // read content
- virtual bool write(const string &data); // write content(you can just append it to content), deal with escape character "\"
- virtual string getContent() const;      // get content
```
这一File类较为简单，我们已经为你实现了构造函数，你只需要完成读写操作的API即可。
更详细的内容请参考框架代码的TODO内容。
</div>

<div style="background-color: #f8f9fa; border-left: 4px solid #6c757d; padding: 15px; margin: 20px 0; border-radius: 4px;">
<h3 style="color: #2c3e50; margin-top: 0;">5-3. Directory class</h3>

```cpp
(src/Directory.cpp)
class Directory: public FileObj {
    std::unordered_map<uint64_t, FileObj*> children;  // store child objects
}
```
对于Directory class，在FileObj的基础上，新增了一个chidren属性， 类型是`unordered_map<uint64_t. FileObj*>`，作用是：用我们前面设计的Inode，来映射对应的FileObj* 指针，也即：存储当前目录下的*所有子项*。

<div style="background-color: #e7f3fe; border-left: 6px solid #2196F3; padding: 15px; margin: 15px 0; border-radius: 4px;">
<strong>💡 提示：</strong><br>
由于inode映射到的是基类指针，所以，你在访问前一般要根据它的type类型来进行类型提升(你可以使用强制类型转换，也可以使用函数<code>dynamic_cast&lt;T&gt;()</code>来实现安全的类型转换)。
</div>

```cpp
(src/Directory.cpp)
- Directory(const string& name, const string& owner, 
            const uint64_t& inode, FileObj* parent);

- bool add(FileObj* child);             // 添加子节点
- bool remove(uint64_t inode);          // 删除文件节点
- bool removeDir(uint64_t inode);       // 递归删除目录节点
- FileObj* getChild(uint64_t inode);    // 获取指定子节点
- std::vector<FileObj*> getAll() const; // 获取所有子节点
- size_t getCount() const;              // 获取子节点数量
- bool isEmpty() const;                 // 检查是否为空目录
```
`Directory`类的构造函数可以参考之前实现的`File`类，对应其他API接口的实现内容如上所示，需要注意的是，remove删除的是子文件，而removeDir删除的是子文件夹，由于这一子文件夹可能还有文件、文件夹，所以需要递归调用完成节点删除。

<div style="background-color: #e7f3fe; border-left: 6px solid #2196F3; padding: 15px; margin: 15px 0; border-radius: 4px;">
<strong>💡 提示：</strong><br>
这里删除子节点时，用且仅用inode作为唯一标识。<br>
更详细的内容请参考框架代码的TODO内容。
</div>
</div>

<div style="background-color: #f8f9fa; border-left: 4px solid #6c757d; padding: 15px; margin: 20px 0; border-radius: 4px;">
<h3 style="color: #2c3e50; margin-top: 0;">5-4. FileSystem (Core functionality)</h3>

```cpp
(include/FileSystem.h)
class FileSystem {
    Directory* root;     // root directory
    Directory* cur;      // current directory
    string username;     // current user
    std::set<string> users;  // all users
    std::unordered_map<string, uint64_t> config_table;  // path to inode mapping
}
```
FileSystem是`VFS`的核心类，它的属性如上所示，其中`root`是文件系统的根目录，`cur`是文件系统的当前目录，`username`是当前用户，`users`是所有注册在内的用户，而`config_table`是一个`unordered_map`，将一个对象的 *绝对路径 + 类型* 映射到它的唯一表示`inode`上（或许这一设计并不完美，但在`search()`函数里搜索文件/文件夹名时会有高效的结果，而且在其他的API接口中也会经常使用`search()`函数）。

```cpp
(src/FileSystem.cpp)
// 目录导航
- changeDir(const uint64_t& inode)     // 切换当前目录
- getCurrentPath() const               // 获取当前路径
- resolvePath(const string& path)      // 解析路径

// 文件操作
- createFile(const string& name)       // 创建文件
- deleteFile(const string& name, const string& user)  // 删除文件

// 目录操作
- createDir(const string& name)        // 创建目录
- deleteDir(const string& name, const string& user, bool recursive)  // 删除目录

// 搜索和用户管理
- search(const string& name, const string& type)       // 搜索文件或目录
- setUser(const string& username)                      // 设置当前用户
- hasUser(const string& username)                      // 检查用户是否存在 
- registerUser(const string& username)                 // 注册新用户
```
各个函数的含义如上所示，更多的TODO内容详见框架代码。

<div style="background-color: #e7f3fe; border-left: 6px solid #2196F3; padding: 15px; margin: 15px 0; border-radius: 4px;">
<strong>💡 提示：</strong><br>
1. 在创建文件/文件夹时不需要权限控制，而删除文件/文件夹时需要注意权限控制，只有<code>owner</code>或者<code>root</code>用户可以删除对应文件/文件夹。<br>
2. <code>changeDir()</code>函数中需要调用<code>resolvePath()</code>函数，而在这一函数中，你需要通过'/'来划分字符串，你可以选择C标准库中的<code>strtok()</code>函数，也可以通过C++中的<code>istringstream</code>字符串流通过<code>getline(istringstream, string, '/')</code>来获取每一个解析出来的<code>token</code>。<br>
3. 不论是增加还是删除，你除了维护当前文件夹的<code>children</code>外，还需要维护全局<code>config_table</code>属性。<br>
4. 不同的用户应该共享同一个文件系统，在不同用户使用文件系统时，需要维护集合<code>users</code>（可以通过<code>insert</code>或者<code>remove</code>等函数修改<code>set</code>集合）。<br>
</div>
</div>

<div style="background-color: #f8f9fa; border-left: 4px solid #6c757d; padding: 15px; margin: 20px 0; border-radius: 4px;">
<h3 style="color: #2c3e50; margin-top: 0;">5-5. ClientInterface (User interface)</h3>

```cpp
(include/ClientInterface.h)
class ClientInterface {
    FileSystem* filesystem;  // filesystem instance
    string username;         // current user
}
```
在ClientInterface这一类中，只拥有filesystem的指针和用户名username，你可能对这一设计模式略感疑惑(明明在FileSystem里面直接调用API就行，为什么还要这么麻烦)，其实我们是按照访问者模式进行设计，你可以这样理解：用户其实只拥有对文件系统的访问权限，而不应该直接嵌入文件系统中；同时，文件系统应该只负责文件管理功能，而不需要有任何解析、除了命令的部分。

所以，聪明的你可能已经发现了，在这一类中，除了命令处理的部分，其他的大多数函数都可以通过filesystem的指针调用API直接实现。
```cpp
ClientInterface类 (src/ClientInterface.cpp)
// 命令处理
- parseCommand(const string& cmdLine)   // 解析命令行
- execueCommand(const vector<string>& cmd)  // 执行命令
- processCommand(const string& cmdLine)     // 处理命令

// 文件操作命令
- createFile(const string& name)           // 创建文件
- deleteFile(const string& name)           // 删除文件
- readFile(const string& name)             // 读取文件
- writeFile(const string& name, const string& data)  // 写入文件·

// 目录操作命令
- createDir(const string& name)            // 创建目录
- deleteDir(const string& name, bool recursive)  // 删除目录
- changeDir(const string& path)            // 切换目录
- listCurrentDir()                         // 列出目录内容
- getCurrentPath() const                   // 获取当前路径

// 其他命令
- showHelp() const                                  // 显示帮助信息
- search(const string& name, const string& type)    // 搜索文件或目录
```
ClientInterface的函数接口如上所示，正如前面所说，对于这部分内容，你可以非常容易的实现文件系统的功能API，剩下的就是对于输入命令行的处理。

`parseCommand` 函数就是将输入的命令行按照**空格切片**，得到字符串数组传入 `execueCommand` 函数;

`execueCommand`就是通过传入的字符串数组`cmd`，根据`cmd[0]`选择具体是哪个命令，而剩下的无非就是该命令的参数`args`，你只需要把这些`args`传入之前你实现文件系统的API即可。 

至于`processCommand`，就是把上面两个函数整合到一起，先调用`parseCommand`,再调用`execueCommand`就行了。
</div>

<div style="background-color: #f8f9fa; border-left: 4px solid #6c757d; padding: 15px; margin: 20px 0; border-radius: 4px;">
<h3 style="color: #2c3e50; margin-top: 0;">5-6. 需要实现的命令</h3>

```bash
# 文件操作
create <filename...>     # 创建一个或多个文件
delete <filename...>     # 删除一个或多个文件
read <filename...>       # 读取一个或多个文件内容
write <filename> <text>  # 写入文件内容（支持多行文本和转义字符）

# 目录操作
mkdir <dirname>         # 创建目录
rmdir [-r] <dirname>    # 删除目录（-r 表示递归删除）
cd <path>               # 切换目录（支持相对,绝对路径, ..路径, . 路径）
ls                      # 列出当前目录内容
pwd                     # 显示当前工作目录
clear                   # 命令行清屏操作

# 系统命令
help                   # 显示帮助信息
exit                   # 退出登录
quit                   # 退出系统
```
</div>

<div style="background-color: #f8f9fa; border-left: 4px solid #6c757d; padding: 15px; margin: 20px 0; border-radius: 4px;">
<h3 style="color: #2c3e50; margin-top: 0;">5-7. 注意事项</h3>

<div style="display: grid; grid-template-columns: repeat(2, 1fr); gap: 20px; margin: 20px 0;">

<div style="background-color: #fff3cd; border-left: 6px solid #ffc107; padding: 10px; border-radius: 4px;">
<strong>⚠️ 错误处理</strong>
<ul>
  <li>文件已存在</li>
  <li>路径不存在</li>
  <li>权限不足</li>
  <li>参数错误</li>
</ul>
</div>

<div style="background-color: #d4edda; border-left: 6px solid #28a745; padding: 10px; border-radius: 4px;">
<strong>👤 用户管理</strong>
<ul>
  <li>用户创建</li>
  <li>权限验证</li>
  <li>会话交互管理</li>
</ul>
</div>

<div style="background-color: #e7f3fe; border-left: 6px solid #2196F3; padding: 10px; border-radius: 4px;">
<strong>📁 文件操作</strong>
<ul>
  <li>空文件处理</li>
  <li>递归删除</li>
  <li>路径解析</li>
  <li>权限验证</li>
</ul>
</div>

<div style="background-color: #f8d7da; border-left: 6px solid #dc3545; padding: 10px; border-radius: 4px;">
<strong>⚡ 内存管理</strong>
<ul>
  <li>正确释放对象</li>
  <li>避免内存泄漏</li>
  <li>防止悬空指针</li>
</ul>
</div>

</div>
</div>

## 🚀 6. 构建和执行

### 6-1 Windows 环境

1. 生成项目
```bash
# 在项目根目录下执行
mkdir build
cd build
cmake ..
cmake --build .
```
2. 运行程序
```bash
# 在 build/bin/Debug 或 build/bin/Release 目录下
FileSimulator.exe
```

### 6-2 Linux 环境
1. 安装依赖
```bash
# Ubuntu/Debian
sudo apt-get install build-essential cmake

# CentOS/RHEL
sudo yum groupinstall "Development Tools"
sudo yum install cmake
```

2. 生成和编译
```bash
mkdir build
cd build
cmake ..
make
```
3. 运行程序
```bash
# 在 build/bin 目录下
./FileSimulator
```


### 6-3 常见问题排查
```
1. CMake 报错
   - 确保 CMake 版本 >= 3.10
   - 检查编译器是否正确安装
   - 确保环境变量正确设置

2. 编译错误
   - 检查是否有未安装的依赖
   - 确保使用了正确的生成器
   - 查看详细的编译日志

3. 运行错误
   - 确保在正确的目录下运行程序
   - 检查是否有缺失的动态库
   - 查看程序的错误输出
```

<div style="background-color: #f8f9fa; border-left: 4px solid #6c757d; padding: 15px; margin: 20px 0; border-radius: 4px;">
<h3 style="color: #2c3e50; margin-top: 0;">7. 示例代码</h3>

```bash
# Start the system
$ ./FileSimulator
File System Simulator Started
Please login with your username
Login: root

# Show help
root@FileSimulator:/$ help
Available commands:
  create <filename...>      - Create one or more new files
  delete <filename...>      - Delete one or more files
  read <filename...>        - Read content from one or more files
  write <filename> <text>   - Write text to file (supports '\\n' for newline)
  mkdir <dirname>           - Create a new directory
  rmdir [-r] <dirname>      - Remove directory (-r for recursive deletion)
  cd <path>                - Change directory (supports relative/absolute paths)
  ls                       - List current directory contents
  pwd                      - Show current working directory
  whoami                   - Show current user name
  clear                    - Clear current command line
  help                     - Show this help message
  exit                     - Logout current user
  quit                     - Exit program

# Some Basic operations
root@FileSimulator:/$ mkdir docs
root@FileSimulator:/$ cd docs
root@FileSimulator:/docs$ create readme1 readme2
root@FileSimulator:/docs$ write readme1 "This is a test file."
root@FileSimulator:/docs$ write readme2 "Hello PA-1"
root@FileSimulator:/docs$ read readme1 readme2
=== readm1 ===
This is a test file.
=== readm2 ===
Hello PA-1
root@FileSimulator:/docs$ pwd 
/docs
root@FileSimulator:/docs$ ls
readme1
readme2
root@FileSimulator:/docs$ exit

# exit the program
User Login (Please input who you are): 
exit
Bye!
```
</div>


### 如在实验过程中有任何疑问，请及时联系助教，感谢您的阅读！