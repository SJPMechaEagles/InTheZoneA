# cmake_minimum_required(VERSION <specify CMake version here>)
project(InTheZoneA)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        include/API.h
        include/auto.h
        include/battery.h
        include/claw.h
        include/controller.h
        include/drive.h
        include/encoders.h
        include/gyro.h
        include/lcd.h
        include/lifter.h
        include/list.h
        include/localization.h
        include/log.h
        include/main.h
        include/matrix.h
        include/menu.h
        include/mobile_goal_intake.h
        include/motor_ports.h
        include/potentiometer.h
        include/routines.h
        include/sensors.h
        include/slew.h
        include/toggle.h
        include/vlib.h
        include/vmath.h
        src/auto.c
        src/battery.c
        src/claw.c
        src/controller.c
        src/drive.c
        src/encoders.c
        src/gyro.c
        src/init.c
        src/lcd.c
        src/lifter.c
        src/list.c
        src/list_iterator.c
        src/list_node.c
        src/localization.c
        src/log.c
        src/matrix.c
        src/menu.c
        src/mobile_goal_intake.c
        src/opcontrol.c
        src/routines.c
        src/slew.c
        src/toggle.c
        src/vlib.c
        src/vmath.c)
include_directories(.)


add_executable(InTheZoneA ${SOURCE_FILES})