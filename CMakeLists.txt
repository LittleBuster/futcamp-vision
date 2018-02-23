cmake_minimum_required(VERSION 2.8)
project(fcvision)


include_directories(".")
include_directories("net")
include_directories("net/http")
include_directories("net/handlers")
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
             net/tcp/tcpserver.cpp net/tcp/tcpserver.hpp
             net/tcp/tcpclient.cpp net/tcp/tcpclient.hpp
             net/deviceserver.cpp net/deviceserver.hpp
             net/handlers/indexhandler.cpp net/handlers/indexhandler.hpp
             net/handlers/syshandler.cpp net/handlers/syshandler.hpp
             net/handlers/notfoundhandler.cpp net/handlers/notfoundhandler.hpp
             net/handlers/errhandler.cpp net/handlers/errhandler.hpp
             net/handlers/camhandler.cpp net/handlers/camhandler.hpp
             net/handlers/photohandler.cpp net/handlers/photohandler.hpp
             net/handlers/handlersmaker.cpp net/handlers/handlersmaker.hpp
             net/handlers/ihandler.hpp
             net/handlers/handlers.hpp
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
target_link_libraries(${PROJECT_NAME} -lpthread -ljansson -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio)
install(FILES fcvision.conf DESTINATION "/etc/")
install(FILES fcvision DESTINATION "/usr/share/fcvision/")
install(FILES templates/index.html DESTINATION "/usr/share/fcvision/templates/")
