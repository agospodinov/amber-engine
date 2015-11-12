#ifndef UTILITIES_H
#define UTILITIES_H

namespace Amber
{
    namespace Math
    {
        const double PI = 3.141592653589793238462643383279502884;

        template <typename T>
        T radians(T d)
        {
            return d * static_cast<T>(PI) / static_cast<T>(180);
        }

        template <typename T>
        T degrees(T r)
        {
            return r * static_cast<T>(180) / static_cast<T>(PI);
        }
    }
}

#endif // UTILITIES_H
