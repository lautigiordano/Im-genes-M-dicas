#include <fstream>
#include <iostream>
#include <cstdio>
#include <cmath>

class Image
{
public:
	std::string fname;
	unsigned int **image, *histogram;
	unsigned int width, height, bit_depth; 

	void Read();
	void SetParams(int*);
	void Allocate();
	void Destroy();
	void MakeHistogram();
	void Apply(Image*, int*);
	void Build();

	Image(std::string i_fname) 		//Constructor para leer imagenes
	{
		fname = i_fname;
		Read();
	}
	
	Image(std::string o_fname, int* o_param)		//Constructor para crear imagenes
	{
		fname = o_fname;
		SetParams(o_param);
		Allocate();
	}
};

class Filter
{
public:
	int **mask;
	unsigned int size, norm;

	Filter(int N, int** W)
	{
		size = N;
		mask = W;
	//	ComputeNorm();
	}

	void ComputeNorm();
	void ApplyFilter(Image*, Image*);
};

void Image::Read()
{
	std::ifstream infile;
	infile.open(fname+".pgm");

	int i, i_param[3];	//i_param[0]: width, [1]: height, [2]: bit_depth
	int c;
	char* c0 = new char;
	std::string string;
 
	std::getline(infile,string);
 	std::getline(infile,string);

 	infile >> i_param[0] >> i_param[1] >> i_param[2];
 	std::cout << "Parametros de entrada: Ancho: " << i_param[0] << " Alto: "  << i_param[1] << " BitDepth: " << i_param[2] << std::endl;

 	SetParams(i_param);
 	Allocate();

 	for(i=0; i<width*height; i++)
 		infile >> image[(int)(i/width)][i%width];
 
 	infile.close();
}

void Image::SetParams(int* io_param)
{
	width = io_param[0];	height = io_param[1];  bit_depth = io_param[2];
}

void Image::Allocate()
{
	image = new unsigned int*[height];		//Alloco matriz

	for(int i=0; i<height; i++)
		image[i] = new unsigned int[width];

	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			image[i][j]=0;

	histogram = new unsigned int[bit_depth+1];	//Alloco histograma
}

void Image::Destroy()
{
	for(int i=0; i<height; i++)
		delete[] image[i];
	delete[] image;
	delete[] histogram;
}

void Image::MakeHistogram()
{
	std::ofstream outfile;
	outfile.open("Outputs/"+fname+"_histo.dat");

	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			histogram[image[i][j]]++;

	for(int i=0; i<bit_depth+1; i++)
		outfile << histogram[i] << std::endl;
}

void Image::Apply(Image* Input, int *T)
{
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			image[i][j] = T[Input->image[i][j]];
}

void Image::Build()
{
	std::ofstream outfile;
	outfile.open("Outputs/"+fname+".pgm");

	outfile << "P2" << std::endl;
	outfile << "#Ejercicio " << fname << std::endl;
	outfile << width << " " << height << std::endl;
	outfile << bit_depth << std::endl;
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			outfile << image[i][j] << std::endl;
	

//	MakeHistogram();
	outfile.close();
}

////////////////////////////////////////////////////////////////////////////
void Filter::ComputeNorm()
{
	norm=0;
	for(int i=0; i<size; i++)
		for(int j=0; j<size; j++){
			norm+=mask[i][j];
		}
}

void Filter::ApplyFilter(Image* Input, Image* Output)
{
	int i,j,a,b, p=(size-1)/2, temp=0;

	for(i=p; i+p<Input->height; i++)
		for(j=p; j+p<Input->width; j++)
		{
			temp=0;
			for(a=0; a<size; a++)
				for(b=0; b<size; b++)
					temp+=(mask[a][b]*Input->image[i-p+a][j-p+b]);

			Output->image[i][j]=abs(temp);
			Output->image[i][j]/=norm;				
		}
}