#include "OpenGL4Renderer.h"

#include <Eigen/Dense>

#include "Amber/Utilities/Defines.h"
#include "Amber/Core/Transform.h"
#include "Amber/Rendering/Mesh.h"
#include "Amber/Rendering/Material.h"
#include "Amber/Rendering/RenderStage.h"
#include "Amber/Rendering/Backend/IObject.h"
#include "Amber/Rendering/Backend/IRenderTarget.h"
#include "Amber/Rendering/Backend/BindLock.h"
#include "Amber/Rendering/Backend/Reference.h"
#include "Amber/IO/ShaderLoader.h"
#include "Amber/Utilities/Logger.h"
#include "OpenGL4Includes.h"
#include "OpenGL4Buffer.h"
#include "OpenGL4Framebuffer.h"
#include "OpenGL4Program.h"
#include "OpenGL4Texture.h"
#include "OpenGL4VertexArray.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            OpenGL4Renderer::OpenGL4Renderer()
            {
            }

            OpenGL4Renderer::~OpenGL4Renderer()
            {
            }

            void OpenGL4Renderer::prepare(IObject &object)
            {
                if (!object.isInHardwareStorage())
                {
                    object.moveToHardwareStorage(context);
                }

                context.createVertexArray(&object);
            }

            void OpenGL4Renderer::prepare(Reference<IProgram> program)
            {
                if (!program.cast<OpenGL4Program>().isValid())
                {
                    throw std::logic_error("OpenGL4 renderer requires OpenGL shader programs");
                }

                if (!program->isLinked())
                {
                    program->link();
                }
            }

            void OpenGL4Renderer::prepare(Reference<ITexture> texture)
            {
                if (!texture.cast<OpenGL4Texture>().isValid())
                {
                    throw std::logic_error("OpenGL4 renderer requires OpenGL textures");
                }
            }

            void OpenGL4Renderer::prepare(Reference<IRenderTarget> renderTarget)
            {
                if (!renderTarget.cast<OpenGL4Framebuffer>().isValid())
                {
                    throw std::logic_error("OpenGL4 renderer requires OpenGL render target");
                }

                BindLock lock(renderTarget.cast<IBindable>());
                GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

                if (status != GL_FRAMEBUFFER_COMPLETE)
                {
                    throw std::runtime_error("Framebuffer is incomplete: " + std::to_string(status));
                }
            }

            void OpenGL4Renderer::render(Core::World &scene)
            {
                glDepthMask(GL_TRUE);
                glEnable(GL_ALPHA);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//                scene.getWorldNode()->traverse([this, &scene](Core::Node *node)
//                {

//                    if (!node->isSetup() && node->hasRenderable())
//                    {
//                        node->getRenderable()->setup(this);
//                        std::for_each(node->getProcedure().getRenderStages().begin(),
//                                      node->getProcedure().getRenderStages().end(),
//                                      std::bind(&RenderStage::setup, std::placeholders::_1, this));

//                        node->markSetup();
//                    }

//                    if (node->hasRenderable())
//                    {
//                        // FIXME change naive loop to a more optimized draw loop
//                        for (const RenderStage &renderStage : node->getProcedure().getRenderStages())
//                        {
//                            BindLock renderTargetLock(renderStage.getRenderTarget().cast<IBindable>());

//                            if (renderStage.shouldClearBeforeRendering())
//                            {
//                                clear();
//                            }

//                            for (const ShaderPass &shaderPass : renderStage.getShaderPasses())
//                            {
//                                BindLock shaderPassLock(shaderPass.getProgram().cast<IBindable>());

//                                Eigen::Matrix4f modelViewMatrix = scene.getCamera().getViewMatrix() * node->getTransform();
//                                shaderPass.getProgram()->setConstant("mdl_ModelView", modelViewMatrix);
//                                shaderPass.getProgram()->setConstant("mdl_Projection", scene.getCamera().getProjectionMatrix());

//                                node->getRenderable()->render(this);
//                            }
//                        }
//                    }
//                });
            }

            void OpenGL4Renderer::render(IObject &object, Material &material)
            {
                Reference<OpenGL4VertexArray> vertexArray = context.getVertexArray(&object);
                if (!vertexArray.isValid())
                {
                    Utilities::Logger log;
                    log.warning("Uninitialized object; no vertex array!");
                    return;
                }

                std::vector<BindLock> locks;

                locks.emplace_back(vertexArray);
                locks.emplace_back(material.getDiffuseTexture());
                locks.emplace_back(material.getNormalMap());
                locks.emplace_back(material.getSpecularMap());
                locks.emplace_back(material.getDisplacementMap());

                if (vertexArray->hasIndexBuffer())
                {
                    glDrawElementsInstanced(GL_TRIANGLES, object.getPrimitiveCount(), GL_UNSIGNED_INT, 0, object.getInstanceCount());
                }
                else
                {
                    glDrawArraysInstanced(GL_TRIANGLES, 0, object.getPrimitiveCount(), object.getInstanceCount());
                }
            }

            void OpenGL4Renderer::clear()
            {
                glClearColor(0.0f, 0.6f, 0.8f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            }


            bool OpenGL4Renderer::getRenderOption(IRenderer::RenderOption renderOption) const
            {
                // TODO a performance optimization is in order here
                // (a map to store property values)

                GLenum propertyId = getRenderOptionId(renderOption);
                GLboolean enabled = glIsEnabled(propertyId);
                return enabled == GL_TRUE;
            }

            void OpenGL4Renderer::setRenderOption(IRenderer::RenderOption renderOption, bool enabled)
            {
                GLenum propertyId = getRenderOptionId(renderOption);

                if (enabled)
                {
                    glEnable(propertyId);
                }
                else
                {
                    glDisable(propertyId);
                }
            }

            Procedure &OpenGL4Renderer::getProcedure()
            {
                return procedure;
            }

            const Procedure &OpenGL4Renderer::getProcedure() const
            {
                return procedure;
            }

            void OpenGL4Renderer::setProcedure(Procedure procedure)
            {
                this->procedure = std::move(procedure);

                for (RenderStage &renderStage : this->procedure.getRenderStages())
                {
                    prepare(renderStage.getRenderTarget());
                    for (const ShaderPass &shaderPass : renderStage.getShaderPasses())
                    {
                        prepare(shaderPass.getProgram());
                    }
                }
            }


            IContext &OpenGL4Renderer::getContext()
            {
                return context;
            }

            Viewport &OpenGL4Renderer::getViewport()
            {
                return viewport;
            }

            GLenum OpenGL4Renderer::getRenderOptionId(IRenderer::RenderOption renderOption) const
            {
                switch (renderOption)
                {
                    case RenderOption::Culling:
                        return GL_CULL_FACE;
                    case RenderOption::DepthTest:
                        return GL_DEPTH_TEST;
                    case RenderOption::StencilTest:
                        return GL_STENCIL_TEST;
                    default:
                        throw std::runtime_error("Unsupported property.");
                }
            }
        }
    }
}
