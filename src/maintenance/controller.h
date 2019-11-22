// Copyright (C) 2019 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef IORAP_SRC_MAINTENANCE_COMPILER_CONTROLLER_H_
#define IORAP_SRC_MAINTENANCE_COMPILER_CONTROLLER_H_

#include "db/file_models.h"
#include "inode2filename/inode_resolver.h"

#include <string>
#include <vector>

namespace iorap::maintenance {

// Represents the parameters used for compilation controller.
struct ControllerParameters {
  bool output_text;
  // The path of inode2filepath file.
  std::optional<std::string> inode_textcache;
  bool verbose;
  bool recompile;
  uint64_t min_traces;

  ControllerParameters(bool output_text,
                       std::optional<std::string> inode_textcache,
                       bool verbose,
                       bool recompile,
                       uint64_t min_traces) :
    output_text(output_text),
    inode_textcache(inode_textcache),
    verbose(verbose),
    recompile(recompile),
    min_traces(min_traces) {
  }
};

// Control the compilation of perfetto traces in the sqlite db.
//
// The strategy now is to compile all the existing perfetto traces for an activity
// and skip ones if the number of perfetto traces is less than the min_traces.
//
// By default, the program doesn't replace the existing compiled trace, it just
// return true. To force replace the existing compiled trace, set `force` to true.
//
// The timestamp limit of the each perfetto trace is determined by `report_fully_drawn_ns`
// timestamp. If it doesn't exists, use `total_time_ns`. If neither of them exists,
// use the max.

// Compile all activities of all packages in the database.
bool Compile(const std::string& db_path, const ControllerParameters& params);

// Compile all activities in the package.
bool Compile(const std::string& db_path,
             const std::string& package_name,
             const ControllerParameters& params);

// Compile trace for the activity.
bool Compile(const std::string& db_path,
             const std::string& package_name,
             const std::string& activity_name,
             const ControllerParameters& params);
} // iorap::compiler_controller

#endif  // IORAP_SRC_MAINTENANCE_COMPILER_CONTROLLER_H_