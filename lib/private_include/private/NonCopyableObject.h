#ifndef VT_NON_COPYABLE_OBJECT_INCLUDE_H
#define VT_NON_COPYABLE_OBJECT_INCLUDE_H

namespace VT
{
class NonCopyableObject
{
public:
    NonCopyableObject() = default;
    virtual ~NonCopyableObject() = default;
    NonCopyableObject(const NonCopyableObject& other) = delete;
    NonCopyableObject(NonCopyableObject&& other) = delete;
    NonCopyableObject& operator=(const NonCopyableObject& other) = delete;
    NonCopyableObject& operator=(NonCopyableObject&& other) = delete;
};
}

#endif
