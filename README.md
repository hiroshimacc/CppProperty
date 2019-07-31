# CppProperty

C#-like properties in C++

## Overview

CppProperty is an experimental project leveraging modern C++ features to achieve a new idiom for writing properties (a getter and a setter to a local or computed value) similar to [the way C# does it](https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/classes-and-structs/properties).

## Example

```cpp
class TimePeriod
{
private:
    double _seconds;

public:
    property<double> Hours
    {
        get { return _seconds / 3600; },
        set
        {
            if (value < 0 || value > 24)
                throw std::invalid_argument{ "value must be between 0 and 24." };

            _seconds = value * 3600;
        }
    };
};
```

## Licence

This work in its entirety (that means source code, build files and all other assets) is licenced under the MIT License. See [LICENCE](../../blob/master/LICENSE) for more information.
