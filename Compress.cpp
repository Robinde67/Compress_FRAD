#include "Compress.h"




Compress::Compress(const char* url)
{
	//
	//unsigned char bild[24];
	//

	//
	//fread(bild, sizeof(unsigned char), 24, f);

	//width = *(int*)&bild[18];
	//height = *(int*)&bild[22];
	//int row_padded = (width * 3 + 3) & (~3);
	
	FILE* file;
	struct BMPHeader header;

	file = fopen(url, "rb");
	char buffer[sizeof(file)], *pixels;
	fread(buffer, 1, sizeof(file), file);
	fclose(file);

	memcpy(&header, buffer, sizeof(struct BMPHeader));
	pixels = buffer + header.offset;

	height = header.height;

	for (int i = 0; i < height; i++)
	{
		fread(pixels, 1,sizeof(unsigned char), file);
		for (int j = 0; j < width * 3; j += 3)
		{
			// Convert (B, G, R) to (R, G, B)
			tmp = pixels[j];
			pixels[j] = pixels[j + 2];
			pixels[j + 2] = tmp;

			std::cout << "R: " << (int)pixels[j] << " G: " << (int)pixels[j + 1] << " B: " << (int)pixels[j + 2] << std::endl;
		}
	}


}



Compress::~Compress()
{

}


