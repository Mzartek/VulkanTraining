#ifndef VT_STATIC_OBJECT_DRAWABLE_INCLUDE_H
#define VT_STATIC_OBJECT_DRAWABLE_INCLUDE_H

#include "BaseDrawable.h"
#include "../Pipelines/StaticObjectPipeline.h"

namespace VT
{
class StaticObjectDrawable : public BaseDrawable
{
public:
    StaticObjectDrawable(StaticObjectPipeline& staticObjectPipeline);

    void Draw() override;

private:
    StaticObjectPipeline& m_staticObjectPipeline;
};
}

#endif
