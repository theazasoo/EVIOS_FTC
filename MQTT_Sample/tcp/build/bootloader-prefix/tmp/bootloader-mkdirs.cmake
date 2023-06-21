# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/jenniferazasoo/esp/esp-idf/components/bootloader/subproject"
  "/Users/jenniferazasoo/Documents/GitHub/EVIOS_FTC/MQTT_Sample/tcp/build/bootloader"
  "/Users/jenniferazasoo/Documents/GitHub/EVIOS_FTC/MQTT_Sample/tcp/build/bootloader-prefix"
  "/Users/jenniferazasoo/Documents/GitHub/EVIOS_FTC/MQTT_Sample/tcp/build/bootloader-prefix/tmp"
  "/Users/jenniferazasoo/Documents/GitHub/EVIOS_FTC/MQTT_Sample/tcp/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/jenniferazasoo/Documents/GitHub/EVIOS_FTC/MQTT_Sample/tcp/build/bootloader-prefix/src"
  "/Users/jenniferazasoo/Documents/GitHub/EVIOS_FTC/MQTT_Sample/tcp/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/jenniferazasoo/Documents/GitHub/EVIOS_FTC/MQTT_Sample/tcp/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/jenniferazasoo/Documents/GitHub/EVIOS_FTC/MQTT_Sample/tcp/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
