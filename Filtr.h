#ifndef FILTR_H_
#define FILTR_H_

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>

typedef std::vector< std::vector< std::vector<int> > > Matrix;

	void print_Matrix(Matrix &);
	Matrix filtr_Medianowy(Matrix &,size_t);
	Matrix filtr_Usredniajacy(Matrix &,size_t);
	Matrix filtr_Wyostrzajacy(Matrix &,size_t);
	Matrix sobel3D(Matrix &);
	Matrix add_Margin(Matrix &,size_t);
	
#endif /* FILTR_H_ */
