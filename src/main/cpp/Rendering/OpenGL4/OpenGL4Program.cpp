#include "OpenGL4Program.h"

#include <algorithm>
#include <stdexcept>

#include <GL/gl.h>

#include "Utilities/Logger.h"
#include "OpenGL4Shader.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            OpenGL4Program::OpenGL4Program()
                : linked(false)
            {
                handle = glCreateProgram();
            }

            OpenGL4Program::OpenGL4Program(OpenGL4Program &&other) noexcept
                : handle(other.handle),
                  shaders(std::move(other.shaders)),
                  layout(std::move(other.layout)),
                  linked(other.linked)
            {
                other.handle = 0;
            }

            OpenGL4Program::~OpenGL4Program()
            {
                if (handle != 0)
                {
                    glDeleteProgram(handle);
                }
            }

            OpenGL4Program &OpenGL4Program::operator =(OpenGL4Program &&other) noexcept
            {
                if (this != &other)
                {
                    handle = other.handle;
                    shaders = std::move(other.shaders);
                    layout = std::move(other.layout);
                    linked = other.linked;

                    other.handle = 0;
                }

                return *this;
            }

            void OpenGL4Program::bind()
            {
                if (!linked)
                {
                    throw std::logic_error("Bind called on program that has not been linked yet.");
                }

                glUseProgram(handle);
            }

            void OpenGL4Program::unbind()
            {
                glUseProgram(0);
            }

            IBindable::BindType OpenGL4Program::getBindType() const
            {
                return BindType::Program;
            }

            std::uint32_t OpenGL4Program::getBindSlot() const
            {
                return 0;
            }

            void OpenGL4Program::link()
            {
                if (linked)
                {
                    throw std::runtime_error("Already linked.");
                }

                for (Reference<OpenGL4Shader> &shader : shaders)
                {
                    if (!shader->isCompiled())
                    {
                        shader->compile();
                    }
                }

                const Layout::AttributeList &attributes = layout.getAttributes();
                for (std::size_t i = 0; i < attributes.size(); i++)
                {
                    glBindAttribLocation(handle, i, attributes.at(i).getName().c_str());
                }

                glLinkProgram(handle);

                int linkSuccessful = 0;
                glGetProgramiv(handle, GL_LINK_STATUS, &linkSuccessful);

                if (linkSuccessful == 0)
                {
                    Utilities::Logger log;

                    GLint length;
                    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);

                    std::vector<GLchar> linkLog(length);
                    glGetProgramInfoLog(handle, length, NULL, linkLog.data());

                    std::string linkLogStr(linkLog.begin(), linkLog.end());
                    log.fatal(linkLogStr);

                    throw std::runtime_error("Program with ID " + std::to_string(handle) + ": linking failed!");
                }

                linked = true;

                introspect();
            }

            bool OpenGL4Program::isLinked() const
            {
                return linked;
            }

            const std::vector<Reference<OpenGL4Shader>> &OpenGL4Program::getShaders() const
            {
                return shaders;
            }

            void OpenGL4Program::addShader(Reference<IShader> shader)
            {
                Reference<OpenGL4Shader> openGlShader = shader.cast<OpenGL4Shader>();

                if (!openGlShader.isValid())
                {
                    throw std::runtime_error("Attempted to add a non-OpenGL4 shader.");
                }

                if (linked)
                {
                    throw std::logic_error("Attempting to modify a linked program.");
                }

                glAttachShader(handle, openGlShader->handle);
                shaders.push_back(std::move(openGlShader));
            }

            const Layout &OpenGL4Program::getLayout() const
            {
                return layout;
            }

            void OpenGL4Program::setLayout(Layout layout)
            {                
                if (linked)
                {
                    throw std::runtime_error("Cannot change layout; program already linked.");
                }

                this->layout = std::move(layout);
            }

            void OpenGL4Program::setConstant(std::string name, std::int32_t value)
            {
                glUniform1i(findConstantByName(name), value);
            }

            void OpenGL4Program::setConstant(std::string name, std::uint32_t value)
            {
                glUniform1ui(findConstantByName(name), value);
            }

            void OpenGL4Program::setConstant(std::string name, float value)
            {
                glUniform1f(findConstantByName(name), value);
            }

            void OpenGL4Program::setConstant(std::string name, Eigen::Matrix4f value)
            {
                glUniformMatrix4fv(findConstantByName(name), 1, value.IsRowMajor, value.data());
            }

            void OpenGL4Program::setConstant(std::string name, Eigen::Vector2f value)
            {
                glUniform2fv(findConstantByName(name), 1, value.data());
            }

            void OpenGL4Program::setConstant(std::string name, Eigen::Vector3f value)
            {
                glUniform3fv(findConstantByName(name), 1, value.data());
            }

            void OpenGL4Program::setConstant(std::string name, Eigen::Vector4f value)
            {
                glUniform4fv(findConstantByName(name), 1, value.data());
            }

            void OpenGL4Program::introspect()
            {
                GLint numActiveUniforms = 0;
                GLint maxNameLength = 0;
                glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &numActiveUniforms);
                glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

                std::vector<GLchar> nameData(maxNameLength);
                for(int i = 0; i < numActiveUniforms; i++)
                {
                    GLint arraySize = 0;
                    GLenum type = 0;
                    GLsizei actualLength = 0;
                    glGetActiveUniform(handle, i, nameData.size(), &actualLength, &arraySize, &type, nameData.data());
                    GLint location = glGetUniformLocation(handle, static_cast<const GLchar *>(nameData.data()));

                    std::string name(static_cast<char *>(nameData.data()), actualLength);
                    constantBindLocationsByName.emplace(name, static_cast<std::size_t>(location));
                }
            }

            GLint OpenGL4Program::findConstantByName(const std::string &name)
            {
                auto it = constantBindLocationsByName.find(name);
                if (it == constantBindLocationsByName.end())
                {
                    return -1;
                }

                return static_cast<GLint>(it->second);
            }
        }
    }
}
