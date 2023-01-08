#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>
#include "Timer.h"
#include "PerfTimer.h"


#define PIXELS_PER_METER (20.0f) // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL (1.0f / PIXELS_PER_METER) // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) std::floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


// Class: Ball object (a simple stoopid physics object)
class PhysBall
{
public:
	PhysBall() {}

	PhysBall(float mass, float surface, float radius, float cd, float cl, float b, float coef_friction, float coef_restitution, float x, float y, float vx, float vy, int color_r, int color_g, int color_b) {

		// Set static properties of the ball
		this->mass = mass; // [kg]
		this->surface = surface; // [m^2]
		this->radius = radius; // [m]
		this->cd = cd; // [-]
		this->cl = cl; // [-]
		this->b = b; // [...]
		this->coef_friction = coef_friction; // [-]
		this->coef_restitution = coef_restitution; // [-]

		// Set initial position and velocity of the ball
		this->x = x;
		this->y = y;
		this->vx = vx;
		this->vy = vy;

		// Set color of the ball

		this->Red = color_r;
		this->Green = color_g;
		this->Blue = color_b;

	}

	// Colours bullet
	int Red;
	int Green;
	int Blue;

	// Position
	// You could also use an array/vector
	float x;
	float y;

	// Velocity
	float vx;
	float vy;

	// Acceleration
	float ax;
	float ay;

	// Force (total) applied to the ball
	float fx;
	float fy;

	// Mass
	float mass;

	// Aerodynamics stuff
	float surface; // Effective wet surface
	float cl; // Aerodynamic Lift coefficient
	float cd; // Aerodynamic Drag coefficient
	float b; // Hydrodynamic Drag coefficient

	// Coefficients of friction & restitution (for bounces)
	float coef_friction;
	float coef_restitution;

	// Shape
	float radius;

	// Has physics enabled?
	bool physics_enabled = true;
};

class PhysRect
{
public:
	// Position
	// You could also use an array/vector
	float x;
	float y;

	// Velocity
	float vx;
	float vy;

	// Acceleration
	float ax;
	float ay;

	// Force (total) applied to the ball
	float fx;
	float fy;

	// Mass
	float mass;

	// Aerodynamics stuff
	float surface; // Effective wet surface
	float cl; // Aerodynamic Lift coefficient
	float cd; // Aerodynamic Drag coefficient
	float b; // Hydrodynamic Drag coefficient

	// Coefficients of friction & restitution (for bounces)
	float coef_friction;
	float coef_restitution;

	// Shape
	float width;
	float height;

	// Has physics enabled?
	bool physics_enabled = true;
};

// Class: Ground
class Ground : public SDL_Rect
{
public:
	float x,y,w,h; // Geometry (x,y,w,h)
	SDL_Rect pixels(); // Convert geometry to pixels to draw w/ SDL
};

// Class: Water
class Water : public Ground
{
public:
	float density; // Density of fluid
	float vx; // Velocity x
	float vy; // Velocity y
};

// Class: Atmosphere
class Atmosphere
{
public:
	float density; // Density of air
	float windx; // Wind x
	float windy; // Wind y
};



class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	// Physics objects
	std::vector<PhysBall> balls{};
	std::vector<PhysBall> players{};
	std::vector<PhysBall> bullets{};
	Atmosphere atmosphere{};
	Ground ground{};
	Ground ground2{};
	Water water{};
	Water waterdeath{};
	Ground ground3{};
	Ground ground4{};
	Ground ground5{};
	Ground ground6{};
	Ground ground7{};
	Ground groundlife{};
	
	//Loading bar
	Ground bar{};

	//Time Bars
	Ground barp1{};
	Ground barp2{};

	//Life
	Ground lifep1{};
	Ground lifep2{};
	Ground lifep1g{};
	Ground lifep2g{};
	Ground borde{};
	Ground borde2{};

	//degree bar:
	Ground degree1{};
	Ground degree2{};

	bool deathp1 = false;
	bool deathp2 = false;

	bool inicio = true;

	int timerintro = 100;

	int corazonx = 190;
	int corazony = 67;
	bool corazondireccion = 0;

	bool damage = true;
	bool damage2 = false;

	bool fade = false;
	// Misc
	float dt;
	uint frames;
	bool disparo = 0;
	bool disparo2 = 0;
	float shootx = 0;
	float shooty = 0;
	float shootx2 = 0;
	float shooty2 = 0;
	float direction = 0;
	float direction2 = 0;
	float menosdirection = 0;
	float masdirection = 0;
	int showcollisions = 0;

	// Bool GUI
	bool gravitybool = true;
	bool aerodragbool = true;
	bool hydrodragbool = true;
	bool buoyancybool = true;
	bool aux;


private:

	bool debug;
	Timer timer;
	PerfTimer ptimer;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	float averageFps = 0.0f;
	float secondsSinceStartup = 0.0f;

	float maxFrameDuration = 0;
};

// Compute modulus of a vector
float modulus(float vx, float vy);

// Compute Aerodynamic Drag force
void compute_aerodynamic_drag(float& fx, float& fy, const PhysBall& ball, const Atmosphere& atmosphere);

// Compute Hydrodynamic Drag force
void compute_hydrodynamic_drag(float& fx, float& fy, const PhysBall& ball, const Water& water);

// Compute Hydrodynamic Buoyancy force
void compute_hydrodynamic_buoyancy(float& fx, float& fy, const PhysBall& ball, const Water& water);

// Integration scheme: Velocity Verlet
void integrator_velocity_verlet(PhysBall& ball, float dt);

// Detect collision with ground
bool is_colliding_with_ground(const PhysBall& ball, const Ground& ground);

// Detect collision with water
bool is_colliding_with_water(const PhysBall& ball, const Water& water);

// Detect collision with bullet
bool is_colliding_with_bullet(const PhysBall& player, const PhysBall& bullet);

// Detect collision between circle and rectange
bool check_collision_circle_rectangle(float cx, float cy, float cr, float rx, float ry, float rw, float rh);

bool check_collision_circle_circle(float cx, float cy, float cr, float c2x, float c2y, float c2r);


