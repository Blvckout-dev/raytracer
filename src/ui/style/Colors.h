#ifndef COLORS_H
#define COLORS_H

#include "geometry/vec.h"

using vec::Vec3;

namespace Ui
{
    namespace Style
    {
        class Colors {
            public:
                inline static constexpr Vec3 Background = Vec3(51.0f, 51.0f, 51.0f);    // app background
                inline static constexpr Vec3 Surface = Vec3(102.0f, 102.0f, 102.0f);    // panels, buttons, containers
                inline static constexpr Vec3 Text = Vec3(255.0f, 255.0f, 255.0f);       // app text
                inline static constexpr Vec3 Primary = Vec3(0.0f, 255.0f, 255.0f);      // highlight/detail active buttons or accents
        };
    } // namespace style
} // namespace Ui


#endif // COLORS_H
