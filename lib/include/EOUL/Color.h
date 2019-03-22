#pragma once

#include <string>
#include <iostream>

namespace EOUL {

	namespace Math {

		class Color {

			friend std::ostream& operator<<(std::ostream& os, const Color& color);

			private:

				union Storage {

					unsigned int decimal = 0;

					struct {

						unsigned char b;
						unsigned char g;
						unsigned char r;
						unsigned char a;

					};

				} storage;

				bool safeMode;

				unsigned char& b = this->storage.b;
				unsigned char& g = this->storage.g;
				unsigned char& r = this->storage.r;
				unsigned char& a = this->storage.a;
				unsigned int& decimal = this->storage.decimal;

			public:

				// safeMode is so that the r, g, b, a values won't overflow
				Color(bool safeMode = false);
				// safeMode is so that the r, g, b, a values won't overflow
				Color(unsigned int decimal, bool safeMode = false);
				// safeMode is so that the r, g, b, a values won't overflow
				Color(std::string hex, bool safeMode = false);
				// safeMode is so that the r, g, b, a values won't overflow
				Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255, bool safeMode = false);

			public:

				/* returns an integer representation of the rgba values */
				unsigned int getRGBA() const;
				
				/* returns the red channel with a scale from 0 - 255 */
				unsigned char getRed() const;
				/* returns the green channel with a scale from 0 - 255 */
				unsigned char getGreen() const;
				/* returns the blue channel with a scale from 0 - 255 */
				unsigned char getBlue() const;
				/* returns the alpha channel with a scale from 0 - 255 */
				unsigned char getAlpha() const;

				/* returns the hex representation of the color */
				std::string getHex() const;

				/* sets r, g, b and a values with an unsigned int */
				void setRGBA(unsigned int rgba);
				/* sets the r value */
				void setRed(unsigned char red);
				/* sets the g value */
				void setGreen(unsigned char green);
				/* sets the b value */
				void setBlue(unsigned char blue);
				/* sets the a value */
				void setAlpha(unsigned char alpha);

			public:

				bool operator==(const Color& other) const;
				bool operator==(Color& other) const;

				bool operator!=(const Color& other) const;
				bool operator!=(Color& other) const;

				Color& operator=(const Color& other);

				Color& operator+=(const Color& other);
				Color& operator+=(Color& other);

				Color& operator-=(const Color& other);
				Color& operator-=(Color& other);

				unsigned char operator[](unsigned int index) const;

			public:

				/* returns a hex representation of the given color */
				static std::string decimalToHex(unsigned int color);
				/* returns a decimal representation of the given hex string */
				static unsigned int hexToDecimal(std::string hex);

		};

	}

}

EOUL::Math::Color operator+(EOUL::Math::Color left, const EOUL::Math::Color& other);
EOUL::Math::Color operator+(EOUL::Math::Color left, EOUL::Math::Color& other);

EOUL::Math::Color operator-(EOUL::Math::Color left, const EOUL::Math::Color& other);
EOUL::Math::Color operator-(EOUL::Math::Color left, EOUL::Math::Color& other);