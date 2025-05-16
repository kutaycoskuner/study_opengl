#pragma once
// ----------------------------------------------------------------------------
// ----- libraries
// ----------------------------------------------------------------------------
#include "../../source/headers/data/scene_data.h"
#include "../../headers/utils/utilities.h"

// ----------------------------------------------------------------------------
// ----- forward declarations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ----- abstract
// ----------------------------------------------------------------------------
void BlinnPhongTestScene::loadData()
{
	scene_state.animate = true;
	//scene_state.emission_factor = -1.0f;
	scene_state.shininess = 1.0f;
	//scene_state.vertex_divider = 6.0f;

	// ----- camera position
	cameras[0].lookAtTarget(Vec3(0.0f, 0.0f, 0.0f));
	cameras[0].position = Vec3(-10.0f, 8.3f, 10.0f);

	// ----- define lights
	// directional
	//directional_lights.push_back(PredefSceneLights::d_light);
	// point
	point_lights.push_back(PredefSceneLights::p_light);
    point_lights[0].position = Vec3(0.0f, 3.0f, 0.0f);
	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights.push_back(PredefSceneLights::p_light);
	// spot
	//spot_lights.push_back(PredefSceneLights::s_light);

	// ----- define predefined elements
	predefined_scene_elements.push_back(PrimitiveSceneNodes::ground_platform);
	predefined_scene_elements[0].shader_id		= ShaderID::BlinnPhong;
	//predefined_scene_elements[0].shader_name		= "blinnphong2";

	//predefined_scene_elements[0].texture_name		= "out_planks023b";
	//predefined_scene_elements[0].transform.scale	= Vec3(40.0f, 0.2f, 40.0f);




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
	texture_names = { "linegrid_darkgray_2k", "out_grass", "out_blending_window_blue", "out_planks023b"};


	// ----- specific position

}

void BlinnPhongTestScene::update() {

	float time = scene_state.time;
	// change shaderes
	// --------------------------------------------------------------------------------------
	static_cast<int>(fmod(time, 2.0f)) == 0 ?
		predefined_scene_elements[0].shader_id = ShaderID::BlinnPhong :
		predefined_scene_elements[0].shader_id = ShaderID::BlinnPhong2;

}

BlinnPhongTestScene::BlinnPhongTestScene() {
}


