# Copyright (C) 2013      Trent Houliston <trent@houliston.me>, Jake Woods <jake.f.woods@gmail.com>
#               2014-2017 Trent Houliston <trent@houliston.me>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
# OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.10)
PROJECT(NUClear)

SET(VERSION_MAJOR 0)
SET(VERSION_MINOR 2)
SET(VERSION_PATCH 0)

# We use additional modules that cmake needs to know about
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# This directory contains our header files and ipp files
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

# Setup our compiler settings
INCLUDE(CompilerSetup)

# Add the source
ADD_SUBDIRECTORY(src)

# Install the headers and templates that nuclear depends on
INSTALL(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/include/ DESTINATION include PATTERN "*.hpp" PATTERN "*.ipp")

# Add the tests directory
ADD_SUBDIRECTORY(tests)

# Add the documentation subdirectory
ADD_SUBDIRECTORY(docs)
