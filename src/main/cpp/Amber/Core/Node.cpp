#include "Node.h"

namespace Amber
{
    namespace Core
    {
        Node::Node()
            : parent(nullptr),
              localTransform(Eigen::Matrix4f::Identity()),
              dirty(true)
        {
        }

        IComponent *Node::getComponent(IComponent::Type type) const
        {
            auto it = components.find(type);
            return it != components.end() ? it->second.get() : nullptr;
        }

        void Node::addComponent(std::unique_ptr<IComponent> component)
        {
            components.emplace(component->getType(), std::move(component));
        }

        const std::vector<std::unique_ptr<Node>> &Node::getChildren() const
        {
            return children;
        }

        void Node::addChild(std::unique_ptr<Node> node)
        {
            node->parent = this;
            node->dirty = true;

            this->children.push_back(std::move(node));
            markDirty();
        }

        Eigen::Matrix4f Node::getTransform() const
        {
            if (isDirty())
            {
                if (parent)
                {
                    calculatedTransform = parent->getTransform() * localTransform;
                }
                else
                {
                    calculatedTransform = localTransform;
                }
            }

            this->dirty = false;
            return calculatedTransform;
        }

        const Eigen::Matrix4f &Node::getLocalTransform() const
        {
            return localTransform;
        }

        void Node::setLocalTransform(Eigen::Matrix4f localTransform)
        {
            this->localTransform = localTransform;
            markDirty();
        }

        bool Node::isDirty() const
        {
            return dirty;
        }

        void Node::markDirty()
        {
            traverse([] (Node *node) { node->dirty = true; });
        }

        void Node::traverse(std::function<void(Node *)> callback)
        {
            callback(this);

            for (const std::unique_ptr<Node> &childNode : children)
            {
                childNode->traverse(callback);
            }
        }
    }
}
