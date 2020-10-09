#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("playsceneBackground", 400, 300, 0, 255, true); // Draw playscene background
	TextureManager::Instance()->draw("Stormtroopers", 515, 500, 0, 255, true); // Draw Stormtroopers
	TextureManager::Instance()->draw("Stormtroopers", 485, 500, 0, 255, true); // Draw Stormtroopers
	TextureManager::Instance()->draw("Stormtroopers", 455, 500, 0, 255, true); // Draw Stormtroopers
	
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	// Check and Display Variable Labels
	// Distance
	float distanceTravelled = 0;
	distanceTravelled = m_pThermalDetonator->getTransform()->position.x;
	m_pDistanceLabel->setText("Distance Travelled = " + std::to_string(distanceTravelled));
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/playsceneBackground.png", "playsceneBackground"); // Load Background
	TextureManager::Instance()->load("../Assets/textures/StormTrooper.png", "Stormtroopers"); // Load Stormtrooper 
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);

	// Target Sprite
	m_pThermalDetonator = new Target();
	addChild(m_pThermalDetonator);

	// Display Variable Labels
	const SDL_Color white = { 255, 255, 255, 255 };
	// Distance
	m_pDistanceLabel = new Label("Distance: ", "Consolas", 20, white, glm::vec2(630.0f, 30.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);
	
	// Distance Value
	m_pDistanceValue = new Label("485m", "Consolas", 20, white, glm::vec2(475.0f, 430.0f));
	m_pDistanceValue->setParent(this);
	addChild(m_pDistanceValue);

	// Scale
	m_pPPMLabel = new Label("Scale: 1px:1m", "Consolas", 15, white, glm::vec2(750.0f, 585.0f));
	m_pPPMLabel->setParent(this);
	addChild(m_pPPMLabel);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(200.0f, 130.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(600.0f, 130.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance()->changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	addChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 90.0f);

	addChild(m_pInstructionsLabel);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Variable Control Center", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("Throw Detonator"))
	{
		m_pThermalDetonator->doThrow();
	}

	static int playerPosX = 0;
	static float VelAngle[2] = { 0, 0 };

	if (ImGui::Button("Reset to Default Values for Question A"))
	{
		// Position Reset
		playerPosX = 0;
		m_pPlayer->getTransform()->position.x = 0;
		m_pThermalDetonator->throwPosition = glm::vec2(0, 500);
		// Variable Reset
		VelAngle[0] = 95; // Velocity
		VelAngle[1] = 16; // Angle
		m_pThermalDetonator->throwSpeed = glm::vec2(VelAngle[0], -VelAngle[1]);
	}
	if (ImGui::Button("Reset to Default Values for Question B"))
	{
		// Position Reset
		playerPosX = 0;
		m_pPlayer->getTransform()->position.x = 0;
		m_pThermalDetonator->throwPosition = glm::vec2(0, 500);
		// Variable Reset
		VelAngle[0] = 95; // Velocity
		VelAngle[1] = 45; // Angle
		m_pThermalDetonator->throwSpeed = glm::vec2(VelAngle[0], -VelAngle[1]);
	}
	ImGui::Separator();

	if (ImGui::Checkbox("Gravity Enabled", m_isGravityEnabledCB));
	{
		m_pThermalDetonator->isGravityEnabled = *m_isGravityEnabledCB;
	}

	if (ImGui::SliderInt("Player's Position", &playerPosX, 0, 800))
	{
		m_pPlayer->getTransform()->position.x = playerPosX;
		m_pThermalDetonator->throwPosition = glm::vec2(playerPosX, 500);
	}

	if (ImGui::SliderFloat2("Velocity | Angle", VelAngle, 0, 180))
	{
		m_pThermalDetonator->throwSpeed = glm::vec2(VelAngle[0], -VelAngle[1]);
	}

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
