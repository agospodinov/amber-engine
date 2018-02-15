#ifndef IPROGRAM_H
#define IPROGRAM_H

#include "IBindable.h"

#include <cstdint>
#include <memory>
#include <string>

#include <Eigen/Core>

#include "Amber/Rendering/Reference.h"

#include "Amber/Rendering/ForwardDeclarations.h"

namespace Amber
{
    namespace Rendering
    {
        class IProgram : public IBindable
        {
            public:
                IProgram() = default;
                virtual ~IProgram() = default;

                virtual void link() = 0;
                virtual bool isLinked() const = 0;

                virtual void addShader(Reference<IShader> shader) = 0;

                virtual const Layout &getLayout() const = 0;
                virtual void setLayout(Layout layout) = 0;

                virtual void setConstant(std::string name, std::int32_t value) = 0;
                virtual void setConstant(std::string name, std::uint32_t value) = 0;
                virtual void setConstant(std::string name, float value) = 0;

                virtual void setConstant(std::string name, Eigen::Matrix4f value) = 0;
                virtual void setConstant(std::string name, Eigen::Matrix3f value) = 0;
                virtual void setConstant(std::string name, Eigen::Vector2f value) = 0;
                virtual void setConstant(std::string name, Eigen::Vector3f value) = 0;
                virtual void setConstant(std::string name, Eigen::Vector4f value) = 0;
        };
    }
}

#endif // IPROGRAM_H
