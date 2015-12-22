#ifndef CAMERA_H
#define CAMERA_H

#include "Amber/Core/IComponent.h"

#include <Eigen/Core>

namespace Amber
{
    namespace Rendering
    {
        class Camera : public Core::IComponent
        {
            public:
                Camera();
                virtual ~Camera() = default;

                virtual Type getType() const override final;
                virtual bool isSetup() const override final;

                void setLookAt(const Eigen::Vector3f &eye, const Eigen::Vector3f &center, const Eigen::Vector3f &up);
                void setPerspectiveProjection(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);

                const Eigen::Matrix4f &getViewMatrix() const;
                const Eigen::Matrix4f &getProjectionMatrix() const;

            private:
                Eigen::Matrix4f viewMatrix;
                Eigen::Matrix4f projectionMatrix;
        };
    }
}

#endif // CAMERA_H
