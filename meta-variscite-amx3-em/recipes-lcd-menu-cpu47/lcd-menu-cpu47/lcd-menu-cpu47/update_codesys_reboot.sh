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

if [ -d "cds_lib" ]; then
	chgrp root cds_lib -R
	chmod g+w cds_lib -R
	cp cds_lib/* /usr/lib/
	rm -r cds_lib
fi

cd CODESYSControl
chgrp root *
chmod g+w *
reboot
