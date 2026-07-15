cmake_minimum_required(VERSION 3.19)
project(MusicPlayer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(MusicPlayer
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    song.h song.cpp
    album.h album.cpp
    playlist.h playlist.cpp
    user.h user.cpp
    artist.h artist.cpp
    listener.h listener.cpp
    abstractrepository.h abstractrepository.cpp
    accountrepository.h accountrepository.cpp
    songrepository.h songrepository.cpp
    playlistrepository.h playlistrepository.cpp
    listenrrepository.h listenrrepository.cpp
    artistrepository.h artistrepository.cpp
    albumrepository.h albumrepository.cpp
)

target_link_libraries(MusicPlayer
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS MusicPlayer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MusicPlayer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
