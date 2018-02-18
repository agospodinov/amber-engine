#include "OpenGL4Buffer.h"

#include <algorithm>
#include <cstring>
#include <functional>

#include "OpenGL4Includes.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            OpenGL4Buffer::OpenGL4Buffer(Type type, std::size_t capacity, void *data, OpenGL4Buffer::UsagePattern usagePattern)
                : type(type),
                  capacity(capacity),
                  usagePattern(usagePattern),
                  bindSlot(0),
                  bound(false)
            {
                glGenBuffers(1, &handle);

                if (capacity > 0)
                {
                    bind();
                    glBufferData(getGLType(type), capacity, data, static_cast<GLenum>(usagePattern));
                }
            }

            OpenGL4Buffer::OpenGL4Buffer(OpenGL4Buffer &&other) noexcept
                : OpenGL4Object(other.handle),
                  type(other.type),
                  capacity(other.capacity),
                  usagePattern(other.usagePattern),
                  bindSlot(other.bindSlot)
            {
                other.handle = 0;
            }

            OpenGL4Buffer::~OpenGL4Buffer()
            {
                if (handle != 0)
                {
                    glDeleteBuffers(1, &handle);
                }
            }

            OpenGL4Buffer &OpenGL4Buffer::operator =(OpenGL4Buffer &&other) noexcept
            {
                if (this != &other)
                {
                    handle = other.handle;
                    type = other.type;
                    capacity = other.capacity;
                    usagePattern = other.usagePattern;
                    bindSlot = other.bindSlot;

                    other.handle = 0;
                }

                return *this;
            }

            OpenGL4Buffer OpenGL4Buffer::clone()
            {
                OpenGL4Buffer cloned(type, capacity, nullptr, usagePattern);

                glBindBuffer(GL_COPY_READ_BUFFER, handle);
                glBindBuffer(GL_COPY_WRITE_BUFFER, cloned.handle);
                glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, capacity);

                return cloned;
            }

            void OpenGL4Buffer::assign(std::size_t offset, std::size_t size, const void *data)
            {
                if (offset < 0 || offset + size > this->capacity)
                {
                    throw std::out_of_range("Attempted to write outside bounds of buffer.");
                }

                bind();
                glBufferSubData(getGLType(type), offset, capacity, data);
                unbind();
            }

            void OpenGL4Buffer::migrate(IBuffer &otherStorage)
            {
                otherStorage.resize(this->getCapacity());

                Utilities::ScopedDataPointer data = this->data();
                std::memcpy(otherStorage.data().get(), data.get(), capacity);
            }

            void OpenGL4Buffer::resize(std::size_t newCapacity)
            {
                using std::swap;

                OpenGL4Buffer resized(type, newCapacity, nullptr, usagePattern);

                if (this->capacity > 0)
                {
                    glBindBuffer(GL_COPY_READ_BUFFER, handle);
                    glBindBuffer(GL_COPY_WRITE_BUFFER, resized.handle);
                    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, std::min(capacity, resized.capacity));
                }

                swap(*this, resized);
            }

            Utilities::ScopedDataPointer OpenGL4Buffer::data()
            {
                bind();
                // TODO choose an appropriate access type; overload this as a const method
                void *bufferPtr = glMapBuffer(getGLType(type), GL_READ_WRITE);
                // FIXME this should lock the bound buffer because someone might unbind it
                return Utilities::ScopedDataPointer(bufferPtr, [this](void *data)
                {
                    this->bind();
                    glUnmapBuffer(getGLType(this->type));
                    this->unbind();
                });
            }

            std::size_t OpenGL4Buffer::getCapacity() const
            {
                return capacity;
            }

            bool OpenGL4Buffer::isNull() const
            {
                return capacity == 0;
            }

            void OpenGL4Buffer::clear()
            {
                // FIXME unsure if this is correct
//                glInvalidateBufferData(handle);
            }

            void OpenGL4Buffer::bind()
            {
                if (!isMultiSlotSupported())
                {
                    glBindBuffer(getGLType(type), handle);
                }
                else
                {
                    glBindBufferBase(getGLType(type), bindSlot, handle);
                }
                this->bound = true;
            }

            void OpenGL4Buffer::unbind()
            {
                if (!isMultiSlotSupported())
                {
                    glBindBuffer(getGLType(type), 0);
                }
                else
                {
                    glBindBufferBase(getGLType(type), bindSlot, 0);
                }
                this->bound = false;
            }

            IBindable::BindType OpenGL4Buffer::getBindType() const
            {
                return BindType::Buffer;
            }

            std::uint32_t OpenGL4Buffer::getBindSlot() const
            {
                return bindSlot;
            }

            void OpenGL4Buffer::setBindSlot(std::uint32_t bindSlot)
            {
                if (!isMultiSlotSupported())
                {
                    throw std::invalid_argument("This buffer does not support multiple bind slots.");
                }

                if (bound)
                {
                    throw std::runtime_error("Cannot change bind slot while buffer is bound");
                }

                this->bindSlot = bindSlot;
            }

            IBuffer::Type OpenGL4Buffer::getType() const
            {
                return type;
            }

            void OpenGL4Buffer::setType(IBuffer::Type type)
            {
                this->type = type;
            }

            GLenum OpenGL4Buffer::getGLType(Type type) const
            {
                switch (type)
                {
                    case Type::Vertex:
                        return GL_ARRAY_BUFFER;
                    case Type::Index:
                        return GL_ELEMENT_ARRAY_BUFFER;
                    case Type::Constant:
                        return GL_UNIFORM_BUFFER;
                    default:
                        throw std::invalid_argument("Unsupported buffer type.");
                }
            }

            bool OpenGL4Buffer::isMultiSlotSupported() const
            {
                // Supported by OpenGL4: Uniform, TransformFeedback, AtomicCounter, ShaderStorage
                return type == Type::Constant;
            }
        }
    }
}
