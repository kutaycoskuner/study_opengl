#pragma once
// ----------------------------------------------------------------------------
//				libraries
// ----------------------------------------------------------------------------
#include "../../source/headers/data/scene_data.h"

// ----------------------------------------------------------------------------
//				forward declarations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
//				abstract
// ----------------------------------------------------------------------------
void ParallaxTestScene::loadData()
{
	scene_state.animate = true;
	scene_state.emission_factor = -1.0f;
	scene_state.shininess = 32.0f;
	// scene_state.vertex_divider = 9.0f;
	//scene_state.b_model_refraction = true;
	//scene_state.display_skybox = true;  
	// scene_state.model_shader_name = "explode";
	// scene_state.display_normals = true;
	scene_state.display_axes = true;

	// camera pos
	// ----------------------------------------------------------------
	cameras[0].position = Vec3(0.0f, 0.0f, 20.0f);
	cameras[0].position = Vec3(-2.0f, 0.0f, 10.0f);
	cameras[0].position = Vec3(-2.0f, 8.0f, 8.0f);
	cameras[0].position = Vec3(0.0f, 0.0f, 12.0f);
	//cameras[0].position = Vec3(0.0f, 0.0f, 14.0f);
	//cameras[0].position = Vec3(0.0f, 1.86f, 0.0f);
	cameras[0].lookAtDirection(Vec3(0.0f, 0.0f, -1.0f));
	//cameras[0].lookAtTarget(Vec3(0.0f, 0.0f, 0.0f));
	//cameras[0].position = Vec3(0.0f, 10.0f, 10.0f);
	//cameras[0].pitch_rad = 0.785f;
	//cameras[0].yaw_rad = -1.120f;

	// light definitions
	// ----------------------------------------------------------------
	// directional
	directional_lights.push_back(PredefSceneLights::d_light);
	directional_lights[0].brightness = 1.0f;

	// point6
	point_lights.push_back(PredefSceneLights::p_light);
	point_lights.back().brightness = 2.0f;
	point_lights.back().position   = Vec3(3.6f, 2.0f, 2.6f);
	point_lights.back().position = Vec3(0.0f, 0.0f, 0.0f);
	//point_lights.back().diffuse = Vec3(0.8f, 0.9f, 0.6f);
	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights.push_back(PredefSceneLights::p_light);

	// spot
	//spot_lights.push_back(PredefSceneLights::s_light);
	//spot_lights[0].position = Vec3(0.0f, 8.0f, 0.0f);
	//spot_lights[0].diffuse = Vec3(1.0f, 1.0f, 1.0f);
	//spot_lights[0].brightness = 2.0f;

	// objects
	// ----------------------------------------------------------------
	// back
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	PrimitiveSceneNode& element = predefined_scene_elements.back();
	element.transform.scale		= Vec3(5.0f, 5.0f, 5.0f);
	element.transform.rotation  = Vec3(0.0f, 0.0f, 0.0f);
	element.transform.position  = Vec3(0.0f, 0.0f, -5.0f);
	element.texture_name		= "out_wood";
	element.texture_name		= "parallax-test";
	element.shader_id			= ShaderID::Parallax;
	element.element_bools.is_using_tan_space = true;


	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		Transform transform;
		predefined_scene_element_transforms.push_back(transform);
		predefined_scene_element_transforms[i].position = predefined_scene_elements[i].transform.position;
	}

	// textures to cache for objects
	// ----------------------------------------------------------------
	texture_names = { "out_planks023a", "out_wood", "out_brickwall", "out_bricks", "parallax-test"};

	// models
	// ----------------------------------------------------------------
        scene_state.model_shader_id = ShaderID::Normal02;
	model_paths = {
		//"models/out_kokorecci_by_berkgedik/out_kokorecci_by_berk gedik.obj"
	};

	// ---- create bools for each imported model
	for (int i = 0; i < model_paths.size(); i++) {
		scene_nodes.push_back(SceneNode("ModelName", Transform()));
		scene_state.model_element_bools.push_back(
			ElementBools{
				.wireframe_mode      = false,
				.depth_testing       = false,
				.stencil_testing	 = false,
				.blending			 = false,
				.partial_render	     = false,
				.indexed		     = true,
				.is_triangle		 = true,
				.is_using_tan_space  = true,
				.face_culling		 = false,
				.gamma			     = false
			}
		);
	}

	if (scene_nodes.size() > 0)
		scene_nodes[0].transform.scale = Vec3(0.01f, 0.01f, 0.01f);

}

