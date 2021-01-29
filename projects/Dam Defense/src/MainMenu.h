//Dam Defense, by Atlas X Games
//MainMenu.h, the header file for the class that represents the main menu
#pragma once

//include required features from titan
#include "Titan/Application.h"
#include "Titan/ObjLoader.h"
#include "Titan/Interpolation.h"

using namespace Titan;

class MainMenu : public TTN_Scene {
public:
	//default constructor
	MainMenu();

	//default destrcutor 
	~MainMenu() = default;

	//sets up the scene
	void InitScene();

	//update the scene
	void Update(float deltaTime);

	//late render (terrain, water, etc.)
	void PostRender();

	//Assets
public:

	//shader programs
	TTN_Shader::sshptr shaderProgramTextured;
	TTN_Shader::sshptr shaderProgramSkybox;
	TTN_Shader::sshptr shaderProgramAnimatedTextured;
	TTN_Shader::sshptr shaderProgramWater;
	TTN_Shader::sshptr shaderProgramTerrain;

	//meshes
	TTN_Mesh::smptr cannonMesh;
	TTN_Mesh::smptr flamethrowerMesh;
	TTN_Mesh::smptr damMesh;
	TTN_Mesh::smptr skyboxMesh;
	TTN_Mesh::smptr sphereMesh; //used for cannonballs and particles
	TTN_Mesh::smptr terrainPlain;

	//textures
	TTN_Texture2D::st2dptr cannonText;
	TTN_TextureCubeMap::stcmptr skyboxText;
	TTN_Texture2D::st2dptr terrainMap;
	TTN_Texture2D::st2dptr sandText;
	TTN_Texture2D::st2dptr rockText;
	TTN_Texture2D::st2dptr grassText;
	TTN_Texture2D::st2dptr waterText;
	TTN_Texture2D::st2dptr flamethrowerText;
	TTN_Texture2D::st2dptr damText;

	//materials
	TTN_Material::smatptr flamethrowerMat;
	TTN_Material::smatptr damMat;
	TTN_Material::smatptr cannonMat;
	TTN_Material::smatptr skyboxMat;

	//Entities
protected:
	entt::entity camera;
	entt::entity light;
	entt::entity skybox;
	entt::entity cannon;
	entt::entity terrain;
	entt::entity water;
	entt::entity dam;

	std::vector<entt::entity> flamethrowers;

	//other data
protected:
	//the terrain scale
	float terrainScale;
	//water animation control
	float time;
	float waveSpeed;
	float waveBaseHeightIncrease;
	float waveHeightMultiplier;
	float waveLenghtMultiplier;

	//Stuff for waves and spawning enemies
	float Timer = 0.F;//timer for boat spawning (left side)
	float Timer2 = 0.F;//timer for boat spawning (right side)
	bool Spawning = true; //whether or not the spawners should be spawning

	float waveTimer = 0.F;//timer for waves
	float restTimer = 0.F;//timer for waves
	int wave = 0; // keep track of wave number

	//set up functions, called by InitScene()
protected:
	void SetUpAssets();
	void SetUpEntities();
	void SetUpOtherData();
};

class MainMenuUI : public TTN_Scene {
public:
	//default constructor
	MainMenuUI();

	//default destrcutor 
	~MainMenuUI() = default;

	//sets up the scene
	void InitScene();

	//update the scene
	void Update(float deltaTime);

	//mouse input
	void MouseButtonDownChecks();

	bool GetShouldPlay() { return shouldPlay; }
	bool GetShouldQuit() { return shouldQuit; }

private:
	//entities
	entt::entity cam;
	entt::entity gameLogo;
	//play
	entt::entity playButton;
	entt::entity playText;
	//arcade
	entt::entity arcadeButton;
	entt::entity arcadeText;
	//options
	entt::entity optionsButton;
	entt::entity optionsText;
	//quit
	entt::entity quitButton;
	entt::entity quitText;

	//assets
	TTN_Texture2D::st2dptr textureGameLogo;
	TTN_Texture2D::st2dptr textureButton1;
	TTN_Texture2D::st2dptr textureButton2;
	TTN_Texture2D::st2dptr texturePlay;
	TTN_Texture2D::st2dptr textureArcade;
	TTN_Texture2D::st2dptr textureOptions;
	TTN_Texture2D::st2dptr textureQuit;

	bool shouldQuit;
	bool shouldPlay;
};