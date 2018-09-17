NVCC=nvcc
CPP= g++

###################################
# These are the default install   #
# locations on most linux distros #
###################################

OPENCV_LIBPATH=/usr/lib
OPENCV_INCLUDEPATH=/usr/include

###################################################
# On Macs the default install locations are below #
###################################################

#OPENCV_LIBPATH=/usr/local/lib
#OPENCV_INCLUDEPATH=/usr/local/include

OPENCV_LIBS=`pkg-config --libs opencv`

CUDA_INCLUDEPATH=/usr/local/cuda-9.0/include
# CUDA_INCLUDEPATH=/usr/local/cuda/lib64/include
# CUDA_INCLUDEPATH=/usr/local/cuda-5.0/include
# CUDA_INCLUDEPATH=/Developer/NVIDIA/CUDA-5.0/include

######################################################
# On Macs the default install locations are below    #
# ####################################################

#CUDA_INCLUDEPATH=/usr/local/cuda/include
#CUDA_LIBPATH=/usr/local/cuda/lib
CUDA_LIBPATH=/usr/local/cuda-9.0/lib64

NVCC_OPTS=-O3 

GCC_OPTS=-O3 -m64

student: main.o student_func.o HW4.o loadSaveImage.o compare.o reference_calc.o Makefile
	$(NVCC) -o HW4 main.o student_func.o HW4.o loadSaveImage.o compare.o reference_calc.o -L $(OPENCV_LIBPATH) $(OPENCV_LIBS) $(NVCC_OPTS)

filegen: file_generator.cpp
	g++ file_generator.cpp -o file_gen $(GCC_OPTS) 
resize : resizeApril.cpp
	g++ resizeApril.cpp -o resize  $(GCC_OPTS) -I $(OPENCV_LIBS)
testVals :testVals.cu
	$(NVCC) testVals.cu -o testVals $(NVCC_OPTS) $(OPENCV_LIBS)
thresh: thresh.cu
	$(NVCC) thresh.cu -o thresh $(NVCC_OPTS) $(OPENCV_LIBS)
main: main.cpp
	g++ -o main $(GCC_OPTS) -I $(CUDA_INCLUDEPATH) $(OPENCV_LIBS)
main.o: main.cpp 
	g++ -c main.cpp $(GCC_OPTS) -I $(CUDA_INCLUDEPATH)

HW4.o: HW4.cu loadSaveImage.h utils.h
	$(NVCC) -c HW4.cu -I $(OPENCV_INCLUDEPATH) $(NVCC_OPTS)

loadSaveImage.o: loadSaveImage.cpp loadSaveImage.h
	g++ -c loadSaveImage.cpp -I $(OPENCV_INCLUDEPATH) $(GCC_OPTS) -I $(CUDA_INCLUDEPATH)

compare.o: compare.cpp compare.h
	g++ -c compare.cpp -I $(OPENCV_INCLUDEPATH) $(GCC_OPTS) -I $(CUDA_INCLUDEPATH)

reference_calc.o: reference_calc.cpp reference_calc.h
	g++ -c reference_calc.cpp -I $(OPENCV_INCLUDEPATH) $(GCC_OPTS) -I $(CUDA_INCLUDEPATH)

student_func.o: student_func.cu reference_calc.cpp utils.h
	$(NVCC) -c student_func.cu $(NVCC_OPTS)
deviceQuery: deviceQuery_simplified.cpp
	g++ -c deviceQuery_simplified.cpp -I $(OPENCV_INCLUDEPATH) $(GCC_OPTS) -I $(CUDA_INCLUDEPATH)

clean:
	rm -f *.o *.png hw
