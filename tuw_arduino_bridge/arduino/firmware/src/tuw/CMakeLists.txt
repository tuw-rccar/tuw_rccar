#include_directories(core)
#include_directories(bldc)
#include_directories(servos)
#include_directories(motion)
#include_directories(sandbox)
#include_directories(interface)
#include_directories(com)

add_subdirectory(sandbox)
add_subdirectory(blink)
add_subdirectory(bldc)
add_subdirectory(servos)
add_subdirectory(imu)
add_subdirectory(com)
add_subdirectory(motion)
