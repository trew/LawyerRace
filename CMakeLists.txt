cmake_minimum_required(VERSION 3.15)

project(lwrace)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(tclap REQUIRED)

add_executable(lwrace
    src/LawyerRace/Core/Config.cpp
    src/LawyerRace/Core/GameState.cpp
    src/LawyerRace/Core/LawyerRace.cpp
    src/LawyerRace/Core/main.cpp
    src/LawyerRace/Core/MenuState.cpp
    src/LawyerRace/Core/PlayerControls.cpp
    src/LawyerRace/Core/SettingsState.cpp
    src/LawyerRace/Entity/AbstractEntity.cpp
    src/LawyerRace/Entity/Dollar.cpp
    src/LawyerRace/Entity/Enemy.cpp
    src/LawyerRace/Entity/Player.cpp
    src/LawyerRace/Entity/Rock.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/../LawyerEngine/include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_image_INCLUDE_DIR}
    ${SDL2_ttf_INCLUDE_DIR}
)

# TODO create a better dependency to LawyerEngine
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../LawyerEngine/build/Release/liblwengine.dylib)

target_link_libraries(${PROJECT_NAME} PRIVATE tclap::tclap)