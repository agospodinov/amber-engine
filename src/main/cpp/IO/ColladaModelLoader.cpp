#include "ColladaModelLoader.h"

#include "Utilities/Config.h"
#ifdef OpenCOLLADA_FOUND

#include <tuple>
#include <utility>

#include <COLLADAFW.h>
#include <COLLADASaxFWLLoader.h>

#include "Utilities/Logger.h"

#include "MeshBuilder.h"

namespace Amber
{
    namespace IO
    {
        class ColladaModelLoader::OCLoader : public COLLADAFW::IWriter
        {
            public:
                OCLoader(Rendering::Model *model);
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
                Utilities::Logger log;
                Rendering::Model *model;
                std::map<COLLADAFW::ObjectId, Rendering::Mesh> meshes;
                std::map<COLLADAFW::MaterialId, Rendering::Material> materials;
        };

        Rendering::Model ColladaModelLoader::loadModel(const std::string &fileName)
        {
            Rendering::Model model;

            COLLADASaxFWL::Loader loader;
            OCLoader writer(&model);
            COLLADAFW::Root root(&loader, &writer);

            if (!root.loadDocument(fileName))
            {
                throw std::runtime_error("Unable to load COLLADA document.");
            }

            return model;
        }

        ColladaModelLoader::OCLoader::OCLoader(Rendering::Model *model)
            : model(model)
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
            //    log.trace("Loading global asset... " + asset->getAbsoluteFileUri());

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

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeLibraryNodes(const COLLADAFW::LibraryNodes *libraryNodes)
        {
            log.trace("Loading library nodes...");

            //        auto materialIt = materials.find(primitive->getMaterialId());
            //        if (materialIt == materials.end())
            //        {
            //            throw std::runtime_error("Material not found.");
            //        }
            //        Material material = materialIt->second;
            //        model->addData(std::make_tuple(std::move(mesh), std::move(material)));

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
                    builder.setNormals(normalsArray->getData(), normalsArray->getCount());
                }

                if (texCoordsArray)
                {
                    builder.setTexCoords(texCoordsArray->getData(), texCoordsArray->getCount());
                }

                //        assert(primitive->getPositionIndices().getCount() == primitive->getNormalIndices().getCount());

                builder.setIndicesCount(primitive->getPositionIndices().getCount());
                builder.setPositionIndices(primitive->getPositionIndices().getData());

                if (primitive->hasNormalIndices())
                {
                    builder.setNormalIndices(primitive->getNormalIndices().getData());
                }

                //        if (primitive->hasColorIndices())
                //            builder.setColorIndices();
                //        builder.setTexCoordIndices(primitive->getUVCoordIndices());

                Rendering::Mesh mesh = builder.build();
                meshes.emplace(colladaMesh->getObjectId(), std::move(mesh));
            }

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeMaterial(const COLLADAFW::Material *material)
        {
            log.trace("Loading material: " + material->getName());

            log.info(material->getObjectId());

            return true;
        }

        bool ColladaModelLoader::OCLoader::writeEffect(const COLLADAFW::Effect *effect)
        {
            log.trace("Loading effect: " + effect->getName());

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
    }
}

#endif
