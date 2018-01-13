#ifndef VT_SIMPLE_DRAWABLE_INCLUDE_H
#define VT_SIMPLE_DRAWABLE_INCLUDE_H

#include "BaseDrawable.h"
#include "../Semaphore.h"
#include "../Pipelines/SimplePipeline.h"

namespace VT
{
class SimpleDrawable : public BaseDrawable
{
public:
    SimpleDrawable(const CommandPool& commandPool, const SimplePipeline& simplePipeline);
    ~SimpleDrawable() override = default;
    SimpleDrawable(const SimpleDrawable& other) = delete;
    SimpleDrawable(SimpleDrawable&& other) = delete;
    SimpleDrawable& operator=(const SimpleDrawable& other) = delete;
    SimpleDrawable& operator=(SimpleDrawable&& other) = delete;

    void Draw() override;

private:
    const SimplePipeline& m_simplePipeline;

    Semaphore m_imageAvailableSemaphore;
    Semaphore m_renderFinishedSemaphore;
};
}

#endif
