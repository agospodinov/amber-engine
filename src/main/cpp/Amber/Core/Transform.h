#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Amber/Core/IComponent.h"

#include <vector>

#include <Eigen/Core>

namespace Amber
{
    namespace Core
    {
        class Transform : public IComponent
        {
            public:
                explicit Transform(Eigen::Matrix4f transform);
                Transform(Eigen::Matrix4f transform, Transform *parent);
                virtual ~Transform();

                const Eigen::Matrix4f &getTransform() const;

                const Eigen::Matrix4f &getLocalTransform() const;
                void setLocalTransform(Eigen::Matrix4f localTransform);

                const Transform *getParent() const;

                void flatten();

            private:
                void addChild(Transform *child);
                void removeChild(Transform *child);
                void markDirty();

                Eigen::Matrix4f localTransform;
                Transform *parent;
                std::vector<Transform *> children;

                mutable Eigen::Matrix4f calculatedTransform;
                mutable bool dirty;
        };
    }
}

#endif // TRANSFORM_H
