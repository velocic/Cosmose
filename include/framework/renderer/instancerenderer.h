#ifndef INSTANCERENDERER_H
#define INSTANCERENDERER_H

#include <framework/sprite/spriteinstancedata.h>
#include <glm/glm.hpp>
#include <opengl/programlinker.h>
#include <vector>

namespace Framework
{
    namespace Renderer
    {
        class InstanceRenderer
        {
            private:
                ProgramLinker &shaderProgram;
                GLuint modelDataBuffer;
                GLuint instanceDataBuffer;
                GLuint instanceDataArray;
            public:
                InstanceRenderer(ProgramLinker &shaderProgram, GLuint modelDataBuffer);
                ~InstanceRenderer();
                void enableVertexAttribPointer(
                    GLuint vertexAttributeIndex,
                    GLint componentSize,
                    GLenum dataType,
                    GLboolean isDataNormalized,
                    GLsizei dataStride,
                    GLvoid *dataPointer,
                    GLuint vertexAttributeDivisor
                );
                void render(
                    const Framework::Sprite::SpriteInstanceData *instanceDataCollection,
                    unsigned int instanceDataCollectionSize,
                    unsigned int instanceDataCollectionSizeInBytes
                );
        };
    }
}

#endif
