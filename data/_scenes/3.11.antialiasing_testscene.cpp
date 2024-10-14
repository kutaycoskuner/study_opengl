#pragma once
// ----------------------------------------------------------------------------
// ----- libraries
// ----------------------------------------------------------------------------
#include "../../headers/data/scenes.h"
#include "../../headers/utils/utilities.h"
#include <cmath>
#include <ctime>

// ----------------------------------------------------------------------------
// ----- forward declarations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----- abstract
// ----------------------------------------------------------------------------
void AntiAliasingTestScene::loadData()
{
	scene_state.animation_stage = 1;
	scene_state.animate = true;
	scene_state.emission_factor = 10.0f;
	scene_state.shininess = 32.0f;
	scene_state.vertex_divider = 9.0f;
	scene_state.model_shader_name = "diffuse";
	scene_state.display_skybox = false;
	scene_state.display_normals = false;
	scene_state.display_axes = false;
	scene_state.using_computed_data = false;
	scene_state.draw_instanced = false;
	//scene_state.b_model_refraction		= true;


	// ----- camera position
	Camera& cam = cameras[0];
	cam.position = Vec3(0.0f, 1.0f, 3.0f);
	cam.lookAtTarget(Vec3(0.0f, 0.0f, 0.0f));
	//cam.lookAtDirection(Vec3(0.0f, 0.0f, -1.0f));
	//cam.position	= Vec3(-0.57f, 0.815f, -0.046f);
	//cam.yaw_rad		= -1.527f;
	//cam.pitch_rad	= -0.276f;
	//cam.fov			= 45.0f;
	// normal cam
	//cam.position = Vec3(0.0f, 0.0f, 10.0f);

	// ----- define lights
	//// directional
	//directional_lights.push_back(PredefSceneLights::d_light);
	//// point
	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights[0].brightness = 0.4f;
	//point_lights[1].brightness = 0.4f;
	//point_lights[2].brightness = 0.4f;
	//// spot
	//spot_lights.push_back(PredefSceneLights::s_light);
	//spot_lights[0].brightness = 0.1f;

	// ----- define predefined elements
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::small_plane);
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::points);
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::single_cube);
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane);
	predefined_scene_elements[0].transform.position = Vec3(-0.8f, 0.0f, 0.0f);
	predefined_scene_elements[0].transform.rotation = Vec3(0.0f, 25.0f, 0.0f);

	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane);
	predefined_scene_elements[1].transform.position = Vec3(0.8f, 0.0f, 0.0f);
	predefined_scene_elements[1].transform.rotation = Vec3(0.0f, -25.0f, 0.0f);
	predefined_scene_elements[1].shader_name = "pink";

	//predefined_scene_elements.push_back(PrimitiveSceneNodes::paircube1);
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::paircube2);

	// ----- define model paths
	model_paths = {
		//{ "models/out_jupiter_by_murilo.kleine/jupiter_self.obj" }
		//"models/testobject0_frustum/testobject.obj"
		//,"models/testobject1_dodecahedron/testobject.obj"
		//,"models/testobject2_sphere/testobject.obj"
		//,"models/testobject3_cube0/testobject.obj"
		//,"models/testobject4_cube1/testobject.obj"
		//,"models/testobject5_cube2/testobject.obj"
		//,"models/testobject6_cube3/testobject.obj"
		//,"models/testobject7_torus/testobject.obj"
		//,"models/testobject8_mine/testobject.obj"
		//,"models/testobject9_cylinder/testobject.obj"
		//,"models/testobject10_suzanne/testobject.obj"
		//,"models/testobject11_cone/testobject.obj"
		//{"models/out_backpack_by_berkgedik/backpack.obj"}
		//{"models/out_kokorecci_by_berkgedik/out_kokorecci_by_berk gedik2.obj"}
	};

	// ----- create bools for each imported model
	for (int i = 0; i < model_paths.size(); i++) {
		scene_state.model_element_bools.push_back(
			ElementBools(
				false,		// wireframe_mode
				false,		// depth testing
				false,		// stencil testing
				false,		// blending
				false,		// partial render
				false		// is indexed
			)
		);
	}

	// ----- generate computed data

	// ----- define texture names
	texture_names = { "out_container2", "linegrid_2k_darkgray", "grid_2k_white" };


	// ----- specific position
	scene_state.time_pin = scene_state.time;
}

void AntiAliasingTestScene::update() {

	// emission pulse/breath
	// --------------------------------------------------------------------------------------
	float time = scene_state.time;
	float sint = sin(scene_state.time);
	float cost = cos(scene_state.time);
	float sint10 = sin(scene_state.time + 1.0f) * .5f;

	scene_state.emission_factor = sint10 * 0.4f;

	// move camera
	// --------------------------------------------------------------------------------------
	/*float camera_pos_multiplier = 80.0f;
	cameras[0].position.y = 25.0f;
	cameras[0].position = Vec3(camera_pos_multiplier * cost, cameras[0].position.y, camera_pos_multiplier * sint);
	cameras[0].lookAtTarget(Vec3(0.0f, 4.0f, 0.0f))*/;
	//cameras[0].yaw_rad = 1.0f;

	// move lights radial
	// --------------------------------------------------------------------------------------
	float distance_multiplier = 3.0f;
	const float pi = 3.141592f;
	for (int ii = 0; ii < point_lights.size(); ii++)
	{
		// change light position
		point_lights[ii].position = Vec3(
			distance_multiplier * cos(scene_state.time + 2 * pi / point_lights.size() * ii),
			3.0f,
			distance_multiplier * sin(scene_state.time + 2 * pi / point_lights.size() * ii))
			;

		// change light color
		float change_key = scene_state.time + ii;
		setTriangleLightColorShiftByTime(point_lights[ii].diffuse, point_lights[ii].specular, change_key);
	}


	// rotate obj x z 
	// --------------------------------------------------------------------------------------

	// move objects
	// --------------------------------------------------------------------------------------
	float waiting_delay = 4.0f;
	if (scene_state.animation_stage == 1)
	{
		scene_state.tant = 0.0f;
		if (scene_state.time > scene_state.time_pin + waiting_delay)
		{
			scene_state.time_difference = scene_state.time - scene_state.time_pin;
			scene_state.animation_stage += 1;
		}
	}
	else if (scene_state.animation_stage == 2)
	{
		scene_state.tant = abs(tan(scene_state.time - scene_state.time_difference));

		if (scene_state.tant > 6.0f)
		{
			scene_state.tant = 2000.0f;
			scene_state.time_pin = scene_state.time;
			scene_state.animation_stage += 1;
		}
	}
	else if (scene_state.animation_stage == 3)
	{
		scene_state.tant = 2000.0f;
		if (scene_state.time > scene_state.time_pin + waiting_delay - .8f)
		{
			scene_state.time_difference = scene_state.time - scene_state.time_pin;
			scene_state.animation_stage += 1;
		}
	}
	else if (scene_state.animation_stage == 4)
	{
		scene_state.tant = abs(tan(scene_state.time));

		if (scene_state.tant < 0.05f)
		{
			scene_state.tant = 0.0f;
			scene_state.time_pin = scene_state.time;
			scene_state.animation_stage = 1;
		}
	}

	// sort objects
	// --------------------------------------------------------------------------------------


}

AntiAliasingTestScene::AntiAliasingTestScene() {
}


