#ifndef NODE_H
#define NODE_H

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include <Eigen/Core>

namespace Amber
{
    namespace Core
    {
        class Node
        {
            public:
                Node();

                const std::vector<std::unique_ptr<Node>> &getChildren() const;
                void addChild(std::unique_ptr<Node> node);

                Eigen::Matrix4f getTransform() const;
                const Eigen::Matrix4f &getLocalTransform() const;
                void setLocalTransform(Eigen::Matrix4f localTransform);

                bool isDirty() const;

                void traverse(std::function<void(Node *)> callback);

            protected:
                void markDirty();

            private:
                const Node *parent;
                std::vector<std::unique_ptr<Node>> children;

                Eigen::Matrix4f localTransform;

                mutable bool dirty;
                mutable Eigen::Matrix4f calculatedTransform;
        };
    }
}

#endif // NODE_H
