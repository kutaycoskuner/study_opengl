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

void Application::lightCasterScene(Uniforms& uni)
{
	UniformsPerObject& uni_obj = uni.upo;
	UniformsPerView& uni_view = uni.upv;
	UniformsPerFrame& uni_frame = uni.upf;
	// create transformations
	const SceneState& ss = scene_state;
	uni_obj.world_matrix = mat_utils::rotationX(radian(-45.0f))
		* mat_utils::rotationXYZ(ss.time, Vec3(1.0f, 1.0f, 1.0f).normalized())
		;
	uni_view.view_matrix = ss.camera.calcViewMatrix();
	uni_view.projection_matrix
		= mat_utils::projectPerspective(radian(ss.fov), ss.aspect_ratio, ss.near, ss.far);
	uni_view.view_proj_matrix = uni_view.projection_matrix * uni_view.view_matrix;
	uni_frame.light.color = ss.light.color;

	// light placeholder
	// --------------------------------------------------------------------------
	// set active shader
	this->active_shader = shaders.at("3d");
	// activate shader
	active_shader->use();
	// assign uniforms
	active_shader->setVec3("light_color", ss.light.color); // light_coloru degistirme
	active_shader->setMat4("view_matrix", uni_view.view_matrix);
	active_shader->setMat4("projection_matrix", uni_view.projection_matrix);
	active_shader->setMat4("view_proj_matrix", uni_view.view_proj_matrix);

	glBindVertexArray(VAOs[0]);
	Mat4 model = mat_utils::translation(ss.light.position)
		* mat_utils::scale(0.05f);
	;
	active_shader->setMat4("world_matrix", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// lit objects
	// --------------------------------------------------------------------------
	const char* shader_name = "lightcaster-point";
	// set active shader
	this->active_shader = shaders.at(shader_name);
	// activate shader
	(*active_shader).use();
	// light uniforms
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
	active_shader->setFloat("mix_val", uni_obj.mixValue);
	active_shader->setVec3("view_pos", ss.camera.position);
	active_shader->setMat4("view_proj_matrix", uni_view.view_proj_matrix);

	// attenuation constants for light
	active_shader->setFloat("light.constant", 1.0f);
	active_shader->setFloat("light.linear", 0.09f);
	active_shader->setFloat("light.quadratic", 0.032f);

	glBindVertexArray(litVAO);
	float angle = 0.0f;
	float mirror_x = -0.6f;
	float mirror_z = 1.0f;
	model
		= mat_utils::identity4();
	//= mat_utils::translation(Vec3(1.5f * mirror_x, -0.8f, mirror_z))
	//* mat_utils::rotationY(radian(45.0f))
	//* mat_utils::rotationY(ss.animation_time)
	//* mat_utils::scale(1.2f);
	;
	//model *= mat_utils::rotationXYZ(ss.animation_time + angle, Vec3(-1.0f, 0.0f, .1f).normalized()); //*mat_utils::scale(scale);
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

	//ss.obj_positions = {};
	//ss.obj_positions = { };
	angle = 20.0f * ss.angle_multiplier;
	float rot_scale = 1.5f;
	model = mat_utils::translation(rot_scale*sin(ss.time), ss.camera.position.y - 2.0f, rot_scale * cos(ss.time))
		* mat_utils::rotationXYZ(ss.animation_time + angle, Vec3(1.0f, 1.0f, 1.0f).normalized())
		* mat_utils::scale(.4f)
		; //*mat_utils::scale(scale);
	active_shader->setMat4("world_matrix", model);
	//model = mat_utils::projectPerspective(radian(45.0f), aspect_ratio, near, far);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//for (unsigned int ii = 0; ii < ss.obj_positions.size(); ii++)
	//{
	//	float angle = 20.0f * ii * ss.angle_multiplier;
	//	Mat4 model = mat_utils::translation(ss.obj_positions[ii])
	//		* mat_utils::rotationXYZ(ss.animation_time + angle, Vec3(1.0f, 1.0f, 1.0f).normalized())
	//		* mat_utils::scale(.5f)
	//	; //*mat_utils::scale(scale);
	//	active_shader->setMat4("world_matrix", model);
	//	//model = mat_utils::projectPerspective(radian(45.0f), aspect_ratio, near, far);
	//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//	glDrawArrays(GL_TRIANGLES, 0, 36);
	//}

	// lit object: ground plane
	// --------------------------------------------------------------------------
	// set active shader
	this->active_shader = shaders.at(shader_name);
	// activate shader
	(*active_shader).use();
	// assign uniforms
	active_shader->setVec3("obj_color", ByteToZeroOne(6, 180, 186));

	glBindVertexArray(litVAO);

	float scale_factor = 3.0f;
	model =
		mat_utils::translation(Vec3(0.0f, ss.camera.position.y - 2.5f, 0.0f))
		* mat_utils::rotationY(radian(-15.0f))
		* mat_utils::scale(scale_factor, 0.05f, scale_factor)
		;
	//model *= mat_utils::rotationXYZ(ss.animation_time + angle, Vec3(-1.0f, 0.0f, .1f).normalized()); //*mat_utils::scale(scale);
	active_shader->setMat4("world_matrix", model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//float both = 20.0f;
	//model =
	//	mat_utils::translation(Vec3(0.0f, 0.0f, -10.0f))
	//	* mat_utils::scale(both, both, 0.05f)
	//;
	//active_shader->setMat4("world_matrix", model);
	//glDrawArrays(GL_TRIANGLES, 0, 36);

}

void Application::lightMapScene(Uniforms& uni)
{
	UniformsPerObject& uni_obj = uni.upo;
	UniformsPerView& uni_view = uni.upv;
	UniformsPerFrame& uni_frame = uni.upf;
	// create transformations
	const SceneState& ss = scene_state;
	uni_obj.world_matrix = mat_utils::rotationX(radian(-45.0f))
		* mat_utils::rotationXYZ(ss.time, Vec3(1.0f, 1.0f, 1.0f).normalized())
		;
	uni_view.view_matrix = ss.camera.calcViewMatrix();
	uni_view.projection_matrix
		= mat_utils::projectPerspective(radian(ss.fov), ss.aspect_ratio, ss.near, ss.far);
	uni_view.view_proj_matrix = uni_view.projection_matrix * uni_view.view_matrix;
	uni_frame.light.color = ss.light.color;

	// light placeholder
	// --------------------------------------------------------------------------
	// set active shader
	this->active_shader = shaders.at("3d");
	// activate shader
	active_shader->use();
	// assign uniforms
	active_shader->setVec3("light.color", ss.light.color);
	active_shader->setMat4("view_matrix", uni_view.view_matrix);
	active_shader->setMat4("projection_matrix", uni_view.projection_matrix);
	active_shader->setMat4("view_proj_matrix", uni_view.view_proj_matrix);

	glBindVertexArray(VAOs[0]);
	Mat4 model = mat_utils::translation(ss.light.position)
		* mat_utils::scale(0.1f);
	;
	active_shader->setMat4("world_matrix", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// lit object: 1
	// --------------------------------------------------------------------------
	// set active shader
	this->active_shader = shaders.at("lightmap");
	// activate shader
	(*active_shader).use();
	// light uniforms
	Vec3 reduced_light_diffuse = ss.light.color * 0.5f;
	Vec3 reduced_light_ambient = reduced_light_diffuse * 0.2f;
	active_shader->setVec3("light.position", ss.light.position);
	active_shader->setVec3("light.ambient", reduced_light_ambient);
	active_shader->setVec3("light.diffuse", reduced_light_diffuse); // darken diffuse light a bit
	active_shader->setVec3("light.specular", 1.0f);
	// assign uniforms
	active_shader->setInt("texture1", 0);
	active_shader->setInt("texture2", 1);
	active_shader->setFloat("mix_val", uni_obj.mixValue);
	active_shader->setVec3("light.position", ss.light.position);
	active_shader->setVec3("view_pos", ss.camera.position);
	active_shader->setMat4("view_proj_matrix", uni_view.view_proj_matrix);

	glBindVertexArray(litVAO);
	float angle = 0.0f;
	float mirror_x = -0.6f;
	float mirror_z = 1.0f;
	model = mat_utils::translation(Vec3(1.5f * mirror_x, -0.8f, mirror_z))
		* mat_utils::rotationY(radian(45.0f))
		* mat_utils::rotationY(ss.animation_time)
		* mat_utils::scale(1.2f);
	;
	//model *= mat_utils::rotationXYZ(ss.animation_time + angle, Vec3(-1.0f, 0.0f, .1f).normalized()); //*mat_utils::scale(scale);
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

	glDrawArrays(GL_TRIANGLES, 0, 36);

}


void Application::phongScene(Uniforms& uni)
{
	// todo: draw parameters structa topla | 
	UniformsPerObject& uni_obj = uni.upo;
	UniformsPerView& uni_view = uni.upv;
	UniformsPerFrame& uni_frame = uni.upf;

	// create transformations
	const SceneState& ss = scene_state;
	uni_obj.world_matrix = mat_utils::rotationX(radian(-45.0f))
		* mat_utils::rotationXYZ(ss.time, Vec3(1.0f, 1.0f, 1.0f).normalized())
		;
	uni_view.view_matrix = ss.camera.calcViewMatrix();
	uni_view.projection_matrix
		= mat_utils::projectPerspective(radian(ss.fov), ss.aspect_ratio, ss.near, ss.far);
	uni_view.view_proj_matrix = uni_view.projection_matrix * uni_view.view_matrix;
	uni_frame.light.color = ss.light.color;

	// light placeholder
	// --------------------------------------------------------------------------
	// set active shader
	this->active_shader = shaders.at("3d");
	// activate shader
	active_shader->use();
	// assign uniforms
	active_shader->setVec3("light.color", ss.light.color);
	active_shader->setMat4("view_matrix", uni_view.view_matrix);
	active_shader->setMat4("projection_matrix", uni_view.projection_matrix);
	active_shader->setMat4("view_proj_matrix", uni_view.view_proj_matrix);

	glBindVertexArray(VAOs[0]);
	Mat4 model = mat_utils::translation(ss.light.position)
		* mat_utils::scale(0.04f);
	;
	active_shader->setMat4("world_matrix", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	//for (unsigned int ii = 0; ii < ss.obj_positions.size(); ii++)
	//{
	//	float angle = 20.0f * ii * ss.angle_multiplier;
	//	Mat4 model = mat_utils::translation(ss.obj_positions[ii]) * mat_utils::rotationXYZ(ss.animation_time + angle, Vec3(1.0f, 1.0f, 1.0f).normalized()); //*mat_utils::scale(scale);
	//	active_shader->setMat4("world_matrix", model);
	//	//model = mat_utils::projectPerspective(radian(45.0f), aspect_ratio, near, far);
	//	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//	glDrawArrays(GL_TRIANGLES, 0, 36);
	//}

	// lit object: 1
	// --------------------------------------------------------------------------
	// set active shader
	this->active_shader = shaders.at("phong");
	// activate shader
	(*active_shader).use();
	// light uniforms
	Vec3 reduced_light_diffuse = ss.light.color * 0.5f;
	Vec3 reduced_light_ambient = reduced_light_diffuse * 0.2f;
	active_shader->setVec3("light.position", ss.light.position);
	active_shader->setVec3("light.ambient", reduced_light_ambient);
	active_shader->setVec3("light.diffuse", reduced_light_diffuse); // darken diffuse light a bit
	active_shader->setVec3("light.specular", 1.0f);
	// assign uniforms
	active_shader->setInt("texture1", 0);
	active_shader->setInt("texture2", 1);
	active_shader->setFloat("mix_val", uni_obj.mixValue);
	active_shader->setVec3("light.position", ss.light.position);
	active_shader->setVec3("view_pos", ss.camera.position);
	active_shader->setMat4("view_proj_matrix", uni_view.view_proj_matrix);

	setMaterial(PresetMaterial::red_plastic);


	glBindVertexArray(litVAO);

	float angle = 0.0f;
	float mirror_x = -0.7f;
	float mirror_z = -1.0f;
	model = mat_utils::translation(Vec3(1.5f * mirror_x, ss.light.position.y / 2, mirror_z))
		* mat_utils::rotationY(radian(45.0f))
		* mat_utils::rotationXYZ(ss.animation_time, Vec3(1.0f, 0.0f, -0.3f).normalized())
		* mat_utils::scale(0.4f);
	;
	//model *= mat_utils::rotationXYZ(ss.animation_time + angle, Vec3(-1.0f, 0.0f, .1f).normalized()); //*mat_utils::scale(scale);
	active_shader->setMat4("world_matrix", model);

	// assign texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// lit object: 2
// --------------------------------------------------------------------------
// set active shader
	this->active_shader = shaders.at("phong");
	// activate shader
	(*active_shader).use();
	// assign uniforms
	active_shader->setVec3("obj_color", ByteToZeroOne(145, 255, 1));

	glBindVertexArray(litVAO);

	model = mat_utils::translation(Vec3(-mirror_x, ss.light.position.y / 2, -mirror_z))
		* mat_utils::rotationY(radian(45.0f))
		* mat_utils::rotationXYZ(ss.animation_time, Vec3(1.0f, 0.0f, -0.3f).normalized())
		* mat_utils::scale(0.4f);
	;
	//model *= mat_utils::rotationXYZ(ss.animation_time + angle, Vec3(-1.0f, 0.0f, .1f).normalized()); //*mat_utils::scale(scale);
	active_shader->setMat4("world_matrix", model);
	setMaterial(PresetMaterial::emerald);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// lit object: ground plane
	// --------------------------------------------------------------------------
	// set active shader
	this->active_shader = shaders.at("phong");
	// activate shader
	(*active_shader).use();
	// assign uniforms
	active_shader->setVec3("obj_color", ByteToZeroOne(6, 180, 186));

	glBindVertexArray(litVAO);

	model =
		mat_utils::translation(Vec3(0.0f, ss.light.position.y - 1.0f, 0.0f))
		//* mat_utils::rotationX(radian(135.0f))
		//* mat_utils::rotationY(radian(100.0f*ss.time))
		//* mat_utils::rotationX(radian(-45.0f))
		* mat_utils::scale(3.0f, 0.05f, 3.0f)
		//* mat_utils::scale(5.0f, 5.0f, 0.1f);
		;
	//model *= mat_utils::rotationXYZ(ss.animation_time + angle, Vec3(-1.0f, 0.0f, .1f).normalized()); //*mat_utils::scale(scale);
	active_shader->setMat4("world_matrix", model);
	setMaterial(PresetMaterial::bronze);

	glDrawArrays(GL_TRIANGLES, 0, 36);

}