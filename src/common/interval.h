#ifndef INTERVAL_H
#define INTERVAL_H
//==============================================================================================
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

class interval {
  public:
    double min, max;

    interval(double _min, double _max) : min(_min), max(_max) {}
    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    bool contains(double x) const {
        return min <= x && x <= max;
    }
};

const static interval empty   (+infinity, -infinity);
const static interval universe(-infinity, +infinity);


#endif
