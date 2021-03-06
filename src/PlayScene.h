#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"
#include "Target.h"

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

private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;
	
	// Target 
	Target* m_pThermalDetonator;
	// Player
	Player* m_pPlayer;
	bool m_isGravityEnabled = false;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	bool* m_isGravityEnabledCB = &m_isGravityEnabled;
	// Display Labels
	Label* m_pDistanceLabel; // Distance Label
	Label* m_pPPMLabel; // Pixel per Meter Label

	Label* m_pDistanceValue; // 485m
};

#endif /* defined (__PLAY_SCENE__) */