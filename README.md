ultra-espnow-gw
===============

work in progress... stay tuned

what is it
----------

- an ESP-NOW to Ethernet gateway: espnow packets in, TCP out

software installation
---------------------

- install [ESP-IDF](https://docs.espressif.com/projects/esp-idf/) v5.5 or later
- fill in your own access points, gateway MACs and target hosts in `main/mcfg.h`
- the values shipped there are placeholders, not working credentials

how to use it
-------------

- build and flash with

        idf.py -p /dev/ttyUSB0 flash monitor

- `buildit.cfg` holds the per-device settings used by the author's build driver

notes
-----

- `main/mcom.h`, `main/mlcf.h` and `main/mnta.h` are shared with the author's other ESP32
  projects and are vendored here rather than referenced
- host names, MAC addresses and IP addresses throughout this repository are placeholders
