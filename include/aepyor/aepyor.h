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

#ifndef INCLUDE_AEPYOR_AEPYOR_H_
#define INCLUDE_AEPYOR_AEPYOR_H_

#include <chrono>  // NOLINT(build/c++11)
#include <memory>

/**
 * Describes a full Aepyor session.
 */
class Experiment {
 public:
};

/**
 * Describes the load to be carried out based on load pattern.
 */
class Load {
 public:
  /**
   * Carry out work load.
   */
  virtual void perform() = 0;
};

/**
 * Describes the load pattern to be carried out.
 */
class LoadPattern {
 public:
  /**
   * Returns total load at timestep step.
   */
  virtual std::shared_ptr<Load> at(int step) = 0;
};

/**
 * Describes the timeline, which works as a time keeper for the experiment.
 */
class Timeline {
 public:
  explicit Timeline(std::chrono::duration<double> resolution) {}

  /**
   * Start time and event cycle, driving load generation.
   */
  virtual void start() = 0;

  /**
   * Stop time and load generation.
   */
  virtual void stop() = 0;
};

/**
 * Describes the component, which represents a load generator.
 */
class Worker {
 public:
  virtual void work(std::shared_ptr<Load> load) = 0;
};

#endif  // INCLUDE_AEPYOR_AEPYOR_H_