void ParallaxTestScene::update() {
	// emission pulse/breath
	// ----------------------------------------------------------------
	float time = scene_state.time;
	float sint = sin(scene_state.time);
	float cost = cos(scene_state.time);
	float sint10 = sin(scene_state.time + 1.0f) * .5f;
	//scene_state.emission_factor = sint10;


	// move lights radial
	// ----------------------------------------------------------------
	float distance_multiplier = 3.0f;
	const float pi = 3.141592f;

	for (int ii = 0; ii < point_lights.size(); ii++)
	{

		// change light color
		float change_key = scene_state.time + ii;
	}

	//setTriangleLightColorShiftByTime(point_lights[0].diffuse, point_lights[0].specular, time);


	// light move rectangular
	// ----------------------------------------------------------------
	if (scene_state.animation_stage < 0) scene_state.animation_stage = 1;
	float multiplier = 2.0f;
	if (scene_state.animation_stage == 1)
	{
		point_lights[0].position.x = multiplier * cost;
		point_lights[0].position.y = multiplier;
		if (cost > 0.99f) scene_state.animation_stage = 2;
	}
	else if (scene_state.animation_stage == 2)
	{
		point_lights[0].position.x = multiplier;
		point_lights[0].position.y = multiplier * cost;
		if (cost < -0.99f) scene_state.animation_stage = 3;
	}
	else if (scene_state.animation_stage == 3)
	{
		point_lights[0].position.x = -multiplier * cost;
		point_lights[0].position.y = -multiplier;
		if (cost > 0.99f) scene_state.animation_stage = 4;
	}
	else if (scene_state.animation_stage == 4)
	{
		point_lights[0].position.x = -multiplier;
		point_lights[0].position.y = -multiplier * cost;
		if (cost < -0.99f) scene_state.animation_stage = 1;
	}
	//point_lights[0].position.z = 2.0f * sint + 2.0f;
	point_lights[0].brightness = 2.0f;

	// rotate obj x z 
	// ----------------------------------------------------------------

	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		//if (predefined_scene_elements[i].name == "ground_plane")
		//	continue;
		//if (predefined_scene_elements[i].name == "light_placeholder")
		//	continue;
		//float x = predefined_scene_elements[i].transform.rotation.x;
		//float y = predefined_scene_elements[i].transform.rotation.y;
		//float z = predefined_scene_elements[i].transform.rotation.z;
		//predefined_scene_elements[i].transform.rotation
		//	= Vec3(fmod(time * 40.0f, 360.0f), y, fmod(time * 40.0f, 360.0f));
	}


	// move objects
	// ----------------------------------------------------------------
	bool b_offset = false;
	float time_offset = sint;
	// Tilt plane in an arc


	if (!predefined_scene_elements.empty()) {
		Transform& plane_transform = predefined_scene_elements.back().transform;

		float amplitude_position = 2.0f;   // Amplitude for position oscillation
		float tilt_angle = 45.0f; // Maximum tilt angle
		float tilt_speed = 1.0f;  // Speed of tilting

		// Arc motion using sin/cos
		plane_transform.position.x = amplitude_position * sinf(scene_state.time);
		plane_transform.rotation.y = tilt_angle * cos(scene_state.time * tilt_speed);
		plane_transform.rotation.z = tilt_angle * sin(scene_state.time * tilt_speed);
	}
}

ParallaxTestScene::ParallaxTestScene() {
}


