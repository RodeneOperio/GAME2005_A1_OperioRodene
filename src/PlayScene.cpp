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

	// Check if position is changed

	// Check if distance value is changed

	// Check and Display Variable Labels
	// Distance
	// Velocity

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

	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);

	// Display Variable Labels
	const SDL_Color white = { 255, 255, 255, 255 };
	// Distance
	m_pDistanceLabel = new Label("Distance: ", "Consolas", 20, white, glm::vec2(680.0f, 30.0f));
	m_pDistanceLabel->setParent(this);
	addChild(m_pDistanceLabel);
	// Velocity
	m_pVelocityLabel = new Label("Velocity: ", "Consolas", 20, white, glm::vec2(680.0f, 60.0f));
	m_pVelocityLabel->setParent(this);
	addChild(m_pVelocityLabel);
	// Scale
	m_pPPMLabel = new Label("Scale: 1px:1m", "Consolas", 15, white, glm::vec2(730.0f, 585.0f));
	m_pPPMLabel->setParent(this);
	addChild(m_pPPMLabel);

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(200.0f, 550.0f);
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
	m_pNextButton->getTransform()->position = glm::vec2(600.0f, 550.0f);
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

// Set Placeholders for GUI Sliders
void PlayScene::setImGuiSliders()
{
	//ImGuiSliders[0] = // stormtrooper pos
	//ImGuiSliders[1] = // wookiee pos
	//ImGuiSliders[2] = // thermal detonator velocity
	//ImGuiSliders[3] = // thermal detonator angle
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
		// Throw Detonator
	}
	if (ImGui::Button("Reset to Default Values"))
	{
		// Reset All Variables To Default
	}

	ImGui::Separator();

	bool tempGravity = false;

	if (ImGui::Checkbox("Gravity Enabled", &tempGravity))
	{
		// Enable Gravity
	}

	float tempStormPos = 485.0f;
	if (ImGui::SliderFloat("Stormtrooper's Position", &tempStormPos, 50, 800))
	{
		// Move Stormtrooper
	}
	float tempWookPos = 485.0f;
	if (ImGui::SliderFloat("Wookiee's Position", &tempWookPos, 50, 800))
	{
		// Move Wookiee
	}
	float tempVel[2] = { 95.0f, 45.0f };
	if (ImGui::SliderFloat2("Velocity | Angle", &tempVel[0], 0, 90))
	{
		// Change Velocity, Change Angle
	}

	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
