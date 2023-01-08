#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "math.h"
#include <cmath>

// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
	frames = 0;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{

	LOG("Creating Physics 2D environment");

	//Delta Time
	timer = Timer();
	maxFrameDuration = 16;
	timer.Start();
	startupTime.Start();
	lastSecFrameTime.Start();

	//Create life
	lifep1 = Ground();
	lifep1.x = 1.0f; // [m]
	lifep1.y = 1.0f; // [m]
	lifep1.w = 5.0f; // [m]
	lifep1.h = 1.0f; // [m]

	lifep2 = Ground();
	lifep2.x = 45.1f; // [m]
	lifep2.y = 1.0f; // [m]
	lifep2.w = 5.0f; // [m]
	lifep2.h = 1.0f; // [m]

	lifep1g = Ground();
	lifep1g.x = 1.0f; // [m]
	lifep1g.y = 1.0f; // [m]
	lifep1g.w = 5.0f; // [m]
	lifep1g.h = 1.0f; // [m]

	lifep2g = Ground();
	lifep2g.x = 45.1f; // [m]
	lifep2g.y = 1.0f; // [m]
	lifep2g.w = 5.0f; // [m]
	lifep2g.h = 1.0f; // [m]

	degree1 = Ground();
	degree1.x = 10.0f; // [m]
	degree1.y = 27.5f; // [m]
	degree1.w = 5.0f; // [m]
	degree1.h = 1.0f; // [m]

	degree2 = Ground();
	degree2.x = 10.0f; // [m]
	degree2.y = 26.0f; // [m]
	degree2.w = 5.0f; // [m]
	degree2.h = 1.0f; // [m]

	borde = Ground();
	borde.x = 0.7f; // [m]
	borde.y = 0.75f; // [m]
	borde.w = 5.5f; // [m]
	borde.h = 1.5f; // [m]

	borde2 = Ground();
	borde2.x = 44.8f; // [m]
	borde2.y = 0.75f; // [m]
	borde2.w = 5.5f; // [m]
	borde2.h = 1.5f; // [m]

	// Create left ground
	ground = Ground();
	ground.x = 0.0f; // [m]
	ground.y = 0.0f; // [m]
	ground.w = 7.0f; // [m]
	ground.h = 15.0f; // [m]

	ground2 = Ground();
	ground2.x = ground.x + ground.w; // [m]
	ground2.y = 0.0f; // [m]
	ground2.w = 7.0f; // [m]
	ground2.h = 10.0f; // [m]

	// Create Water
	water = Water();
	water.x = ground2.x + ground2.w; // Start where ground ends [m]
	water.y = 0.0f; // [m]
	water.w = 23.2f; // [m]
	water.h = 5.0f; // [m]
	water.density = 50.0f; // [kg/m^3]
	water.vx = -1.0f; // [m/s]
	water.vy = 0.0f; // [m/s]

	//Colision water death
	waterdeath = Water();
	waterdeath.x = ground2.x + ground2.w; // Start where ground ends [m]
	waterdeath.y = 0.0f; // [m]
	waterdeath.w = 23.2f; // [m]
	waterdeath.h = 3.0f; // [m]
	waterdeath.density = 50.0f; // [kg/m^3]
	waterdeath.vx = -1.0f; // [m/s]
	waterdeath.vy = 0.0f; // [m/s]

	//Create right ground
	ground3 = Ground();
	ground3.x = water.x + water.w; // [m]
	ground3.y = 0.0f; // [m]
	ground3.w = 7.0f; // [m]
	ground3.h = 10.0f; // [m]

	ground4 = Ground();
	ground4.x = ground3.x + ground3.w; // [m]
	ground4.y = 0.0f; // [m]
	ground4.w = 7.0f; // [m]
	ground4.h = 15.0f; // [m]

	ground6 = Ground();
	ground6.x = -1.0f; // [m]
	ground6.y = 15.3f; // [m]
	ground6.w = 1.0f; // [m]
	ground6.h = 6.0f; // [m]

	ground7 = Ground();
	ground7.x = 51.2f; // [m]
	ground7.y = 15.3f; // [m]
	ground7.w = 1.0f; // [m]
	ground7.h = 6.0f; // [m]

	groundlife = Ground();
	groundlife.x = 25.1f; // [m]
	groundlife.y = 33.3f; // [m]
	groundlife.w = 1.0f; // [m]
	groundlife.h = 1.0f; // [m]

	//Loading bar
	bar = Ground();
	bar.x = -30.0f; // [m]
	bar.y = 5.0f; // [m]
	bar.w = 0.01f; // [m]
	bar.h = 0.5f; // [m]

	//Time bars
	barp1 = Ground();
	barp1.x = 0.0f; // [m]
	barp1.y = 20.0f; // [m]
	barp1.w = 1.0f; // [m]
	barp1.h = 10.0f; // [m]

	barp2 = Ground();
	barp2.x = 50.2f; // [m]
	barp2.y = 20.0f; // [m]
	barp2.w = 1.0f; // [m]
	barp2.h = 10.0f; // [m]

	// Create atmosphere
	atmosphere = Atmosphere();
	atmosphere.windx = 0.0f; // [m/s]
	atmosphere.windy = 5.0f; // [m/s]
	atmosphere.density = 1.0f; // [kg/m^3]

	// Create a ball
	PhysBall ball = PhysBall();

	// Set static properties of the ball
	ball.mass = 10.0f; // [kg]
	ball.surface = 1.0f; // [m^2]
	ball.radius = 0.5f; // [m]
	ball.cd = 0.4f; // [-]
	ball.cl = 1.2f; // [-]
	ball.b = 10.0f; // [...]
	ball.coef_friction = 0.9f; // [-]
	ball.coef_restitution = 0.8f; // [-]

	// Set initial position and velocity of the ball
	ball.x = 2.0f;
	ball.y = (ground.y + ground.h) + 2.0f;
	ball.vx = 0.0f;
	ball.vy = 0.0f;

	// Add ball to the collection
	balls.emplace_back(ball);

	// Create the player
	PhysBall player = PhysBall();

	// Set static properties of the ball
	player.mass = 10.0f; // [kg]
	player.surface = 1.0f; // [m^2]
	player.radius = 0.5f; // [m]
	player.cd = 0.4f; // [-]
	player.cl = 1.2f; // [-]
	player.b = 10.0f; // [...]
	player.coef_friction = 0.9f; // [-]
	player.coef_restitution = 0.8f; // [-]

	// Set initial position and velocity of the ball
	player.x = 3.0f;
	player.y = (ground.y + ground.h);
	player.vx = 0.0f;
	player.vy = 0.0f;

	// Add ball to the collection
	players.emplace_back(player);

	// Create the player2
	PhysBall player2 = PhysBall();

	// Set static properties of the ball
	player2.mass = 10.0f; // [kg]
	player2.surface = 1.0f; // [m^2]
	player2.radius = 0.5f; // [m]
	player2.cd = 0.4f; // [-]
	player2.cl = 1.2f; // [-]
	player2.b = 10.0f; // [...]
	player2.coef_friction = 0.9f; // [-]
	player2.coef_restitution = 0.8f; // [-]

	// Set initial position and velocity of the ball
	player2.x = 48.0f;
	player2.y = (ground.y + ground.h);
	player2.vx = 0.0f;
	player2.vy = 0.0f;

	// Add ball to the collection
	players.emplace_back(player2);

	// Create a ball
	PhysRect boat = PhysRect();

	// Set static properties of the ball
	boat.mass = 10.0f; // [kg]
	boat.surface = 1.0f; // [m^2]
	boat.width = 3.0f; // [m]
	boat.height = 0.5f; // [m]
	boat.cd = 0.4f; // [-]
	boat.cl = 1.2f; // [-]
	boat.b = 10.0f; // [...]
	boat.coef_friction = 0.9f; // [-]
	boat.coef_restitution = 0.8f; // [-]

	// Set initial position and velocity of the ball
	boat.x = water.x + water.w/4;
	boat.y = (ground.y + ground.h) + 2.0f;
	boat.vx = 0.0f;
	boat.vy = 0.0f;

	// Add ball to the collection

	// Bool for GUI forces

	return true;
}

