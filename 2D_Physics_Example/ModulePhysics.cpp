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
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

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

	ground5 = Ground();
	ground5.x = 20.0f; // [m]
	ground5.y = 25.0f; // [m]
	ground5.w = 10.0f; // [m]
	ground5.h = 1.0f; // [m]

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
	bool gravitybool = true;
	bool aerodragbool = true;
	bool hydrodragbool = true;
	bool buoyancybool = true;

	return true;
}

update_status ModulePhysics::PreUpdate()
{
	// Process all balls in the scenario
	for (auto& ball : balls)
	{
		// Skip ball if physics not enabled
		if (!ball.physics_enabled)
		{
			continue;
		}

		// Step #0: Clear old values
		// ----------------------------------------------------------------------------------------
		
		// Reset total acceleration and total accumulated force of the ball
		ball.fx = ball.fy = 0.0f;
		ball.ax = ball.ay = 0.0f;

		// Step #1: Compute forces
		// ----------------------------------------------------------------------------------------

		// Gravity force
		float fgx = ball.mass * 0.0f;
		float fgy = ball.mass * -10.0f; // Let's assume gravity is constant and downwards
		ball.fx += fgx; ball.fy += fgy; // Add this force to ball's total force

		// Aerodynamic Drag force (only when not in water)
		if (!is_colliding_with_water(ball, water))
		{
			float fdx = 0.0f; float fdy = 0.0f;
			compute_aerodynamic_drag(fdx, fdy, ball, atmosphere);
			ball.fx += fdx; ball.fy += fdy; // Add this force to ball's total force
		}

		// Hydrodynamic forces (only when in water)
		if (is_colliding_with_water(ball, water))
		{
			// Hydrodynamic Drag force
			float fhdx = 0.0f; float fhdy = 0.0f;
			compute_hydrodynamic_drag(fhdx, fhdy, ball, water);
			ball.fx += fhdx; ball.fy += fhdy; // Add this force to ball's total force

			// Hydrodynamic Buoyancy force
			float fhbx = 0.0f; float fhby = 0.0f;
			compute_hydrodynamic_buoyancy(fhbx, fhby, ball, water);
			ball.fx += fhbx; ball.fy += fhby; // Add this force to ball's total force
		}

		// Other forces
		// ...

		// Step #2: 2nd Newton's Law
		// ----------------------------------------------------------------------------------------
		
		// SUM_Forces = mass * accel --> accel = SUM_Forces / mass
		ball.ax = ball.fx / ball.mass;
		ball.ay = ball.fy / ball.mass;

		// Step #3: Integrate --> from accel to new velocity & new position
		// ----------------------------------------------------------------------------------------

		// We will use the 2nd order "Velocity Verlet" method for integration.
		integrator_velocity_verlet(ball, dt);

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
		if (is_colliding_with_ground(ball, ground5))
		{

			// Elastic bounce with ground
			ball.vy = -ball.vy;

			// FUYM non-elasticity
			ball.vx *= ball.coef_friction;
			ball.vy *= ball.coef_restitution;
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
		
		if (gravitybool) 
		{
			float fgx = player.mass * 0.0f;
			float fgy = player.mass * -10.0f; // Let's assume gravity is constant and downwards
			player.fx += fgx; player.fy += fgy; // Add this force to ball's total force
		}

		// Aerodynamic Drag force (only when not in water)
		
		if (aerodragbool) 
		{
			if (!is_colliding_with_water(player, water))
			{
				float fdx = 0.0f; float fdy = 0.0f;
				compute_aerodynamic_drag(fdx, fdy, player, atmosphere);
				player.fx += fdx; player.fy += fdy; // Add this force to ball's total force
			}
		}

		// Hydrodynamic forces (only when in water)
		if (is_colliding_with_water(player, water))
		{
			
			if (hydrodragbool) 
			{
				// Hydrodynamic Drag force
				float fhdx = 0.0f; float fhdy = 0.0f;
				compute_hydrodynamic_drag(fhdx, fhdy, player, water);
				player.fx += fhdx; player.fy += fhdy; // Add this force to ball's total force
			}

			
			if (buoyancybool)
			{
				// Hydrodynamic Buoyancy force
				float fhbx = 0.0f; float fhby = 0.0f;
				compute_hydrodynamic_buoyancy(fhbx, fhby, player, water);
				player.fx += fhbx; player.fy += fhby; // Add this force to ball's total force
			}
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
		integrator_velocity_verlet(player, dt);

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
	}

	// Continue game
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{
	// Draw Text
	App->renderer->BlitText("Prueba GUI", 50, 50, 150, 30, { 255,255,0 });
	App->renderer->BlitText("Prueba GUI 2", 50, 80, 150, 30, { 255,255,0 });
	 
	// Colors
	int color_r, color_g, color_b;

	// Draw ground
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

	// Draw water
	color_r = 0; color_g = 0; color_b = 255;
	App->renderer->DrawQuad(water.pixels(), color_r, color_g, color_b);

	// Draw Boat
	color_r = 200; color_g = 100; color_b = 40;
	

	 //Draw all balls in the scenario
	//for (auto& ball : balls)
	//{
	//	// Convert from physical magnitudes to geometrical pixels
	//	int pos_x = METERS_TO_PIXELS(ball.x);
	//	int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS(ball.y);
	//	int size_r = METERS_TO_PIXELS(ball.radius);

	//	// Select color
	//	if (ball.physics_enabled)
	//	{
	//		color_r = 255; color_g = 255; color_b = 255;
	//	}
	//	else
	//	{
	//		color_r = 255; color_g = 0; color_b = 0;
	//	}

	//	// Draw ball
	//	App->renderer->DrawCircle(pos_x, pos_y, size_r, color_r, color_g, color_b);
	//}

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
		shootx = METERS_TO_PIXELS(App->physics->players[0].x);
		shooty = METERS_TO_PIXELS(App->physics->players[0].y + 120);
		App->renderer->DrawCircle(x, y, r, 255, 100, 100);
	}
	if(disparo == 1){

		float r = METERS_TO_PIXELS(0.2f);
		float fuerza = 0.4f;
		direction -= -0.01f;
		shootx += METERS_TO_PIXELS(fuerza * sin(direction));
		shooty += -METERS_TO_PIXELS(fuerza * cos(direction));

		App->renderer->DrawCircle(shootx, shooty, r, 255, 100, 100);
		
	}

	if (disparo2 == 0) {
		int x = App->physics->players[0].x;
		int y = App->physics->players[0].y - 700;
		float r = 0.5f;
		direction2 = 45;
		shootx2 = METERS_TO_PIXELS(App->physics->players[0].x);
		shooty2 = METERS_TO_PIXELS(App->physics->players[0].y + 120);
		App->renderer->DrawCircle(x, y, r, 255, 100, 100);
	}
	if (disparo2 == 1) {

		float r = METERS_TO_PIXELS(0.2f);
		float fuerza = -0.4f;
		direction2 += 0.01f;
		shootx2 += METERS_TO_PIXELS(fuerza * sin(direction2));
		shooty2 += METERS_TO_PIXELS(fuerza * cos(direction2));

		App->renderer->DrawCircle(shootx2, shooty2, r, 255, 100, 100);

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
