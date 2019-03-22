#include "../../header/game/ScoreManager.h"

unsigned int ScoreManager::score_player_0 = 0;
unsigned int ScoreManager::high_score_player_0 = 0;
unsigned int ScoreManager::latest_score_player_0 = 0;

unsigned int ScoreManager::score_player_1 = 0;
unsigned int ScoreManager::high_score_player_1 = 0;
unsigned int ScoreManager::latest_score_player_1 = 0;

void ScoreManager::giveScore(ScoreAction type, int player) {

	if (player == 0) {

		score_player_0 += scores[int(type)];
		latest_score_player_0 = score_player_0;

		if (score_player_0 > high_score_player_0) {

			high_score_player_0 = score_player_0;

		}

	} else if (player == 1) {

		score_player_1 += scores[int(type)];
		latest_score_player_1 = score_player_1;

		if (score_player_1 > high_score_player_1) {

			high_score_player_1 = score_player_1;

		}

	}

}