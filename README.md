# Firmata4CIAA

A firmata protocol implementation for CIAA Project boards.

This program allows the user to work with applications, like snap (http://s4a.cat/snap/), that use the firmata protocol (http://firmata.org/wiki/Main_Page) to communicate with the board.

Other applications that use Firmata: 

- cylonjs: http://cylonjs.com/
- Johnny five: http://johnny-five.io/

## Versions

- [Firmata4CIAA](https://github.com/OlivieriIan/Firmata4CIAA) 2.0.
- [Firmata](https://github.com/firmata/protocol) 2.3.
- [CIAA Firmware](https://github.com/ciaa/Firmware/releases) Upa 1.0.0 LTS.
- [sAPI](https://github.com/epernia/sapi) 0.1.

## Supported boards: 

- EDU-CIAA-NXP.

## Using

See "docs" folder for user guides and pin mapping. It is recommended:

1. Download Firmata4CIAA firmware to EDU-CIAA-NXP board (see "Guia de instalacion de Firmata4CIAA.pdf"). This firmware is also included as an Embedded IDE tempalte (download latest release of Embedded IDE at https://github.com/martinribelotta/embedded-ide-builder/releases).
2. Use "Firmata Test" program to test that firmata protocol works (see "Guia de instalacion de Firmata4CIAA.pdf", step 5, page 8).  
3. Install Snap (see "Guia de instalacion de Snap.pdf") or other firmata-compatible software.  
