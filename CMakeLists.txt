project(aeircd CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake/Modules
)

set(AEIRCD_SOURCES src/main.cpp src/aeircd.cpp src/Logger.cpp src/Message.cpp)
set(AEIRCD_HEADERS src/aeircd.hpp src/SysDep.hpp src/Logger.hpp src/Logger.hpp src/Message.hpp)

if(WIN32 AND NOT UNIX)
  set(AEIRCD_SOURCES ${AEIRCD_SOURCES} src/SysDep_win32.cpp)
elseif(UNIX AND NOT WIN32)
  set(AEIRCD_SOURCES ${AEIRCD_SOURCES} src/SysDep_unix.cpp)
endif(WIN32 AND NOT UNIX)


include(EnsureOutOfSourceBuild)

EnsureOutOfSourceBuild("Out-of-source build required.")

find_package( Boost 1.47.0 COMPONENTS system regex thread )
find_package( OpenSSL )
if(Boost_FOUND AND OPENSSL_FOUND)
    include_directories(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})
    link_directories(${Boost_LIBRARY_DIRS})
    
    if(WIN32)
        add_definitions(-D_WIN32_WINNT=0x0501 -D_CRT_SECURE_NO_WARNINGS -D_ATL_SECURE_NO_WARNINGS -D_AFX_SECURE_NO_WARNINGS)
    endif(WIN32)
    
    add_executable(aeircd ${AEIRCD_HEADERS} ${AEIRCD_SOURCES})
    target_link_libraries(aeircd ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})
    
    install(TARGETS aeircd
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)
    if(WIN32 AND NOT UNIX)
      install(CODE "file(MAKE_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/logs/\")")
      install(CODE "file(MAKE_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/config/\")")
    endif(WIN32 AND NOT UNIX)
endif(Boost_FOUND AND OPENSSL_FOUND)
