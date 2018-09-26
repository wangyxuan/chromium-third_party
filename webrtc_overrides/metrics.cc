// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/metrics/histogram.h"
#include "base/metrics/sparse_histogram.h"

namespace webrtc {

// Define webrtc::metrics functions to provide webrtc with implementations.
namespace metrics {

// This class doesn't actually exist, so don't go looking for it :)
// This type is just fwd declared here in order to use it as an opaque type
// between the Histogram functions in this file.
class Histogram;

Histogram* HistogramFactoryGetCounts(
    const std::string& name, int min, int max, int bucket_count) {
  return reinterpret_cast<Histogram*>(
      base::Histogram::FactoryGet(name, min, max, bucket_count,
          base::HistogramBase::kUmaTargetedHistogramFlag));
}

Histogram* HistogramFactoryGetCountsLinear(
    const std::string& name, int min, int max, int bucket_count) {
  return reinterpret_cast<Histogram*>(
      base::LinearHistogram::FactoryGet(name, min, max, bucket_count,
          base::HistogramBase::kUmaTargetedHistogramFlag));
}

Histogram* HistogramFactoryGetEnumeration(
    const std::string& name, int boundary) {
  return reinterpret_cast<Histogram*>(
      base::LinearHistogram::FactoryGet(name, 1, boundary, boundary + 1,
          base::HistogramBase::kUmaTargetedHistogramFlag));
}

Histogram* SparseHistogramFactoryGetEnumeration(const std::string& name,
                                                int boundary) {
  return reinterpret_cast<Histogram*>(base::SparseHistogram::FactoryGet(
      name, base::HistogramBase::kUmaTargetedHistogramFlag));
}

const char* GetHistogramName(Histogram* histogram_pointer) {
  base::HistogramBase* ptr =
      reinterpret_cast<base::HistogramBase*>(histogram_pointer);
  return ptr->histogram_name();
}

void HistogramAdd(Histogram* histogram_pointer, int sample) {
  base::HistogramBase* ptr =
      reinterpret_cast<base::HistogramBase*>(histogram_pointer);
  ptr->Add(sample);
}
}  // namespace metrics
}  // namespace webrtc
