#ifndef LIGHT_H
#define LIGHT_H

#include <eigen3/Eigen/Core>

namespace Amber
{
    namespace Graphics
    {
        namespace Rendering
        {
            class Light
            {
                public:
                    Light();

                private:
                    Eigen::Vector3f position;
                    Eigen::Vector3f direction;
                    float strength;
            };
        }
    }
}

#endif // LIGHT_H
