#include "ColladaModelLoader.h"

#include "Amber/Utilities/Config.h"
#ifdef OpenCOLLADA_FOUND

#include <tuple>
#include <utility>

#include <COLLADAFW.h>
#include <COLLADASaxFWLLoader.h>

#include "Amber/Core/Entity.h"
#include "Amber/Core/Transform.h"
#include "Amber/Rendering/Light.h"
#include "Amber/Rendering/Material.h"
#include "Amber/Rendering/Mesh.h"
#include "Amber/Rendering/Backend/Reference.h"
#include "Amber/Rendering/ForwardDeclarations.h"
#include "Amber/Utilities/Logger.h"
#include "ImageTextureLoader.h"
#include "MeshBuilder.h"
#include "ShaderLoader.h"

namespace Amber
{
    namespace IO
    {
        class ColladaModelLoader::OCLoader : public COLLADAFW::IWriter
        {
            public:
                OCLoader(std::vector<Core::Entity> &entities);
                virtual ~OCLoader();

                virtual void cancel(const COLLADAFW::String& errorMessage);
                virtual void start();
                virtual void finish();

                virtual bool writeGlobalAsset(const COLLADAFW::FileInfo* asset);
                virtual bool writeScene(const COLLADAFW::Scene* scene);
                virtual bool writeVisualScene(const COLLADAFW::VisualScene* visualScene);
                virtual bool writeLibraryNodes(const COLLADAFW::LibraryNodes* libraryNodes);
                virtual bool writeGeometry(const COLLADAFW::Geometry* geometry);
                virtual bool writeMaterial(const COLLADAFW::Material* material);
                virtual bool writeEffect(const COLLADAFW::Effect* effect);
                virtual bool writeCamera(const COLLADAFW::Camera* camera);
                virtual bool writeImage(const COLLADAFW::Image* image);
                virtual bool writeLight(const COLLADAFW::Light* light);
                virtual bool writeAnimation(const COLLADAFW::Animation* animation);
                virtual bool writeAnimationList(const COLLADAFW::AnimationList* animationList);
                virtual bool writeSkinControllerData(const COLLADAFW::SkinControllerData* skinControllerData);
                virtual bool writeController(const COLLADAFW::Controller* controller);
                virtual bool writeFormulas(const COLLADAFW::Formulas* formulas);
                virtual bool writeKinematicsScene(const COLLADAFW::KinematicsScene* kinematicsScene);

            private:
                Eigen::Vector4f convertColor(const COLLADAFW::Color &color);
                Rendering::Reference<Rendering::ITexture> findTexture(const COLLADAFW::Texture &texture, const COLLADAFW::SamplerPointerArray &samplers);
                void traverseNodes(const COLLADAFW::NodePointerArray &nodes, Core::Transform *parentTransform);

                Utilities::Logger log;
                std::vector<Core::Entity> &entities;

                std::map<COLLADAFW::UniqueId, Rendering::Mesh> meshes;
                std::map<COLLADAFW::UniqueId, Rendering::Material> effects;
                std::map<COLLADAFW::UniqueId, Rendering::Reference<Rendering::ITexture>> textures;
                std::map<COLLADAFW::UniqueId, Rendering::Light> lights;

                std::multimap<COLLADAFW::UniqueId, COLLADAFW::UniqueId> meshesByModel;
                std::map<COLLADAFW::UniqueId, COLLADAFW::MaterialId> materialsByMesh;
                std::map<COLLADAFW::UniqueId, COLLADAFW::UniqueId> effectsByMaterial;
        };


        std::vector<Core::Entity> ColladaModelLoader::loadModel(const std::string &fileName)
        {
            std::vector<Core::Entity> entities;

            COLLADASaxFWL::Loader loader;
            OCLoader writer(entities);
            COLLADAFW::Root root(&loader, &writer);

            if (!root.loadDocument(fileName))
            {
                throw std::runtime_error("Unable to load COLLADA document.");
            }

            return entities;
        }

        ColladaModelLoader::OCLoader::OCLoader(std::vector<Core::Entity> &entities)
            : entities(entities)
        {
        }

