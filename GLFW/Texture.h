#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include "Image.h"


namespace Graphics
{
	class Texture
	{
	public:
		Texture();

		Texture(Image* image, GLint min_filter, GLint mag_filter, GLint mipmap_level, GLint wrap_s, GLint wrap_t);

		Texture(const char* file_name, bool flip, GLint min_filter, GLint mag_filter, GLint mipmap_level, GLint wrap_s, GLint wrap_t);

		Texture(Texture& texture);

		void GenerateMipmap(Image* image, GLint mipmap_level);

		void Use();

		void Dispose();

		~Texture();

	private:
		GLenum target;
		GLuint ID;
	};
}


#endif
