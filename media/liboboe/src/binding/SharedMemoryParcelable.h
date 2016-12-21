/*
 * Copyright 2016 The Android Open Source Project
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

#ifndef BINDING_SHAREDMEMORYPARCELABLE_H
#define BINDING_SHAREDMEMORYPARCELABLE_H

#include <stdint.h>

#include <sys/mman.h>
#include <binder/Parcel.h>
#include <binder/Parcelable.h>

using android::status_t;
using android::Parcel;
using android::Parcelable;

namespace oboe {

// Arbitrary limits for sanity checks. TODO remove after debugging.
#define MAX_SHARED_MEMORIES (32)
#define MAX_MMAP_OFFSET (32 * 1024)
#define MAX_MMAP_SIZE (32 * 1024)

/**
 * This is a parcelable description of a shared memory referenced by a file descriptor.
 * It may be divided into several regions.
 */
class SharedMemoryParcelable : public Parcelable {
public:
    SharedMemoryParcelable();
    virtual ~SharedMemoryParcelable();

    void setup(int fd, int32_t sizeInBytes);

    virtual status_t writeToParcel(Parcel* parcel) const override;

    virtual status_t readFromParcel(const Parcel* parcel) override;

    oboe_result_t resolve(int32_t offsetInBytes, int32_t sizeInBytes, void **regionAddressPtr);

    int32_t getSizeInBytes();

    oboe_result_t validate();

    void dump();

protected:
    int mFd = -1;
    int32_t mSizeInBytes = 0;
    uint8_t *mResolvedAddress = nullptr;
};

} /* namespace oboe */

#endif //BINDING_SHAREDMEMORYPARCELABLE_H