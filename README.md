ultra-espnow-gw
===============

work in progress... stay tuned

what is it
----------

- an ESP-NOW to Ethernet gateway: espnow packets in, TCP out

software installation
---------------------

- install [ESP-IDF](https://docs.espressif.com/projects/esp-idf/) v5.5 or later
- CMake 4.0 or later: `CMakeLists.txt` asks for it, but ESP-IDF itself needs only 3.16, so the
  CMake it installs (3.30 with v5.5) or your system's may well be older - check `cmake --version`
- fill in your own access points, gateway MACs and target hosts in `main/mcfg.h`
- the values shipped there are placeholders, not working credentials

how to build
------------

the firmware is built for one device at a time. `main/build_id.h` says which, and the
`#if ESP32_(n)` blocks in `main/ultra_espnow_gw.c` hold each device's settings - pick the block
that matches your board, or add one. for the ESP32-S3-ETH board `sdkconfig.defaults` is set up
for, device 87 for example:

    // main/build_id.h
    #pragma once
    #define PROJECT "ultra-espnow-gw"
    #define ENTITY  87
    #define SERNO   "0001"
    #define MYDATE  "26-10-01"

then build and flash with that file forced into every compile:

    OPTS_="-include $PWD/main/build_id.h" idf.py -p /dev/ttyUSB0 build flash monitor

- `OPTS_` is read when cmake first configures the build: after changing it, remove `build/`
- `SERNO` is the firmware version the OTA update check compares (hex), `MYDATE` a free label
- the `ethernet_init` component comes from the ESP-IDF ethernet example, see
  `main/idf_component.yml`
- `buildit.cfg` holds the per-device settings of the author's own build driver, which writes
  `main/build_id.h` by itself

notes
-----

- `main/mcom.h`, `main/mlcf.h` and `main/mnta.h` are shared with the author's other ESP32
  projects and are vendored here rather than referenced
- host names, MAC addresses and IP addresses throughout this repository are placeholders
