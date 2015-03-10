#include "Node.h"

#include "Model.h"
#include "Skybox.h"

namespace Amber
{
    namespace Rendering
    {
        Node::Node(std::unique_ptr<IRenderable> renderable)
            : renderable(std::move(renderable)),
              parent(nullptr),
              localTransform(Eigen::Matrix4f::Identity()),
              dirty(true),
              setup(false)
        {
        }

        Node::Type Node::getType() const
        {
            if (dynamic_cast<Model *>(renderable.get()) != nullptr)
            {
                return Type::Model;
            }
//            else if (dynamic_cast<Light *>(renderable.get()) != nullptr)
//            {
//                return Type::Light;
//            }
            else if (dynamic_cast<Skybox *>(renderable.get()) != nullptr)
            {
                return Type::World;
            }

            return Type::Undefined;
        }

        const std::unique_ptr<IRenderable> &Node::getRenderable() const
        {
            return renderable;
        }

        void Node::setRenderable(std::unique_ptr<IRenderable> renderable)
        {
            this->renderable = std::move(renderable);
            this->dirty = true;
        }

        const std::vector<std::unique_ptr<Node>> &Node::getChildren() const
        {
            return children;
        }

        void Node::addChild(std::unique_ptr<Node> node)
        {
            Type nodeType = node->getType();
            if (nodeType == Type::World || nodeType == Type::Undefined)
            {
                throw std::invalid_argument("Cannot parent a node of this type");
            }

            node->parent = this;
            node->dirty = true;
            this->children.push_back(std::move(node));
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

            return calculatedTransform;
        }

        const Eigen::Matrix4f &Node::getLocalTransform() const
        {
            return localTransform;
        }

        void Node::setLocalTransform(Eigen::Matrix4f localTransform)
        {
            this->localTransform = localTransform;
            this->dirty = true;
        }

        bool Node::isDirty() const
        {
            if (!dirty && parent != nullptr)
            {
                dirty |= parent->isDirty();
            }

            return dirty;
        }

        bool Node::isSetup() const
        {
            return setup;
        }

        void Node::markSetup()
        {
            this->setup = true;
        }

        void Node::traverse(std::function<void(Node *)> callback, Type filterType)
        {
            Eigen::Matrix4f transform = getTransform();

            // World can only be root node, so don't bother traversing children
            if (filterType != Type::World)
            {
                for (const std::unique_ptr<Node> &childNode : children)
                {
                    childNode->traverse(callback);
                }
            }

            if (filterType == Type::Undefined || getType() == filterType)
            {
                callback(this/*, transform*/);
            }
            this->dirty = false;
        }
    }
}
