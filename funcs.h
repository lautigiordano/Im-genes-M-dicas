#include "classes.h"

void semilinear(Image* Input, Image* Output);
void Equalizer(Image* Input, Image* Output);
void Substract(Image* I1, Image* I2, std::string fname, int* Params);
int** LowPassSpatial(unsigned int size);
int** Sharpening(unsigned int size);
void Rescale(Image* Input, int* Params, std::string Method);