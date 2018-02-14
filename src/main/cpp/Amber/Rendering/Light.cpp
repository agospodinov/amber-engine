#include "Light.h"

namespace Amber
{
    namespace Rendering
    {
        Light::Light(Light::Type type)
            : type(type),
              attenuationCoefficients(Eigen::Vector3f(1, 0.1, 0.01)),
              color(Eigen::Vector4f(1, 1, 1, 1))
        {
        }

        const Eigen::Vector3f &Light::getAttenuationCoefficients() const
        {
            return attenuationCoefficients;
        }

        void Light::setAttenuationCoefficients(Eigen::Vector3f attenuationCoefficients)
        {
            this->attenuationCoefficients = std::move(attenuationCoefficients);
        }

        const Eigen::Vector4f &Light::getColor() const
        {
            return color;
        }

        void Light::setColor(Eigen::Vector4f color)
        {
            this->color = std::move(color);
        }
    }
}
