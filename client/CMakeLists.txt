# 设置客户端名称
set(CLIENT_NAME mount-client)

# 添加可执行文件
add_executable(${CLIENT_NAME}
    src/main.cpp
)

# 设置包含目录
target_include_directories(${CLIENT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 链接 Qt 库
target_link_libraries(${CLIENT_NAME}
    PRIVATE
        Qt5::Core
        Qt5::DBus
)

# 安装目标
install(TARGETS ${CLIENT_NAME}
    RUNTIME DESTINATION bin
)
