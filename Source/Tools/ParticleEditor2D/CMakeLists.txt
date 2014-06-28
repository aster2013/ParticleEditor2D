#
# Copyright (c) 2014 the ParticleEditor2D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

# Define target name
set (TARGET_NAME ParticleEditor2D)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

# Find Urho3D library
# find_package (Urho3D REQUIRED)
# include_directories (${URHO3D_INCLUDE_DIRS})

# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# Define source files
define_source_files ()

# Moccing h files
qt4_wrap_cpp( MOC_FILES ${H_FILES} )

# Compile ui files
file (GLOB UI_FILES *.ui)
qt4_wrap_ui( UI_HEADERS ${UI_FILES} )

# Rccing qrc files
file (GLOB QRC_FILES *.qrc)
qt4_add_resources( RCC_FILES ${QRC_FILES} )

set (SOURCE_FILES ${SOURCE_FILES} ${MOC_FILES} ${UI_HEADERS} ${RCC_FILES})

# Setup target with resource copying
setup_main_executable ()

target_link_libraries(${TARGET_NAME} ${QT_LIBRARIES})
