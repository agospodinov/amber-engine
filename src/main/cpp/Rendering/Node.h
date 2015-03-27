#ifndef NODE_H
#define NODE_H

#include <functional>
#include <memory>

#include <Eigen/Core>

#include "IRenderable.h"
#include "Procedure.h"
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
                    Group,
                    Model,
                    Light
                };

                Node(std::unique_ptr<IRenderable> renderable = nullptr);

                Type getType() const;

                bool hasRenderable() const;
                const std::unique_ptr<IRenderable> &getRenderable() const;
                void setRenderable(std::unique_ptr<IRenderable> renderable);

                const std::vector<std::unique_ptr<Node>> &getChildren() const;
                void addChild(std::unique_ptr<Node> node);

                Eigen::Matrix4f getTransform() const;
                const Eigen::Matrix4f &getLocalTransform() const;
                void setLocalTransform(Eigen::Matrix4f localTransform);

                Procedure &getProcedure();
                const Procedure &getProcedure() const;
                void setProcedure(Procedure procedure);

                bool isSetup() const;
                void markSetup();

                bool isDirty() const;

                void traverse(std::function<void(Node *)> callback, Type filterType = Type::Undefined);

            private:
                std::unique_ptr<IRenderable> renderable;
                const Node *parent;
                std::vector<std::unique_ptr<Node>> children;
                Eigen::Matrix4f localTransform;
                Procedure procedure;
                bool setup;

                mutable bool dirty;
                mutable Eigen::Matrix4f calculatedTransform;
        };
    }
}

#endif // NODE_H
