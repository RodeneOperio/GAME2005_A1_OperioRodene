#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	float ImGuiSliders[4]; // Control Different Variables in One array
	void setImGuiSliders(); // Set which index controls each variable
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;
	
	// Target 
	//Target* m_pThermalDetonator;
	// Enemy
	//Enemy* m_pEnemy;
	// Player
	Player* m_pPlayer;


	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	// Display Labels
	Label* m_pDistanceLabel; // Distance Label
	Label* m_pVelocityLabel; // Velocity Label
	Label* m_pPPMLabel; // Pixel per Meter Label
};

#endif /* defined (__PLAY_SCENE__) */