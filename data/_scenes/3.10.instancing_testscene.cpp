#pragma once
// ----------------------------------------------------------------------------
// ----- libraries
// ----------------------------------------------------------------------------
#include "../../source/headers/data/scene_data.h"
#include "../../source/headers/utils/utilities.h"
#include <cmath>
#include <ctime>

// ----------------------------------------------------------------------------
// ----- forward declarations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----- abstract
// ----------------------------------------------------------------------------
void InstancingTestScene::loadData()
{
	scene_state.animation_stage			= 1;
	scene_state.animate					= true;
	scene_state.emission_factor			= 10.0f;
	scene_state.shininess				= 32.0f;
	scene_state.vertex_divider			= 9.0f;
	scene_state.display_skybox			= true;
        scene_state.model_shader_id                             = ShaderID::Diffuse;
	scene_state.display_normals			= false;
	scene_state.display_axes			= false;
	scene_state.use_computed_data		= true;
	scene_state.draw_instanced			= true;
	//scene_state.b_model_refraction		= true;
	

	// ----- camera position
	//Camera& cam = cameras[0];
	//cam.position = Vec3(-9.4f, 7.3f, 16.0f);
	//cam.lookAtTarget(Vec3(0.0f, 1.6f, 0.0f));
	// normal cam
	//cam.position = Vec3(0.0f, 0.0f, 10.0f);
	//cam.lookAtTarget(Vec3(.2f, 0.0f, -.2f));

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
	//predefined_scene_elements[0].shader_name = "cubemaplit";
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::paircube1);
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::paircube2);

	// ----- define model paths
	model_paths = {
		{ "yurt/models/jupiter_by-murilo.kleine_sketchfab/gltf/scene.gltf" }
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
	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			Vec2 translation;
			translation.x = (float)x / 10.0f + offset;
			translation.y = (float)y / 10.0f + offset;
			computed_data.translations2d.push_back(translation);
		}
	}
	
	unsigned int amount = 50000;
	scene_state.instance_count = amount;
	srand(scene_state.time); // initialize random seed	
	float radius = 40.0f;
	offset = 10.0f;
	for (unsigned int i = 0; i < amount; i++)
	{
		Mat4 model = mat_utils::identity4();
		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f + x / 5.0f; // keep height of field smaller compared to width of x and z
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;

		float scale = (rand() % 20) / 1000.0f + 0.05;
		float rotAngle = (rand() % 360);

		model = mat_utils::translate(Vec3(x, y, z))
			* mat_utils::rotateXYZ(rotAngle, Vec3(0.4f, 0.6f, 0.8f).normalized())
			* mat_utils::scale(scale);

		model = model.transposed();
		// 4. now add to list of matrices
		computed_data.mat4.push_back(model);
	}

	// ----- define texture names
	texture_names = { "out_container", "linegrid_darkgray_2k", "grid_2k_white" };


	// ----- specific position
	scene_state.time_pin = scene_state.time;
}

void InstancingTestScene::update() {

	// emission pulse/breath
	// --------------------------------------------------------------------------------------
	float time = scene_state.time;
	float sint = sin(scene_state.time);
	float cost = cos(scene_state.time);
	float sint10 = sin(scene_state.time + 1.0f) * .5f;

	scene_state.emission_factor = sint10 * 0.4f;

	// move camera
	// --------------------------------------------------------------------------------------
	float camera_pos_multiplier = 80.0f;
	cameras[0].position.y = 25.0f;
	cameras[0].position = Vec3(camera_pos_multiplier * cost, cameras[0].position.y, camera_pos_multiplier * sint);
	cameras[0].lookAtTarget(Vec3(0.0f, 4.0f, 0.0f));
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

InstancingTestScene::InstancingTestScene() {
}


