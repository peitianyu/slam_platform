file(GLOB_RECURSE ALL_LIBRIRY_HEDS "src/*.h*")
file(GLOB_RECURSE ALL_LIBRIRY_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/*.cc ${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cc)

# 添加头文件
INCLUDE_DIRECTORIES(src)

# 添加动态库
add_library(${PROJECT_NAME} SHARED ${ALL_LIBRIRY_SRCS})

# 安装到本工程的lib文件夹下
set(INSTALL_LIB ${PROJECT_SOURCE_DIR}/install/lib)
set(INSTALL_INCLUDE ${PROJECT_SOURCE_DIR}/install/include)

# 安装lv_math库
install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_LIB})

# 安装头文件
install(DIRECTORY  ./ DESTINATION ${INSTALL_INCLUDE} FILES_MATCHING PATTERN "*.h*")