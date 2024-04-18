#pragma once

namespace nigl
{
    struct NonCopyable
    {
        NonCopyable() = default;
        NonCopyable(const NonCopyable& other) = delete;
        NonCopyable operator=(const NonCopyable& other) = delete;
    };
} // namespace nigl
