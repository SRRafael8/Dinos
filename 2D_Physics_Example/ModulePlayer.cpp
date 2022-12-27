#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "PhysBody.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//Move left
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		App->physics->players[0].vx = -1.0f;
	}

	//Move right
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		App->physics->players[0].vx = 1.0f;
	}

	//idle condition
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE) {
		App->physics->players[0].vx = 0.0f;
	}

	//Shoot
	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) { App->physics->disparo = 1; }
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) { App->physics->disparo = 0; }

	return UPDATE_CONTINUE;
}



