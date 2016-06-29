
Debian
====================
This directory contains files used to package uniqreditd/uniqredit-qt
for Debian-based Linux systems. If you compile uniqreditd/uniqredit-qt yourself, there are some useful files here.

## uniqredit: URI support ##


uniqredit-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install uniqredit-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your uniqredit-qt binary to `/usr/bin`
and the `../../share/pixmaps/uniqredit128.png` to `/usr/share/pixmaps`

uniqredit-qt.protocol (KDE)

