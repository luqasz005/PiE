#include "Filtr.h"


void print_Matrix (Matrix &mat){
	size_t sizeX = mat.size();
    size_t sizeY = mat[0].size();
    size_t sizeZ = mat[0][0].size();
	std::cout << "Wypisze"<<"\n";
	for(size_t i=0;i<sizeX;i++){
		for(size_t j=0;j<sizeY;j++){
			for(size_t k=0;k<sizeZ;k++){
				std::cout << mat[i][j][k] << " ";
			}
			std::cout <<"\n";
		}
		std::cout << "\n";
	}
}

Matrix add_Margin (Matrix &mat,size_t marg){
	
	size_t sizeX = mat.size();
    size_t sizeY = mat[0].size();
    size_t sizeZ = mat[0][0].size();
	Matrix output(sizeX + (2*marg),std::vector< std::vector<int> >(sizeY + (2*marg),std::vector<int>(sizeZ + (2*marg),0)));
	size_t outSizeX = output.size();
	size_t outSizeY = output[0].size();
	size_t outSizeZ = output[0][0].size();
	
	for(size_t i=0;i<outSizeX;i++){
		for(size_t j=0;j<outSizeY;j++){
			for(size_t k=0;k<outSizeZ;k++){
				//wnetrze macierzy
				if((i>=marg && i<(outSizeX-marg)) && (j>=marg && j<(outSizeY-marg)) && (k>=marg && k<(outSizeZ-marg)))
					output[i][j][k] = mat[i-marg][j-marg][k-marg];
				//wierzcholki i krawêdzie
				else if(i<marg && j<marg && k<marg)
					output[i][j][k] = mat[0][0][0];
				else if(i<marg && j<marg && k>=(outSizeZ-marg))
					output[i][j][k] = mat[0][0][sizeZ-1];
				else if(i<marg && j>=(outSizeY-marg) && k<marg)
					output[i][j][k] = mat[0][sizeY-1][0];
				else if(i<marg && j>=(outSizeY-marg) && k>=(outSizeZ-marg))
					output[i][j][k] = mat[0][sizeY-1][sizeZ-1];
				else if(i>=(outSizeX-marg) && j<marg && k<marg)
					output[i][j][k] = mat[sizeX-1][0][0];
				else if(i>=(outSizeX-marg) && j<marg && k>=(outSizeZ-marg))
					output[i][j][k] = mat[sizeX-1][0][sizeZ-1];
				else if(i>=(outSizeX-marg) && j>=(outSizeY-marg) && k<marg)
					output[i][j][k] = mat[ sizeX-1][ sizeY-1][0];
				else if(i>=(outSizeX-marg) && j>=(outSizeY-marg) && k>=(outSizeZ-marg))
					output[i][j][k] = mat[ sizeX-1][ sizeY-1][ sizeZ-1];
				else if((i>=marg && i<(outSizeX-marg)) && j<marg && k<marg)
					output[i][j][k] = mat[i-marg][0][0];
				else if((i>=marg && i<(outSizeX-marg)) && j<marg && k>=(outSizeZ-marg))
					output[i][j][k] = mat[i-marg][0][ sizeZ-1];
				else if((i>=marg && i<(outSizeX-marg)) && j>=(outSizeY-marg) && k<marg)
					output[i][j][k] = mat[i-marg][ sizeY-1][0];
				else if((i>=marg && i<(outSizeX-marg)) && j>=(outSizeY-marg) && k>=(outSizeZ-marg))
					output[i][j][k] = mat[i-marg][ sizeY-1][ sizeZ-1];
				
				//sciany	
				else if ((i<marg)&& (j>=marg && j<(outSizeY-marg)) && (k>=marg && k<(outSizeZ-marg)))
					output[i][j][k] = mat[0][j-marg][k-marg];
				else if ((i>=outSizeX-marg)&& (j>=marg && j<(outSizeY-marg)) && (k>=marg && k<(outSizeZ-marg)))
					output[i][j][k] = mat[ sizeX-1][j-marg][k-marg];
				else if ((j<marg) && (k>=marg && k<(outSizeZ-marg))){
					if(i<marg)
						output[i][j][k] = mat[0][0][k-marg]; 
					else if(i>=outSizeX-marg)
						output[i][j][k] = mat[ sizeX-1][0][k-marg];
					else
						output[i][j][k] = mat[i-marg][0][k-marg];
				}
				else if ((j>=(outSizeY-marg)) && (k>=marg && k<(outSizeZ-marg))){
					if(i<marg)
						output[i][j][k] = mat[0][ sizeY-1][k-marg]; 
					else if(i>=outSizeX-marg)
						output[i][j][k] = mat[ sizeX-1][ sizeY-1][k-marg];
					else
						output[i][j][k] = mat[i-marg][ sizeY-1][k-marg];
				}
				else if ((j>=marg && j<(outSizeY-marg)) && (k<marg)){
					if(i<marg)
						output[i][j][k] = mat[0][j-marg][0]; 
					else if(i>=outSizeX-marg)
						output[i][j][k] = mat[ sizeX-1][j-marg][0];
					else
						output[i][j][k] = mat[i-marg][j-marg][0];
				}
				else if ((j>=marg && j<(outSizeY-marg)) && (k>=(outSizeZ-marg))){
					if(i<marg)
						output[i][j][k] = mat[0][j-marg][ sizeZ-1]; 
					else if(i>=outSizeX-marg)
						output[i][j][k] = mat[ sizeX-1][j-marg][ sizeZ-1];
					else
						output[i][j][k] = mat[i-marg][j-marg][ sizeZ-1];
				}
			}
		}
	}
	return output;	
}

