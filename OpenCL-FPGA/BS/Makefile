# 
#  Copyright (c) 2016 University of Cordoba and University of Illinois
#  All rights reserved.
# 
#  Developed by:    IMPACT Research Group
#                   University of Cordoba and University of Illinois
#                   http://impact.crhc.illinois.edu/
# 
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  with the Software without restriction, including without limitation the 
#  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
#  sell copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
# 
#       > Redistributions of source code must retain the above copyright notice,
#         this list of conditions and the following disclaimers.
#       > Redistributions in binary form must reproduce the above copyright
#         notice, this list of conditions and the following disclaimers in the
#         documentation and/or other materials provided with the distribution.
#       > Neither the names of IMPACT Research Group, University of Cordoba, 
#         University of Illinois nor the names of its contributors may be used 
#         to endorse or promote products derived from this Software without 
#         specific prior written permission.
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
#  CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH
#  THE SOFTWARE.
# 

CXX=g++
CXX_FLAGS=-std=c++11 -w

# ifndef CHAI_OCL_LIB
#     $(error CHAI_OCL_LIB not defined. This environment variable must be defined to point to the location of the OpenCL library)
# endif
# LIB=-L/usr/lib/ -L$(CHAI_OCL_LIB) -lm -lOpenCL -lopencv_core -lopencv_highgui -lopencv_imgproc 
LIB=-L/usr/lib/ -lpthread -lm -lOpenCL  $(shell aocl link-config)

# ifndef CHAI_OCL_INC
#     $(error CHAI_OCL_INC not defined. This environment variable must be defined to point to the location of the OpenCL header files)
# endif
# INC=-I$(CHAI_OCL_INC)
INC=-I support/common/inc/AOCLUtils/ -I support/common/inc/ -I support/ $(shell aocl compile-config)

DEP=kernel.cpp kernel.h main.cpp support/common.h support/ocl.h support/partitioner.h support/timer.h support/verify.h
SRC=main.cpp kernel.cpp support/common/src/AOCLUtils/opencl.cpp 
EXE=bs

all:
	$(CXX) $(CXX_FLAGS) $(SRC) $(LIB) $(INC) -o $(EXE)

clean:
	rm -f $(EXE)
