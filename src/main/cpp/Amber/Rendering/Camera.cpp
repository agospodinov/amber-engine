#include "Camera.h"

#include <Eigen/Geometry>

#include "Amber/Math/Utilities.h"

namespace Amber
{
    namespace Rendering
    {
        Camera::Camera()
            : viewMatrix(Eigen::Matrix4f::Identity()),
              projectionMatrix(Eigen::Matrix4f::Zero())
        {
        }

        void Camera::setLookAt(const Eigen::Vector3f &eye, const Eigen::Vector3f &center, const Eigen::Vector3f &up)
        {
            Eigen::Vector3f f = (center - eye).normalized();
            Eigen::Vector3f u = up.normalized();
            Eigen::Vector3f s = f.cross(u).normalized();
            u = s.cross(f);

            Eigen::Matrix4f viewMatrix;
            viewMatrix <<  s.x(),  s.y(),  s.z(), -s.dot(eye),
                           u.x(),  u.y(),  u.z(), -u.dot(eye),
                          -f.x(), -f.y(), -f.z(),  f.dot(eye),
                               0,      0,      0,           1;

            this->viewMatrix = viewMatrix;
        }

        void Camera::setPerspectiveProjection(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
        {
            assert(aspectRatio > 0);
            assert(farPlane > nearPlane);

            float radf = Math::radians(fieldOfView);

            double tanHalfFovy = tan(radf / 2.0f);
            Eigen::Matrix4f projectionMatrix = Eigen::Matrix4f::Zero();
            projectionMatrix(0,0) = 1.0f / (aspectRatio * tanHalfFovy);
            projectionMatrix(1,1) = 1.0f / (tanHalfFovy);
            projectionMatrix(2,2) = -(farPlane + nearPlane) / (farPlane - nearPlane);
            projectionMatrix(2,3) = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
            projectionMatrix(3,2) = -1.0f;

            this->projectionMatrix = projectionMatrix;
        }

        const Eigen::Matrix4f &Camera::getViewMatrix() const
        {
            return viewMatrix;
        }

        const Eigen::Matrix4f &Camera::getProjectionMatrix() const
        {
            return projectionMatrix;
        }
    }
}
