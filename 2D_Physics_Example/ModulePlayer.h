#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class PhysBody;

struct Object
{
	SDL_Texture* graphic;
	PhysBody* body;
	uint fx;

	Object() : graphic(NULL), body(NULL)
	{}
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	Object ball;
	Object flipper1;
	Object flipper2;
	Object spring;

	PhysBody* flipper1_wheel;
	PhysBody* flipper2_wheel;
	PhysBody* spring_wheel;

	Object flipper_up1;
	Object flipper_up2;
	PhysBody* flipper_up1_wheel;
	PhysBody* flipper_up2_wheel;

	PhysBody* sensor1;

	bool laequis = true;

	float xup = 20.0f;
	float yup = 10.0f;
	float xup2 = -20.0f;
	float yup2 = 10.0f;


	int timer = 200;
	int timer2 = 200;

	int timerdeathp1 = 260;
	int timerdeathp2 = 260;

	int timerplayer1 = 1000;
	int timerplayer2 = 1000;

	bool turn = 0;
};