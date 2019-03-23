#pragma once

#include "../enums/ScoreAction.h"
#include "../entity/Player.h"

class GAME_LOGIC_API_CPP ScoreManager {

	public:

		static unsigned int score_player_0;
		static unsigned int high_score_player_0;
		static unsigned int latest_score_player_0;

		static unsigned int score_player_1;
		static unsigned int high_score_player_1;
		static unsigned int latest_score_player_1;

		static constexpr int scores[] = {

			100,
			30,
			150,
			10

		};

	public:

		static void giveScore(ScoreAction type, int player);

};