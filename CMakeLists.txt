cmake_minimum_required(VERSION 3.10)
project(DogShelterManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include_directories(src)

add_executable(shelter_app 
    src/main.cpp 
    src/Dog.cpp 
    src/MemoryRepository.cpp 
    src/TextFileRepository.cpp 
    src/AdminService.cpp
    src/UserService.cpp 
    src/UI.cpp
    src/Tests.cpp
)