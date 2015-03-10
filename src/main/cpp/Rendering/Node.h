#ifndef NODE_H
#define NODE_H

#include <functional>
#include <memory>

#include <Eigen/Core>

#include "IRenderable.h"
#include "ForwardDeclarations.h"

namespace Amber
{
    namespace Rendering
    {
        class Node
        {
            public:
                enum class Type
                {
                    Undefined,
                    World,
                    Model,
                    Light
                };

                Node(std::unique_ptr<IRenderable> renderable = nullptr);

                Type getType() const;

                const std::unique_ptr<IRenderable> &getRenderable() const;
                void setRenderable(std::unique_ptr<IRenderable> renderable);

                const std::vector<std::unique_ptr<Node>> &getChildren() const;
                void addChild(std::unique_ptr<Node> node);

                Eigen::Matrix4f getTransform() const;
                const Eigen::Matrix4f &getLocalTransform() const;
                void setLocalTransform(Eigen::Matrix4f localTransform);

                bool isDirty() const;

                bool isSetup() const;
                void markSetup();

                void traverse(std::function<void(Node *)> callback, Type filterType = Type::Undefined);

            private:
                std::unique_ptr<IRenderable> renderable;
                const Node *parent;
                std::vector<std::unique_ptr<Node>> children;
                Eigen::Matrix4f localTransform;
                mutable bool dirty;
                bool setup;

                mutable Eigen::Matrix4f calculatedTransform;
        };
    }
}

#endif // NODE_H