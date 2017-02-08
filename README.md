# ChaoticBilliard

The purpose of this program is to compute the dynamics of chaotic billiards and display
the trajectories both in physical space and phase space.

Currently, three types of billiards are supported:
- Circular billiard (not chaotic)
- Elliptic billiard
- Deformed circular billiard with shape `r(theta) = 1 + e*cos(theta)`

## Dependancies and compilation
The graphical display uses [Qt 5](http://doc.qt.io/qt-5/). 
See [here](http://doc.qt.io/qt-5/gettingstarted.html) for information on how to install Qt.

Once Qt is installed, the program can be compiled with the command-line: `qmake && make`.
The executable is called `Billiard`.

The compilation was only tested on Linux but should work as well with MacOS and Windows. Currently no binaries are provided.

## License

This software is licensed under [GNU GPL 3](https://www.gnu.org/licenses/gpl-3.0.html).
You are very welcome to contribute to it!

Qt is licensed under [GNU LGPL](http://doc.qt.io/qt-5/licensing.html).
