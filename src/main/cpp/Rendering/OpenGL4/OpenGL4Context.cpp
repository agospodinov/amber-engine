#include "OpenGL4Context.h"

#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <utility>

#include <GL/gl.h>

#include "Rendering/IObject.h"
#include "OpenGL4Buffer.h"
#include "OpenGL4Framebuffer.h"
#include "OpenGL4Shader.h"
#include "OpenGL4Program.h"
#include "OpenGL4Texture.h"

#include <mutex>

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Context::Private
            {
                public:
                    Private(bool multithreadingSupported);

                    std::map<Reference<IBindable>, std::uint32_t> bindLocks;
                    std::unique_ptr<std::mutex> bindLocksMutex;
                    std::unique_ptr<std::condition_variable> bindSlotLocked;

                    std::map<const IObject *, std::unique_ptr<OpenGL4VertexArray>> vertexArrays;
                    std::vector<std::unique_ptr<IBuffer>> buffers;
                    std::vector<std::unique_ptr<IRenderTarget>> renderTargets;
                    std::vector<std::unique_ptr<IShader>> shaders;
                    std::vector<std::unique_ptr<IProgram>> programs;
                    std::vector<std::unique_ptr<ITexture>> textures;
            };

            OpenGL4Context::Private::Private(bool multithreadingSupported)
            {
                renderTargets.emplace_back(new OpenGL4Framebuffer(0));
                if (multithreadingSupported)
                {
                    bindLocksMutex.reset(new std::mutex());
                    bindSlotLocked.reset(new std::condition_variable());
                }
            }

            OpenGL4Context::OpenGL4Context()
                : p(new Private(isMultithreadingSupported()))
            {
                activate();
            }

            OpenGL4Context::~OpenGL4Context()
            {
                deactivate();
            }

            void OpenGL4Context::activate()
            {
                if (!isActive())
                {
                    IContext::activeContext = this;
                }
            }

            void OpenGL4Context::deactivate()
            {
                if (isActive())
                {
                    IContext::activeContext = nullptr;
                }
            }

            bool OpenGL4Context::isActive() const
            {
                return IContext::getActiveContext() == this;
            }

            bool OpenGL4Context::isMultithreadingSupported() const
            {
                return false;
            }

            bool OpenGL4Context::tryLock(const Reference<IBindable> &bindable)
            {
                std::unique_lock<std::mutex> lock;

                if (isMultithreadingSupported())
                {
                    lock = std::unique_lock<std::mutex>(*p->bindLocksMutex);
                }

                auto testLock = [bindable](const std::pair<const Reference<IBindable>, std::uint32_t> &lock)
                {
                    return lock.first->getBindType() == bindable->getBindType()
                            && lock.first->getBindSlot() == bindable->getBindSlot();
                };

                auto it = std::find_if(p->bindLocks.begin(), p->bindLocks.end(), testLock);

                if (it != p->bindLocks.end() && it->first != bindable)
                {
                    return false;
                }
                else if (it != p->bindLocks.end())
                {
                    it->second += 1;
                }
                else
                {
                    p->bindLocks.emplace(bindable, 1);
                }

                return true;
            }

            void OpenGL4Context::lock(const Reference<IBindable> &bindable)
            {
                while (!tryLock(bindable))
                {
                    if (isMultithreadingSupported())
                    {
                        std::unique_lock<std::mutex> lock(*p->bindLocksMutex);
                        p->bindSlotLocked->wait(lock);
                    }
                    else
                    {
                        throw std::runtime_error("Unable to lock bindable. Would deadlock.");
                    }
                }
            }

            void OpenGL4Context::unlock(const Reference<IBindable> &bindable)
            {
                std::unique_lock<std::mutex> lock;

                if (isMultithreadingSupported())
                {
                    lock = std::unique_lock<std::mutex>(*p->bindLocksMutex);
                }

                auto it = p->bindLocks.find(bindable);

                if (it != p->bindLocks.end())
                {
                    it->second -= 1;

                    if (it->second == 0)
                    {
                        p->bindLocks.erase(it);
                    }

                    if (isMultithreadingSupported())
                    {
                        p->bindSlotLocked->notify_all();
                    }
                }
            }

            Reference<IBuffer> OpenGL4Context::createHardwareBuffer(IBuffer::Type type)
            {
                p->buffers.emplace_back(new OpenGL4Buffer(type));
                return Reference<IBuffer>(this, p->buffers.back().get());
            }

            Reference<IRenderTarget> OpenGL4Context::createRenderTarget()
            {
                p->renderTargets.emplace_back(new OpenGL4Framebuffer());
                return Reference<IRenderTarget>(this, p->renderTargets.back().get());
            }

            Reference<IShader> OpenGL4Context::createShader(IShader::Type type)
            {
                p->shaders.emplace_back(new OpenGL4Shader(type));
                return Reference<IShader>(this, p->shaders.back().get());
            }

            Reference<IProgram> OpenGL4Context::createProgram()
            {
                p->programs.emplace_back(new OpenGL4Program());
                return Reference<IProgram>(this, p->programs.back().get());
            }

            Reference<ITexture> OpenGL4Context::createTexture(ITexture::Type type, ITexture::DataFormat dataFormat)
            {
                p->textures.emplace_back(new OpenGL4Texture(type, dataFormat));
                return Reference<ITexture>(this, p->textures.back().get());
            }

            Reference<IRenderTarget> OpenGL4Context::getDefaultRenderTarget()
            {
                return Reference<IRenderTarget>(this, p->renderTargets.front().get());
            }

            // FIXME this breaks if object's address changes
            Reference<OpenGL4VertexArray> OpenGL4Context::getVertexArray(const IObject *object)
            {
                auto it = p->vertexArrays.find(object);
                return it != p->vertexArrays.end() ? Reference<OpenGL4VertexArray>(this, it->second.get()) : Reference<OpenGL4VertexArray>();
            }

            void OpenGL4Context::createVertexArray(IObject *object)
            {
                Reference<OpenGL4Buffer> vertexBuffer = object->getVertexBuffer().cast<OpenGL4Buffer>();
                Reference<OpenGL4Buffer> indexBuffer = object->getIndexBuffer().cast<OpenGL4Buffer>();

                assert(vertexBuffer.isValid());

                std::unique_ptr<OpenGL4VertexArray> vertexArray(new OpenGL4VertexArray(vertexBuffer, indexBuffer));
                vertexArray->setLayout(object->getLayout());

                p->vertexArrays.emplace(object, std::move(vertexArray));
            }
        }
    }
}