update_status ModulePhysics::PreUpdate()
{

	//Delta Time
	frameTime.Start();

	// Process all balls in the scenario
	for (auto& ball : balls)
	{
		// Skip ball if physics not enabled
		if (!ball.physics_enabled)
		{
			continue;
		}
		
		// Reset total acceleration and total accumulated force of the ball
		ball.fx = ball.fy = 0.0f;
		ball.ax = ball.ay = 0.0f;

		
		// Gravity force
		if (gravitybool)
		{
			float fgx = ball.mass * 0.0f;
			float fgy = ball.mass * -10.0f; // Let's assume gravity is constant and downwards
			ball.fx += fgx; ball.fy += fgy; // Add this force to ball's total force
		}
		// Aerodynamic Drag force (only when not in water)
		if (aerodragbool)
		{
			if (!is_colliding_with_water(ball, water))
			{
				float fdx = 0.0f; float fdy = 0.0f;
				compute_aerodynamic_drag(fdx, fdy, ball, atmosphere);
				ball.fx += fdx; ball.fy += fdy; // Add this force to ball's total force
			}
		}
		// Hydrodynamic forces (only when in water)
		if (is_colliding_with_water(ball, water))
		{
			if (hydrodragbool)
			{
				// Hydrodynamic Drag force
				float fhdx = 0.0f; float fhdy = 0.0f;
				compute_hydrodynamic_drag(fhdx, fhdy, ball, water);
				ball.fx += fhdx; ball.fy += fhdy; // Add this force to ball's total force
			}
			if (buoyancybool)
			{
				// Hydrodynamic Buoyancy force
				float fhbx = 0.0f; float fhby = 0.0f;
				compute_hydrodynamic_buoyancy(fhbx, fhby, ball, water);
				ball.fx += fhbx; ball.fy += fhby; // Add this force to ball's total force
			}
		}
		//2nd Newton's Law		
		// SUM_Forces = mass * accel --> accel = SUM_Forces / mass
		ball.ax = ball.fx / ball.mass;
		ball.ay = ball.fy / ball.mass;

		//Integrate --> from accel to new velocity & new position

		// We will use the 2nd order "Velocity Verlet" method for integration.
		integrator_velocity_verlet(ball, maxFrameDuration/1000);

		// Step #4: solve collisions
		// ----------------------------------------------------------------------------------------

		// Solve collision between ball and ground
		if (is_colliding_with_ground(ball, ground))
		{
			// TP ball to ground surface
			ball.y = ground.y + ground.h + ball.radius;

			// Elastic bounce with ground
			ball.vy = - ball.vy;

			// FUYM non-elasticity
			ball.vx *= ball.coef_friction;
			ball.vy *= ball.coef_restitution;
		}
		if (is_colliding_with_ground(ball, ground2))
		{
			// TP ball to ground surface
			ball.y = ground2.y + ground2.h + ball.radius;

			// Elastic bounce with ground
			ball.vy = -ball.vy;

			// FUYM non-elasticity
			ball.vx *= ball.coef_friction;
			ball.vy *= ball.coef_restitution;
		}
		if (is_colliding_with_ground(ball, ground3))
		{
			// TP ball to ground surface
			ball.y = ground3.y + ground3.h + ball.radius;

			// Elastic bounce with ground
			ball.vy = -ball.vy;

			// FUYM non-elasticity
			ball.vx *= ball.coef_friction;
			ball.vy *= ball.coef_restitution;
		}
		if (is_colliding_with_ground(ball, ground4))
		{
			// TP ball to ground surface
			ball.y = ground4.y + ground4.h + ball.radius;

			// Elastic bounce with ground
			ball.vy = -ball.vy;

			// FUYM non-elasticity
			ball.vx *= ball.coef_friction;
			ball.vy *= ball.coef_restitution;
		}

	}

	for (auto& bullet : bullets)
	{
		// Skip ball if physics not enabled
		if (!bullet.physics_enabled)
		{
			continue;
		}

		// Step #0: Clear old values

		// Reset total acceleration and total accumulated force of the ball
		bullet.fx = bullet.fy = 0.0f;
		bullet.ax = bullet.ay = 0.0f;

		// Gravity force
		if (gravitybool)
		{
			float fgx = bullet.mass * 0.0f;
			float fgy = bullet.mass * -10.0f; // Let's assume gravity is constant and downwards
			bullet.fx += fgx; bullet.fy += fgy; // Add this force to ball's total force
		}

		// Aerodynamic Drag force (only when not in water)
		if (aerodragbool)
		{
			if (!is_colliding_with_water(bullet, water))
			{
				float fdx = 0.0f; float fdy = 0.0f;
				compute_aerodynamic_drag(fdx, fdy, bullet, atmosphere);
				bullet.fx += fdx; bullet.fy += fdy; // Add this force to ball's total force
			}
		}

		// Hydrodynamic forces (only when in water)
		if (is_colliding_with_water(bullet, water))
		{
			if (hydrodragbool)
			{
				// Hydrodynamic Drag force
				float fhdx = 0.0f; float fhdy = 0.0f;
				compute_hydrodynamic_drag(fhdx, fhdy, bullet, water);
				bullet.fx += fhdx; bullet.fy += fhdy; // Add this force to ball's total force
			}
			if (buoyancybool)
			{
				// Hydrodynamic Buoyancy force
				float fhbx = 0.0f; float fhby = 0.0f;
				compute_hydrodynamic_buoyancy(fhbx, fhby, bullet, water);
				bullet.fx += fhbx; bullet.fy += fhby; // Add this force to ball's total force
			}
		}

		//2nd Newton's Law

		// SUM_Forces = mass * accel --> accel = SUM_Forces / mass
		bullet.ax = bullet.fx / bullet.mass;
		bullet.ay = bullet.fy / bullet.mass;

		//Integrate --> from accel to new velocity & new position

		// We will use the 2nd order "Velocity Verlet" method for integration.
		integrator_velocity_verlet(bullet, maxFrameDuration / 1000);

		// Solve collision between ball and ground
		if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
			if (fade == true) {
				fade = false;
			}
			else {
				fade = true;
			}
		}

		if (is_colliding_with_ground(bullet, ground))
		{
			// TP ball to ground surface
			if (fade == false) {
				if (bullet.y >= ground.y + ground.h) {
					bullet.y = ground.y + ground.h + bullet.radius;
					bullet.vy = -bullet.vy;
				}
				if (bullet.y < ground.y + ground.h) {
					bullet.x = ground.x + ground.w + bullet.radius;
					bullet.vx = bullet.vx * -1;
				}
			}
			if (fade == true) {
				bullet.x = -200;
			}

			// Elastic bounce with ground
			

			// FUYM non-elasticity
			bullet.vx *= bullet.coef_friction;
			bullet.vy *= bullet.coef_restitution;
		}
		if (is_colliding_with_ground(bullet, ground2))
		{
			// TP ball to ground surface
			if (fade == false) {
				if (bullet.y >= ground2.y + ground2.h) {
					bullet.y = ground2.y + ground2.h + bullet.radius;

					// Elastic bounce with ground
					bullet.vy = -bullet.vy;
				}
				if (bullet.y < ground2.y + ground2.h) {
					bullet.x = ground2.x + ground2.w + bullet.radius;
					bullet.vx = bullet.vx * -1;
				}
			}
			
			if (fade == true) {
				bullet.x = -200;
			}

			// FUYM non-elasticity
			bullet.vx *= bullet.coef_friction;
			bullet.vy *= bullet.coef_restitution;
		}
		if (is_colliding_with_ground(bullet, ground3))
		{
			if (fade == false) {
				if (bullet.y >= ground3.y + ground3.h) {
					// TP ball to ground surface
					bullet.y = ground3.y + ground3.h + bullet.radius;

					// Elastic bounce with ground
					bullet.vy = -bullet.vy;
				}
				if (bullet.y < ground3.y + ground3.h) {
					bullet.x = ground3.x - 0.2f;
					bullet.vx = bullet.vx * -1;
				}
			}
			
			if (fade == true) {
				bullet.x = -200;
			}

			// FUYM non-elasticity
			bullet.vx *= bullet.coef_friction;
			bullet.vy *= bullet.coef_restitution;
		}
		if (is_colliding_with_ground(bullet, ground4))
		{
			if (fade == false) {
				if (bullet.y >= ground4.y + ground4.h) {
					// TP ball to ground surface
					bullet.y = ground4.y + ground4.h + bullet.radius;

					// Elastic bounce with ground
					bullet.vy = -bullet.vy;
				}
				if (bullet.y < ground4.y + ground4.h) {
					bullet.x = ground4.x - 0.2f;
					bullet.vx = bullet.vx * -1;
				}
			}
			
			if (fade == true) {
				bullet.x = -200;
			}

			// FUYM non-elasticity
			bullet.vx *= bullet.coef_friction;
			bullet.vy *= bullet.coef_restitution;
		}
		if (is_colliding_with_ground(bullet, ground6))
		{
			// TP ball to ground surface
			bullet.x = ground6.x + ground6.w + bullet.radius;
			bullet.vx= bullet.vx * -1;

			// Elastic bounce with ground
			

			// FUYM non-elasticity
			bullet.vx *= bullet.coef_friction;
			bullet.vy *= bullet.coef_restitution;
		}
		if (is_colliding_with_ground(bullet, ground7))
		{
			// TP ball to ground surface
			bullet.x = ground7.x - ground7.w + bullet.radius + 0.5f;
			bullet.vx = bullet.vx*-1;

			// FUYM non-elasticity
			bullet.vx *= bullet.coef_friction;
			bullet.vy *= bullet.coef_restitution;
		}
		if (is_colliding_with_ground(bullet, groundlife))
		{
			// TP ball to ground surface
			if (bullet.vx > 0) {
				if (lifep1.w < 5) { lifep1.w = lifep1.w + 1; }
				if (lifep1.w = 5) {continue;}
			}
			if (bullet.vx < 0) {
				if (lifep2.w < 5) { 
					lifep2.w = lifep2.w + 1;
					lifep2.x = lifep2.x - 1;
				}
				if (lifep2.w = 5) { continue; }
			}

			// FUYM non-elasticity
			bullet.vx *= bullet.coef_friction;
			bullet.vy *= bullet.coef_restitution;
		}
		if (is_colliding_with_bullet(bullet, players[0]))
		{
			if (damage == true) {
				lifep1.w = lifep1.w - 1.0f;
				damage = false;
			}
			if (fade == true) {
				bullet.x = -200;
			}
		}
		if (is_colliding_with_bullet(bullet, players[1]))
		{
			if (damage2 == true) {
				lifep2.w = lifep2.w - 1.0f;
				lifep2.x = lifep2.x + 1.0f;
				damage2 = false;
			}
			if (fade == true) {
				bullet.x = -200;
			}
		}
		if (lifep2.w <= 0.0f) {
			deathp2 = true;
		}
		if (lifep1.w <= 0.0f) {
			deathp1 = true;
		}
	}

	for (auto& player : players)
	{
		// Skip ball if physics not enabled
		if (!player.physics_enabled)
		{
			continue;
		}

		// Step #0: Clear old values
		// ----------------------------------------------------------------------------------------

		// Reset total acceleration and total accumulated force of the ball
		player.fx = player.fy = 0.0f;
		player.ax = player.ay = 0.0f;

		// Step #1: Compute forces
		// ----------------------------------------------------------------------------------------

		// Gravity force
		

		float fgx = player.mass * 0.0f;
		float fgy = player.mass * -10.0f; // Let's assume gravity is constant and downwards
		player.fx += fgx; player.fy += fgy; // Add this force to ball's total force
		

		// Aerodynamic Drag force (only when not in water)
		if (!is_colliding_with_water(player, water))
		{
			float fdx = 0.0f; float fdy = 0.0f;
			compute_aerodynamic_drag(fdx, fdy, player, atmosphere);
			player.fx += fdx; player.fy += fdy; // Add this force to ball's total force
		}
		

		// Hydrodynamic forces (only when in water)
		if (is_colliding_with_water(player, water))
		{
			// Hydrodynamic Drag force
			float fhdx = 0.0f; float fhdy = 0.0f;
			compute_hydrodynamic_drag(fhdx, fhdy, player, water);
			player.fx += fhdx; player.fy += fhdy; // Add this force to ball's total force

			// Hydrodynamic Buoyancy force
			float fhbx = 0.0f; float fhby = 0.0f;
			compute_hydrodynamic_buoyancy(fhbx, fhby, player, water);
			player.fx += fhbx; player.fy += fhby; // Add this force to ball's total force
		}

		// Other forces
		// ...

		// Step #2: 2nd Newton's Law
		// ----------------------------------------------------------------------------------------

		// SUM_Forces = mass * accel --> accel = SUM_Forces / mass
		player.ax = player.fx / player.mass;
		player.ay = player.fy / player.mass;

		// Step #3: Integrate --> from accel to new velocity & new position
		// ----------------------------------------------------------------------------------------

		// We will use the 2nd order "Velocity Verlet" method for integration.
		integrator_velocity_verlet(player, maxFrameDuration/1000);

		// Step #4: solve collisions
		// ----------------------------------------------------------------------------------------

		// Solve collision between ball and ground
		if (is_colliding_with_ground(player, ground))
		{
			// TP ball to ground surface
			player.y = ground.y + ground.h + player.radius;

			// Elastic bounce with ground
			player.vy = -player.vy;

			// FUYM non-elasticity
			player.vx *= player.coef_friction;
			player.vy *= player.coef_restitution;
		}
		if (is_colliding_with_ground(player, ground2))
		{
			// TP ball to ground surface
			player.y = ground2.y + ground2.h + player.radius;

			// Elastic bounce with ground
			player.vy = -player.vy;

			// FUYM non-elasticity
			player.vx *= player.coef_friction;
			player.vy *= player.coef_restitution;
		}
		if (is_colliding_with_ground(player, ground3))
		{
			// TP ball to ground surface
			player.y = ground3.y + ground3.h + player.radius;

			// Elastic bounce with ground
			player.vy = -player.vy;

			// FUYM non-elasticity
			player.vx *= player.coef_friction;
			player.vy *= player.coef_restitution;
		}
		if (is_colliding_with_ground(player, ground4))
		{
			// TP ball to ground surface
			player.y = ground4.y + ground4.h + player.radius;

			// Elastic bounce with ground
			player.vy = -player.vy;

			// FUYM non-elasticity
			player.vx *= player.coef_friction;
			player.vy *= player.coef_restitution;
		}
		if (is_colliding_with_ground(player, ground5))
		{
			// Elastic bounce with ground
			player.vy = -player.vy;

			// FUYM non-elasticity
			player.vx *= player.coef_friction;
			player.vy *= player.coef_restitution;
		}
		if (is_colliding_with_ground(player, ground6))
		{
			// TP ball to ground surface
			player.x = ground6.x + ground6.w + player.radius;

			// Elastic bounce with ground
			player.vy = 0;

			// FUYM non-elasticity
			player.vx *= player.coef_friction;
			player.vy *= player.coef_restitution;
		}
		if (is_colliding_with_ground(player, ground7))
		{
			// TP ball to ground surface
			player.x = ground7.x - ground7.w + player.radius;

			// Elastic bounce with ground
			player.vy = 0;

			// FUYM non-elasticity
			player.vx *= player.coef_friction;
			player.vy *= player.coef_restitution;
		}

		// FALL INTO WATER
		if (is_colliding_with_water(players[0], waterdeath))
		{
			lifep1.w = 0.0f;
			deathp1 = true;
		}
		if (is_colliding_with_water(players[1], waterdeath))
		{
			lifep2.w = 0.0f;
			deathp2 = true;
		}

		if (deathp1 == true) {
			App->player->timerdeathp1--;
		}

		if (deathp2 == true) {
			App->player->timerdeathp2--;
		}

	}

	if (groundlife.x < 5) {
		corazondireccion = 0;
	}
	if (groundlife.x > 10) {
		corazondireccion = 1;
	}
	if (corazondireccion == 0) {
		groundlife.x = groundlife.x + 0.01f;
	}

	// Continue game
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{
	//Background
	if (inicio == false && App->scene_intro->introscenes == false && App->scene_intro->win == false) {
		App->renderer->Blit(App->scene_intro->background, -340, 0);
		if (App->scene_intro->introscenes == true && App->scene_intro->win == true) {
			SDL_DestroyTexture(App->scene_intro->background);
		}
	}
	
	//Draw Heart

	if (corazondireccion == 1) {
		groundlife.x = groundlife.x - 0.01f;
	}

	App->renderer->Blit(App->scene_intro->heart, METERS_TO_PIXELS(groundlife.x), METERS_TO_PIXELS(groundlife.y));

	// Draw GUI Text
	App->renderer->BlitText("Gravity", 50, 30, 80, 30, { 255,255,255 });
	App->renderer->BlitText("Aerodynamic", 50, 60, 150, 30, { 255,255,255 });
	App->renderer->BlitText("Drag", 50, 90, 60, 30, { 255,255,255 });
	App->renderer->BlitText("Buoyancy", 50, 120, 110, 30, { 255,255,255 });
	App->renderer->BlitText("Shooting", 50, 150, 110, 30, { 255,255,255 });

	App->renderer->BlitText("grados p1:", 50, 180, 150, 30, { 255,255,255 });
	App->renderer->BlitText("grados p2:", 50, 210, 150, 30, { 255,255,255 });

	App->renderer->BlitText("Buonce Bullet:", 50, 240, 180, 30, { 255,255,255 });

	// Control GUI
	// Gravity Force
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		if (!gravitybool) gravitybool = true;
		else gravitybool = false;
	}

	if (gravitybool)
	{
		App->renderer->BlitText("Yes", 220, 30, 40, 30, { 0,255,0 });
	}

	else {
		App->renderer->BlitText("No", 220, 30, 35, 30, { 255,0,0 });
	}

	if (!fade)
	{
		App->renderer->BlitText("Yes", 240, 240, 40, 30, { 0,255,0 });
	}

	else {
		App->renderer->BlitText("No", 240, 240, 35, 30, { 255,0,0 });
	}

	if (App->player->laequis)
	{
		App->renderer->BlitText("Yes", 220, 150, 40, 30, { 0,255,0 });
	}

	else {
		App->renderer->BlitText("No", 220, 150, 35, 30, { 255,0,0 });
	}

	//Aerodynamic Force
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		if (!aerodragbool) aerodragbool = true;
		else aerodragbool = false;
	}

	if (aerodragbool)
	{
		App->renderer->BlitText("Yes", 220, 60, 40, 30, { 0,255,0 });
	}

	else {
		App->renderer->BlitText("No", 220, 60, 35, 30, { 255,0,0 });
	}

	//Hydrodynamic Drag Force
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		if (!hydrodragbool) hydrodragbool = true;
		else hydrodragbool = false;
	}

	if (hydrodragbool)
	{
		App->renderer->BlitText("Yes", 220, 90, 40, 30, { 0,255,0 });
	}

	else {
		App->renderer->BlitText("No", 220, 90, 35, 30, { 255,0,0 });
	}

	//Hydrodynamic Buoyancy Force
	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN) {
		if (!buoyancybool) buoyancybool = true;
		else buoyancybool = false;
	}

	if (buoyancybool)
	{
		App->renderer->BlitText("Yes", 220, 120, 40, 30, { 0,255,0 });
	}

	else {
		App->renderer->BlitText("No", 220, 120, 35, 30, { 255,0,0 });
	}
	
	// Draw world collisions
	if (showcollisions == 0 && App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		showcollisions = 1;
	}

	if (showcollisions == 1 && App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) {
		showcollisions = 0;
	}

	//Draw Setas
	App->renderer->Blit(App->scene_intro->seta, 0, 0);

	// Colors
	int color_r, color_g, color_b;

	// Draw ground
	if (showcollisions == 1) {
		color_r = 0; color_g = 255; color_b = 0;
		App->renderer->DrawQuad(ground.pixels(), color_r, color_g, color_b);

		color_r = 0; color_g = 255; color_b = 0;
		App->renderer->DrawQuad(ground2.pixels(), color_r, color_g, color_b);

		color_r = 0; color_g = 255; color_b = 0;
		App->renderer->DrawQuad(ground3.pixels(), color_r, color_g, color_b);

		color_r = 0; color_g = 255; color_b = 0;
		App->renderer->DrawQuad(ground4.pixels(), color_r, color_g, color_b);

		color_r = 128; color_g = 64; color_b = 0;
		App->renderer->DrawQuad(ground5.pixels(), color_r, color_g, color_b);

		color_r = 0; color_g = 255; color_b = 0;
		App->renderer->DrawQuad(ground6.pixels(), color_r, color_g, color_b);

		color_r = 0; color_g = 255; color_b = 0;
		App->renderer->DrawQuad(ground7.pixels(), color_r, color_g, color_b);

		color_r = 255; color_g = 0; color_b = 0;
		App->renderer->DrawQuad(groundlife.pixels(), color_r, color_g, color_b);

		// Draw water
		color_r = 255; color_g = 139; color_b = 15;
		App->renderer->DrawQuad(water.pixels(), color_r, color_g, color_b);

		color_r = 255; color_g = 75; color_b = 15;
		App->renderer->DrawQuad(waterdeath.pixels(), color_r, color_g, color_b);
	}

	//Draw life
	App->renderer->BlitText("Player 1", 16, 693, 70, 20, { 0,0,0 });
	App->renderer->BlitText("Player 2", 934, 693, 70, 20, { 0,0,0 });

	color_r = 0; color_g = 0; color_b = 0;
	App->renderer->DrawQuad(borde.pixels(), color_r, color_g, color_b);

	color_r = 0; color_g = 0; color_b = 0;
	App->renderer->DrawQuad(borde2.pixels(), color_r, color_g, color_b);

	color_r = 55; color_g = 55; color_b = 55;
	App->renderer->DrawQuad(lifep1g.pixels(), color_r, color_g, color_b);

	color_r = 55; color_g = 55; color_b = 55;
	App->renderer->DrawQuad(lifep2g.pixels(), color_r, color_g, color_b);

	color_r = 255; color_g = 0; color_b = 0;
	App->renderer->DrawQuad(lifep1.pixels(), color_r, color_g, color_b);

	color_r = 255; color_g = 0; color_b = 0;
	App->renderer->DrawQuad(lifep2.pixels(), color_r, color_g, color_b);

	//draw degree bar
	color_r = 54; color_g = 78; color_b = 255;
	App->renderer->DrawQuad(degree2.pixels(), color_r, color_g, color_b);

	color_r = 255; color_g = 200; color_b = 0;
	App->renderer->DrawQuad(degree1.pixels(), color_r, color_g, color_b);

	// Draw Boat
	color_r = 200; color_g = 100; color_b = 40;

	//Draw time bars
	color_r = 255; color_g = 205; color_b = 53;
	App->renderer->DrawQuad(barp1.pixels(), color_r, color_g, color_b);

	color_r = 54; color_g = 78; color_b = 255;
	App->renderer->DrawQuad(barp2.pixels(), color_r, color_g, color_b);
	

	 //Draw all balls in the scenario
	for (auto& ball : balls)
	{
		// Convert from physical magnitudes to geometrical pixels
		int pos_x = METERS_TO_PIXELS(ball.x);
		int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS(ball.y);
		int size_r = METERS_TO_PIXELS(ball.radius);

		// Select color
		if (ball.physics_enabled)
		{
			color_r = 255; color_g = 255; color_b = 255;
		}
		else
		{
			color_r = 255; color_g = 0; color_b = 0;
		}
	}

	for (auto& bullet : bullets)
	{
		// Convert from physical magnitudes to geometrical pixels
		int pos_x = METERS_TO_PIXELS(bullet.x);
		int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS(bullet.y);
		int size_r = METERS_TO_PIXELS(bullet.radius);

		// Select color
		if (bullet.physics_enabled)
		{
			color_r = 255; color_g = 255; color_b = 255;
		}
		else
		{
			color_r = 255; color_g = 0; color_b = 0;
		}

		// Draw ball
		if (App->player->laequis) {
			App->renderer->DrawCircle(pos_x, pos_y, size_r, color_r, color_g, color_b);
		}

	}

	for (auto& player : players)
	{
		// Convert from physical magnitudes to geometrical pixels
		int pos_x = METERS_TO_PIXELS(player.x);
		int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS(player.y);
		int size_r = METERS_TO_PIXELS(player.radius);

		// Select color
		if (player.physics_enabled)
		{
			color_r = 255; color_g = 255; color_b = 255;
		}
		else
		{
			color_r = 255; color_g = 0; color_b = 0;
		}

		// Draw ball

		App->renderer->DrawCircle(pos_x, pos_y, size_r, color_r, color_g, color_b);
	}

	for (auto& player2 : players)
	{
		// Convert from physical magnitudes to geometrical pixels
		int pos_x = METERS_TO_PIXELS(player2.x);
		int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS(player2.y);
		int size_r = METERS_TO_PIXELS(player2.radius);

		// Select color
		if (player2.physics_enabled)
		{
			color_r = 255; color_g = 255; color_b = 255;
		}
		else
		{
			color_r = 255; color_g = 0; color_b = 0;
		}

		// Draw ball
		App->renderer->DrawCircle(pos_x, pos_y, size_r, color_r, color_g, color_b);
	}

	if (disparo == 0) {
		int x = App->physics->players[0].x;
		int y = App->physics->players[0].y-700;
		float r = 0.5f;
		direction = 45;
		shootx = METERS_TO_PIXELS(players[0].x);
		shooty = -METERS_TO_PIXELS(players[0].y - 740);
		App->renderer->DrawCircle(x, y, r, 255, 100, 100);


	}
	
	if (App->player->timerdeathp1 <= 0) {
		App->renderer->Blit(App->scene_intro->deathplayer1, 0, 0);
		App->scene_intro->win = true;
	}
	if (App->player->timerdeathp2 <= 0) {
		App->renderer->Blit(App->scene_intro->deathplayer2, 0, 0);
		App->scene_intro->win = true;
	}



	//Scenes Intro
	if (inicio == true) {
		App->renderer->Blit(App->scene_intro->scenelogo, 0, 0);

		color_r = 255; color_g = 255; color_b = 255;
		App->renderer->DrawQuad(bar.pixels(), color_r, color_g, color_b);
		bar.w++;

		timerintro--;
	}

	if (timerintro <= 0) {
		bar.w = 0.0f;
		App->renderer->Blit(App->scene_intro->scenegame, 0, 0);
		SDL_DestroyTexture(App->scene_intro->scenelogo);
		App->scene_intro->scenelogo = App->textures->Load("Assets/Scenes/OurLogo.png");
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			SDL_DestroyTexture(App->scene_intro->scenegame);
			App->scene_intro->scenegame = App->textures->Load("Assets/Scenes/GameScene.png");
			inicio = false;
			App->scene_intro->introscenes = false;
			timerintro = 100;
		}
	}

	//if (corazonx >= 800) {
	//	corazondireccion = 1;
	//}
	//if (corazonx <= 190) {
	//	corazondireccion = 0;
	//}

	if (inicio == false) {
		App->player->timerplayer1--;
	}

	if (App->scene_intro->introscenes == true && App->scene_intro->win==false) {
		App->renderer->Blit(App->scene_intro->scenegame, 0, 0);
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			SDL_DestroyTexture(App->scene_intro->scenegame);
			App->scene_intro->scenegame = App->textures->Load("Assets/Scenes/GameScene.png");
			inicio = false;
			App->scene_intro->introscenes = false;
		}
	}

	//Delta Time
	// 
	// Amount of frames since startup

	frameCount++;

	// Amount of time since game start (use a low resolution timer)

	secondsSinceStartup = startupTime.ReadSec();

	// Amount of ms took the last update

	dt = frameTime.ReadMSec();

	// Amount of frames during the last second

	lastSecFrameCount++;

	if (lastSecFrameTime.ReadMSec() > 1000) {

		lastSecFrameTime.Start();

		framesPerSecond = lastSecFrameCount;

		lastSecFrameCount = 0;

		// Average FPS for the whole game life

		averageFps = (averageFps + framesPerSecond) / 2;

	}

	float delay = float(maxFrameDuration) - dt;

	PerfTimer delayTimer = PerfTimer();

	delayTimer.Start();

	if (maxFrameDuration > 0 && delay > 0) {

		SDL_Delay(delay);

		LOG("We waited for %f milliseconds and the real delay is % f", delay, delayTimer.ReadMs());

		dt = maxFrameDuration;

	}

	// Shows the time measurements in the window title

	static char title[256];

	sprintf_s(title, 256, "Av.FPS: %.2f Last sec frames: %i Last dt: %.3f Time since startup: %.3f Frame Count: %I64u ",
		averageFps, framesPerSecond, dt, secondsSinceStartup, frameCount);

	App->window->SetTitle(title);

	// Change FPS Delta Time
	
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN) {
		maxFrameDuration = 33;
	}

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		maxFrameDuration = 16;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		maxFrameDuration = 11;
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	return true;
}

