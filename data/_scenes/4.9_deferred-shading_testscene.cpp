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
void DeferredShadingTestScene::loadData()
{
	scene_state.animate = true;
	scene_state.emission_factor = -1.0f;
	scene_state.shininess = 32.0f;
    scene_state.b_deferred_shading = true;
	// scene_state.vertex_divider = 9.0f;
	//scene_state.b_model_refraction = true;
	//scene_state.display_skybox = true;  
	// scene_state.model_shader_name = "explode";
	// scene_state.display_normals = true;
	scene_state.b_display_axes = true;
    //scene_state.b_bloom        = false;

	// camera pos
	// ----------------------------------------------------------------
	cameras[0].position.y += 2.0f;
	//cameras[0].position = Vec3(0.0f, 0.0f, 20.0f);
	//cameras[0].position = Vec3(-2.0f, 0.0f, 10.0f);
	//cameras[0].position = Vec3(-8.0f, 4.0f, 0.0f);
	////cameras[0].position = Vec3(-3.0f, 1.0f, 0.0f);
	////cameras[0].position = Vec3(0.0f, 0.0f, 14.0f);
	////cameras[0].position = Vec3(0.0f, 1.86f, 0.0f);
	//cameras[0].lookAtDirection(Vec3(1.0f, 0.0f, 0.0f));
	////cameras[0].lookAtTarget(Vec3(0.0f, 0.0f, 0.0f));
	////cameras[0].position = Vec3(0.0f, 10.0f, 10.0f);
	//cameras[0].yaw_rad = +1.520f;
	//cameras[0].pitch_rad = -0.200f;

	// light definitions
	// ----------------------------------------------------------------
	// directional
	//directional_lights.push_back(PredefSceneLights::d_light);
	//DirectionalLight& dl0 = directional_lights[0];
	//dl0.brightness = 1.0f;
	//dl0.direction = Vec3(0.0f, -1.0f, 0.0f);

	// point6
	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights.back().diffuse = Vec3(1.0f, 1.0f, 1.0f);
	//point_lights.back().brightness = 1.0f;
	//point_lights.back().position = Vec3(1.0, 2.0f, 1.0f);

	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights.back().diffuse = Vec3(1.0f, 0.0f, 0.0f);
	//point_lights.back().brightness = 1.0f;
	//point_lights.back().position = Vec3(-1.0, 2.0f, 1.0f);

	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights.back().diffuse = Vec3(0.0f, 1.0f, 0.0f);
	//point_lights.back().brightness = 1.0f;
	//point_lights.back().position = Vec3(1.0, 2.0f, -1.0f);

	int num_point_lights = 200;
	for (int i = 0; i < num_point_lights; i++)
    {
		point_lights.push_back(PredefSceneLights::p_light);
	}
    for (int i = 0; i < num_point_lights; i++)
    {
        point_lights[i].position.x = math_utils::randomFloat(-5.0f, 5.0f);
        point_lights[i].position.y = math_utils::randomFloat(0.0f, 10.0f);
        point_lights[i].position.z = math_utils::randomFloat(-5.0f, 5.0f);
        point_lights[i].diffuse.x = math_utils::randomFloat(0.0f, 5.0f);
        point_lights[i].diffuse.y = math_utils::randomFloat(0.0f, 5.0f);
        point_lights[i].diffuse.z = math_utils::randomFloat(0.0f, 5.0f);
        point_lights[i].diffuse.normalize();
        point_lights[i].brightness = math_utils::randomFloat(3.0f, 5.0f);
	}

	//float multiplier = 3.0f;

	//point_lights[0].position = Vec3(multiplier,  4.0f, multiplier);
 //   point_lights[1].position = Vec3(-multiplier, 4.0f, multiplier);
 //   point_lights[2].position = Vec3(multiplier,  4.0f, -multiplier);
 //   point_lights[3].position = Vec3(-multiplier, 4.0f, -multiplier);

	//point_lights[0].diffuse = Vec3(1.0f, 0.0f, 0.0f);
 //   point_lights[1].diffuse = Vec3(0.0f, 1.0f, 0.0f);
 //   point_lights[2].diffuse = Vec3(0.0f, 0.0f, 1.0f);
 //   point_lights[3].diffuse = Vec3(1.0f, 0.0f, 1.0f);

	//point_lights.push_back(PredefSceneLights::p_light);
	//point_lights.back().diffuse = Vec3(0.0f, 0.0f, 1.0f);
	//point_lights.back().brightness = 2.0f;
	//point_lights.back().position = Vec3(-1.0, 2.0f, -1.0f);


	// spot
	//spot_lights.push_back(PredefSceneLights::s_light);
	////spot_lights[0].position = Vec3(0.0f, 8.0f, 0.0f);
	////spot_lights[0].diffuse = Vec3(1.0f, 1.0f, 1.0f);
	//spot_lights[0].brightness = 2.0f;

	// primitive scene objects
	// ----------------------------------------------------------------
	//predefined_scene_elements.push_back(PrimitiveSceneNodes::ground_platform);
	//PrimitiveSceneNode& element				 = predefined_scene_elements.back();
	//element.texture_name					 = "linegrid01_white_2k";
	//element.shader_name                      = "multiplelights";

	//element.texture_name					 = "gamma-test-rgb";

	for (int i = 0; i < predefined_scene_elements.size(); i++)
	{
		Transform transform;
		predefined_scene_element_transforms.push_back(transform);
		predefined_scene_element_transforms[i].position = predefined_scene_elements[i].transform.position;
	}

	// textures to cache for objects
	// ----------------------------------------------------------------
	texture_names = { "linegrid01_white_2k" };

	// models
	// ----------------------------------------------------------------
	scene_state.model_shader_name = "hdr";
	model_paths = {
		// "models/out_sponza/glTF/Sponza.gltf"
		//std::string("/yurt/scenes/sponza_crytek/gltf/sponza.gltf"),
        //std::string("/yurt/scenes/sponza_intel/gltf/intel-sponza.gltf"),
        std::string("/yurt/scenes/outliner-testscene/obj/outliner-testscene.obj"),
		//std::string("models/testobject0_frustum/testobject.obj"),
		//std::string("models/testobject1_dodecahedron/testobject.obj"),
		//std::string("models/testobject2_sphere/testobject.obj"),
		//std::string("models/testobject3_cube0/testobject.obj"),
		//std::string("models/testobject4_cube1/testobject.obj"),
		//std::string("models/testobject5_cube2/testobject.obj"),
		//std::string("models/testobject6_cube3/testobject.obj"),
		//std::string("models/testobject7_torus/testobject.obj"),
		//std::string("models/testobject8_mine/testobject.obj"),
		//std::string("models/testobject9_cylinder/testobject.obj"),
		//std::string("models/testobject10_suzanne/testobject.obj"),
		//std::string("models/testobject11_cone/testobject.obj")
		//std::string("models/testobjects_by_kutaycoskuner/testobjects.obj")
	};

	// ---- create bools for each imported model
	for (int i = 0; i < model_paths.size(); i++) {
		scene_nodes.push_back(SceneNode("ModelName", Transform()));
		scene_state.model_element_bools.push_back(
			ElementBools{
				.wireframe_mode = false,
				.depth_testing = false,
				.stencil_testing = false,
				.blending = false,
				.partial_render = false,
				.indexed = false,
				.is_triangle = true,
				.is_using_tan_space = false,
				.face_culling = false,
				.gamma = false
			}
		);
	}

	//if (scene_nodes.size() > 0)
	//	scene_nodes[0].transform.scale = Vec3(0.01f, 0.01f, 0.01f);
        scene_state.model_shader_name = "deferred-geometry-pass";

}

