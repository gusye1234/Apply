UNAME_S:=$(shell uname -s)
# echo ${UNAME_S}

ifeq ($(UNAME_S),Darwin)
    CC=g++-10
    OS_flag=-undefined dynamic_lookup
else
    CC=g++
    OS_flag=
endif

OMP_TARGET=operator_omp`python3-config --extension-suffix`

.PHONY: build test clean

build: ./apply/${OMP_TARGET}
	@echo "Rebuild"
	# python setup.py install --inplace

# build_omp : apply/${OMP_TARGET}
# 	@echo "Rebuild Openmp support"

./apply/${OMP_TARGET} : ./apply/src/operator_omp.cpp
	@echo I am at ${OMP_TARGET}
	python setup.py clean --all
	python setup.py build_ext --inplace
	# ${CC} -fopenmp -O3 -Wall -shared ${OS_flag} `python3 -m pybind11 --includes` apply/src/operator_omp.cpp -o ${OMP_TARGET}

test: build
	python -m apply

# install: build

clean:
	python setup.py clean --all
	-rm apply/*.so
