#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	TextureManager::Instance()->draw("startBackground", 400, 300, 0, 255, true); // Draw Start Scene Background
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/startBackground.jpg", "startBackground"); // Load Start Background
 
	const SDL_Color yellow = { 255, 255, 0, 255 };
	const SDL_Color white = { 255, 255, 255, 255 };
	const SDL_Color blue = { 0, 0, 255, 255 };

	m_pStartLabel = new Label("GAME2005: Assignment 1", "Consolas", 60, yellow, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pStartLabel2 = new Label("Motion in 1 and 2 Directions", "Consolas", 40, yellow, glm::vec2(400.0f, 100.0f));
	m_pStartLabel2->setParent(this);
	addChild(m_pStartLabel2);

	m_pName = new Label("By: Rodene Operio (101140007)", "Consolas", 30, white, glm::vec2(400.0f, 150.0f));
	m_pName->setParent(this);
	addChild(m_pName);

	m_pInstructionsLabel = new Label("Press 'Start' to Play!", "Consolas", 30, blue, glm::vec2(400.0f, 250.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 300.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	
}

