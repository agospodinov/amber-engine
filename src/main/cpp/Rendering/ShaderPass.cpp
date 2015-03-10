#include "ShaderPass.h"

#include "IRenderer.h"
#include "BindLock.h"
#include "Node.h"
#include "Scene.h"

namespace Amber
{
    namespace Rendering
    {
        ShaderPass::ShaderPass(Reference<IProgram> program, Node::Type filterType, std::function<bool(IRenderable *)> renderPredicate)
            : program(program),
              filterType(filterType),
              renderPredicate(renderPredicate)
        {
        }

        void ShaderPass::setup(IRenderer *renderer)
        {
            renderer->prepare(program);
        }

        void ShaderPass::render(IRenderer *renderer)
        {
            BindLock lock(program.cast<IBindable>());
            renderer->getScene().getWorldNode().traverse([this, renderer](Node *node)
            {
                if (!node->isSetup())
                {
                    node->getRenderable()->setup(renderer);
                    node->markSetup();
                }

                if (!renderPredicate || renderPredicate(node->getRenderable().get()))
                {
                    program->setConstant("mdl_ModelView", node->getTransform());
                    program->setConstant("mdl_Projection", renderer->getScene().getCamera().getProjectionMatrix());

                    node->getRenderable()->render(renderer);
                }
            }, filterType);
        }
    }
}
