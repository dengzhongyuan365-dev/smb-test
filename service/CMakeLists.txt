set(SERVICE_NAME mount-service)

# 收集源文件
set(SERVICE_SOURCES
    src/main.cpp
    src/mountservice.cpp
    src/mountservice.h
)

# 添加可执行文件
add_executable(${SERVICE_NAME} ${SERVICE_SOURCES})

# 设置包含目录
target_include_directories(${SERVICE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 链接 Qt 库
target_link_libraries(${SERVICE_NAME}
    PRIVATE
        Qt5::Core
        Qt5::DBus
)

# 安装可执行文件
install(TARGETS ${SERVICE_NAME}
    RUNTIME DESTINATION /usr/local/bin
)

# 安装 DBus 配置文件
install(FILES dbus/com.deepin.test.conf
    DESTINATION /etc/dbus-1/system.d/
)

# 安装 systemd 服务文件
install(FILES systemd/mount-test.service
    DESTINATION /etc/systemd/system/
)

# 添加安装后的 systemd 重新加载命令
install(CODE "execute_process(COMMAND systemctl daemon-reload)")