/*
Copyright (C) 2017 Alexis Poncet

ChaoticBilliard is a computer program whose purpose is to compute the
dynamics of chaotic billiards and show the trajectories both in physical
space and phase space.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
 * ChaoticBilliard
 * main.cpp
 *
 * Author: Alexis Poncet
 * Email: alexis.poncet@ens.fr
 * Version: 1.0
 *
 * Launch the gui application for ChaoticBilliard.
 */

#include <QApplication>
#include "gui/MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();
    return app.exec();
}
