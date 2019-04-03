#ifndef IMAGE_H
#define IMAGE_H
#include <GL/glew.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>


namespace Graphics
{
	class Image
	{
	public:
		Image();

		Image(const char* file_name, bool flip);

		Image(Image& image);

		int GetWidth();

		int GetHeight();

		int GetnrChannels();

		int GetFormat();

		unsigned char* GetData();

		void Load(const char* file_name, bool flip);

		void Dispose();

		~Image();

	private:
		int width, height, nrChannels, format;
		unsigned char* data;
	};
}


#endif
