#!/bin/sh

/etc/init.d/codesys stop
cd /usr/bin/codesys
tar -xf update.tar
rm update.tar
if [ -d "PlcLogic" ]; then
	chgrp root PlcLogic -R
	chmod g+w PlcLogic -R
	rm -r /home/plc/PlcLogic
	mv PlcLogic /home/plc/PlcLogic
fi
cd CODESYSControl
chgrp root *
chmod g+w *
reboot
