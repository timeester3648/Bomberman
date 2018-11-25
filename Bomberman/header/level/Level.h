#pragma	once

#include "../objects/Tile.h"
#include "../entity/Entity.h"
#include "../util/TexturedModelCompare.h"

#include <vector>
#include <map>
#include <glm/glm.hpp>

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;

class Level {

	public:

		std::map<TexturedModel*, std::vector<Tile*>, TexturedModelCompare> tiles;
		Vec2 desiredSize;

	public:

		~Level();

	public:

		void addTile(Tile* tile);

		Vec3 gridToWorldPos(Vec2 gridPos);
		Vec2 worldToGridPos(Vec3 pos);
		Tile* getTileByPos(Vec2 pos);
		std::vector<Tile*> getTilesByPos(Vec2 pos);
		std::vector<Entity*> getEntities();

};