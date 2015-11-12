#include "ColladaModelLoader.h"

#include "Amber/Utilities/Config.h"
#ifdef OpenCOLLADA_FOUND

#include <tuple>
#include <utility>

#include <COLLADAFW.h>
#include <COLLADASaxFWLLoader.h>

#include "Amber/Rendering/Material.h"
#include "Amber/Rendering/Mesh.h"
#include "Amber/Rendering/Model.h"
#include "Amber/Rendering/Node.h"
#include "Amber/Rendering/Reference.h"
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
                OCLoader(Rendering::Node *rootNode);
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
                Rendering::Reference<Rendering::ITexture> findTexture(const COLLADAFW::Texture &texture, const COLLADAFW::SamplerPointerArray &samplers);
                Rendering::Procedure loadProcedure(const COLLADAFW::UniqueId &id, Rendering::Node::Type node);

                Utilities::Logger log;
                Rendering::Node *rootNode;
                std::map<COLLADAFW::UniqueId, Rendering::Mesh> meshes;
                std::map<COLLADAFW::UniqueId, Rendering::Material> materials;
                std::map<COLLADAFW::UniqueId, Rendering::Reference<Rendering::ITexture>> textures;
                std::map<COLLADAFW::UniqueId, Rendering::Procedure> procedures;

                std::map<COLLADAFW::UniqueId, COLLADAFW::MaterialId> materialsByMesh;
                std::map<COLLADAFW::UniqueId, COLLADAFW::UniqueId> effectsByMaterial;
        };

        std::unique_ptr<Rendering::Node> ColladaModelLoader::loadModel(const std::string &fileName)
        {
            std::unique_ptr<Rendering::Node> rootNode(new Rendering::Node());

            COLLADASaxFWL::Loader loader;
            OCLoader writer(rootNode.get());
            COLLADAFW::Root root(&loader, &writer);

            if (!root.loadDocument(fileName))
            {
                throw std::runtime_error("Unable to load COLLADA document.");
            }

            return rootNode;
        }

        ColladaModelLoader::OCLoader::OCLoader(Rendering::Node *rootNode)
            : rootNode(rootNode)
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

            const COLLADAFW::NodePointerArray &nodes = visualScene->getRootNodes();
            for (std::size_t i = 0; i < nodes.getCount(); i++)
            {
                std::unique_ptr<Rendering::Node> baseNode(new Rendering::Node());
                COLLADAFW::Node *colladaNode = nodes[i];

                COLLADABU::Math::Matrix4 m = colladaNode->getTransformationMatrix();
                Eigen::Matrix4f modelMatrix;
                modelMatrix << m[0][0], m[0][1], m[0][2], m[0][3],
                               m[1][0], m[1][1], m[1][2], m[1][3],
                               m[2][0], m[2][1], m[2][2], m[2][3],
                               m[3][0], m[3][1], m[3][2], m[3][3];

                baseNode->setLocalTransform(axisFixMatrix * modelMatrix);

                const COLLADAFW::InstanceGeometryPointerArray &geometries = colladaNode->getInstanceGeometries();

                for (std::size_t j = 0; j < geometries.getCount(); j++)
                {
                    COLLADAFW::InstanceGeometry *geometry = geometries[j];
                    std::unique_ptr<Rendering::Node> modelNode(new Rendering::Node());

                    std::unique_ptr<Rendering::Model> model(new Rendering::Model());
                    Rendering::Mesh &mesh = meshes.at(geometry->getInstanciatedObjectId());
                    Rendering::Material material;

                    auto materialIt = materialsByMesh.find(geometry->getInstanciatedObjectId());
                    if (!geometry->getMaterialBindings().empty() && materialIt != materialsByMesh.end())
                    {
                        const COLLADAFW::MaterialBindingArray &bindings = geometry->getMaterialBindings();
                        for (std::size_t k = 0; k < bindings.getCount(); k++)
                        {
                            if (bindings[k].getMaterialId() == materialIt->second)
                            {
                                auto effectIt = effectsByMaterial.find(bindings[k].getReferencedMaterial());
                                material = materials.at(effectIt->second);
                            }
                        }
                    }

                    model->addData(std::make_tuple(std::move(mesh), std::move(material)));

                    // FIXME this should be reworked
                    Rendering::Procedure procedure = loadProcedure(geometry->getUniqueId(), Rendering::Node::Type::Model);
                    for (const Rendering::RenderStage &renderStage : procedure.getRenderStages())
                    {
                        for (const Rendering::ShaderPass &shaderPass : renderStage.getShaderPasses())
                        {
                            shaderPass.getProgram()->setLayout(mesh.getLayout());
                        }
                    }

                    modelNode->setProcedure(std::move(procedure));
                    modelNode->setRenderable(std::move(model));

                    baseNode->addChild(std::move(modelNode));
                }

//                colladaNode->getInstanceLights()

                rootNode->addChild(std::move(baseNode));
            }

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

                Rendering::Mesh mesh = builder.build();
                meshes.emplace(colladaMesh->getUniqueId(), std::move(mesh));
                materialsByMesh.emplace(colladaMesh->getUniqueId(), primitive->getMaterialId());
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

            materials.emplace(effect->getUniqueId(), std::move(material));

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

        Rendering::Procedure ColladaModelLoader::OCLoader::loadProcedure(const COLLADAFW::UniqueId &id, Rendering::Node::Type nodeType)
        {
            auto procedureIt = procedures.find(id);
            if (procedureIt != procedures.end())
            {
                return procedureIt->second;
            }
            else
            {
                // FIXME I really don't like this
                switch (nodeType)
                {
                    case Rendering::Node::Type::Model:
                    {
                        Rendering::IContext *activeContext = Rendering::IContext::getActiveContext();
                        IO::ShaderLoader shaderLoader;
                        Rendering::Procedure procedure;
                        Rendering::RenderStage renderStage(activeContext->getDefaultRenderTarget(), false);
                        Rendering::Reference<Rendering::IShader> vertexShader = activeContext->createShader(Rendering::IShader::Type::VertexShader);
                        shaderLoader.loadShader("BaseModel", vertexShader);

                        Rendering::Reference<Rendering::IShader> pixelShader = activeContext->createShader(Rendering::IShader::Type::PixelShader);
                        shaderLoader.loadShader("BaseModel", pixelShader);

                        Rendering::Reference<Rendering::IProgram> modelsProgram = activeContext->createProgram();
                        modelsProgram->addShader(vertexShader);
                        modelsProgram->addShader(pixelShader);

                        Rendering::ShaderPass modelsPass(std::move(modelsProgram));
                        renderStage.addShaderPass(std::move(modelsPass));
                        procedure.appendRenderStage(std::move(renderStage));
                        return procedure;
                    }
                    case Rendering::Node::Type::Light:
                        throw std::runtime_error("Not yet implemented");
                    default:
                        throw std::invalid_argument("Invalid node type");
                }
            }

        }
    }
}

#endif
