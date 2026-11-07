cmake_minimum_required(VERSION 3.16)
project(DogShelterManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt's meta-object compiler (needed for signals/slots and QObject subclasses)
set(CMAKE_AUTOMOC ON)

# Qt 6 preferred, Qt 5.15 accepted.
# If CMake can't find Qt, pass its location, e.g.
#   -DCMAKE_PREFIX_PATH=C:/Qt/6.8.0/msvc2022_64
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SOURCES
    src/main.cpp
    src/Dog.cpp
    src/DogValidator.cpp
    src/Exceptions.cpp
    src/MemoryRepository.cpp
    src/TextFileRepository.cpp
    src/AdminService.cpp
    src/UserService.cpp
    src/Action.cpp
    src/ActionAdd.cpp
    src/ActionRemove.cpp
    src/ActionUpdate.cpp
    src/AdoptionList.cpp
    src/CSVAdoptionList.cpp
    src/HTMLAdoptionList.cpp
    src/AdoptionListTableModel.cpp
    src/ChartWidget.cpp
    src/AdminGUI.cpp
    src/UserGUI.cpp
)

add_executable(shelter_app ${SOURCES})
target_include_directories(shelter_app PRIVATE src)
target_link_libraries(shelter_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Don't open a console window behind the GUI on Windows / build a .app on macOS
set_target_properties(shelter_app PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

if(MSVC)
    target_compile_options(shelter_app PRIVATE /utf-8)
endif()

# The app reads "dogs.txt" from its working directory: ship the sample data
# next to the executable so it works straight out of the build folder.
add_custom_command(TARGET shelter_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/data/dogs.txt
            $<TARGET_FILE_DIR:shelter_app>/dogs.txt
)

# On Windows, copy the Qt DLLs next to the .exe so it can be double-clicked.
if(WIN32)
    get_target_property(_qmake Qt${QT_VERSION_MAJOR}::qmake IMPORTED_LOCATION)
    get_filename_component(_qt_bin "${_qmake}" DIRECTORY)
    find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin}")
    if(WINDEPLOYQT)
        add_custom_command(TARGET shelter_app POST_BUILD
            COMMAND "${WINDEPLOYQT}" --no-translations
                    $<IF:$<CONFIG:Debug>,--debug,--release>
                    $<TARGET_FILE:shelter_app>
            COMMENT "Copying Qt runtime next to shelter_app.exe"
        )
    endif()
endif()

# `cmake --install build --prefix <dir>` produces a self-contained folder
install(TARGETS shelter_app
    RUNTIME DESTINATION .
    BUNDLE DESTINATION .
)
install(FILES data/dogs.txt DESTINATION .)
