#ifndef VT_STATIC_OBJECT_DRAWABLE_INCLUDE_H
#define VT_STATIC_OBJECT_DRAWABLE_INCLUDE_H

#include "BaseDrawable.h"
#include "../Pipelines/StaticObjectPipeline.h"
#include "../Buffer.h"

namespace VT
{
class StaticObjectDrawable : public BaseDrawable
{
public:
    StaticObjectDrawable(StaticObjectPipeline& staticObjectPipeline,
        const std::vector<StaticObjectPipeline::Vertex>& vertices,
        const std::vector<StaticObjectPipeline::Index>& indices);

    void Draw() override;

private:
    StaticObjectPipeline& m_staticObjectPipeline;

    Buffer m_vertexBuffer;
    Buffer m_indexBuffer;
};
}

#endif
