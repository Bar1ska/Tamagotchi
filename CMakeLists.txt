# CMakeList.txt: проект CMake для Tamagotchi; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Tamagotchi "Tamagotchi.cpp"    "Textures.cpp" "Textures.h" "TimaAndStatus.cpp" "TimeAndStatus.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Tamagotchi PROPERTY CXX_STANDARD 20)
endif()
# TODO: Добавьте тесты и целевые объекты, если это необходимо.

# текстуры :
set(CRYING "${CMAKE_CURRENT_SOURCE_DIR}/textures/crying.txt")
set(EATING "${CMAKE_CURRENT_SOURCE_DIR}/textures/eating.txt")
set(IDLE "${CMAKE_CURRENT_SOURCE_DIR}/textures/idle.txt")
set(LOSE "${CMAKE_CURRENT_SOURCE_DIR}/textures/lose.txt")
set(PLAYING "${CMAKE_CURRENT_SOURCE_DIR}/textures/playing.txt")
set(SLEEPING "${CMAKE_CURRENT_SOURCE_DIR}/textures/sleeping.txt")
set(WASHING "${CMAKE_CURRENT_SOURCE_DIR}/textures/washing.txt")

# время и статистика :
set(TIMEBATH "${CMAKE_CURRENT_SOURCE_DIR}/time_and_state/bathing/time.txt")
set(STATEBATH "${CMAKE_CURRENT_SOURCE_DIR}/time_and_state/bathing/state.txt")
set(TIMEFOOD "${CMAKE_CURRENT_SOURCE_DIR}/time_and_state/food/time.txt")
set(STATEFOOD "${CMAKE_CURRENT_SOURCE_DIR}/time_and_state/food/state.txt")
set(TIMEPLAY "${CMAKE_CURRENT_SOURCE_DIR}/time_and_state/play/time.txt")
set(STATEPLAY "${CMAKE_CURRENT_SOURCE_DIR}/time_and_state/play/state.txt")
set(TIMESLEEP "${CMAKE_CURRENT_SOURCE_DIR}/time_and_state/sleep/time.txt")
set(STATESLEEP "${CMAKE_CURRENT_SOURCE_DIR}/time_and_state/sleep/state.txt")

add_compile_definitions(CRYING="${CRYING}")
add_compile_definitions(EATING="${EATING}")
add_compile_definitions(IDLE="${IDLE}")
add_compile_definitions(LOSE="${LOSE}")
add_compile_definitions(PLAYING="${PLAYING}")
add_compile_definitions(SLEEPING="${SLEEPING}")
add_compile_definitions(WASHING="${WASHING}")
add_compile_definitions(TIMEBATH="${TIMEBATH}")
add_compile_definitions(STATEBATH="${STATEBATH}")
add_compile_definitions(TIMEFOOD="${TIMEFOOD}")
add_compile_definitions(STATEFOOD="${STATEFOOD}")
add_compile_definitions(TIMEPLAY="${TIMEPLAY}")
add_compile_definitions(STATEPLAY="${STATEPLAY}")
add_compile_definitions(TIMESLEEP="${TIMESLEEP}")
add_compile_definitions(STATESLEEP="${STATESLEEP}")