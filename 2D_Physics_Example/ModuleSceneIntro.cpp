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

	scenegame = App->textures->Load("Assets/Scenes/GameScene.png");
	scenelogo = App->textures->Load("Assets/Scenes/OurLogo.png");

	background = App->textures->Load("Assets/Scenes/Background.png");

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
	

	
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT && win == true) {

		SDL_DestroyTexture(deathplayer1);
		deathplayer1 = App->textures->Load("Assets/Scenes/Player2win.png");
		App->physics->deathp1 = false;
		App->physics->deathp2 = false;
		App->player->timerdeathp1 = 260;
		App->player->timerdeathp2 = 260;
		App->physics->lifep1.w = 5.0f;
		App->physics->lifep2.w = 5.0f;
		App->physics->lifep2.x = 45.1f;
		win = false;

		introscenes = true;
		//return players to initial position
		//player1
		App->physics->players[0].x = 3.0f;
		App->physics->players[0].y = (App->physics->ground.y + App->physics->ground.h);

		////player2
		App->physics->players[1].x = 48.0f;
		App->physics->players[1].y = (App->physics->ground.y + App->physics->ground.h);

	}

	
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT && win == true) {

		SDL_DestroyTexture(deathplayer2);
		deathplayer2 = App->textures->Load("Assets/Scenes/Player1win.png");
		App->physics->deathp1 = false;
		App->physics->deathp2 = false;
		App->player->timerdeathp1 = 260;
		App->player->timerdeathp2 = 260;
		App->physics->lifep1.w = 5.0f;
		App->physics->lifep2.w = 5.0f;
		App->physics->lifep2.x = 45.1f;
		win = false;

		introscenes = true;
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
