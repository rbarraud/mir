/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_FRAMEBUFFER_NATIVE_WINDOW_H
#define ANDROID_FRAMEBUFFER_NATIVE_WINDOW_H

#include <stdint.h>
#include <sys/types.h>

#include <EGL/egl.h>

#include "androidfw/Platform.h"
#include ANDROIDFW_UTILS(String8.h)
#include ANDROIDFW_UTILS(Condition.h)
#include ANDROIDFW_UTILS(Mutex.h)
#include ANDROIDFW_UTILS(Errors.h)
#include <ui/Rect.h>

#include <pixelflinger/pixelflinger.h>

#include <ui/egl/android_natives.h>

#include <memory>
#include <mutex>
#include <condition_variable>

#define NUM_FRAME_BUFFERS  2

// ---------------------------------------------------------------------------
namespace android {
// ---------------------------------------------------------------------------

class Surface;
class NativeBuffer;

// ---------------------------------------------------------------------------

class FramebufferNativeWindow : public ANativeWindow
{
public:
    FramebufferNativeWindow(hw_module_t const* module, std::shared_ptr<framebuffer_device_t> const& fb);

    framebuffer_device_t const * getDevice() const { return fbDev.get(); } 

    bool isUpdateOnDemand() const { return mUpdateOnDemand; }
    status_t setUpdateRectangle(const Rect& updateRect);
    status_t compositionComplete();

    void dump(String8& result);

    // for debugging only
    int getCurrentBufferIndex() const;

    ~FramebufferNativeWindow(); // this class cannot be overloaded

private:
    static int setSwapInterval(ANativeWindow* window, int interval);
    static int dequeueBuffer(ANativeWindow* window, ANativeWindowBuffer** buffer, int*);
    static int dequeueBuffer_DEPRECATED(ANativeWindow* window, ANativeWindowBuffer** buffer);
    static int lockBuffer_DEPRECATED(ANativeWindow* window, ANativeWindowBuffer* buffer);
    static int queueBuffer(ANativeWindow* window, ANativeWindowBuffer* buffer, int);
    static int queueBuffer_DEPRECATED(ANativeWindow* window, ANativeWindowBuffer* buffer);
    static int query(const ANativeWindow* window, int what, int* value);
    static int perform(ANativeWindow* window, int operation, ...);
    
    std::shared_ptr<framebuffer_device_t> fbDev;
    alloc_device_t* grDev;

    NativeBuffer* buffers[NUM_FRAME_BUFFERS];
    
    std::mutex mutex;
    std::condition_variable mCondition;
    int32_t mNumBuffers;
    int32_t mNumFreeBuffers;
    int32_t mBufferHead;
    int32_t mCurrentBufferIndex;
    bool mUpdateOnDemand;
};
    
// ---------------------------------------------------------------------------
}; // namespace android
// ---------------------------------------------------------------------------

#endif // ANDROID_FRAMEBUFFER_NATIVE_WINDOW_H

