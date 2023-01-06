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
	

	if (App->player->timerdeathp1 <= 0) {
		App->renderer->Blit(deathplayer1, 0, 0);
		win = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && win == true) {
		SDL_DestroyTexture(deathplayer1);
		App->physics->deathp1 = false;
		App->physics->deathp2 = false;
		App->player->timerdeathp1 = 50;
		App->player->timerdeathp2 = 50;
		App->physics->lifep1.w = 5.0f;
		App->physics->lifep2.w = 5.0f;
		win = false;

		//return players to initial position
		//player1
		App->physics->players[0].x = 3.0f;
		App->physics->players[0].y = (App->physics->ground.y + App->physics->ground.h);

		////player2
		App->physics->players[1].x = 48.0f;
		App->physics->players[1].y = (App->physics->ground.y + App->physics->ground.h);
	}

	if (App->player->timerdeathp2 <= 0) {
		App->renderer->Blit(deathplayer2, 0, 0);
		win = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && win == true) {
		SDL_DestroyTexture(deathplayer2);
		App->physics->deathp1 = false;
		App->physics->deathp2 = false;
		App->player->timerdeathp1 = 50;
		App->player->timerdeathp2 = 50;
		App->physics->lifep1.w = 5.0f;
		App->physics->lifep2.w = 5.0f;
		win = false;

		//return players to initial position
		//player1
		App->physics->players[0].x = 3.0f;
		App->physics->players[0].y = (App->physics->ground.y + App->physics->ground.h);

		////player2
		App->physics->players[1].x = 48.0f;
		App->physics->players[1].y = (App->physics->ground.y + App->physics->ground.h);
	}

	return UPDATE_CONTINUE;
}