Matrix filtr_Medianowy (Matrix &matrix, size_t maska){
	
	size_t sizeX = matrix.size();
    size_t sizeY = matrix[0].size();
    size_t sizeZ = matrix[0][0].size();
	int marg = (static_cast<int>(maska)-1)/2;
	std::vector<int> mediana(static_cast<int>(pow(maska,3)),0);
	Matrix temp = add_Margin(matrix,marg);
	
	for(size_t x=marg;x<sizeX+marg;x++){
		for(size_t y=marg;y<sizeY+marg;y++){
			for(size_t z=marg;z<sizeZ+marg;z++){

				size_t elem=0;
				for(int i=-marg;i<=marg;i++){
					for(int j=-marg;j<=marg;j++){
						for(int k=-marg;k<=marg;k++){
							mediana[elem] = temp.at(x+i).at(y+j).at(z+k);
							elem++;
						}
					}
				}
				std::nth_element(mediana.begin(),mediana.begin() + mediana.size()/2,mediana.end());
				matrix[x-marg][y-marg][z-marg] =  mediana.at(mediana.size()/2);
			}
		}
	}
	return matrix;
}

Matrix filtr_Usredniajacy (Matrix &matrix, size_t maska){
	
	size_t sizeX = matrix.size();
    size_t sizeY = matrix[0].size();
    size_t sizeZ = matrix[0][0].size();
	int marg = (static_cast<int>(maska)-1)/2;
	Matrix temp = add_Margin(matrix,marg);
	int mask_size = static_cast<int>(pow(maska,3));
	for(size_t x=marg;x<sizeX+marg;x++){
		for(size_t y=marg;y<sizeY+marg;y++){
			for(size_t z=marg;z<sizeZ+marg;z++){
				int sum = 0;
				for(int i=-marg;i<=marg;i++){
					for(int j=-marg;j<=marg;j++){
						for(int k=-marg;k<=marg;k++){
							sum += temp.at(x+i).at(y+j).at(z+k);
						}
					}
				}
				matrix[x-marg][y-marg][z-marg] = static_cast<int>(sum /mask_size);
			}
		}
	}
	return matrix;
}

