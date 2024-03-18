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
void BlendingTestScene::loadData()
{
	scene_state.animate = true;
	scene_state.emission_factor = -1.0f;
	scene_state.shininess = 32.0f;
	scene_state.vertex_divider = 6.0f;

	// ----- camera position
	cameras[0].lookAtTarget(Vec3(0.0f, 0.0f, 0.0f));

	// ----- define lights
	// directional
	directional_lights.push_back(PredefSceneLights::d_light);
	// point
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.push_back(PredefSceneLights::p_light);
	// spot
	spot_lights.push_back(PredefSceneLights::s_light);

	// ----- define predefined elements
	predefined_scene_elements.push_back(PredefSceneElements::ground_plane);

	predefined_scene_elements.push_back(PredefSceneElements::transparent_window);
	predefined_scene_elements.push_back(PredefSceneElements::transparent_window);
	predefined_scene_elements.push_back(PredefSceneElements::transparent_window);
	predefined_scene_elements.push_back(PredefSceneElements::transparent_window);
	predefined_scene_elements.push_back(PredefSceneElements::transparent_window);
	predefined_scene_elements.push_back(PredefSceneElements::transparent_window);
	predefined_scene_elements.push_back(PredefSceneElements::transparent_window);
	predefined_scene_elements.push_back(PredefSceneElements::transparent_window);

	predefined_scene_elements.push_back(PredefSceneElements::nobg_grass);
	predefined_scene_elements.push_back(PredefSceneElements::nobg_grass);
	predefined_scene_elements.push_back(PredefSceneElements::nobg_grass);
	predefined_scene_elements.push_back(PredefSceneElements::nobg_grass);
	predefined_scene_elements.push_back(PredefSceneElements::nobg_grass);
	predefined_scene_elements.push_back(PredefSceneElements::nobg_grass);
	predefined_scene_elements.push_back(PredefSceneElements::nobg_grass);
	predefined_scene_elements.push_back(PredefSceneElements::nobg_grass);

	float veg_posy = 0.6f;
	float pdm = 1.0f; // planar distance multiplier
	float window_offset = 1.0f;
	predefined_scene_elements[1].transform.position = Vec3(0.0f, veg_posy, 0.0f * pdm + window_offset);
	predefined_scene_elements[2].transform.position = Vec3(1.5f * pdm, veg_posy, 1.0f * pdm + window_offset);
	predefined_scene_elements[3].transform.position = Vec3(-1.5f * pdm, veg_posy, -1.0f * pdm + window_offset);
	predefined_scene_elements[4].transform.position = Vec3(-3.0f * pdm, veg_posy, -2.0f * pdm + window_offset);
	predefined_scene_elements[5].transform.position = Vec3(-3.0f * pdm, veg_posy, +2.0f * pdm + window_offset);
	predefined_scene_elements[6].transform.position = Vec3(4.5f * pdm, veg_posy, +0.5f * pdm + window_offset);
	predefined_scene_elements[7].transform.position = Vec3(4.5f * pdm, veg_posy, -2.5f * pdm + window_offset);
	predefined_scene_elements[8].transform.position = Vec3(2.0f * pdm, veg_posy, -1.0f * pdm + window_offset);

	predefined_scene_elements[9].transform.position = Vec3(0.0f * pdm, veg_posy, 0.0f * pdm);
	predefined_scene_elements[10].transform.position = Vec3(1.5f * pdm, veg_posy, +1.0f * pdm);
	predefined_scene_elements[11].transform.position = Vec3(-1.5f * pdm, veg_posy, -1.0f * pdm);
	predefined_scene_elements[12].transform.position = Vec3(-3.0f * pdm, veg_posy, -2.0f * pdm);
	predefined_scene_elements[13].transform.position = Vec3(-3.0f * pdm, veg_posy, +2.0f * pdm);
	predefined_scene_elements[14].transform.position = Vec3(4.5f * pdm, veg_posy, +0.5f * pdm);
	predefined_scene_elements[15].transform.position = Vec3(4.0f * pdm, veg_posy, -2.5f * pdm);
	predefined_scene_elements[16].transform.position = Vec3(2.0f * pdm, veg_posy, -1.0f * pdm);


	// ----- define model paths
	model_paths = {
	};

	// ----- create bools for each imported model
	for (int i = 0; i < model_paths.size(); i++) {
		scene_state.model_element_bools.push_back(
			ElementBools(
				false,		// wireframe_mode
				true,		// depth testing
				true,		// stencil testing
				false		// blending
			)
		);
	}

	// ----- define texture names
	texture_names = { "linegrid_2k_darkgray", "out_grass", "out_blending_window_blue" };


	// ----- specific position

}

void BlendingTestScene::update() {

	// emission pulse/breath
	// --------------------------------------------------------------------------------------
	float time = scene_state.time;
	float sint = sin(scene_state.time);
	float cost = cos(scene_state.time);
	float sint10 = sin(scene_state.time + 1.0f) * .5f;

	//scene_state.emission_factor = sint10;
		// move camera
	// --------------------------------------------------------------------------------------
	float camera_pos_multiplier = 8.0f;
	cameras[0].position = Vec3(camera_pos_multiplier * cost, 2.0f, camera_pos_multiplier * sint);
	cameras[0].lookAtTarget(Vec3(0.0f, 0.0f, 0.0f));

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
	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		//if (predefined_scene_elements[i].name == "ground_plane")
		//	continue;
		if (predefined_scene_elements[i].name == "grass")
		{
			// align 2d object always perpendicular to camera position
	/*		predefined_scene_elements[i].transform.rotation.y =
				math_utils::toDegree(-cameras[0].yaw_rad);*/
			/*predefined_scene_elements[i].transform.rotation.x =
				math_utils::toDegree(cameras[0].pitch_rad);*/
		}
	}

	// move objects
	// --------------------------------------------------------------------------------------
	bool b_offset = false;
	float time_offset = sint;
	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		//if (predefined_scene_elements[i].name == "ground_plane")
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
	std::map<float, PredefSceneElement> sorted;
	std::sort(predefined_scene_elements.begin(), predefined_scene_elements.end(),
		[this](const PredefSceneElement& a, const PredefSceneElement& b) {
			float distanceA = vec_utils::length(this->cameras[0].position - a.transform.position);
			float distanceB = vec_utils::length(this->cameras[0].position - b.transform.position);
			return distanceA > distanceB;
		});

}

BlendingTestScene::BlendingTestScene() {
}


