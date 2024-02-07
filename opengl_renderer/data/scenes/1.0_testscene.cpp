#pragma once
// ----------------------------------------------------------------------------
// ----- libraries
// ----------------------------------------------------------------------------
#include "../../headers/data/scenes.h"

// ----------------------------------------------------------------------------
// ----- forward declarations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----- abstract
// ----------------------------------------------------------------------------
void TestScene::loadData()
{
	scene_state.animate = true;
	scene_state.emission_factor = 1.0f;
	scene_state.shininess = 128.0f;

	// --- define lights
	// directional
	directional_lights.push_back(PredefSceneLights::d_light);
	// point
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.push_back(PredefSceneLights::p_light);
	// spot
	spot_lights.push_back(PredefSceneLights::s_light);

	predefined_scene_elements.push_back(PredefSceneElements::cube_0_10);
	predefined_scene_elements.push_back(PredefSceneElements::cube_10_0);
	predefined_scene_elements.push_back(PredefSceneElements::ground_plane);
	texture_names = { "test_2k", "checker_800" }; // todo sete cvir bir kere yuklensin

	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		Transform transform;
		predefined_scene_element_transforms.push_back(transform);
		predefined_scene_element_transforms[i].position = predefined_scene_elements[i].transform.position;
	}
}

void TestScene::update() {
	// emission pulse/breath
	// --------------------------------------------------------------------------------------
	float time = scene_state.time;
	float sint = sin(scene_state.time);
	float cost = cos(scene_state.time);
	float sint10 = sin(scene_state.time + 1.0f) * .5f;
	
	scene_state.emission_factor = sint10;


	// rotate obj x z 
	// --------------------------------------------------------------------------------------
	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		if (predefined_scene_elements[i].name == "ground_plane")
			continue;
		float x = predefined_scene_elements[i].transform.rotation.x;
		float y = predefined_scene_elements[i].transform.rotation.y;
		float z = predefined_scene_elements[i].transform.rotation.z;
		predefined_scene_elements[i].transform.rotation 
			= Vec3(fmod(time * 40.0f, 360.0f), y, fmod(time * 40.0f, 360.0f));
	}

	// move 
	// --------------------------------------------------------------------------------------
	bool b_offset = false;
	float time_offset = sint;
	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		if (predefined_scene_elements[i].name == "ground_plane")
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

TestScene::TestScene() {
}


