#pragma once
// ----------------------------------------------------------------------------
// ----- libraries
// ----------------------------------------------------------------------------
#include "../../source/headers/data/scene_data.h"

// ----------------------------------------------------------------------------
// ----- forward declarations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----- abstract
// ----------------------------------------------------------------------------
void ImportModelTestScene::loadData()
{
	scene_state.animate = true;
	scene_state.emission_factor = -1.0f;
	scene_state.shininess = 32.0f;

	// --- define lights
	// directional
	directional_lights.push_back(PredefSceneLights::d_light);
	// point
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.push_back(PredefSceneLights::p_light);
	// spot
	spot_lights.push_back(PredefSceneLights::s_light);

	predefined_scene_elements.push_back(PrimitiveSceneNodes::ground_platform);
	texture_names = { "test_2k", "linegrid_darkgray_2k", "out_container" }; 

	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		Transform transform;
		predefined_scene_element_transforms.push_back(transform);
		predefined_scene_element_transforms[i].position = predefined_scene_elements[i].transform.position;
	}

	model_paths = {
		"models/testobject0_frustum/testobject.obj",
		"models/testobject1_dodecahedron/testobject.obj",
	};

	// ---- create bools for each imported model
	for (int i = 0; i < model_paths.size(); i++) {
		scene_state.model_element_bools.push_back(
			ElementBools(
				false,		// wireframe_mode
				false,		// depth testing
				false,		// stencil testing
				false		// blending
			)
		);
	}

}

void ImportModelTestScene::update() {
	// emission pulse/breath
	// --------------------------------------------------------------------------------------
	float time = scene_state.time;
	float sint = sin(scene_state.time);
	float cost = cos(scene_state.time);
	float sint10 = sin(scene_state.time + 1.0f) * .5f;

	//scene_state.emission_factor = sint10;

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
			= Vec3(fmod(time * 40.0f, 360.0f), y, fmod(time * 40.0f, 360.0f));
	}

	// move objects
	// --------------------------------------------------------------------------------------
	bool b_offset = false;
	float time_offset = sint;
	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		if (predefined_scene_elements[i].name == "ground_plane")
			continue;
		if (predefined_scene_elements[i].name == "light_placeholder")
			continue;
		b_offset = !b_offset;
		time_offset = sint;
		if (b_offset) time_offset = sin(time + 3.14f / 2.0f);
		float x = predefined_scene_element_transforms[i].position.x;
		float y = predefined_scene_elements[i].transform.position.y;
		float z = predefined_scene_element_transforms[i].position.z;
		predefined_scene_elements[i].transform.position
			= Vec3(time_offset * x, y, time_offset * z);
	}
}

ImportModelTestScene::ImportModelTestScene() {
}


