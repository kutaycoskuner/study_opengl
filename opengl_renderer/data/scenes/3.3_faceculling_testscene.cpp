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
void FaceCullingTestScene::loadData()
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
	//spot_lights[0].brightness = 10.0f;

	// ----- define predefined elements
	predefined_scene_elements.push_back(PrimitiveSceneNodes::big_cube);
	predefined_scene_elements.back().transform.position.y = 2.0f;



	// ----- define model paths
	model_paths = {};

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
	texture_names = { "linegrid_2k_darkgray", "test_2k" };


	// ----- specific position

}

void FaceCullingTestScene::update() {

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
	//cameras[0].position = Vec3(camera_pos_multiplier * cost, 2.0f, camera_pos_multiplier * sint);
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
		if (predefined_scene_elements[i].name == "ground_plane")
			continue;
		if (predefined_scene_elements[i].name == "light_placeholder")
			continue;
		float x = predefined_scene_elements[i].transform.rotation.x;
		float y = predefined_scene_elements[i].transform.rotation.y;
		float z = predefined_scene_elements[i].transform.rotation.z;
		predefined_scene_elements[i].transform.rotation
			= Vec3(x, fmod(time * 40.0f, 360.0f), z);
	}

	// move objects
	// --------------------------------------------------------------------------------------

	// sort objects
	// --------------------------------------------------------------------------------------


}

FaceCullingTestScene::FaceCullingTestScene() {
}


