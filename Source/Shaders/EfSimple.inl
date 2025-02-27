// Copyright (c) 2022 Sultim Tsyrendashiev
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#define DESC_SET_FRAMEBUFFERS 0
#define DESC_SET_GLOBAL_UNIFORM 1
#include "ShaderCommonGLSLFunc.h"

layout(local_size_x = COMPUTE_EFFECT_GROUP_SIZE_X, local_size_y = COMPUTE_EFFECT_GROUP_SIZE_Y, local_size_z = 1) in;

layout(constant_id = 0) const uint isSourcePing = 0;

#define EFFECT_SOURCE_IS_PING (isSourcePing != 0)
#include "EfCommon.inl"

layout(push_constant) uniform EffectSimplePush_BT
{
    uint transitionType; // 0 - no transition, 1 - in, 2 - out
    float transitionBeginTime;
    float transitionDuration;
#ifdef EFFECT_PUSH_CONST_T
    EFFECT_PUSH_CONST_T custom;
#endif
} push;

// 0 - no effect, 1 - full effect
float getProgress()
{
    float progress = 
        max(globalUniform.time - push.transitionBeginTime, 0.001) / 
        max(push.transitionDuration, 0.001);

    progress = clamp(progress, 0, 1);

    if (push.transitionType == 1)
    {
        return 1.0 - progress;
    }
    else
    {
        return progress;
    }
}