// Compute modulus of a vector
float modulus(float vx, float vy)
{
	return std::sqrt(vx * vx + vy * vy);
}


// Compute Aerodynamic Drag force
void compute_aerodynamic_drag(float &fx, float& fy, const PhysBall &ball, const Atmosphere &atmosphere)
{
	float rel_vel[2] = { ball.vx - atmosphere.windx, ball.vy - atmosphere.windy }; // Relative velocity
	float speed = modulus(rel_vel[0], rel_vel[1]); // Modulus of the relative velocity
	float rel_vel_unitary[2] = { rel_vel[0] / speed, rel_vel[1] / speed }; // Unitary vector of relative velocity
	float fdrag_modulus = 0.5f * atmosphere.density * speed * speed * ball.surface * ball.cd; // Drag force (modulus)
	fx = -rel_vel_unitary[0] * fdrag_modulus; // Drag is antiparallel to relative velocity
	fy = -rel_vel_unitary[1] * fdrag_modulus; // Drag is antiparallel to relative velocity
}

// Compute Hydrodynamic Drag force
void compute_hydrodynamic_drag(float& fx, float& fy, const PhysBall& ball, const Water& water)
{
	float rel_vel[2] = { ball.vx - water.vx, ball.vy - water.vy }; // Relative velocity
	float speed = modulus(rel_vel[0], rel_vel[1]); // Modulus of the relative velocity
	float rel_vel_unitary[2] = { rel_vel[0] / speed, rel_vel[1] / speed }; // Unitary vector of relative velocity
	float fdrag_modulus = ball.b * speed; // Drag force (modulus)
	fx = -rel_vel_unitary[0] * fdrag_modulus; // Drag is antiparallel to relative velocity
	fy = -rel_vel_unitary[1] * fdrag_modulus; // Drag is antiparallel to relative velocity
}

