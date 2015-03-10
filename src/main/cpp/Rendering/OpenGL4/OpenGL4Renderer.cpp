#include "OpenGL4Renderer.h"

#include <GL/gl.h>
#include <GL/glext.h>

#include "Utilities/Defines.h"
#include "Rendering/IObject.h"
#include "Rendering/IRenderTarget.h"
#include "Rendering/BindLock.h"
#include "Rendering/Material.h"
#include "Rendering/Reference.h"
#include "Rendering/RenderStage.h"
#include "IO/ShaderLoader.h"
#include "Utilities/Logger.h"
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
                : procedure(Procedure::getDefaultProcedure(context))
            {
                prepare();
            }

            OpenGL4Renderer::OpenGL4Renderer(Procedure procedure)
                : procedure(std::move(procedure))
            {
                prepare();
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

            void OpenGL4Renderer::prepare(Material &material)
            {
                if (material.getDiffuseTexture().isValid())
                {
                    prepare(material.getDiffuseTexture());
                }

                if (material.getNormalMap().isValid())
                {
                    prepare(material.getNormalMap());
                }

                if (material.getSpecularMap().isValid())
                {
                    prepare(material.getSpecularMap());
                }

                if (material.getDisplacementMap().isValid())
                {
                    prepare(material.getDisplacementMap());
                }
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

            void OpenGL4Renderer::render()
            {
                std::for_each(procedure.getRenderStages().begin(),
                              procedure.getRenderStages().end(),
                              std::bind(&RenderStage::render, std::placeholders::_1, this));
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

                locks.emplace_back(vertexArray.cast<IBindable>());
                locks.emplace_back(material.getDiffuseTexture().cast<IBindable>());
                locks.emplace_back(material.getNormalMap().cast<IBindable>());
                locks.emplace_back(material.getSpecularMap().cast<IBindable>());
                locks.emplace_back(material.getDisplacementMap().cast<IBindable>());

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

            Procedure &OpenGL4Renderer::getProcedure()
            {
                return procedure;
            }

            void OpenGL4Renderer::setProcedure(Procedure procedure)
            {
                this->procedure = std::move(procedure);
                prepare();
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

            void OpenGL4Renderer::handleWindowResize(int width, int height)
            {
                viewport.setSize(width, height);
                scene.getCamera().setPerspectiveProjection(60.0f, static_cast<float>(viewport.getWidth()) / static_cast<float>(viewport.getHeight()), 0.1f, 1000.0f);
            }

            IContext &OpenGL4Renderer::getContext()
            {
                return context;
            }

            Scene &OpenGL4Renderer::getScene()
            {
                return scene;
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

            void OpenGL4Renderer::prepare()
            {
                scene.getWorldNode().traverse([this](Node *node)
                {
                    if (!node->isSetup())
                    {
                        node->getRenderable()->setup(this);
                        node->markSetup();
                    }
                });

                std::for_each(procedure.getRenderStages().begin(), procedure.getRenderStages().end(),
                              std::bind(&RenderStage::setup, std::placeholders::_1, this));
            }
        }
    }
}
