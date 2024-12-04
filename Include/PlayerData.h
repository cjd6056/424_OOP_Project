#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include <vector>
#include <string>
#include <iostream>

/* Container Requirement met
PlayerData class uses two separate containers:

std::vector<std::string> playerNames to store the names of the players.
std::vector<int> gamesPlayed to store the number of games played for each player.

*/

class PlayerData {
public:
    // Vectors to store player names and their respective games played
    std::vector<std::string> playerNames;
    std::vector<int> gamesPlayed;

    // Function to add a new player
    void addPlayer(const std::string& name) {
        playerNames.push_back(name);
        gamesPlayed.push_back(0);  // Initialize games played to 0 for a new player
    }

    // Function to update the number of games played for a specific player
    void incrementGamesPlayed(int playerIndex) {
        if (playerIndex >= 0 && playerIndex < gamesPlayed.size()) {
            gamesPlayed[playerIndex]++;
        }
    }

    // Function to display player names and games played
    void displayPlayerData() {
        for (size_t i = 0; i < playerNames.size(); ++i) {
            std::cout << playerNames[i] << " - Games Played: " << gamesPlayed[i] << std::endl;
        }
    }
};

#endif // PLAYERDATA_H
