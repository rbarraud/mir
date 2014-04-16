/*
 * Copyright © 2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Christopher James Halse Rogers <christopher.halse.rogers@canonical.com>
 */

#include "mir_test_framework/semaphore.h"

namespace mtf = mir_test_framework;

mtf::Semaphore::Semaphore()
    : signalled{false}
{
}

void mtf::Semaphore::raise()
{
    std::unique_lock<decltype(mutex)> lock(mutex);
    signalled = true;
    cv.notify_all();
}

bool mtf::Semaphore::raised()
{
    std::unique_lock<decltype(mutex)> lock(mutex);
    return signalled;
}

void mtf::Semaphore::wait(void)
{
    std::unique_lock<decltype(mutex)> lock(mutex);
    cv.wait(lock, [this]() { return signalled; });
}
