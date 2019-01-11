#!/bin/sh

if [ -z $1 ] || [ -z $2 ] || [ -z $3 ]
then
 echo "You need to specify parameters IP-address Mask Gateway in such order"
 exit 1
fi

cat << EOF >/etc/systemd/network/10-eth.network
[Match]
Name=eth0

[Network]
DHCP=no

IPv6PrivacyExtensions=false
Address=$1/$2
Gateway=$3 
EOF

systemctl restart systemd-networkd
