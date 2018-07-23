
Debian
====================
This directory contains files used to package hostmasternoded/hostmasternode-qt
for Debian-based Linux systems. If you compile hostmasternoded/hostmasternode-qt yourself, there are some useful files here.

## hostmasternode: URI support ##


hostmasternode-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install hostmasternode-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your hostmasternode-qt binary to `/usr/bin`
and the `../../share/pixmaps/hostmasternode128.png` to `/usr/share/pixmaps`

hostmasternode-qt.protocol (KDE)

