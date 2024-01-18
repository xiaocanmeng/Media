// #include <iostream>
// #include <filesystem>
// #include <sys/stat.h>  // 添加这一行

// void createTestPaths() {
//     // 1. 一个总长度为127的路径
//     std::string path1 = "/home/dev/";
//     path1.append(127 - path1.size(), 'a');
//     std::filesystem::create_directories(path1);

//     // 2. 一个总长度为128的路径
//     std::string path2 = "/home/dev/";
//     path2.append(128 - path2.size(), 'b');
//     std::filesystem::create_directories(path2);

//     // 3. 一个没有写权限的路径，长度小于127
//     std::string path3 = "/home/dev/nopermission";
//     std::filesystem::create_directories(path3);
//     // 设置没有写权限
//     chmod(path3.c_str(), S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
// }

// int main() {
//     createTestPaths();
//     std::cout << "Test paths created successfully." << std::endl;
//     return 0;
// }


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

bool hasWritePermission(const std::string& path) {
    // 使用 access 函数检查写入权限
    if (access(path.c_str(), W_OK) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    // 指定要检查权限的路径
    std::string pathToCheck = "/home/dev/nopermission";

    // 调用函数检查权限
    if (hasWritePermission(pathToCheck)) {
        std::cout << "The path has write permission." << std::endl;
    } else {
        std::cout << "The path does not have write permission." << std::endl;
    }

    return 0;
}
