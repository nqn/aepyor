/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <math.h>

#include <iostream>
#include <queue>

#include "aepyor/aepyor.h"

#include "gtest/gtest.h"

using std::cout;
using std::make_shared;
using std::queue;
using std::shared_ptr;

/**
 * TODO(nnielsen): Inline worker to test values.
 */
class TestWorker : public Worker {
 public:
  void work(std::shared_ptr<Load> load) {
    for (int secondsCursor = 0;
         secondsCursor < load->seconds();
         secondsCursor++) {
      for (int requestsCursor = 0;
           requestsCursor < load->requests();
           requestsCursor++) {
        cout << "#";
      }
      cout << std::endl;
    }
  }
};

/**
 * Test LoadPattern which generates a (non-zero) sinus curve load.
 */
class SinusLoadPattern : public LoadPattern {
 public:
  SinusLoadPattern()
    : amplitude(10.0),
      frequency(0.2),
      offset(amplitude) {}

  shared_ptr<Load> at(int step) {
    int result =
      static_cast<int>(floor(amplitude * sin(frequency * step) + offset));

    return make_shared<Load>(result, 3);
  }

 private:
  double amplitude;
  double frequency;
  double offset;
};


/**
 * Test timeline which generates loads on virtual time.
 */
class TestTimeline : public Timeline {
 public:
  explicit TestTimeline(
    shared_ptr<LoadPattern> pattern,
    shared_ptr<Worker> worker)
    : pattern(pattern), worker(worker) {}

  void start() {
    // TODO(nnielsen): Make work generation asynchrous.
    const int limit = 100;
    for (int step = 0; step < limit; step++) {
      workQueue.push(pattern->at(step));
    }

    // TODO(nnielsen): Make work execution asynchrous.
    while (!workQueue.empty()) {
      auto load = workQueue.front();

      worker->work(load);

      workQueue.pop();
    }
  }

  void stop() {
  }

 private:
  shared_ptr<LoadPattern> pattern;
  queue<shared_ptr<Load>> workQueue;

  // TODO(nnielsen): Make this a list of workers.
  shared_ptr<Worker> worker;
};


TEST(sinus_load, sample_test) {
  TestTimeline timeline(
    make_shared<SinusLoadPattern>(),
    make_shared<TestWorker>());

  timeline.start();
}

