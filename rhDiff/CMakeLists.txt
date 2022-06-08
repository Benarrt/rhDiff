include_directories(${RH_DIFF_INCLUDE})

file(GLOB SOURCES "src/*.cpp")

add_library(rhDiff SHARED ${SOURCES})

