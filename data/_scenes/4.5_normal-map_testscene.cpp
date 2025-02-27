#pragma once
// ----------------------------------------------------------------------------
//				libraries
// ----------------------------------------------------------------------------
#include "../../headers/data/scenes.h"

// ----------------------------------------------------------------------------
//				forward declarations
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
//				abstract
// ----------------------------------------------------------------------------
void NormalMapTestScene::loadData()
{
	scene_state.animate = true;
	scene_state.emission_factor = -1.0f;
	scene_state.shininess = 32.0f;
	// scene_state.vertex_divider = 9.0f;
	//scene_state.b_model_refraction = true;
	//scene_state.display_skybox = true;  
	// scene_state.model_shader_name = "explode";
	// scene_state.display_normals = true;
	scene_state.b_display_axes = true;

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

	// front
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	//predefined_scene_elements.back().transform.scale = Vec3(9.0f, 5.0f, 5.0f);
	//predefined_scene_elements.back().transform.rotation = Vec3(-90.0f, 0.0f, 0.0f);
	//predefined_scene_elements.back().transform.position = Vec3(0.0f, 0.0f, 5.0f);
	//predefined_scene_elements.back().texture_name = "out_planks023a";
	//predefined_scene_elements.back().shader_name = "plight-shadow";
	//predefined_scene_elements.back().element_bools.face_culling = true;
	//predefined_scene_elements.back().shader_name = "multiplelights";

	// back
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	predefined_scene_elements.back().transform.scale	= Vec3(5.0f, 5.0f, 5.0f);
	predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 0.0f, 0.0f);
	predefined_scene_elements.back().transform.position = Vec3(0.0f, 0.0f, -5.0f);
	predefined_scene_elements.back().texture_name		= "out_brickwall";
	predefined_scene_elements.back().shader_name = "normal02";
	predefined_scene_elements.back().element_bools.is_using_tan_space = true;

	// bottom
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	predefined_scene_elements.back().transform.scale = Vec3(5.0f, 5.0f, 5.0f);
	predefined_scene_elements.back().transform.rotation = Vec3(-90.0f, 0.0f, 0.0f);
	predefined_scene_elements.back().transform.position = Vec3(0.0f, -5.0f, 0.0f);
	predefined_scene_elements.back().texture_name = "out_brickwall";
	predefined_scene_elements.back().shader_name = "normal02";
	predefined_scene_elements.back().element_bools.is_using_tan_space = true;

	// top
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	predefined_scene_elements.back().transform.scale = Vec3(5.0f, 5.0f, 5.0f);
	predefined_scene_elements.back().transform.rotation = Vec3(90.0f, 0.0f, 0.0f);
	predefined_scene_elements.back().transform.position = Vec3(0.0f, +5.0f, 0.0f);
	predefined_scene_elements.back().texture_name = "out_brickwall";
	predefined_scene_elements.back().shader_name = "normal02";
	predefined_scene_elements.back().element_bools.is_using_tan_space = true;

	// left
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	predefined_scene_elements.back().transform.scale = Vec3(5.0f, 5.0f, 5.0f);
	predefined_scene_elements.back().transform.rotation = Vec3(0.0f, 90.0f, 0.0f);
	predefined_scene_elements.back().transform.position = Vec3(-5.0f, 0.0f, 0.0f);
	predefined_scene_elements.back().texture_name = "out_brickwall";
	predefined_scene_elements.back().shader_name = "normal02";
	predefined_scene_elements.back().element_bools.is_using_tan_space = true;

	////// right
	predefined_scene_elements.push_back(PrimitiveSceneNodes::plane01);
	predefined_scene_elements.back().transform.scale = Vec3(5.0f, 5.0f, 5.0f);
	predefined_scene_elements.back().transform.rotation = Vec3(0.0f, -90.0f, 0.0f);
	predefined_scene_elements.back().transform.position = Vec3(+5.0f, 0.0f, 0.0f);
	predefined_scene_elements.back().texture_name = "out_brickwall";
	predefined_scene_elements.back().shader_name = "normal02";
	predefined_scene_elements.back().element_bools.is_using_tan_space = true;



	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		Transform transform;
		predefined_scene_element_transforms.push_back(transform);
		predefined_scene_element_transforms[i].position = predefined_scene_elements[i].transform.position;
	}

	//predefined_scene_elements[0].texture_name = "out_planks023a";
	//predefined_scene_elements[0].transform = {
	//		Vec3(0.0f, -0.85f, 0.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(50.0f, 0.2f, 50.0f)
	//};

	//predefined_scene_elements[0].shader_name = "light-shadow";

	//predefined_scene_elements[0].tiling_factor = 4.0f;

	//predefined_scene_elements[1].transform = {
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		//Vec3(0.0f, 0.0f, -4.0f),
	//		Vec3(0.0f, 0.0f, 0.0f),
	//		Vec3(1.5f, 1.5f, 1.5f)
	//};
	//predefined_scene_elements[1].shader_name = "light-shadow";

	//predefined_scene_elements[2].transform = {
	//	Vec3(3.0f, 2.0f, 3.0f),
	//	//Vec3(0.0f, 0.0f, 4.0f),
	//	Vec3(0.0f, -48.0f, 0.0f),
	//	//Vec3(0.0f, 0.0f, 0.0f),
	//	Vec3(1.5f, 1.5f, 1.5f)
	//};
	//predefined_scene_elements[2].shader_name = "light-shadow";


	//predefined_scene_elements[3].transform = {
	//Vec3(-2.0f, 0.0f, 4.0f),
	//Vec3(0.0f, -28.0f, 0.0f),
	//Vec3(1.5f, 1.5f, 1.5f)
	//};
	//predefined_scene_elements[3].shader_name = "light-shadow";

	// textures to cache for objects
	// ----------------------------------------------------------------
	texture_names = { "out_planks023a", "out_container", "out_brickwall"};

	// models
	// ----------------------------------------------------------------
	scene_state.model_shader_name = "normal02";
	model_paths = {
		//"models/out_kokorecci_by_berkgedik/out_kokorecci_by_berk gedik.obj"
		//"models/out_sponza/glTF/Sponza.gltf"
		//"models/testobject0_frustum/testobject.obj",
		//"models/testobject1_dodecahedron/testobject.obj",
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

void NormalMapTestScene::update() {
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

	//Vec3 origin = (0.0f, 0.0f, 0.0f);
	//directional_lights[0].direction = (origin - directional_lights[0].position);


	for (int ii = 0; ii < point_lights.size(); ii++)
	{
		// change light position
		//point_lights[0].position.x 
		//	= distance_multiplier * cos(scene_state.time + 2 * pi / point_lights.size() * ii);
		//point_lights[0].position.y
		//	= 4.0f * sinf(scene_state.time);
		//point_lights[0].position.z
		//	= distance_multiplier * sin(scene_state.time + 2 * pi / point_lights.size() * ii);


		// change light color
		float change_key = scene_state.time + ii;
		//setTriangleLightColorShiftByTime(point_lights[ii].diffuse, point_lights[ii].specular, change_key);
	}

	//setTriangleLightColorShiftByTime(point_lights[0].diffuse, point_lights[0].specular, time);

	//point_lights[0].position.x = 3.0f * cost;
	//directional_lights[0].position = point_lights[0].position;
	//directional_lights[0].direction = -(directional_lights[0].position - Vec3(0.0f, 0.0f, 0.0f));


	// light move rectangular
	// ----------------------------------------------------------------
	if (scene_state.animation_stage < 0) scene_state.animation_stage = 1;
	float multiplier = 1.0f;
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
	point_lights[0].position.z = 2.0f * sint + 2.0f;
	point_lights[0].brightness = 2.0f;

	// rotate obj x z 
	// ----------------------------------------------------------------
	//Transform& tf = predefined_scene_elements.back().transform;

	//tf.position.x = 5.0f * cost;
	//tf.position.y = 5.0f * sint;

	////tf.rotation.x = 30.0f;
	//tf.rotation.z = 90.0f + fmod(scene_state.time * 360.0f / 6.28f, 360.0f);


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

	//predefined_scene_elements[7].transform.position.x = 5.0f * sint;
	//predefined_scene_elements[7].transform.position.y = 3.0f * cost;
	//for (int i = 0; i < predefined_scene_elements.size(); i++)
	//{
	//	if (predefined_scene_elements[i].name == "ground_plane")
	//		continue;
	//	if (predefined_scene_elements[i].name == "light_placeholder")
	//		continue;
	//	b_offset = !b_offset;
	//	time_offset = sint;
	//	if (b_offset) time_offset = sin(time + 3.14f / 2.0f);
	//	float x = predefined_scene_element_transforms[i].position.x;
	//	float y = predefined_scene_elements[i].transform.position.y;
	//	float z = predefined_scene_element_transforms[i].position.z;
	//	predefined_scene_elements[i].transform.position
	//		= Vec3(time_offset * x, y, time_offset * z);
	//}
}

NormalMapTestScene::NormalMapTestScene() {
}


