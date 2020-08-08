#设置cmake最低版本号
CMAKE_MINIMUM_REQUIRED(VERSION 3.4.0)

#设置工程名称
PROJECT(tinystl)

#查找文件夹中的所有源代码文件，也可以通过Set命令将所有文件设置为一个变量
AUX_SOURCE_DIRECTORY(test SRC_LIST)
#同理，查找当前文件夹中所有的头文件
INCLUDE_DIRECTORIES(include)


#创建工程文件
ADD_EXECUTABLE(${PROJECT_NAME} ${SRC_LIST})

#添加Qt5依赖项
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)