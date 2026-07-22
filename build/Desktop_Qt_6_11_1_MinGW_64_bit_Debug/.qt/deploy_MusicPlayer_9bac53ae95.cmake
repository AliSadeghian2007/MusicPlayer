include("F:/Project/Cpp/MyCppProjects/MusicPlayer/build/Desktop_Qt_6_11_1_MinGW_64_bit_Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MusicPlayer-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "F:/Project/Cpp/MyCppProjects/MusicPlayer/build/Desktop_Qt_6_11_1_MinGW_64_bit_Debug/MusicPlayer.exe"
    GENERATE_QT_CONF
)
