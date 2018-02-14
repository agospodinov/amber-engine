#ifndef LIGHT_H
#define LIGHT_H

#include "Amber/Core/IComponent.h"

#include <Eigen/Core>

namespace Amber
{
    namespace Rendering
    {
        class Light : public Core::IComponent
        {
            public:
                enum class Type
                {
                    Directional,
                    Point,
                    Spotlight
                };

                Light(Type type);
                virtual ~Light() = default;

                const Eigen::Vector3f &getAttenuationCoefficients() const;
                void setAttenuationCoefficients(Eigen::Vector3f attenuationCoefficients);

                const Eigen::Vector4f &getColor() const;
                void setColor(Eigen::Vector4f color);

            private:
                Type type;
                Eigen::Vector3f attenuationCoefficients;
                Eigen::Vector4f color;

        };
    }
}

#endif // LIGHT_H
