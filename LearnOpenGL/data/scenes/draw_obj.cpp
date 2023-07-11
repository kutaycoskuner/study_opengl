#include "../../headers/abstract/application.h"
#include "../../headers/abstract/uniforms.h"
#include "../../headers/abstract/shader.h"
#include "../../headers/data/data.h"
#include "../../headers/utils/utilities.h"

// self keywords
// ------------------------------------------------------------------------------------------------
using uint = unsigned int;		// unsigned int yerine uint kisayolu tanimlama
using namespace math_utils;
using namespace str_utils;
using namespace file_utils;
using namespace img_utils;


void Application::drawLightPlaceholder(int vao, const char* shader_name, Uniforms& uni)
{

	// create transformations
	uni.upo.world_matrix = mat_utils::rotationX(radian(-45.0f))
		* mat_utils::rotationXYZ(scene_state.time, Vec3(1.0f, 1.0f, 1.0f).normalized())
		;
	uni.upv.view_matrix = scene_state.camera.calcViewMatrix(world_up);
	uni.upv.projection_matrix
		= mat_utils::projectPerspective(radian(scene_state.camera.fov),
			scene_state.camera.aspect_ratio,
			scene_state.camera.near, scene_state.camera.far);
	uni.upv.view_proj_matrix = uni.upv.projection_matrix * uni.upv.view_matrix;

	// light placeholder
	this->active_shader = shaders.at(shader_name);
	// activate shader
	active_shader->use();
	// assign uniforms
	active_shader->setVec3("light_color", scene_state.point_lights[0].diffuse); // light_coloru degistirme
	active_shader->setMat4("view_matrix", uni.upv.view_matrix);
	active_shader->setMat4("projection_matrix", uni.upv.projection_matrix);
	active_shader->setMat4("view_proj_matrix", uni.upv.view_proj_matrix);

	glBindVertexArray(vao);

	float multiplier = 2.0f;

	for (int ii = 0; ii < 3; ii++)
	{
		if (ii == 0)
		{
			active_shader->setVec3("light_color", Vec3(1.0f, 0.0f, 0.0f)); // light_coloru degistirme
		}
		if (ii == 1)
		{
			active_shader->setVec3("light_color", Vec3(0.0f, 1.0f, 0.0f)); // light_coloru degistirme
		}
		if (ii == 2)
		{
			active_shader->setVec3("light_color", Vec3(0.0f, 0.0f, 1.0f)); // light_coloru degistirme
		}
		Mat4 model = mat_utils::translation(Vec3(
			multiplier * sin(scene_state.time + 2 * PI/3.0f*ii),
			1.0f, 
			multiplier * cos(scene_state.time + 2 * PI / 3.0f * ii)
			))
			* mat_utils::scale(0.05f);
		;
		active_shader->setMat4("world_matrix", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
}

void Application::drawAxis(int vao, const char* shader_name, Uniforms& uni)
{
	// create transformations
	uni.upo.world_matrix = mat_utils::rotationX(radian(-45.0f))
		* mat_utils::rotationXYZ(scene_state.time, Vec3(1.0f, 1.0f, 1.0f).normalized())
		;
	uni.upv.view_matrix = scene_state.camera.calcViewMatrix(world_up);
	uni.upv.projection_matrix
		= mat_utils::projectPerspective(radian(scene_state.camera.fov),
			scene_state.camera.aspect_ratio,
			scene_state.camera.near, scene_state.camera.far);
	uni.upv.view_proj_matrix = uni.upv.projection_matrix * uni.upv.view_matrix;

	// light placeholder
	this->active_shader = shaders.at(shader_name);
	// activate shader
	active_shader->use();
	// assign uniforms
	active_shader->setVec3("light_color", scene_state.point_lights[0].diffuse); // light_coloru degistirme
	active_shader->setMat4("view_matrix", uni.upv.view_matrix);
	active_shader->setMat4("projection_matrix", uni.upv.projection_matrix);
	active_shader->setMat4("view_proj_matrix", uni.upv.view_proj_matrix);

	glBindVertexArray(vao);

	// ground orientation axes x and z
	// --------------------------------------------------------------------------------------
	float main_axis = 10.0f;
	float other_axis = 0.015f;
	float scale_factor = 0.8f;
	float color_dim = 0.5f;
	float color_sec = 0.1f;
	Mat4 model = mat_utils::scale(Vec3(
		main_axis,
		other_axis,
		other_axis
		))
		* mat_utils::scale(scale_factor)
	;
	active_shader->setVec3("light_color", Vec3(1.0, 0.0f, 0.282f)); // light_coloru degistirme
	active_shader->setMat4("world_matrix", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//// -----
	//model = mat_utils::scale(Vec3(
	//	other_axis,
	//	main_axis,
	//	other_axis
	//	))
	//	* mat_utils::scale(scale_factor)
	//;
	//active_shader->setVec3("light_color", Vec3(color_sec, color_dim, color_sec)); // light_coloru degistirme
	//active_shader->setMat4("world_matrix", model);

	//glDrawArrays(GL_TRIANGLES, 0, 36);

	// -----
	model = mat_utils::scale(Vec3(
		other_axis,
		other_axis,
		main_axis
		))
		* mat_utils::scale(scale_factor)
	;
	active_shader->setVec3("light_color", Vec3(.024f, 0.706f, 0.729f)); // light_coloru degistirme
	active_shader->setMat4("world_matrix", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// -----
	//model = mat_utils::translation(Vec3(
	//	2.0f,
	//	0.5f,
	//	2.0f
	//))
	//	* mat_utils::scale(scale_factor * scale_factor)
	//	;
	//active_shader->setVec3("light_color", Vec3(1.0f, 0.0f, 1.0f)); // light_coloru degistirme
	//active_shader->setMat4("world_matrix", model);

	//glDrawArrays(GL_TRIANGLES, 0, 36);

}


void Application::setPointLightParameters(Uniforms& uni)
{
	// point light
	float multiplier = 2.0f;
	for (int ii = 0; ii < 3; ii++)
	{
		std::string name = "point_lights[" + std::to_string(ii) + "].";
		active_shader->setVec3(name + "position",
			Vec3(multiplier * sin(scene_state.time + 2 * PI / 3.0f * ii),
				scene_state.camera.position.y - 1.0f,
				multiplier * cos(scene_state.time + 2 * PI / 3.0f * ii))
		);
		active_shader->setVec3(name + "ambient"		, scene_state.point_lights[ii].ambient);
		active_shader->setVec3(name + "specular"	, scene_state.point_lights[ii].specular);
		active_shader->setFloat(name + "constant"	, scene_state.point_lights[ii].constant);
		active_shader->setFloat(name + "linear"		, scene_state.point_lights[ii].linear);
		active_shader->setFloat(name + "quadratic"	, scene_state.point_lights[ii].quadratic);
		if (ii % 3 == 0)
		{
			active_shader->setVec3(name + "diffuse"	, Vec3(1.0f, 0.0f, 0.0f)); // light_coloru degistirme
			active_shader->setVec3(name + "specular", Vec3(0.5f, 0.2f, 0.2f));
		}
		if (ii % 3 == 1)
		{
			active_shader->setVec3(name + "diffuse"	, Vec3(0.0f, 1.0f, 0.0f)); // light_coloru degistirme
			active_shader->setVec3(name + "specular", Vec3(0.2f, 0.5f, 0.2f));
		}
		if (ii % 3 == 2)
		{
			active_shader->setVec3(name + "diffuse"	, Vec3(0.0f, 0.0f, 1.0f)); // light_coloru degistirme
			active_shader->setVec3(name + "specular", Vec3(0.2f, 0.2f, 0.5f));
		}
	}
}

void Application::setDirectionalLightParameters(Uniforms& uni)
{
	SceneState& ss = scene_state;
	active_shader->setVec3("directional_light.direction", ss.directional_lights[0].direction);
	active_shader->setVec3("directional_light.diffuse", ss.directional_lights[0].diffuse); // darken diffuse light a bit
	active_shader->setVec3("directional_light.ambient", ss.directional_lights[0].ambient);
	active_shader->setVec3("directional_light.specular", ss.directional_lights[0].specular);
}

void Application::setSpotLightParameters(Uniforms& uni)
{
	SceneState& ss = scene_state;
	active_shader->setVec3("spot_light.position", ss.spot_lights[0].position);
	active_shader->setVec3("spot_light.direction", ss.spot_lights[0].direction);
	active_shader->setVec3("spot_light.ambient", ss.spot_lights[0].ambient);
	active_shader->setVec3("spot_light.diffuse", ss.spot_lights[0].diffuse);
	active_shader->setVec3("spot_light.specular", ss.spot_lights[0].specular);
	active_shader->setFloat("spot_light.constant", ss.spot_lights[0].constant);
	active_shader->setFloat("spot_light.linear", ss.spot_lights[0].linear);
	active_shader->setFloat("spot_light.quadratic", ss.spot_lights[0].quadratic);
	active_shader->setFloat("spot_light.cutoff", ss.spot_lights[0].cutoff);
	active_shader->setFloat("spot_light.outer_cutoff", ss.spot_lights[0].outer_cutoff);
}

void Application::drawObj(int vao, const char* shader_name, Uniforms& uni)
{

	// lit object: ground plane
	// --------------------------------------------------------------------------
	// set active shader
	this->active_shader = shaders.at(shader_name);
	// activate shader
	(*active_shader).use();
	// light uniforms
	SceneState& ss = scene_state;
	UniformsPerObject& upo = uni.upo;
	UniformsPerView& upv = uni.upv;
	UniformsPerFrame& upf = uni.upf;

	// assign uniforms
	active_shader->setInt("texture1", 0);
	active_shader->setInt("texture2", 1);
	active_shader->setFloat("mix_val", upo.mix_value);
	active_shader->setVec3("view_pos", ss.camera.position);
	active_shader->setMat4("view_proj_matrix", upv.view_proj_matrix);

	// directional light
	setDirectionalLightParameters(uni);
	// point light
	setPointLightParameters(uni);
	//// spotLight
	setSpotLightParameters(uni);

	Mat4 model = mat_utils::identity4();
	active_shader->setMat4("world_matrix", model);

	// material
	active_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	active_shader->setInt("material.diffuse_map", 0);
	active_shader->setInt("material.specular_map", 1);
	active_shader->setInt("material.emission_map", 2);
	active_shader->setFloat("material.emission_factor", sin(ss.time));
	active_shader->setFloat("material.shininess", 64.0f);
	
	// assign texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_diffuse);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture_specular);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture_emission);

	glBindVertexArray(vao);

	float scale_factor = .4f;
	float movement_scale = 2.0f;
	float y_position_of_models = .5f;
	model =
		mat_utils::translation(Vec3(0.0f, y_position_of_models, movement_scale * cos(ss.time)))
		* mat_utils::rotationY(radian(360.0f) * ss.time)
		* mat_utils::rotationX(ss.time)
		* mat_utils::scale(scale_factor, scale_factor, scale_factor)
		;
	active_shader->setMat4("world_matrix", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model =
		mat_utils::translation(Vec3(movement_scale * sin(ss.time), y_position_of_models, 0.0f))
		* mat_utils::rotationX(radian(360.0f) * ss.time)
		* mat_utils::rotationY(ss.time)
		* mat_utils::scale(scale_factor, scale_factor, scale_factor)
		;
	active_shader->setMat4("world_matrix", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// ----- draw ground plane with same 
	// --------------------------------------------------------------------------------------
	// assign texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_ground_diffuse);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture_ground_specular);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture_ground_emission);

	scale_factor = 3.0f;
	model =
		mat_utils::translation(Vec3(0.0f, 0.0f, 0.0f))
		//* mat_utils::rotationY(radian(-15.0f))
		* mat_utils::scale(scale_factor, 0.01f, scale_factor)
		;
	active_shader->setMat4("world_matrix", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);


}
