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
	uni.upv.view_matrix = scene_state.camera.calcViewMatrix();
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
	active_shader->setVec3("light_color", scene_state.light.color); // light_coloru degistirme
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
			scene_state.light.position.y, 
			multiplier * cos(scene_state.time + 2 * PI / 3.0f * ii)
			))
			* mat_utils::scale(0.05f);
		;
		active_shader->setMat4("world_matrix", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
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

	Vec3 reduced_light_diffuse = ss.light.color * 0.5f;
	Vec3 reduced_light_ambient = reduced_light_diffuse * 0.2f;
	active_shader->setVec3("light.position", ss.light.position);
	active_shader->setVec3("light.direction", ss.light.direction);
	active_shader->setFloat("light.inner_cutoff", cos(radian(12.5f)));
	active_shader->setFloat("light.outer_cutoff", cos(radian(17.5f)));
	active_shader->setFloat("light.brightness", ss.light.brightness);
	active_shader->setVec3("light.ambient", reduced_light_ambient);
	active_shader->setVec3("light.diffuse", reduced_light_diffuse); // darken diffuse light a bit
	active_shader->setVec3("light.specular", 1.0f);
	// assign uniforms
	active_shader->setInt("texture1", 0);
	active_shader->setInt("texture2", 1);
	active_shader->setFloat("mix_val", upo.mixValue);
	active_shader->setVec3("view_pos", ss.camera.position);
	active_shader->setMat4("view_proj_matrix", upv.view_proj_matrix);

	// directional light
	active_shader->setVec3("directional_light.direction", ss.light.direction);
	active_shader->setVec3("directional_light.ambient", reduced_light_ambient);
	active_shader->setVec3("directional_light.diffuse", reduced_light_diffuse); // darken diffuse light a bit
	active_shader->setVec3("directional_light.specular", 1.0f);

	// point light
	float multiplier = 2.0f;
	for (int ii = 0; ii < 3; ii++)
	{
		active_shader->setVec3("point_lights[" + std::to_string(ii) + "].position",
			Vec3(multiplier * sin(scene_state.time + 2 * PI / 3.0f * ii),
				ss.light.position.y,
				multiplier * cos(scene_state.time + 2 * PI / 3.0f * ii))
		);
		active_shader->setVec3("point_lights[" + std::to_string(ii) + "].ambient", 0.05f, 0.05f, 0.05f);
		active_shader->setVec3("point_lights[" + std::to_string(ii) + "].diffuse", 0.8f, 0.8f, 0.8f);
		active_shader->setVec3("point_lights[" + std::to_string(ii) + "].specular", 1.0f, 1.0f, 1.0f);
		active_shader->setFloat("point_lights[" + std::to_string(ii) + "].constant", 1.0f);
		active_shader->setFloat("point_lights[" + std::to_string(ii) + "].linear", 0.09f);
		active_shader->setFloat("point_lights[" + std::to_string(ii) + "].quadratic", 0.032f);
		if (ii == 0)
		{
			active_shader->setVec3("point_lights[" + std::to_string(ii) + "].diffuse", Vec3(1.0f, 0.0f, 0.0f)); // light_coloru degistirme
		}
		if (ii == 1)
		{
			active_shader->setVec3("point_lights[" + std::to_string(ii) + "].diffuse", Vec3(0.0f, 1.0f, 0.0f)); // light_coloru degistirme
		}
		if (ii == 2)
		{
			active_shader->setVec3("point_lights[" + std::to_string(ii) + "].diffuse", Vec3(0.0f, 0.0f, 1.0f)); // light_coloru degistirme
		}

	}

	// spotLight
	active_shader->setVec3("spot_light.position", ss.light.position);
	active_shader->setVec3("spot_light.direction", Vec3(0.0f, -1.0f, 0.0f));
	active_shader->setVec3("spot_light.ambient", 0.0f, 0.0f, 0.0f);
	active_shader->setVec3("spot_light.diffuse", 1.0f, 1.0f, 1.0f);
	active_shader->setVec3("spot_light.specular", 1.0f, 1.0f, 1.0f);
	active_shader->setFloat("spot_light.constant", 1.0f);
	active_shader->setFloat("spot_light.linear", 0.09f);
	active_shader->setFloat("spot_light.quadratic", 0.032f);
	active_shader->setFloat("spot_light.cutoff", cos(radian(27.5f)));
	active_shader->setFloat("spot_light.outer_cutoff", cos(radian(30.0f)));


	Mat4 model = mat_utils::identity4();
	active_shader->setMat4("world_matrix", model);
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
	model =
		mat_utils::translation(Vec3(0.0f, scene_state.camera.position.y - 2.2f, movement_scale * cos(ss.time)))
		* mat_utils::rotationY(radian(360.0f) * ss.time)
		* mat_utils::rotationX(ss.time)
		* mat_utils::scale(scale_factor, scale_factor, scale_factor)
		;
	active_shader->setMat4("world_matrix", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model =
		mat_utils::translation(Vec3(movement_scale * sin(ss.time), scene_state.camera.position.y - 2.2f, 0.0f))
		* mat_utils::rotationX(radian(360.0f) * ss.time)
		* mat_utils::rotationY(ss.time)
		* mat_utils::scale(scale_factor, scale_factor, scale_factor)
		;
	active_shader->setMat4("world_matrix", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);


}

void Application::drawGroundPlane(int vao, const char* shader_name, Uniforms& uni)
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

	Vec3 reduced_light_diffuse = ss.light.color * 0.5f;
	Vec3 reduced_light_ambient = reduced_light_diffuse * 0.2f;
	active_shader->setVec3("light.position", ss.light.position);
	active_shader->setVec3("light.direction", ss.light.direction);
	active_shader->setFloat("light.inner_cutoff", cos(radian(12.5f)));
	active_shader->setFloat("light.outer_cutoff", cos(radian(17.5f)));
	active_shader->setFloat("light.brightness", ss.light.brightness);
	active_shader->setVec3("light.ambient", reduced_light_ambient);
	active_shader->setVec3("light.diffuse", reduced_light_diffuse); // darken diffuse light a bit
	active_shader->setVec3("light.specular", 1.0f);
	// assign uniforms
	active_shader->setInt("texture1", 0);
	active_shader->setInt("texture2", 1);
	active_shader->setFloat("mix_val", upo.mixValue);
	active_shader->setVec3("view_pos", ss.camera.position);
	active_shader->setMat4("view_proj_matrix", upv.view_proj_matrix);

	// directional light
	active_shader->setVec3("directional_light.direction", ss.light.direction);
	active_shader->setVec3("directional_light.ambient", reduced_light_ambient);
	active_shader->setVec3("directional_light.diffuse", reduced_light_diffuse); // darken diffuse light a bit
	active_shader->setVec3("directional_light.specular", 1.0f);

	// point light
	float multiplier = 2.0f;
	for (int ii = 0; ii < 3; ii++)
	{
		active_shader->setVec3("point_lights[" + std::to_string(ii) + "].position",
			Vec3(multiplier * sin(scene_state.time + 2 * PI / 3.0f * ii),
				ss.light.position.y, 
				multiplier * cos(scene_state.time + 2 * PI / 3.0f * ii))
		);
		active_shader->setVec3("point_lights[" + std::to_string(ii) + "].ambient", 0.05f, 0.05f, 0.05f);
		active_shader->setVec3("point_lights[" + std::to_string(ii) + "].diffuse", 0.8f, 0.8f, 0.8f);
		active_shader->setVec3("point_lights[" + std::to_string(ii) + "].specular", 1.0f, 1.0f, 1.0f);
		active_shader->setFloat("point_lights[" + std::to_string(ii) + "].constant", 1.0f);
		active_shader->setFloat("point_lights[" + std::to_string(ii) + "].linear", 0.09f);
		active_shader->setFloat("point_lights[" + std::to_string(ii) + "].quadratic", 0.032f);
		if (ii == 1)
		{
			active_shader->setVec3("point_lights[" + std::to_string(ii) + "].diffuse", Vec3(1.0f, 0.0f, 0.0f)); // light_coloru degistirme
		}
		if (ii == 2)
		{
			active_shader->setVec3("point_lights[" + std::to_string(ii) + "].diffuse", Vec3(0.0f, 1.0f, 0.0f)); // light_coloru degistirme
		}
		if (ii == 3)
		{
			active_shader->setVec3("point_lights[" + std::to_string(ii) + "].diffuse", Vec3(0.0f, 0.0f, 1.0f)); // light_coloru degistirme
		}
	
	}

	// spotLight
	active_shader->setVec3("spot_light.position", ss.light.position);
	active_shader->setVec3("spot_light.direction", Vec3(0.0f, -1.0f, 0.0f));
	active_shader->setVec3("spot_light.ambient", 0.0f, 0.0f, 0.0f);
	active_shader->setVec3("spot_light.diffuse", 1.0f, 1.0f, 1.0f);
	active_shader->setVec3("spot_light.specular", 1.0f, 1.0f, 1.0f);
	active_shader->setFloat("spot_light.constant", 1.0f);
	active_shader->setFloat("spot_light.linear", 0.09f);
	active_shader->setFloat("spot_light.quadratic", 0.032f);
	active_shader->setFloat("spot_light.cutoff", cos(radian(27.5f)));
	active_shader->setFloat("spot_light.outer_cutoff", cos(radian(30.0f)));


	Mat4 model = mat_utils::identity4();
	active_shader->setMat4("world_matrix", model);
	active_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	active_shader->setInt("material.diffuse_map", 0);
	active_shader->setInt("material.specular_map", 1);
	active_shader->setInt("material.emission_map", 2);
	active_shader->setFloat("material.emission_factor", sin(ss.time));
	active_shader->setFloat("material.shininess", 64.0f);
	// assign texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_ground_diffuse);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture_ground_specular);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture_ground_emission);

	glBindVertexArray(vao);

	float scale_factor = 3.0f;
	model =
		mat_utils::translation(Vec3(0.0f, scene_state.camera.position.y - 2.5f, 0.0f))
		* mat_utils::rotationY(radian(-15.0f))
		* mat_utils::scale(scale_factor, 0.05f, scale_factor)
		;
	active_shader->setMat4("world_matrix", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);


}

