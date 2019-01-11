#!/bin/sh
cp /home/plc/PlcLogic /tmp/PlcLogic -R
cp /usr/bin/codesys/CODESYSControl /tmp/CODESYSControl -R
tar -cf /tmp/firmware.tar  -C /tmp CODESYSControl PlcLogic
rm /tmp/PlcLogic -R
rm /tmp/CODESYSControl -R