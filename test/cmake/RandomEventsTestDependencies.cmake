# Copyright 2021 DeepMind Technologies Limited
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Build configuration for third party libraries used in MuJoCo.
set(RANDOM_EVENTS_VERSION_gtest
    f8d7d77c06936315286eb55f8de22cd23c188571 # v1.14.0
    CACHE STRING "Version of `gtest` to be fetched."
)

mark_as_advanced(RANDOM_EVENTS_VERSION_gtest)

include(FetchContent)
include(FindOrFetch)

if(RANDOM_EVENTS_BUILD_TESTS)
  # Avoid linking errors on Windows by dynamically linking to the C runtime.
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE
  )

  findorfetch(
    USE_SYSTEM_PACKAGE
    OFF
    PACKAGE_NAME
    GTest
    LIBRARY_NAME
    googletest
    GIT_REPO
    https://github.com/google/googletest.git
    GIT_TAG
    ${RANDOM_EVENTS_VERSION_gtest}
    TARGETS
    gtest
    gmock
    gtest_main
    EXCLUDE_FROM_ALL
  )
endif()