// Compute Hydrodynamic Buoyancy force
void compute_hydrodynamic_buoyancy(float& fx, float& fy, const PhysBall& ball, const Water& water)
{
	// Compute submerged area (assume ball is a rectangle, for simplicity)
	float water_top_level = water.y + water.h; // Water top level y
	float h = 2.0f * ball.radius; // Ball "hitbox" height
	float surf = h * (water_top_level - ball.y); // Submerged surface
	if ((ball.y + ball.radius) < water_top_level) surf = h * h; // If ball completely submerged, use just all ball area
	surf *= 0.4; // FUYM to adjust values (should compute the area of circle segment correctly instead; I'm too lazy for that)

	// Compute Buoyancy force
	double fbuoyancy_modulus = water.density * 10.0 * surf; // Buoyancy force (modulus)
	fx = 0.0; // Buoyancy is parallel to pressure gradient
	fy = fbuoyancy_modulus; // Buoyancy is parallel to pressure gradient
}

// Integration scheme: Velocity Verlet
void integrator_velocity_verlet(PhysBall& ball, float dt)
{
	ball.x += ball.vx * dt + 0.05f * ball.ax * dt * dt;
	ball.y += ball.vy * dt + 0.2f * ball.ay * dt * dt;
	ball.vx += ball.ax * dt;
	ball.vy += ball.ay * dt;
}

