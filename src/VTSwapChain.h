#ifndef VT_SWAP_CHAIN_INCLUDE_H
#define VT_SWAP_CHAIN_INCLUDE_H

namespace VT
{
class VTSwapChain
{
public:
    VTSwapChain();
    virtual ~VTSwapChain() = default;
    VTSwapChain(const VTSwapChain& other) = delete;
    VTSwapChain(VTSwapChain&& other) = delete;
    VTSwapChain& operator=(const VTSwapChain& other) = delete;
    VTSwapChain& operator=(VTSwapChain&& other) = delete;
};
}

#endif
