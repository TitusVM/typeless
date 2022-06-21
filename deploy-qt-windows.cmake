set(WINDEPLOYQT "C:/Qt/6.2.4/msvc2019_64/bin/windeployqt.exe")
set(COMPONENT_NAME_MAIN "Typeless")
set(CMAKE_CURRENT_SOURCE_DIR "C:/DEV/deuxieme_2/Algo2/projet/typeless")


execute_process(COMMAND ${WINDEPLOYQT} --qmldir ${CMAKE_CURRENT_SOURCE_DIR} ${COMPONENT_NAME_MAIN}/data/bin WORKING_DIRECTORY ${CPACK_TEMPORARY_INSTALL_DIRECTORY}/packages)
