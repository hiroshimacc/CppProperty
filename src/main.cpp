/* MIT License

Copyright (c) 2019 Alexandre Bourlon

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#include <iostream>
#include <stdexcept>
#include "property.h"

namespace x = CppProperty;

struct TimePeriod
{
    double _seconds;

    x::property<double> Hours // Hours returns a computed rvalue
    {
        get { return _seconds / 3600; },
        set
        {
            if (value < 0 || value > 24)
                throw std::invalid_argument{ "Value must be between 0 and 24." };

            _seconds = value * 3600;
        }
    };
};

struct S
{
    int i;

    x::property<int&> myInt // myInt returns a reference to a member
    {
        getref { return i; }, // could also be `get { return std::ref(i); }'
        set { i = value; }
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
    t.Hours = 24;
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
