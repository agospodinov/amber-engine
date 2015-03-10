#ifndef UTILITIES_H
#define UTILITIES_H

namespace Math
{
    const double pi = 3.141592653589793238462643383279502884;

    template <typename T>
    T radians(T d)
    {
        return d * static_cast<T>(pi) / static_cast<T>(180);
    }

    template <typename T>
    T degrees(T r)
    {
        return r * static_cast<T>(180) / static_cast<T>(pi);
    }
}

#endif // UTILITIES_H
