/// Copyright 2016 Pinterest Inc.
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
/// http://www.apache.org/licenses/LICENSE-2.0

/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.

//
// @author bol (bol@pinterest.com)
//

#include "common/global_cpu_executor.h"

#include "wangle/concurrent/CPUThreadPoolExecutor.h"

namespace common {

wangle::CPUThreadPoolExecutor* getGlobalCPUExecutor() {
  static const auto n_threads = sysconf(_SC_NPROCESSORS_ONLN);
  static const auto queue_sz = (1 << 14);

  LOG(INFO) << "Running global CPU thread pool with "
            << n_threads << " threads, and "
            << queue_sz << " length queue.";

  static wangle::CPUThreadPoolExecutor g_executor(
    n_threads,
    std::make_unique<
      wangle::LifoSemMPMCQueue<wangle::CPUThreadPoolExecutor::CPUTask,
      wangle::QueueBehaviorIfFull::BLOCK>>(queue_sz));

  return &g_executor;
}

}  // namespace common
