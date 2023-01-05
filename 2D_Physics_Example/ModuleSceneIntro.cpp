#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	deathplayer1 = App->textures->Load("Assets/Scenes/Player2win.png");
	deathplayer2 = App->textures->Load("Assets/Scenes/Player1win.png");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// Death Players
	

	if (App->player->timerdeathp1 <= 0 && App->physics->deathp1 == false && App->physics->deathp2 == false) {
		App->renderer->Blit(deathplayer1, 0, 0);
	}

	if (App->player->timerdeathp2 <= 0) {
		App->renderer->Blit(deathplayer2, 0, 0);
	}

	return UPDATE_CONTINUE;
}
