#include "../../header/level/LevelLoader.h"
#include "../../header/handler/ModelHandler.h"
#include "../../header/game/TileProperties.h"

Level* LevelLoader::loadLevel(String json, bool content) {

	Level* level = new Level();
	rapidjson::Document json_document;

	if (!content) {

		std::ifstream in("res/levels/" + json + ".json");
		String lines, line;

		while (getline(in, line)) {

			lines += line + '\n';

		}

		lines = lines.substr(0, lines.length() - 1);

		json_document.Parse(lines.c_str());

	} else {

		json_document.Parse(json.c_str());

	}

	auto size = json_document["desired-size"].GetObject();
	auto tiles = json_document["tiles"].GetArray();

	level->desiredSize.x = float(size["x"].GetInt());
	level->desiredSize.y = float(size["y"].GetInt());

	for (auto& tile : tiles) {

		String other_type = tile.HasMember("other-type") ? tile["other-type"].GetString() : "none";
		bool hollow = tile.HasMember("hollow") ? tile["hollow"].GetBool() : false;
		Vec2 index = (!tile.HasMember("positions")) ? Vec2(tile["x"].GetInt(), tile["y"].GetInt()) : Vec2(0, 0);
		Vec2 offset = { tile["tile-index"].GetObject()["x"].GetInt(), tile["tile-index"].GetObject()["y"].GetInt() };
		bool collidable = tile.HasMember("collidable") ? tile["collidable"].GetBool() : false;
		bool explodeable = tile.HasMember("explodeable") ? tile["explodeable"].GetBool() : false;

		if (tile.HasMember("positions")) {

			auto tls = tile["positions"].GetArray();

			for (auto& pos : tls) {

				Tile* tileObj = new Tile(getPosition(Vec2(pos["x"].GetInt(), pos["y"].GetInt()), level->desiredSize), offset, *ModelHandler::getModelById(tile["model"].GetInt()));

				tileObj->collidable = collidable;
				tileObj->explodeable = explodeable;
				tileObj->level = level;
				tileObj->index = Vec2(pos["x"].GetInt(), pos["y"].GetInt());

				if (tile.HasMember("rotation")) {

					auto str = tile["rotation"].GetString();

					if (strcmp(str, "north") == 0) {

						tileObj->rotation = Rotation::North;

					} else if (strcmp(str, "south") == 0) {

						tileObj->rotation = Rotation::South;

					} else if (strcmp(str, "west") == 0) {

						tileObj->rotation = Rotation::West;

					} else if (strcmp(str, "east") == 0) {

						tileObj->rotation = Rotation::East;

					} else if (strcmp(str, "random") == 0) {

						int random = rand() % 4;

						tileObj->rotation = *reinterpret_cast<Rotation*>(&random);

					}

				}

				level->addTile(tileObj);

			}

		} else if (tile.HasMember("end-index")) {

			auto end = tile["end-index"].GetObject();
			Vec2 index_end = { end["x"].GetInt(), end["y"].GetInt() };

			for (int i = int(index.x); i <= index_end.x; i++) {

				for (int j = int(index.y); j <= index_end.y; j++) {

					if (hollow && i != int(index.x) && hollow && i != index_end.x && hollow && j != int(index.y) && hollow && j != index_end.y) {

						continue;

					}

					if (other_type == "even" && i % 2 != 0 || other_type == "even" && j % 2 != 0 || other_type == "odd" && i % 2 != 1 || other_type == "odd" && j % 2 != 1) {

						continue;

					}

					Tile* tileObj = new Tile(getPosition(Vec2(i, j), level->desiredSize), offset, *ModelHandler::getModelById(tile["model"].GetInt()));

					tileObj->collidable = collidable;
					tileObj->explodeable = explodeable;
					tileObj->level = level;
					tileObj->index = Vec2(i, j);

					if (tile.HasMember("rotation")) {

						auto str = tile["rotation"].GetString();

						if (strcmp(str, "north") == 0) {

							tileObj->rotation = Rotation::North;

						} else if (strcmp(str, "south") == 0) {

							tileObj->rotation = Rotation::South;

						} else if (strcmp(str, "west") == 0) {

							tileObj->rotation = Rotation::West;

						} else if (strcmp(str, "east") == 0) {

							tileObj->rotation = Rotation::East;

						} else if (strcmp(str, "random") == 0) {

							int random = rand() % 4;

							tileObj->rotation = *reinterpret_cast<Rotation*>(&random);

						}

					}

					level->addTile(tileObj);

				}

			}

		} else {

			Tile* tileObj = new Tile(getPosition(index, level->desiredSize), offset, *ModelHandler::getModelById(tile["model"].GetInt()));

			tileObj->collidable = collidable;
			tileObj->explodeable = explodeable;
			tileObj->level = level;
			tileObj->index = index;

			if (tile.HasMember("rotation")) {

				auto str = tile["rotation"].GetString();

				if (strcmp(str, "north") == 0) {

					tileObj->rotation = Rotation::North;

				} else if (strcmp(str, "south") == 0) {

					tileObj->rotation = Rotation::South;

				} else if (strcmp(str, "west") == 0) {

					tileObj->rotation = Rotation::West;

				} else if (strcmp(str, "east") == 0) {

					tileObj->rotation = Rotation::East;

				} else if (strcmp(str, "random") == 0) {

					int random = rand() % 4;

					tileObj->rotation = *reinterpret_cast<Rotation*>(&random);

				}

			}

			level->addTile(tileObj);

		}

	}

	return level;

}

Vec3 LevelLoader::getPosition(Vec2 index, Vec2 desiredSize) {

	float scl = TileProperties::tile_scale;
	float width = desiredSize.x * scl;
	float height = desiredSize.y * scl;

	float x = index.x * scl - (width * .5f);
	float y = index.y * scl - (height * .5f);

	return { x, EOUL::Math::map(y, -1, 1, 1, -1), TileProperties::tile_z };

}