# c++ interface to cython
from libcpp.vector cimport vector

ctypedef vector[vector[vector[int]]] Matrix

cdef extern from "Filtr.h":
    void print_Matrix (const Matrix &)
    Matrix filtr_Medianowy (Matrix &,size_t)
    Matrix filtr_Usredniajacy (Matrix &,size_t)
    Matrix filtr_Wyostrzajacy(Matrix &,size_t)
    Matrix sobel3D(Matrix &)