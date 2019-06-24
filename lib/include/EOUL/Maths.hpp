#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <array>
#include <cmath>
#include <random>
#include <string>

#include <EOUL/Constants.hpp>

namespace EOUL::Math {

	/* return the given value as a binary string */
	template <typename StringType = std::string>
	inline StringType toBinaryString(unsigned long long value, bool keepTrailingZeros = false, unsigned long long groupSize = -1) {

		StringType result = "";

		for (unsigned long long i = sizeof(i) * 8 - 1; i >= 0; i--) {

			unsigned long long mask = ((unsigned long long) 1) << i;

			result.append((value & mask) != 0 ? "1" : "0");

			if (i % groupSize == 0 && groupSize != -1) {

				result.append(" ");

			}

			if (i == 0) {

				break;

			}

		}

		result.replace(result.length() - 1, result.length(), "");

		if (!keepTrailingZeros) {

			size_t i = 0;
			while (i < result.size()) {

				if (result.at(i) == '1') {

					result.erase(0, i);

					break;

				}

				i++;

			}

		}

		return result;

	}

	/* generates a random number between the given min and the given max */
	template <typename RandomEngine = std::mt19937_64>
	inline double random(double min = 0.0, double max = 1.0) {

		static std::random_device device;
		static RandomEngine engine = RandomEngine(device());
		static std::uniform_real_distribution<double> distribution = std::uniform_real_distribution<double>(0.0, 1.0);

		return distribution(engine) * (max - min) + min;

	}

	/* returns the 2d distance of 2 points */
	inline double dist(double x1, double y1, double x2, double y2) {

		return hypot(x2 - x1, y2 - y1);

	}
	/* returns the 3d distance of 2 points */
	inline double dist(double x1, double y1, double z1, double x2, double y2, double z2) {

		double diffX = fabs(x1 - x2);
		double diffZ = fabs(z1 - z2);

		double gD = hypot(diffX, diffZ);

		return hypot(gD, fabs(y1 - y2));

	}

	/* retuns a constrained value of the given number */
	inline double constrain(double val, double min, double max) {

		return fmax(min, fmin(val, max));

	}

	/* lerps between a start and a stop, based on the given amt, also known as linear interpolation */
	inline double lerp(double start, double stop, double amt) {

		return amt * (stop - start) + start;

	}

	/* maps two ranges to eachother */
	inline double map(double value, double min1, double max1, double min2, double max2, bool constrainValue = false) {

		double mapped = ((value - min1) / (max1 - min1)) * (max2 - min2) + min2;

		if (constrainValue) {

			return constrain(mapped, min2, max2);

		}

		return mapped;

	}
	/* maps a range to [0.0 - 1.0] */
	inline double norm(double value, double min, double max) {

		return map(value, min, max, 0.0, 1.0);

	}

	/* transforms degrees into radians */
	inline double radians(double degrees) {

		return degrees * PI / 180.0;

	}
	/* transforms radians into degrees */
	inline double degrees(double radians) {

		return radians * 180.0 / PI;

	}

	/* squares the given number */
	inline double sq(double num) {

		return num * num;

	}

	template <typename T>
	inline T& random(std::vector<T>& arr) {

		return arr[(unsigned int) random(0, arr.size())];

	}

	template <typename T, unsigned long long size>
	inline T& random(std::array<T, size>& arr) {

		return arr[(unsigned int)random(0, size)];

	}

}