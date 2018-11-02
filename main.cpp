#include "funcs.cpp"

int main(int argc, char *argv[])
{

	int defParams[3],i;

	/* Ej 1		*/
	Image* Input = new Image("ImagenA");
	Input->MakeHistogram();
	defParams[0]=Input->width; defParams[1]=Input->height; defParams[2]=Input->bit_depth;
	
	int size = Input->bit_depth+1;
	
	Image* Output = new Image("1",defParams);
	semilinear(Input, Output);
	Output->Destroy();

	Output = new Image("2b",defParams);
	Equalizer(Input, Output);
	Output->Destroy();

	int Tc1[size],Tc2[size],Tc3[size];
	bool flag=false;

	/*	Ej 2	*/		
	for(i=0; i<size; i++){
		if(i<128)
			Tc1[i]=Input->bit_depth;
		if(i>=128)
			Tc1[i]=0;
		Tc2[i]=45*log(1+i);
		if(i>0 && Tc3[i-1] > Input->bit_depth){
			flag=true;
			Tc3[i-1] = Input->bit_depth;
			for(int j=i; j<size; j++)
				Tc3[i] = Input->bit_depth;
		}
		if(flag==false)
			Tc3[i] = exp(i);
	}

	Image* Output2c1 = new Image("2c1",defParams);
	Image* Output2c2 = new Image("2c2",defParams);
	Image* Output2c3 = new Image("2c3",defParams);


	Output2c1->Apply(Input, Tc1);
	Output2c1->Build();
	Substract(Input, Output2c1, "2d1Sub", defParams);
	Output2c1->Destroy();

	Output2c2->Apply(Input, Tc2);
	Output2c2->Build();
	Substract(Input, Output2c2, "2d2Sub", defParams);
	Output2c2->Destroy();

	Output2c3->Apply(Input, Tc3);
	Output2c3->Build();
	Substract(Input, Output2c3, "2d3Sub", defParams);
	Output2c3->Destroy();

	/*	Ej 3	

	int *Params = new int[3];
	unsigned int idx[] = {5, 8, 10};
	Params[2] = Input->bit_depth;
	Image* InputC = new Image("ImagenC");
	int *Params2 = new int[3];
	Params2[2] = Params[2];
	Params2[0] = Params2[1] = 2000;

//	Rescale(InputC, Params2, "NearestNeighbour");
	Rescale(InputC, Params2, "LinearInterpolation");
/*
	for(i=0; i<3; i++){
		Params[0] = Params[1] = pow(2, idx[i]);
		Rescale(InputC, Params, "NearestNeighbour");
		Rescale(InputC, Params, "LinearInterpolation");
	}

	/*	Ej 4	*/
	int** mask3x3 = LowPassSpatial(3);
	int** mask5x5 = LowPassSpatial(5);
	int** mask7x7 = LowPassSpatial(7);
	
	Filter* Smooth = new Filter(3,mask3x3);
	Output = new Image("4a1", defParams);
	Smooth->ApplyFilter(Input, Output);
	Output->Build();
	Output->Destroy();

	Smooth = new Filter(5,mask5x5);
	Output = new Image("4a2", defParams);
	Smooth->ApplyFilter(Input, Output);
	Output->Build();
	Output->Destroy();

	Smooth = new Filter(7,mask7x7);
	Output = new Image("4a3", defParams);
	Smooth->ApplyFilter(Input, Output);
	Output->Build();
	Output->Destroy();

	int **maskSharp = Sharpening(3);

	Filter* Sharp = new Filter(3,(int **)maskSharp);
	std::cout << maskSharp[0][1] << std::endl;

	Sharp->norm = 1;
	Image* Output2 = new Image("4bdx", defParams);
	Sharp->ApplyFilter(Input, Output2);
	Output2->Build();
	Output2->Destroy();
	


	/* Ej 6	
	std::string idx[3] = {"2","3","4"};

	for(int i=0; i<3; i++)
	{
		Input = new Image("AAA000"+idx[i]);
		std::cout << Input->fname << std::endl;
		Input->MakeHistogram();		
		Input->Destroy();
	}
*/

}