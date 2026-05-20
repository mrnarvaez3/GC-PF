#include "Texture.h"

#include "Image.h"
#include <fstream>
#include <cstring>

Texture::~Texture()
{
	if (mId != 0)
		glDeleteTextures(1, &mId);
}

void
Texture::init()
{
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);

	// Filters and clamping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // GL_CLAMP_TO_EDGE
}

void
Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, mId);
}

void
Texture::load(const std::string& name, GLubyte alpha)
{
	if (mId == 0)
		init();

	Image image;
	image.load(name);

	if (alpha != 255)
		image.setAlpha(alpha);

	mWidth = image.width();
	mHeight = image.height();

	GLint level = 0;  // Base image level
	GLint border = 0; // No border

	glBindTexture(GL_TEXTURE_2D, mId);
	glTexImage2D(GL_TEXTURE_2D,
	             level,
	             GL_RGBA,
	             mWidth,
	             mHeight,
	             border,
	             GL_RGBA,
	             GL_UNSIGNED_BYTE,
	             image.data());

	glBindTexture(GL_TEXTURE_2D, 0);
}

void
Texture::setWrap(GLuint wp) // GL_REPEAT, GL_CLAMP_TO_EDGE, ...
{
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wp);
	glBindTexture(GL_TEXTURE_2D, 0);
}

// Apartado 34
void 
Texture::loadColorBuffer(GLsizei width, GLsizei height, GLuint buffer)
{
	// inicializamos la textura
	if (mId == 0)
		init();

	// cargamos su tamaño
	mWidth = width;
	mHeight = height;

	glReadBuffer(buffer);

	// cargamos la textura
	glBindTexture(GL_TEXTURE_2D, mId);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, width, height, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void
Texture::GetTextureImage()
{
	// inicializamos pixels a su tamaño
	pixels = std::vector<unsigned char>(mWidth * mHeight * 4);
	// cargamos la info de la textura en pixels
	glBindTexture(GL_TEXTURE_2D, mId);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool 
Texture::createBMPFile(const char* filename, int width, int height)
{
	// si pixels esta inicializado creamos el archivo
	if (pixels.empty()) {
		std::string finalFilename = PHOTO_PATH + filename;

		// cargamos la textura en pixels
		this->GetTextureImage();

		int rowSize = ((width * 3 + 3) / 4) * 4;
		int dataSize = rowSize * height;
		int fileSize = 54 + dataSize;

		// cabecera del tipo de archivo
		unsigned char fileHeader[14] = {
			'B','M',
			0,0,0,0,
			0,0,0,0,
			54,0,0,0
		};
		// información de la cabecera (tamaño de archivo, offset, tipo inf)
		unsigned char infoHeader[40] = {
			40,0,0,0,
			0,0,0,0,
			0,0,0,0,
			1,0,
			24,0
		};

		// cargamos la cabecera y su info
		memcpy(&fileHeader[2], &fileSize, 4);
		memcpy(&infoHeader[4], &width, 4);
		memcpy(&infoHeader[8], &height, 4);

		std::ofstream file(finalFilename, std::ios::out | std::ios::binary);

		file.write((char*)fileHeader, 14);
		file.write((char*)infoHeader, 40);

		std::vector<unsigned char> row(rowSize);

		std::vector<unsigned char> flipped(width * height * 4);

		for (int y = 0; y < height; y++)
		{
			memcpy(
				&flipped[y * width * 4],
				&pixels[(height - 1 - y) * width * 4],
				width * 4
			);
		}

		pixels = flipped;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int src = ((height - 1 - y) * width + x) * 4;

				row[x * 3 + 0] = pixels[src + 2]; // B
				row[x * 3 + 1] = pixels[src + 1]; // G
				row[x * 3 + 2] = pixels[src + 0]; // R
			}

			file.write((char*)row.data(), rowSize);
		}

		file.close();

		return true;
	}
	
	return false;
}
