/*  LanChess
    Copyright (C) 2011  Eugenio Cano-Manuel

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* This class definition provides a set of utilities that might
 * be useful for all classes such as conversions or command line output
 * for notification
 */

#ifndef DEVUTILS_H
#define DEVUTILS_H

#include <iostream>
#include <string>

class SwissKnife
{
	private:

	public:
		SwissKnife();
		~SwissKnife();
		void report(const std::string& input);
		void report(int input);
};

#endif
