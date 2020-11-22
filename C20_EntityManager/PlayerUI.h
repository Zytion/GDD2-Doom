#pragma once
#include <string>

class PlayerUI
{
	// draws the ui
public:
	void DrawUI();
	void SetHealth(int health);
	int GetHealth();
	// put all writing here for now
private:
	std::string title = "DOOM";
	int health = 100;
	std::string health_ui = "HEALTH: " + health;
};

