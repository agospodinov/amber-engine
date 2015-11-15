#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

namespace Amber
{
    namespace Core
    {
        class Node;

        class Scene
        {
            public:
                Scene();
                Scene(std::unique_ptr<Node> worldNode);
                Scene(const Scene &other) = delete;
                Scene(Scene &&other) noexcept;
                virtual ~Scene();

                Scene &operator =(const Scene &other) = delete;
                Scene &operator =(Scene &&other) noexcept;

                Node *getWorldNode();
                const Node *getWorldNode() const;

            private:
                std::unique_ptr<Node> worldNode;
        };
    }
}

#endif // SCENE_H
