# distutils: language = c++
# distutils: sources = Filtr.cpp

#Cython interface file for wrapping
#
#python setup.py build_ext --inplace

cimport def_filtr_wrap

# creating a cython wrapper
def print_mat(matrix):
    def_filtr_wrap.print_Matrix(matrix)
def medianowy(matrix,f_size):
    return def_filtr_wrap.filtr_Medianowy(matrix,f_size)
def usredniajacy(matrix,f_size):
    return def_filtr_wrap.filtr_Usredniajacy(matrix,f_size)
def wyostrzajacy(matrix,f_size):
    return def_filtr_wrap.filtr_Wyostrzajacy(matrix,f_size)
def sobel3d(matrix):
    return def_filtr_wrap.sobel3D(matrix)
	