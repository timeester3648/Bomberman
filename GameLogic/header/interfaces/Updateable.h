#pragma once

class GAME_LOGIC_API_CPP Updateable {

	public:

		virtual void update() = 0;

	public:

		virtual ~Updateable() = default;

};