        ColladaModelLoader::OCLoader::~OCLoader()
        {
        }

        void ColladaModelLoader::OCLoader::cancel(const COLLADAFW::String &errorMessage)
        {
            log.error("Cancelled loading: " + errorMessage);
        }

        void ColladaModelLoader::OCLoader::start()
        {
            log.trace("Beginning loading document");
        }

        void ColladaModelLoader::OCLoader::finish()
        {
            log.trace("Finished loading document");
        }

        bool ColladaModelLoader::OCLoader::writeGlobalAsset(const COLLADAFW::FileInfo *asset)
        {
            log.trace("Loading global asset... ");

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeScene(const COLLADAFW::Scene *scene)
        {
            log.trace("Loading scene... ");

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeVisualScene(const COLLADAFW::VisualScene *visualScene)
        {
            log.trace("Loading visual scene: " + visualScene->getName());

            Eigen::Matrix4f axisFixMatrix;
            axisFixMatrix << 1, 0, 0, 0,
                             0, 0, 1, 0,
                             0,-1, 0, 0,
                             0, 0, 0, 1;

            Core::Transform rootTransform(axisFixMatrix);
            traverseNodes(visualScene->getRootNodes(), &rootTransform);

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeLibraryNodes(const COLLADAFW::LibraryNodes *libraryNodes)
        {
            log.trace("Loading library nodes...");

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeGeometry(const COLLADAFW::Geometry *geometry)
        {
            log.trace("Loading geometry: " + geometry->getName());

            const COLLADAFW::Mesh *colladaMesh = dynamic_cast<const COLLADAFW::Mesh *>(geometry);

            const COLLADAFW::FloatArray *positionsArray = colladaMesh->getPositions().getFloatValues();
            const COLLADAFW::FloatArray *normalsArray = colladaMesh->getNormals().getFloatValues();
            const COLLADAFW::FloatArray *colorsArray = colladaMesh->getColors().getFloatValues();
            const COLLADAFW::FloatArray *texCoordsArray = colladaMesh->getUVCoords().getFloatValues();

            const COLLADAFW::MeshPrimitiveArray &primitives = colladaMesh->getMeshPrimitives();
            log.info("Number of submeshes: " + std::to_string(primitives.getCount()));

            for (std::size_t i = 0; i < primitives.getCount(); i++)
            {
                COLLADAFW::MeshPrimitive *primitive = primitives[i];

                MeshBuilder builder;

                builder.setPositions(positionsArray->getData(), positionsArray->getCount());
                if (normalsArray)
                {
                    builder.setNormals(normalsArray->getData(), normalsArray->getCount());
                }

                if (colorsArray)
                {
                    builder.setColors(colorsArray->getData(), colorsArray->getCount());
                }

                if (texCoordsArray)
                {
                    builder.setTexCoords(texCoordsArray->getData(), texCoordsArray->getCount());
                }

                builder.setIndicesCount(primitive->getPositionIndices().getCount());
                builder.setPositionIndices(primitive->getPositionIndices().getData());

                if (primitive->hasNormalIndices())
                {
                    builder.setNormalIndices(primitive->getNormalIndices().getData());
                }

                // TODO add support for multiple color and UV sets
                if (primitive->hasColorIndices())
                {
                    builder.setColorIndices(primitive->getColorIndices(0)->getIndices().getData());
                }

                if (primitive->hasUVCoordIndices())
                {
                    builder.setTexCoordIndices(primitive->getUVCoordIndices(0)->getIndices().getData());
                }

                // TODO a performance optimization is probably necessary here...
                // the vertex data can be shared between the meshes so that they only
                // use a single vertex buffer and a single index buffer and instead
                // use a baseIndex when rendering
                Rendering::Mesh mesh = builder.build();
                meshes.emplace(primitive->getUniqueId(), std::move(mesh));
                materialsByMesh.emplace(primitive->getUniqueId(), primitive->getMaterialId());

                meshesByModel.emplace(colladaMesh->getUniqueId(), primitive->getUniqueId());
            }

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeMaterial(const COLLADAFW::Material *material)
        {
            log.trace("Loading material: " + material->getName());

            effectsByMaterial.emplace(material->getUniqueId(), material->getInstantiatedEffect());

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeEffect(const COLLADAFW::Effect *effect)
        {
            log.trace("Loading effect: " + effect->getName());

            Rendering::Material material;
            COLLADAFW::CommonEffectPointerArray commonEffects = effect->getCommonEffects();

            for (std::size_t i = 0; i < commonEffects.getCount(); i++)
            {
                COLLADAFW::EffectCommon *commonEffect = commonEffects[i];
                COLLADAFW::SamplerPointerArray samplers = commonEffect->getSamplerPointerArray();

                if (commonEffect->getDiffuse().isTexture())
                {
                    material.setDiffuseTexture(findTexture(commonEffect->getDiffuse().getTexture(), samplers));
                }
                else if (commonEffect->getDiffuse().isColor())
                {
                    material.setDiffuseColor(convertColor(commonEffect->getDiffuse().getColor()));
                }

                if (commonEffect->getSpecular().isTexture())
                {
                    material.setSpecularMap(findTexture(commonEffect->getSpecular().getTexture(), samplers));
                }

                // TODO add normal and displacement maps as well as emission and translucency values
//                material.setNormalMap();
//                material.setDisplacementMap();

//                material.setEmission();
//                material.setTranslucency();
                material.setReflectivity(commonEffect->getReflectivity().getFloatValue());
                material.setIndexOfRefraction(commonEffect->getIndexOfRefraction().getFloatValue());
            }

            effects.emplace(effect->getUniqueId(), std::move(material));

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeCamera(const COLLADAFW::Camera *camera)
        {
            log.trace("Loading camera: " + camera->getName());

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeImage(const COLLADAFW::Image *image)
        {
            log.trace("Loading image: " + image->getName());

            // FIXME I don't like depending on an active context here
            Rendering::IContext *activeContext = Rendering::IContext::getActiveContext();
            Rendering::Reference<Rendering::ITexture> texture = activeContext->createTexture(Rendering::ITexture::Type::Texture2D);
            ImageTextureLoader loader;
            loader.loadTexture(image->getImageURI().toNativePath(), texture);
            texture->setFilterMode(Rendering::ITexture::FilterMode::Linear);
            textures.emplace(image->getUniqueId(), std::move(texture));

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeLight(const COLLADAFW::Light *light)
        {
            log.trace("Loading light: " + light->getName());

            using Amber::Rendering::Light;

            Light::Type lightType;
            switch (light->getLightType())
            {
            case COLLADAFW::Light::DIRECTIONAL_LIGHT:
                lightType = Light::Type::Directional;
                break;
            case COLLADAFW::Light::POINT_LIGHT:
                lightType = Light::Type::Point;
                break;
            case COLLADAFW::Light::SPOT_LIGHT:
                lightType = Light::Type::Spotlight;
                break;
            default:
                return true;
            }

            Light l(lightType);
            l.setColor(convertColor(light->getColor()));
            l.setAttenuationCoefficients(Eigen::Vector3f(light->getConstantAttenuation(),
                                                         light->getLinearAttenuation(),
                                                         light->getQuadraticAttenuation()));

            lights.emplace(light->getUniqueId(), std::move(l));

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeAnimation(const COLLADAFW::Animation *animation)
        {
            log.trace("Loading animation: " + animation->getName());

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeAnimationList(const COLLADAFW::AnimationList *animationList)
        {
            log.trace("Loading animation list...");

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeSkinControllerData(const COLLADAFW::SkinControllerData *skinControllerData)
        {
            log.trace("Loading skin controller data: " + skinControllerData->getName());

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeController(const COLLADAFW::Controller *controller)
        {
            log.trace("Loading controller...");

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeFormulas(const COLLADAFW::Formulas *formulas)
        {
            log.trace("Loading formulas...");

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeKinematicsScene(const COLLADAFW::KinematicsScene *kinematicsScene)
        {
            log.trace("Loading kinematics scene...");

            return true;
        }

        Eigen::Vector4f ColladaModelLoader::OCLoader::convertColor(const COLLADAFW::Color &color)
        {
            return Eigen::Vector4f(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
        }

        Rendering::Reference<Rendering::ITexture> ColladaModelLoader::OCLoader::findTexture(const COLLADAFW::Texture &texture, const COLLADAFW::SamplerPointerArray &samplers)
        {
            COLLADAFW::SamplerID id = texture.getSamplerId();
            COLLADAFW::Sampler *sampler = samplers[id];

            auto it = textures.find(sampler->getSourceImage());
            if (it != textures.end())
            {
                return it->second;
            }

            return Rendering::Reference<Rendering::ITexture>();
        }

        void ColladaModelLoader::OCLoader::traverseNodes(const COLLADAFW::NodePointerArray &nodes, Core::Transform *parentTransform)
        {
            for (std::size_t i = 0; i < nodes.getCount(); i++)
            {
                COLLADAFW::Node *colladaNode = nodes[i];

                // FIXME might have to change to (COLLADAFW::Matrix *) getTransformations()[0]
                COLLADABU::Math::Matrix4 m = colladaNode->getTransformationMatrix();
                Eigen::Matrix4f modelMatrix;
                modelMatrix << m[0][0], m[0][1], m[0][2], m[0][3],
                               m[1][0], m[1][1], m[1][2], m[1][3],
                               m[2][0], m[2][1], m[2][2], m[2][3],
                               m[3][0], m[3][1], m[3][2], m[3][3];

                Core::Transform transformComponent(modelMatrix, parentTransform);
                transformComponent.flatten(); // FIXME find way to share transform across entities

                const COLLADAFW::InstanceGeometryPointerArray &geometries = colladaNode->getInstanceGeometries();

                for (std::size_t j = 0; j < geometries.getCount(); j++)
                {
                    COLLADAFW::InstanceGeometry *geometry = geometries[j];

                    auto meshesIt = meshesByModel.equal_range(geometry->getInstanciatedObjectId());

                    for (auto it = meshesIt.first; it != meshesIt.second; it++)
                    {
                        Core::Entity entity;
                        entity.addComponent(std::unique_ptr<Core::Transform>(new Core::Transform(transformComponent)));

                        Rendering::Mesh &mesh = meshes.at(it->second);
                        Rendering::Material material;

                        // In collada, each mesh (a.k.a. primitive) has a MaterialId that it's bound to.
                        // So we need to search through the material bindings to find the one that corresponds
                        // to that mesh, get its unique id and then find the corresponding material.
                        auto materialIt = materialsByMesh.find(it->second);
                        if (!geometry->getMaterialBindings().empty() && materialIt != materialsByMesh.end())
                        {
                            const COLLADAFW::MaterialBindingArray &bindings = geometry->getMaterialBindings();
                            for (std::size_t k = 0; k < bindings.getCount(); k++)
                            {
                                if (bindings[k].getMaterialId() == materialIt->second)
                                {
                                    auto effectIt = effectsByMaterial.find(bindings[k].getReferencedMaterial());
                                    material = effects.at(effectIt->second);
                                    break;
                                }
                            }
                        }

                        entity.addComponent(std::unique_ptr<Rendering::Mesh>(new Rendering::Mesh(std::move(mesh))));
                        entity.addComponent(std::unique_ptr<Rendering::Material>(new Rendering::Material(std::move(material))));

                        entities.push_back(std::move(entity));
                    }
                }

                const COLLADAFW::InstanceLightPointerArray &instanceLights = colladaNode->getInstanceLights();
                for (int j = 0; j < instanceLights.getCount(); j++)
                {
                    COLLADAFW::InstanceLight *light = instanceLights[j];
                    Rendering::Light l = lights.at(light->getInstanciatedObjectId());

                    Core::Entity entity;
                    entity.addComponent(std::unique_ptr<Core::Transform>(new Core::Transform(transformComponent)));
                    entity.addComponent(std::unique_ptr<Rendering::Light>(new Rendering::Light(std::move(l))));

                    entities.push_back(std::move(entity));
                }

                traverseNodes(colladaNode->getChildNodes(), &transformComponent);
            }
        }
    }
}

#endif
