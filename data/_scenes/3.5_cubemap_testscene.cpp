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
void CubemapTestScene::loadData()
{
	scene_state.animate = true;
	scene_state.emission_factor = -1.0f;
	scene_state.shininess = 32.0f;
	scene_state.vertex_divider = 6.0f;
	scene_state.b_model_refraction = true;
	scene_state.display_skybox = true;

	// ----- camera position
	Camera& cam = cameras[0];
	cam.position = Vec3(10.0f, 5.0f, 8.0f);
	cam.lookAtTarget(Vec3(0.0f, 2.0f, 0.0f));

	// ----- define lights
	//// directional
	//directional_lights.push_back(PredefSceneLights::d_light);
	//// point
	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights.push_back(PredefSceneLights::p_light);
	//// spot
	//spot_lights.push_back(PredefSceneLights::s_light);
	////spot_lights[0].brightness = 10.0f;

	// ----- define predefined elements
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::single_cube);
	//predefined_scene_elements[0].shader_name = "cubemaplit";
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::paircube1);
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::paircube2);

	// ----- define model paths
	model_paths = {
		"models/testobject0_frustum/testobject.obj",
		"models/testobject1_dodecahedron/testobject.obj"
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

	// ----- define texture names
	texture_names = { "out_container", "linegrid_darkgray_2k", "grid_2k_white" };


	// ----- specific position

}

void CubemapTestScene::update() {

	// emission pulse/breath
	// --------------------------------------------------------------------------------------
	float time = scene_state.time;
	float sint = sin(scene_state.time);
	float cost = cos(scene_state.time);
	float sint10 = sin(scene_state.time + 1.0f) * .5f;

	scene_state.emission_factor = sint10 * 0.4f;
	// move camera
	// --------------------------------------------------------------------------------------
	float camera_pos_multiplier = 12.0f;
	cameras[0].position = Vec3(camera_pos_multiplier * cost, cameras[0].position.y, camera_pos_multiplier * sint);
	cameras[0].lookAtTarget(Vec3(0.0f, 2.0f, 0.0f));

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

	// sort objects
	// --------------------------------------------------------------------------------------


}

CubemapTestScene::CubemapTestScene() {
}


