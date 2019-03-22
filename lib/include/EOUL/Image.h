#pragma once

#include <EOUL\File.h>
#include <string>

namespace EOUL {

	namespace IO {

		class Image : public FileBase {

			private:

				unsigned char* pixels = nullptr;
				unsigned int width = 0, height = 0, numComponents = 0;

			public:

				Image() = default;
				Image(std::string path);
				~Image();

			public:

				/* loads/reloads image and deletes current pixel data */
				void load();

				/* returns the red channel with a scale from 0 - 255, of the specified pixel */
				unsigned char getRed(unsigned int x, unsigned int y) const;
				/* returns the green channel with a scale from 0 - 255, of the specified pixel */
				unsigned char getGreen(unsigned int x, unsigned int y) const;
				/* returns the blue channel with a scale from 0 - 255, of the specified pixel */
				unsigned char getBlue(unsigned int x, unsigned int y) const;
				/* returns the alpha channel with a scale from 0 - 255, of the specified pixel */
				unsigned char getAlpha(unsigned int x, unsigned int y) const;
				/* returns an unsigned integer representation of the rgba values, of the specified pixel */
				unsigned int getRGBA(unsigned int x, unsigned int y) const;

				/* returns width of the image */
				unsigned int getWidth() const;
				/* returns height of the image */
				unsigned int getHeight() const;

				/* returns a pointer to the pixel array */
				unsigned char* getPixels() const;

		};

	}

}