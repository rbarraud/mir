/*
 * Copyright © 2016 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
<<<<<<< TREE
 * under the terms of the GNU Lesser General Public License version 3,
=======
 * under the terms of the GNU General Public License version 3,
>>>>>>> MERGE-SOURCE
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
<<<<<<< TREE
 * GNU Lesser General Public License for more details.
=======
 * GNU General Public License for more details.
>>>>>>> MERGE-SOURCE
 *
<<<<<<< TREE
 * You should have received a copy of the GNU Lesser General Public License
=======
 * You should have received a copy of the GNU General Public License
>>>>>>> MERGE-SOURCE
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#ifndef MIR_GRAPHICS_NESTED_NATIVE_BUFFER_H_
#define MIR_GRAPHICS_NESTED_NATIVE_BUFFER_H_

#include "mir/geometry/size.h"
#include "mir/graphics/native_buffer.h"
#include "mir_toolkit/client_types_nbs.h"
#include "mir_toolkit/client_types.h"
#include "mir_toolkit/mir_native_buffer.h"
#include <chrono>
#include <functional>

namespace mir
{
namespace graphics
{
namespace nested
{
class NativeBuffer : public graphics::NativeBuffer
{
public:
    virtual ~NativeBuffer() = default;
    virtual void sync(MirBufferAccess, std::chrono::nanoseconds) = 0;
    virtual MirBuffer* client_handle() const = 0;
    virtual MirNativeBuffer* get_native_handle() = 0;
    virtual MirGraphicsRegion get_graphics_region() = 0;
    virtual geometry::Size size() const = 0;
    virtual MirPixelFormat format() const = 0;
    virtual void tag_submitted() = 0;
    virtual void when_back(std::function<void()> const& fn) = 0;
protected:
    NativeBuffer() = default;
    NativeBuffer(NativeBuffer const&) = delete;
    NativeBuffer& operator=(NativeBuffer const&) = delete;
};
}
}
}

#endif /* MIR_GRAPHICS_NESTED_NATIVE_BUFFER_H_ */
