#include "funcs.h"

void semilinear(Image* Input, Image* Output)
{
	int first=0,last=0;
	int T[Output->bit_depth];
	
	for(int i=0; i<Input->bit_depth+1; i++){
		if(Input->histogram[i]!=0){
			if(first==0)
				first = i;
		if(i!=0 && Input->histogram[i-1]!=0)
			last = i;
		}
	}

	float slope = (float)Output->bit_depth/(last-first);

	for(int i=0; i<Input->bit_depth+1; i++){
		if(i<first)
			T[i]=0;

		if(i>=first && i<=last)
			T[i]=slope*(i-first);
		
		if(i>=last)
			T[i]=Output->bit_depth;
	}

	Output->Apply(Input, T);
	Output->Build();
}

void Equalizer(Image* Input, Image* Output)
{
	int size=Output->bit_depth+1, Q[size], T[size];
	double Norma = (double)Input->bit_depth/(double)(Input->width*Input->height);

	Q[0]=0;
	T[0]=0;

	for(int i=1; i<size; i++){
		Q[i] = Q[i-1] + Input->histogram[i];
		T[i] = Q[i]*Norma;
	}

	Output->Apply(Input, T);
	Output->Build();
}

void Substract(Image* I1, Image* I2, std::string fname, int* Params)
{
	Image* Output = new Image(fname,Params);

	for(int i=0; i<I1->height; i++)
		for(int j=0; j<I1->width; j++)
			Output->image[i][j] = abs(I1->image[i][j] - I2->image[i][j]);

	Output->Build();
}

int** LowPassSpatial(unsigned int size)
{
	int** mask = new int*[size];

	for(int i=0; i<size; i++)
		mask[i] = new int[size];

	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++)
			mask[i][j]=1;
	return mask;
}

int** Sharpening(unsigned int size)
{
	int** mask = new int*[size],i,j;
	for(i=0; i<size; i++)
		mask[i] = new int[size];

	int p = (size-1)/2;

	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			mask[i][j]=0; 
		}
	}

	mask[0][0]=mask[2][0]=1;	//Mascara dx
	mask[1][1]=2;
	mask[0][2]=mask[2][2]=-1;
	mask[1][2]=-2;
	return mask;
}

void Rescale(Image* Input, int* Params, std::string Method)
{
	int i,j,x0,y0;
	float xi, yj, ax = (1.0*Input->height-1)/(Params[0]-1), ay = (1.0*Input->width-1)/(Params[1]-1);
	std::string size = std::to_string(Params[0])+"x"+std::to_string(Params[1]);
		
	Image* Output = new Image("3a"+size+Method,Params);
	
	if(Method=="NearestNeighbour")
		for(i=0; i<Output->height; i++){
			xi = i*ax;
			x0 = (int)xi;

			for(j=0; j<Output->width; j++){
				yj = j*ay;
				y0 = (int)yj;
				Output->image[i][j] = Input->image[x0][y0];
			}
		}

	if(Method=="LinearInterpolation"){
		int a00, a10, a01, a11;
		double xrel, yrel;

		for(i=0; i<Output->height; i++){
			xi = i*ax;
			x0 = (int)xi;
			xrel = xi-x0;

			for(j=0; j<Output->width; j++){
				yj = j*ay;
				y0 = (int)yj;
				yrel = yj-y0;
				if(x0<Input->height-1 && y0<Input->width-1){		//No incluyo los bordes
					a00=Input->image[x0][y0];
					a01=Input->image[x0+1][y0];
					a10=Input->image[x0][y0+1];
					a11=Input->image[x0+1][y0+1];
					Output->image[i][j] = ((a00 + (a10-a00)*xrel + (a01-a00)*yrel + (a00+a11-a10-a01)*xrel*yrel));
				}
				else	Output->image[i][j] = Input->image[x0][y0];	//Para los bordes
				std::cout << Output->image[i][j] << " " << a00 << " " << a10 << " " << a01 << " " << a11 << " " << xrel << " " << yrel << std::endl;
				
			}

		}	
	}

	Output->Build();
	Output->Destroy();
}