Matrix filtr_Wyostrzajacy (Matrix &matrix, size_t maska){
	
	size_t sizeX = matrix.size();
    size_t sizeY = matrix[0].size();
    size_t sizeZ = matrix[0][0].size();
	int marg = (static_cast<int>(maska)-1)/2;
	Matrix temp = add_Margin(matrix,marg);
	int mask_size = static_cast<int>(pow(maska,3));
	for(size_t x=marg;x<sizeX+marg;x++){
		for(size_t y=marg;y<sizeY+marg;y++){
			for(size_t z=marg;z<sizeZ+marg;z++){
				int sum = 0;
				for(int i=-marg;i<=marg;i++){
					for(int j=-marg;j<=marg;j++){
						for(int k=-marg;k<=marg;k++){
							if((i==0) && (j==0) && (k==0))
								sum += 27*temp.at(x+i).at(y+j).at(z+k);
							else
								sum += -temp.at(x+i).at(y+j).at(z+k);								
						}
					}
				}
				int value = static_cast<int>(sum / mask_size);
				if (value < 0){
					matrix[x-marg][y-marg][z-marg] = 0;
				}
				else  if (value > 255){
					matrix[x-marg][y-marg][z-marg] = 255;
				}
				else{
					matrix[x-marg][y-marg][z-marg] = value;
				}
			}
		}
	}
	return matrix;
}

Matrix sobel3D(Matrix &matrix){
	
	size_t sizeX = matrix.size();
    size_t sizeY = matrix[0].size();
    size_t sizeZ = matrix[0][0].size();
	int marg = 1;
	Matrix temp = add_Margin(matrix,marg);
	
	for(size_t x=marg;x<sizeX+marg;x++){
		for(size_t y=marg;y<sizeY+marg;y++){
			for(size_t z=marg;z<sizeZ+marg;z++){
				int Gx = (-  temp[x-1][y-1][z-1] - 3*temp[x-1][y-1][z] -  temp[x-1][y-1][z+1]
						  -3*temp[x-1][y][z-1]   - 6*temp[x-1][y][z]   -3*temp[x-1][y][z+1]
						  -  temp[x-1][y+1][z-1] - 3*temp[x-1][y+1][z] -  temp[x-1][y+1][z+1])+
				
						 (   temp[x+1][y-1][z-1] + 3*temp[x+1][y-1][z] +  temp[x+1][y-1][z+1]
 						  +3*temp[x+1][y][z-1]   + 6*temp[x+1][y][z]   +3*temp[x+1][y][z+1]
						  +  temp[x+1][y+1][z-1] + 3*temp[x+1][y+1][z] +  temp[x+1][y+1][z+1]);
	   			
				
	   			int Gy = (   temp[x-1][y-1][z-1] + 3*temp[x-1][y-1][z] +  temp[x-1][y-1][z+1]
			    		  -  temp[x-1][y+1][z-1] - 3*temp[x-1][y+1][z] -  temp[x-1][y+1][z+1])+
					
	 					 ( 3*temp[x][y-1][z-1]   + 6*temp[x][y-1][z]   +3*temp[x][y-1][z+1] 
						  -3*temp[x][y+1][z-1]   - 6*temp[x][y+1][z]   -3*temp[x][y+1][z+1])+
						 
						 (   temp[x+1][y-1][z-1] + 3*temp[x+1][y-1][z] +  temp[x+1][y-1][z+1]
			    		  -  temp[x+1][y+1][z-1] - 3*temp[x+1][y+1][z] -  temp[x+1][y+1][z+1]);
			    		 
    		 	int Gz = (-  temp[x-1][y-1][z-1] +   temp[x-1][y-1][z+1]
 		 				  -3*temp[x-1][y][z-1]   + 3*temp[x-1][y][z+1]
						  -  temp[x-1][y+1][z-1] +   temp[x-1][y+1][z+1])+
				
						 (-3*temp[x][y-1][z-1]   + 3*temp[x][y-1][z+1]
 		 				  -6*temp[x][y][z-1]     + 6*temp[x][y][z+1]
						  -3*temp[x][y+1][z-1]   + 3*temp[x][y+1][z+1])+
					  
					  	 (-  temp[x+1][y-1][z-1] +   temp[x+1][y-1][z+1]
 		 				  -3*temp[x+1][y][z-1]   + 3*temp[x+1][y][z+1]
						  -  temp[x+1][y+1][z-1] +   temp[x+1][y+1][z+1]);
						  
 			    int value = static_cast<int>(cbrt(pow(Gx,2)+pow(Gy,2)+pow(Gz,2)));
				if (value < 0){
					matrix[x-marg][y-marg][z-marg] = 0;
				}
				else  if (value > 255){
					matrix[x-marg][y-marg][z-marg] = 255;
				}
				else{
					matrix[x-marg][y-marg][z-marg] = value;
				}
			}
		}
	}
	return matrix;
}
