cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

# SFML Yükleme
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)

# NLOHMANN JSON Yükleme
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3 # İhtiyacınıza göre sürümü güncelleyebilirsiniz
    GIT_SHALLOW ON
    SYSTEM)


# Kütüphaneleri Belirt
FetchContent_MakeAvailable(SFML json)

# Derleme dosyalarını belirt
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.hpp"
    "src/*.h"
)

# Dosyaları derlemeye ekleme
add_executable(main ${SOURCES})

target_compile_features(main PRIVATE cxx_std_17)

# Projeye kütüphaneleri bağlama
target_link_libraries(main PRIVATE 
    SFML::Graphics
    nlohmann_json::nlohmann_json
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)