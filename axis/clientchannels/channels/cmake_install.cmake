# Install script for directory: Z:/FreeRDP-master/channels

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/FreeRDP")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("Z:/FreeRDP-master/channels/audin/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/cliprdr/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/disp/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/drdynvc/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/drive/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/echo/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/encomsp/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/printer/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/rail/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/rdpdr/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/rdpei/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/rdpgfx/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/rdpsnd/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/remdesk/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/smartcard/cmake_install.cmake")
  include("Z:/FreeRDP-master/channels/client/cmake_install.cmake")

endif()

