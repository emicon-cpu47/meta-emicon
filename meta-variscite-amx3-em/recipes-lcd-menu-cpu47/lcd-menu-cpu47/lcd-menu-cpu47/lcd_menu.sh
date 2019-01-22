#!/bin/sh

case "$1" in
start)


	# Init the system
	echo "starting lcd_menu...done"
    #. /etc/profile
    export LCD_MENU_DIR=/usr/bin/codesys/
	cd $LCD_MENU_DIR
	./lcd_menu &
	;;
stop)
	echo "stopping lcd_menu"
	killall lcd_menu
	echo "stopping done"
	;;
*)
	echo "usage: $0 [start|stop]"
	;;
esac

