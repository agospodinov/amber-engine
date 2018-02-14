#include "Transform.h"

namespace Amber
{
    namespace Core
    {
        Transform::Transform(Eigen::Matrix4f transform)
            : Transform(std::move(transform), nullptr)
        {
        }

        Transform::Transform(Eigen::Matrix4f transform, Transform *parent)
            : localTransform(std::move(transform)),
              parent(parent),
              dirty(true)
        {
            if (parent != nullptr)
            {
                parent->addChild(this);
            }
        }

        Transform::~Transform()
        {
            for (Transform *child : children)
            {
                child->localTransform = child->getTransform();
                child->parent = nullptr;
            }
        }

        const Eigen::Matrix4f &Transform::getTransform() const
        {
            if (dirty)
            {
                if (parent)
                {
                    calculatedTransform = parent->getTransform() * localTransform;
                }
                else
                {
                    calculatedTransform = localTransform;
                }

                this->dirty = false;
            }

            return calculatedTransform;
        }

        const Eigen::Matrix4f &Transform::getLocalTransform() const
        {
            return localTransform;
        }

        void Transform::setLocalTransform(Eigen::Matrix4f localTransform)
        {
            this->localTransform = std::move(localTransform);
            markDirty();
        }

        const Transform *Transform::getParent() const
        {
            return parent;
        }

        void Transform::flatten()
        {
            this->localTransform = getTransform();
            this->parent->removeChild(this);
            this->parent = nullptr;
        }

        void Transform::addChild(Transform *child)
        {
            this->children.push_back(child);
        }

        void Transform::removeChild(Transform *child)
        {
            this->children.erase(std::remove(this->children.begin(), this->children.end(), child));
        }

        void Transform::markDirty()
        {
            this->dirty = true;
            for (Transform *child : children)
            {
                child->markDirty();
            }
        }
    }
}
