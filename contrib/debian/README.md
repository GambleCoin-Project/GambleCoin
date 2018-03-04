
Debian
====================
This directory contains files used to package gamblecoind/gamblecoin-qt
for Debian-based Linux systems. If you compile gamblecoind/gamblecoin-qt yourself, there are some useful files here.

## gamblecoin: URI support ##


gamblecoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install gamblecoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your gamblecoinqt binary to `/usr/bin`
and the `../../share/pixmaps/gamblecoin128.png` to `/usr/share/pixmaps`

gamblecoin-qt.protocol (KDE)

