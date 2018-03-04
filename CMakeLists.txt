cmake_minimum_required(VERSION 2.8)
project(fcvision)


include_directories(".")
include_directories("net")
include_directories("net/http")
include_directories("net/http/handlers")
include_directories("net/tcp")
include_directories("hware")
include_directories("utils")
include_directories("utils/cfg")
include_directories("sys")


set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wextra -Wall -O2")
set(SRC_LIST net/http/httpserver.cpp net/http/httpserver.hpp
             net/http/httpclient.cpp net/http/httpclient.hpp
             net/http/pageparser.cpp net/http/pageparser.hpp
             net/http/handlers/indexhandler.cpp net/http/handlers/indexhandler.hpp
             net/http/handlers/syshandler.cpp net/http/handlers/syshandler.hpp
             net/http/handlers/notfoundhandler.cpp net/http/handlers/notfoundhandler.hpp
             net/http/handlers/errhandler.cpp net/http/handlers/errhandler.hpp
             net/http/handlers/camhandler.cpp net/http/handlers/camhandler.hpp
             net/http/handlers/photohandler.cpp net/http/handlers/photohandler.hpp
             net/http/handlers/fileshandler.cpp net/http/handlers/fileshandler.hpp
             net/http/handlers/handlersmaker.cpp net/http/handlers/handlersmaker.hpp
             net/http/handlers/ihandler.hpp
             net/http/handlers/handlers.hpp
             net/tcp/tcpserver.cpp net/tcp/tcpserver.hpp
             net/tcp/tcpclient.cpp net/tcp/tcpclient.hpp
             net/deviceserver.cpp net/deviceserver.hpp
             sys/system.cpp sys/system.hpp
             utils/log.cpp utils/log.hpp
             utils/locker.cpp utils/locker.hpp
             utils/utils.cpp utils/utils.hpp
             utils/configs.cpp utils/configs.hpp
             utils/cfg/cfgreader.cpp utils/cfg/cfgreader.hpp
             hware/camera.cpp hware/camera.hpp
             threadmanager.cpp threadmanager.hpp
             app.cpp app.hpp
             imodule.hpp
             path.cpp path.hpp
             platform.hpp
             main.cpp)


add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} -lpthread -ljansson -lopencv_core -lopencv_highgui -lopencv_imgproc)
install(FILES fcvision.conf DESTINATION "/etc/")
install(FILES fcvision DESTINATION "/usr/share/fcvision/")
install(FILES templates/html/index.html DESTINATION "/usr/share/fcvision/templates/html/")
install(FILES templates/html/photo.html DESTINATION "/usr/share/fcvision/templates/html/")
install(FILES templates/html/403.html DESTINATION "/usr/share/fcvision/templates/html/")
install(FILES templates/html/404.html DESTINATION "/usr/share/fcvision/templates/html/")
install(FILES templates/css/style.css DESTINATION "/usr/share/fcvision/templates/css/")
