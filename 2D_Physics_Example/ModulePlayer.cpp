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
	
	//Texturas
	stone = App->textures->Load("Assets/Sprites/Stone.png");

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
	if (App->physics->deathp1 == false && App->physics->deathp2 == false && App->physics->inicio == false && App->scene_intro->introscenes == false && timerplayer1<=0) {

		App->physics->barp2.h = 0;
		App->physics->barp1.h = 10;

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

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
			xup--;
			yup++;
			App->physics->degree1.w = App->physics->degree1.w + 0.1f;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
			xup++;
			yup--;
			App->physics->degree1.w = App->physics->degree1.w - 0.1f;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
			xup++;
			yup++;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
			xup--;
			yup--;
		}


		if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN) {

			App->physics->disparo = 1; 
			
			PhysBall bullet = PhysBall(8.0f, 1.0f, 0.2f, 0.4f, 0.2f, 10.0f, 0.9f, 0.8f, App->physics->players[0].x, App->physics->players[0].y + App->physics->players[0].radius + 0.3f, xup, yup, 255, 255, 0);
			App->physics->bullets.emplace_back(bullet);

			int x, y;
			x = bullet.x;
			y = bullet.y;
			App->renderer->Blit(stone, x, y, NULL);

			timerplayer1 = 1000;

			App->physics->damage2 = true;
		}
		if (timer == 0) {
			App->physics->disparo = 0;
			timer = 200;
		}

		if (timerplayer1 <= -500) {
			timerplayer1 = 1000;
		}

	}
	//PLAYER 2
	//Move left
	if (App->physics->deathp1 == false && App->physics->deathp2 == false && App->physics->inicio==false && App->scene_intro->introscenes==false && timerplayer1>0) {

		timerplayer1--;

		App->physics->barp1.h = 0;
		App->physics->barp2.h = 10;

		//Move left
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			App->physics->players[1].vx = -1.0f;
		}
		//Move right
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			App->physics->players[1].vx = 1.0f;
		}
		//idle condition
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE) {
			App->physics->players[1].vx = 0.0f;
		}

		//Shoot
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
			xup2++;
			yup2++;
			App->physics->degree2.w = App->physics->degree2.w + 0.1f;
		}

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
			xup2--;
			yup2--;
			App->physics->degree2.w = App->physics->degree2.w - 0.1f;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
			xup2--;
			yup2++;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
			xup2++;
			yup2--;
		}

		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
			App->physics->disparo2 = 1;
			PhysBall bullet = PhysBall(8.0f, 1.0f, 0.2f, 0.4f, 0.2f, 10.0f, 0.9f, 0.8f, App->physics->players[1].x, App->physics->players[1].y + App->physics->players[1].radius + 0.3f, xup2, yup2, 255, 0, 255);
			App->physics->bullets.emplace_back(bullet);
			
			timerplayer1 = 0;

			App->physics->damage = true;
		}
		if (timer2 == 0) {
			App->physics->disparo2 = 0;
			timer2 = 200;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN) {
		if (laequis) { laequis = false; }
		else { laequis = true; }
	}
	return UPDATE_CONTINUE;
}



