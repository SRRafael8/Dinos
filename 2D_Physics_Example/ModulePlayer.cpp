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

	//PLAYER 1
	if (App->physics->deathp1 == false && App->physics->deathp2 == false && App->physics->inicio == false && App->scene_intro->introscenes == false) {
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
		if (timer == 0) {
			App->physics->disparo = 0;
			timer = 200;
		}
	}
	//PLAYER 2
	//Move left
	if (App->physics->deathp1 == false && App->physics->deathp2 == false && App->physics->inicio==false && App->scene_intro->introscenes==false) {
		if (App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT) {
			App->physics->players[1].vx = -1.0f;
		}

		//Move right
		if (App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT) {
			App->physics->players[1].vx = 1.0f;
		}

		//idle condition
		if (App->input->GetKey(SDL_SCANCODE_L) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_J) == KEY_IDLE) {
			App->physics->players[1].vx = 0.0f;
		}

		//Shoot
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) {
			App->physics->disparo2 = 1;
		}
		if (timer2 == 0) {
			App->physics->disparo2 = 0;
			timer2 = 200;
		}
	}
	

	////Shoot
	//if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {
	//	int x = App->physics->players[1].x;
	//	int y = App->physics->players[1].y;
	//	float r = 0.5f;
	//	float vx = 0;
	//	float vy = 0;
	//	App->renderer->DrawCircle(x, y, r, 255, 100, 100);
	//}

	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN) {
		App->physics->menosdirection = 0;
		App->physics->masdirection = 0;

		if (laequis) { laequis = false; }
		else { laequis = true; }
	}
	if (laequis == true) {


		if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {
			App->physics->masdirection = 1;
			App->physics->menosdirection = 0;
		}
		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) {
			App->physics->menosdirection = 1;
			App->physics->masdirection = 0;
		}
	}
	return UPDATE_CONTINUE;
}



