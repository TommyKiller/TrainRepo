#include "Texture.h"

Graphics::Texture::Texture() : ID(0), target(GL_TEXTURE_2D){}

Graphics::Texture::Texture(Image* image, GLint min_filter, GLint mag_filter, GLint mipmap_level, GLint wrap_s, GLint wrap_t)
	: target(GL_TEXTURE_2D)
{
	glGenTextures(1, &ID);
	glBindTexture(target, ID);

	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap_t);

	if (mipmap_level >= 0)
	{
		GenerateMipmap(image, mipmap_level);
	}
	else
	{
		GenerateMipmap(image, 0);
		glGenerateMipmap(target);
	}
}

Graphics::Texture::Texture(const char* file_name, bool flip, GLint min_filter, GLint mag_filter, GLint mipmap_level, GLint wrap_s, GLint wrap_t)
	: target(GL_TEXTURE_2D)
{
	glGenTextures(1, &ID);
	glBindTexture(target, ID);

	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap_t);

	Graphics::Image image;
	image.Load(file_name, flip);

	if (mipmap_level > 0)
	{
		GenerateMipmap(&image, mipmap_level);
	}
	else
	{
		GenerateMipmap(&image, 0);
		glGenerateMipmap(target);
	}
}

Graphics::Texture::Texture(Texture& texture) : ID(texture.ID), target(texture.target){}

void Graphics::Texture::GenerateMipmap(Image* image, GLint mipmap_level)
{
	glTexImage2D(target, mipmap_level, image->GetFormat(), image->GetWidth(), image->GetHeight(), 0, image->GetFormat(), GL_UNSIGNED_BYTE, image->GetData());
}

void Graphics::Texture::Use()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(target, ID);
}

void Graphics::Texture::Dispose()
{
	if (ID != 0)
	{
		glDeleteTextures(1, &ID);
		ID = 0;
	}
}

Graphics::Texture::~Texture()
{
	Dispose();
}