// Detect collision with ground
bool is_colliding_with_ground(const PhysBall& ball, const Ground& ground)
{
	float rect_x = (ground.x + ground.w / 2.0f); // Center of rectangle
	float rect_y = (ground.y + ground.h / 2.0f); // Center of rectangle
	return check_collision_circle_rectangle(ball.x, ball.y, ball.radius, rect_x, rect_y, ground.w, ground.h);
}

// Detect collision with water
bool is_colliding_with_water(const PhysBall& ball, const Water& water)
{
	float rect_x = (water.x + water.w / 2.0f); // Center of rectangle
	float rect_y = (water.y + water.h / 2.0f); // Center of rectangle
	return check_collision_circle_rectangle(ball.x, ball.y, ball.radius, rect_x, rect_y, water.w, water.h);
}

// Detect collision with bullet
bool is_colliding_with_bullet(const PhysBall& player, const PhysBall& bullet)
{
	return check_collision_circle_circle(bullet.x, bullet.y, bullet.radius, player.x, player.y, player.radius);
}

// Detect collision between circle and rectange
bool check_collision_circle_rectangle(float cx, float cy, float cr, float rx, float ry, float rw, float rh)
{
	// Algorithm taken from https://stackoverflow.com/a/402010

	// Distance from center of circle to center of rectangle
	float dist_x = std::abs(cx - rx);
	float dist_y = std::abs(cy - ry);

	// If circle is further than half-rectangle, not intersecting
	if (dist_x > (rw / 2.0f + cr)) { return false; }
	if (dist_y > (rh / 2.0f + cr)) { return false; }

	// If circle is closer than half-rectangle, is intersecting
	if (dist_x <= (rw / 2.0f)) { return true; }
	if (dist_y <= (rh / 2.0f)) { return true; }

	// If all of above fails, check corners
	float a = dist_x - rw / 2.0f;
	float b = dist_y - rh / 2.0f;
	float cornerDistance_sq = a * a + b * b;
	return (cornerDistance_sq <= (cr * cr));
}

bool check_collision_circle_circle(float cx, float cy, float cr, float c2x, float c2y, float c2r)
{
	// Algorithm taken from https://stackoverflow.com/a/402010

	// Distance from center of circle to center of rectangle
	float dist_x = std::abs(cx - c2x);
	float dist_y = std::abs(cy - c2y);

	// If circle is further than half-rectangle, not intersecting
	if (dist_x > (c2r + cr)) { return false; }
	if (dist_y > (c2r + cr)) { return false; }

	// If circle is closer than half-rectangle, is intersecting
	if (dist_x <= (c2r)) { return true; }
	if (dist_y <= (c2r)) { return true; }
}

// Convert from meters to pixels (for SDL drawing)
SDL_Rect Ground::pixels()
{
	SDL_Rect pos_px{};
	pos_px.x = METERS_TO_PIXELS(x);
	pos_px.y = SCREEN_HEIGHT - METERS_TO_PIXELS(y);
	pos_px.w = METERS_TO_PIXELS(w);
	pos_px.h = METERS_TO_PIXELS(-h); // Can I do this? LOL
	return pos_px;
}
