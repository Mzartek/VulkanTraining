#ifndef VT_SIMPLE_DRAWABLE_INCLUDE_H
#define VT_SIMPLE_DRAWABLE_INCLUDE_H

#include "BaseDrawable.h"
#include "../Pipelines/SimplePipeline.h"

namespace VT
{
class SimpleDrawable : public BaseDrawable
{
public:
    SimpleDrawable(CommandPool& commandPool, SimplePipeline& simplePipeline);

    void Draw() override;

private:
    SimplePipeline& m_simplePipeline;
};
}

#endif
