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

#include "aepyor/aepyor.h"

#include "gtest/gtest.h"

using std::cout;
using std::make_shared;
using std::shared_ptr;

/**
 * Test load for SinusLoadPattern.
 */
class PrintIntLoad : public Load {
 public:
  explicit PrintIntLoad(int value) : value(value) {
  }

  virtual void perform() {
    // TODO(nnielsen): Figure out how to generalize the load output for testing.
    for (int cursor = 0; cursor < value; cursor++) {
      cout << "#";
    }
    cout << std::endl;
  }

 private:
  int value;
};

/**
 * Test LoadPattern which generates a (non-zero) sinus curve load.
 */
class SinusLoadPattern : public LoadPattern {
 public:
  SinusLoadPattern()
    : amplitude(10.0),
      frequency(0.2),
      offset(amplitude),
      lastStep(0) {}

  shared_ptr<Load> at(int step) {
    int result =
      static_cast<int>(floor(amplitude * sin(frequency * step) + offset));

    return make_shared<PrintIntLoad>(result);
  }

 private:
  double amplitude;
  double frequency;
  double offset;
  int lastStep;
};


/**
 * Test timeline which generates loads on virtual time.
 */
class TestTimeline : public Timeline {
 public:
  explicit TestTimeline(shared_ptr<LoadPattern> pattern)
    : pattern(pattern) {}

  void start() {
    const int limit = 100;
    for (int step = 0; step < limit; step++) {
      // TODO(nnielsen): Dispatch work to worker scheduler.
      pattern->at(step)->perform();
    }
  }

  void stop() {
  }

 private:
  shared_ptr<LoadPattern> pattern;
};


TEST(sinus_load, sample_test) {
  TestTimeline timeline(make_shared<SinusLoadPattern>());

  timeline.start();
}
