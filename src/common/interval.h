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
    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(double _min, double _max) : min(_min), max(_max) {}

    interval(const interval& a, const interval& b)
      : min(fmin(a.min, b.min)), max(fmax(a.max, b.max)) {}

    bool is_empty() const {
        return max < min;
    }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    interval& operator+=(double offset) {
        min += offset;
        max += offset;
        return *this;
    }

    static const interval empty;
    static const interval universe;

  public:
    double min, max;
};

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);


#endif
