cmake_minimum_required(VERSION 3.8)
project(nev_launch)

# 查找依赖
find_package(ament_cmake REQUIRED)

# 安装launch文件
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()