void DeferredShadingTestScene::update() {
//	// emission pulse/breath
//	// --------------------------------------------------------------------------------------
//	float time = scene_state.time;
//	float sint = sin(scene_state.time);
//	float cost = cos(scene_state.time);
//	float sint10 = sin(scene_state.time + 1.0f) * .5f;
//
//	//scene_state.emission_factor = sint10;
//
//	// move lights radial
//// --------------------------------------------------------------------------------------
//	float distance_multiplier = 3.0f;
//	const float pi = 3.141592f;
//	for (int ii = 0; ii < point_lights.size(); ii++)
//	{
//		// change light position
//		point_lights[ii].position = Vec3(
//			distance_multiplier * cos(scene_state.time + 2 * pi / point_lights.size() * ii),
//			3.0f,
//			distance_multiplier * sin(scene_state.time + 2 * pi / point_lights.size() * ii))
//			;
//
//		// change light color
//		float change_key = scene_state.time + ii;
//		setTriangleLightColorShiftByTime(point_lights[ii].diffuse, point_lights[ii].specular, change_key);
//	}
//
//
//	// rotate obj x z 
//	// --------------------------------------------------------------------------------------
//	for (int i = 0; i < predefined_scene_elements.size(); i++)
//	{
//		if (predefined_scene_elements[i].name == "ground_plane")
//			continue;
//		if (predefined_scene_elements[i].name == "light_placeholder")
//			continue;
//		float x = predefined_scene_elements[i].transform.rotation.x;
//		float y = predefined_scene_elements[i].transform.rotation.y;
//		float z = predefined_scene_elements[i].transform.rotation.z;
//		predefined_scene_elements[i].transform.rotation
//			= Vec3(fmod(time * 40.0f, 360.0f), y, fmod(time * 40.0f, 360.0f));
//	}
//
//	// move objects
//	// --------------------------------------------------------------------------------------
//	bool b_offset = false;
//	float time_offset = sint;
//	for (int i = 0; i < predefined_scene_elements.size(); i++)
//	{
//		if (predefined_scene_elements[i].name == "ground_plane")
//			continue;
//		if (predefined_scene_elements[i].name == "light_placeholder")
//			continue;
//		b_offset = !b_offset;
//		time_offset = sint;
//		if (b_offset) time_offset = sin(time + 3.14f / 2.0f);
//		float x = predefined_scene_element_transforms[i].position.x;
//		float y = predefined_scene_elements[i].transform.position.y;
//		float z = predefined_scene_element_transforms[i].position.z;
//		predefined_scene_elements[i].transform.position
//			= Vec3(time_offset * x, y, time_offset * z);
//	}

	//scene_state.emission_factor = sint;
}

DeferredShadingTestScene::DeferredShadingTestScene() {
}


