# ATTENTION!!

# DO NOT RUN THIS BUILD IF YOU HAVE ALREADY INSTALLED JAIL!
# IT CAN DAMAGE YOUR DATA!


####Installation:
1. Set FreeBSD release version in file release_version.txt, for example:
```
# cat release_version.txt
12.2
```
2. Choose zfs or ufs filesystem:
```
# cp makefile_zfs Makefile
```
2. Build jm:
```
  make install
```

<br/><br/>

####Unninstall:

make deinstall
