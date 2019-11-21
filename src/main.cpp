#include <iostream>
#include <stdexcept>
#include <property.h>

namespace x = CppProperty;

struct TimePeriod
{
    double _seconds;

    x::property<double> Hours{
        prop_get { return _seconds / 3600; },
        prop_set {
            if (value < 0 || value > 24)
                throw std::invalid_argument{"Value must be between 0 and 24."};

            _seconds = value * 3600;
        }
    };
};

struct S
{
    int i;

    x::property<int&> myInt
    {
        prop_getref { return i; }, // could also be `get { return std::ref(i); }'
        prop_set { i = value; }
    };
};

int main()
{
    S s;
    s.myInt = 42;
    std::cout << s.i << "\n";
    std::cout << s.myInt << "\n";

    TimePeriod t;

    // The property assignment causes the 'set' accessor to be called.
    t.Hours = 24.;
    std::cout << t._seconds << "\n";

    // Retrieving the property causes the 'get' accessor to be called.
    std::cout << "Time in hours: " << t.Hours << "\n";

    // Testing assignment with lvalue;
    int i = 24;
    s.myInt = i;
    std::cout << s.myInt << "\n";

    double d = 12.;
    t.Hours = d;
    std::cout << t.Hours << "\n";
}
