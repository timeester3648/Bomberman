#include "../../header/game/GameSaver.h"
#include "../../header/game/ScoreManager.h"

String GameSaver::path = "gamedata.dat";

void GameSaver::saveGame() {

	SaveFile save = SaveFile(path);

	save.remove();

	save.saveQueued((char*) &ScoreManager::high_score_player_0, sizeof(ScoreManager::high_score_player_0));
	save.saveQueued((char*) &ScoreManager::high_score_player_1, sizeof(ScoreManager::high_score_player_1));
	save.saveQueued((char*) &ScoreManager::latest_score_player_0, sizeof(ScoreManager::latest_score_player_0));
	save.saveQueued((char*) &ScoreManager::latest_score_player_1, sizeof(ScoreManager::latest_score_player_1));

	save.saveAllQueued();

}

void GameSaver::loadGame() {

	SaveFile save = SaveFile(path);

	std::vector<SaveData> saveData = save.readData();

	if (saveData.size() == 4) {

		memcpy(&ScoreManager::high_score_player_0, saveData[0].data.get(), sizeof(ScoreManager::high_score_player_0));
		memcpy(&ScoreManager::high_score_player_1, saveData[1].data.get(), sizeof(ScoreManager::high_score_player_1));
		memcpy(&ScoreManager::latest_score_player_0, saveData[2].data.get(), sizeof(ScoreManager::latest_score_player_0));
		memcpy(&ScoreManager::latest_score_player_1, saveData[3].data.get(), sizeof(ScoreManager::latest_score_player_1));

	}

}