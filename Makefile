ext_if=$$(netstat -r | grep default | awk '{print $$4}')
jail_if=lo1

install:
	zfs create -o mountpoint=/usr/local/jails zroot/jails || true
	zfs create zroot/jails/basejail || true
	fetch https://download.freebsd.org/ftp/releases/amd64/12.1-RELEASE/base.txz -o /tmp
	fetch https://download.freebsd.org/ftp/releases/amd64/12.1-RELEASE/lib32.txz -o /tmp
	tar xvf /tmp/base.txz -C /usr/local/jails/basejail
	tar xvf /tmp/lib32.txz -C /usr/local/jails/basejail
	env PAGER=cat freebsd-update -b /usr/local/jails/basejail fetch install
	echo 'nameserver 8.8.8.8' > /usr/local/jails/basejail/etc/resolv.conf
	echo 'sshd_enable="YES"' > /usr/local/jails/basejail/etc/rc.conf
	echo 'PermitRootLogin yes' >> /usr/local/jails/basejail/etc/ssh/sshd_config
	zfs snapshot zroot/jails/basejail@12.0-RELEASE || true
	echo 'exec.start = "/bin/sh /etc/rc";' > /etc/jail.conf
	echo 'exec.stop = "/bin/sh /etc/rc.shutdown";' >> /etc/jail.conf
	echo 'exec.clean;' >> /etc/jail.conf
	echo 'mount.devfs;' >> /etc/jail.conf
	echo 'path = "/usr/local/jails/$$name";' >> /etc/jail.conf
	echo 'allow.raw_sockets = 1;' >> /etc/jail.conf
	echo 'allow.sysvipc = 1;' >> /etc/jail.conf
	sysrc jail_enable="YES"
	sysrc pf_enable="YES"
	echo '' >> /etc/rc.conf
	echo '# Jail network' >> /etc/rc.conf
	echo 'cloned_interfaces="lo1"' >> /etc/rc.conf
	echo 'ifconfig_lo1_alias0="inet 10.0.1.1 netmask 255.255.255.0"' >> /etc/rc.conf
	echo 'ipv4_addrs_lo1="10.0.1.239-254/24"' >> /etc/rc.conf
	echo ext_if = "$(ext_if)" >> /etc/pf.conf
	echo 'ext_addr = $$ext_if:0' >> /etc/pf.conf
	echo 'jail_if = "$(jail_if)"' >> /etc/pf.conf
	echo 'jail_net = $$jail_if:network' >> /etc/pf.conf
	echo >> /etc/pf.conf
	echo 'set skip on lo0' >> /etc/pf.conf
	echo 'scrub in all' >> /etc/pf.conf
	echo >> /etc/pf.conf
	echo '# Nat on jails' >> /etc/pf.conf
	echo 'nat on $$ext_if from $$jail_net to any -> ($$ext_if)' >> /etc/pf.conf
	rm /tmp/base.txz || true
	rm /tmp/lib32.txz || true
	ifconfig lo1 create
	ifconfig lo1 alias 10.0.0.1 netmask 255.255.255.0
	service netif restart && service routing restart
	service pf restart
	clang++ cpp/jm.cpp -o /usr/local/bin/jm

deinstall:
	service jail stop
	sysrc -x jail_enable
	rm /etc/jail.conf || true
#	zfs destroy -R -f zroot/jails/basejail@12.0-RELEASE || true
#	zfs destroy -f zroot/jails/basejail || true
#	zfs destroy -f zroot/jails || true
	sed -i '' '/# Nat/d' /etc/pf.conf
	sed -i '' '/jail_net/d' /etc/pf.conf
	sed -i '' '/jail_if/d' /etc/pf.conf
	sed -i '' '/scrub in all/d' /etc/pf.conf
	sed -i '' '/set skip on lo0/d' /etc/pf.conf
	sed -i '' '/int_if/d' /etc/pf.conf
	sed -i '' '/ext_if/d' /etc/pf.conf
	sed -i '' '/ext_addr/d' /etc/pf.conf
	sed -i '' '/lo1/d' /etc/rc.conf
	sed -i '' '/Jail/d' /etc/rc.conf
	ifconfig lo1 destroy || true
	rm -f /usr/local/bin/jm
