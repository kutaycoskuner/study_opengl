#pragma once
// ----------------------------------------------------------------------------
// ----- libraries
// ----------------------------------------------------------------------------
#include "../../headers/data/scenes.h"
#include "../../headers/utils/utilities.h"

// ----------------------------------------------------------------------------
// ----- forward declarations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----- abstract
// ----------------------------------------------------------------------------
void GammaCorrectionTestScene::loadData()
{
	scene_state.animate = true;
	scene_state.emission_factor = -1.0f;
	scene_state.shininess = .5f;
	scene_state.vertex_divider = 6.0f;
	scene_state.b_gamma = true;

	// ----- camera position
	cameras[0].lookAtTarget(Vec3(0.0f, 0.0f, 0.0f));
	cameras[0].position = Vec3(-4.14f, 8.14f, 10.99f);
	cameras[0].yaw_rad = .363f;
	cameras[0].pitch_rad = -.532f;

	// ----- define lights
	// directional
	directional_lights.push_back(PredefSceneLights::d_light);
	// point
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.push_back(PredefSceneLights::p_light);
	// spot
	//point_lights[1].position = Vec3(0.0f, 0.0f, -2.0f);
	//point_lights[2].position = Vec3(0.0f, 0.0f, 2.0f);

	spot_lights.push_back(PredefSceneLights::s_light);
	spot_lights[0].position = Vec3(0.0f, 4.0f, 0.0f);

	// ----- define predefined elements
	predefined_scene_elements.push_back(PrimitiveSceneNodes::ground_platform);
	predefined_scene_elements[0].shader_name = "blinnphong";
	predefined_scene_elements[0].shader_name = "gamma";

	predefined_scene_elements[0].texture_name		= "out_pavingstones080_2k";
	//predefined_scene_elements[0].transform.scale	= Vec3(40.0f, 0.2f, 40.0f);

	float veg_posy = 0.6f;
	float pdm = 1.0f; // planar distance multiplier
	float window_offset = 1.0f;



	// ----- define model paths
	model_paths = {
	};

	// ----- create bools for each imported model
	for (int i = 0; i < model_paths.size(); i++) {
		scene_state.model_element_bools.push_back(
			ElementBools(
			// techniques
			false,
			true,
			true,
			false,
			false,
			false,
			true,
			false,
			true
			)
		);
	}

	// ----- define texture names
	texture_names = { "out_pavingstones080_2k" };


	// ----- specific position

}

void GammaCorrectionTestScene::update() {

	// emission pulse/breath
	// --------------------------------------------------------------------------------------
	float time = scene_state.time;
	float sint = sin(scene_state.time);
	float cost = cos(scene_state.time);
	float sint10 = sin(scene_state.time + 1.0f) * .5f;

	//scene_state.emission_factor = sint10;
		// move camera
	// --------------------------------------------------------------------------------------
	//float camera_pos_multiplier = 8.0f;
	//cameras[0].lookAtTarget(Vec3(0.0f, 0.0f, 0.0f));

	// move lights radial
	// --------------------------------------------------------------------------------------
	float distance_multiplier = 3.0f;
	const float pi = 3.141592f;
	for (int ii = 0; ii < point_lights.size(); ii++)
	{
		// change light position
		point_lights[ii].position = Vec3(
			distance_multiplier * cos(scene_state.time + 2 * pi / point_lights.size() * ii),
			1.0f,
			distance_multiplier * sin(scene_state.time + 2 * pi / point_lights.size() * ii))
			;

		// change light color
		float change_key = scene_state.time + ii;
		setTriangleLightColorShiftByTime(point_lights[ii].diffuse, point_lights[ii].specular, change_key);
	}
	//spot_lights[0].position = Vec3(0.0f, 2.0f, 0.0f);
	//spot_lights[0].direction = Vec3(-1.0f, -1.0f, -1.0f);

	// change shaderes
	// --------------------------------------------------------------------------------------
	static_cast<int>(fmod(time, 2.0f)) == 0 ?
		scene_state.b_gamma = true :
		scene_state.b_gamma = false;


	// rotate obj x z 
	// --------------------------------------------------------------------------------------
	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		//if (predefined_scene_elements[i].name == "ground_platform")
		//	continue;
		if (predefined_scene_elements[i].name == "grass")
		{
			// align 2d object always perpendicular to camera position
			predefined_scene_elements[i].transform.rotation.y =
				math_utils::toDegree(-cameras[0].yaw_rad);
			//predefined_scene_elements[i].transform.rotation.x =
			//	math_utils::toDegree(cameras[0].pitch_rad);
		}
	}

	// move objects
	// --------------------------------------------------------------------------------------
	bool b_offset = false;
	float time_offset = sint;
	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		//if (predefined_scene_elements[i].name == "ground_platform")
		//	continue;
		//if (predefined_scene_elements[i].name == "light_placeholder")
		//	continue;
		//b_offset = !b_offset;
		//time_offset = sint;
		//if (b_offset) time_offset = sin(time + 3.14f / 2.0f);
		//float x = predefined_scene_element_transforms[i].position.x;
		//float y = predefined_scene_elements[i].transform.position.y;
		//float z = predefined_scene_element_transforms[i].position.z;
		//predefined_scene_elements[i].transform.position
		//	= Vec3(time_offset * x, y, time_offset * z);
	}


	// sort objects
	// --------------------------------------------------------------------------------------
	/*
	1. Draw all opaque objects first.
	2. Sort all the transparent objects.
	3. Draw all the transparent objects in sorted order.
	*/
	// normalde blendingin calismasi icin objeleri arkadan one dogru sort edip cizmek egerekiyor ama su anda garip bir sekilde calisiyor.
	std::map<float, PrimitiveSceneNode> sorted;
	std::sort(predefined_scene_elements.begin(), predefined_scene_elements.end(),
		[this](const PrimitiveSceneNode& a, const PrimitiveSceneNode& b) {
			float distanceA = vec_utils::length(this->cameras[0].position - a.transform.position);
			float distanceB = vec_utils::length(this->cameras[0].position - b.transform.position);
			return distanceA > distanceB;
		});

}

GammaCorrectionTestScene::GammaCorrectionTestScene() {
}


