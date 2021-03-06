#pragma once

#include "../text/Font.h"

#include <vector>

class GAME_LOGIC_API_CPP FontHandler {

	friend class DisplayManager;
	
	private:

		struct FontData {

			std::string name;
			float size;
			Font* font;

		};

	private:

		static std::vector<FontData> fonts;

	public:

		static void addFont(std::string filename, float size, bool preload = false);
		static void preloadFonts(std::string file, std::vector<float> sizes);
		static void preloadFont(std::string file, float size);
		static void cleanUp();

		static const Font* getFont(std::string name, float size, bool preload = false);

};