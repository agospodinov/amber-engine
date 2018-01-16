#ifndef NODE_H
#define NODE_H

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include <Eigen/Core>

#include "Amber/Core/IComponent.h"

namespace Amber
{
    namespace Core
    {
        class Node
        {
            public:
                Node();

                IComponent *getComponent(IComponent::Type type) const;
                void addComponent(std::unique_ptr<IComponent> component);

                const std::vector<std::unique_ptr<Node>> &getChildren() const;
                void addChild(std::unique_ptr<Node> node);

                Eigen::Matrix4f getTransform() const;
                const Eigen::Matrix4f &getLocalTransform() const;
                void setLocalTransform(Eigen::Matrix4f localTransform);

                bool isDirty() const;

                void traverse(std::function<void(Node *)> callback);

            private:
                void propagateDirtyFlag() const;

                const Node *parent;
                std::vector<std::unique_ptr<Node>> children;

                std::map<IComponent::Type, std::unique_ptr<IComponent>> components;
                Eigen::Matrix4f localTransform;

                mutable bool dirty;
                mutable Eigen::Matrix4f calculatedTransform;
        };
    }
}

#endif // NODE_H
