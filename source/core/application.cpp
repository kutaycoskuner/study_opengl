// ---------------------------------------------------------------------------------------
//				Notes
// ---------------------------------------------------------------------------------------
/*
	I will write some stuff here someday.
	...
*/
#if 1
// ---------------------------------------------------------------------------------------
//				Libraries
// ---------------------------------------------------------------------------------------
#include "basic.h"			// project start basic test
#include "utilities.h"		// self written utilities
#include "data.h"			// data headers ex. model vertices
#include "events.h"		// window, mouse-, keyboard input events
#include "application.h"	
#include "camera.h"				
#include "shader.h"				
#include "material.h"				
#include "uniforms.h"	
#include "model.h"		
#include "shaders.h"			
#include "opengl.h"			

#include "../../headers/data/scenes.h"

#include <GLFW/glfw3.h>  // opengl i daha rahat kullanabilmek icin fonksion kutuphanesi
#include <glad/glad.h>	 // opengl hardware adaptor before glfw
#include <iostream>				
#include <string>				
#include <unordered_map>		
#include <cmath>     			

#include <memory>
#include <filesystem>
#include <format>

// ---------------------------------------------------------------------------------------
//				self keywords
// ---------------------------------------------------------------------------------------
using uint = unsigned int;		// unsigned int yerine uint kisayolu tanimlama
using namespace math_utils;
using namespace str_utils;
using namespace file_utils;
using namespace img_utils;

// ---------------------------------------------------------------------------------------
//				global, constant variables
// ---------------------------------------------------------------------------------------
constexpr unsigned int kg_error_buffer_size = 512;
Application* gp_app;
const Vec3	Application::world_up = Vec3(0.0f, 1.0f, 0.0f);
const Vec3	Application::world_origin = Vec3(0.0f, 0.0f, 0.0f);
bool		Application::toggle_mouselock = true;

// ---------------------------------------------------------------------------------------
//				functions definitions
// ---------------------------------------------------------------------------------------   
void Application::disableStencil()
{
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
}

void Application::enableStencil()
{
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);
	//glDisable(GL_DEPTH_TEST);
}

void Application::clearStencil()
{
	// return to default state
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	glClear(GL_STENCIL_BUFFER_BIT);

	//glEnable(GL_DEPTH_TEST);
}


bool Application::initialize(const ConfigData& config)
{
	gp_app = this;

	shadowmap_aspect_ratio = float(shadowmap_resolution_x) / float(shadowmap_resolution_y);

	const unsigned int k_scr_width = std::stoul(config.at("scr").at("width"));
	const unsigned int k_scr_height = std::stoul(config.at("scr").at("height"));
	const char* kp_wndw_name = config.at("scr").at("wndw_name").c_str();


	initWindowSystem(k_scr_width, k_scr_height, kp_wndw_name);
	const char* glsl_version = "#version 330";
	window_state.b_first_mouse = true;
	window_state.mouse_x = std::stoul(config.at("scr").at("width")) / 2.0f;
	window_state.mouse_y = std::stoul(config.at("scr").at("height")) / 2.0f;

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return bool(-1);
	}

	initUISystem(glsl_version);


	// init asset importer
	Assimp::Importer importer;
	if (!importer.IsExtensionSupported("obj")) {
		std::cout << "Failed to load Assimp library." << std::endl;
	}

	// our state
	std::vector<unsigned int> bg_rgb = color_utils::hexToRGB(config.at("colors").at("bg"));


	this->clear_color = Vec4(
		scaleByteToZeroOne(float(bg_rgb[0])),
		scaleByteToZeroOne(float(bg_rgb[1])),
		scaleByteToZeroOne(float(bg_rgb[2])),
		1.00f
	);


	// 3.11 configure MSAA framebuffer / hdr
	// --------------------------
	glGenFramebuffers(1, &fbo_illumination_msaa);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_illumination_msaa);
	// create a multisampled color attachment texture
	glGenTextures(1, &tex_illumination_msaa_color);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, tex_illumination_msaa_color);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sample_count, GL_RGBA16F, display_width, display_height, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, tex_illumination_msaa_color, 0);
	// create a (also multisampled) renderbuffer object for depth and stencil attachments
	glGenRenderbuffers(1, &rbo_illumination_msaa);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_illumination_msaa);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, sample_count, GL_DEPTH24_STENCIL8, display_width, display_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_illumination_msaa);

	// set up floating point framebuffer to render scene to
	glGenFramebuffers(1, &fbo_illumination_hdr);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_illumination_hdr);
	glGenTextures(2, tex_illumination_hdr);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, tex_illumination_hdr[i]);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA16F, display_width, display_height, 0, GL_RGBA, GL_FLOAT, NULL
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// attach texture to framebuffer
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, tex_illumination_hdr[i], 0
		);
	}

	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// bloom buffer and textures
	glGenFramebuffers(2, fbo_bloom);
	glGenTextures(2, tex_bloom);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_bloom[i]);
		glBindTexture(GL_TEXTURE_2D, tex_bloom[i]);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA16F, display_width, display_height, 0, GL_RGBA, GL_FLOAT, NULL
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(
			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_bloom[i], 0
		);
	}

	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	// 3.4 generate frame buffer object 
	// -------------------------
	glGenFramebuffers(1, &fbo_backbuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_backbuffer);
	//// create floating point color buffer
	//unsigned int color_buffer;
	//glGenTextures(1, &color_buffer);
	//glBindTexture(GL_TEXTURE_2D, color_buffer);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, display_width, display_height, 0, GL_RGBA, GL_FLOAT, NULL);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glBindFramebuffer(GL_FRAMEBUFFER, fbo_lighting);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_buffer, 0);
	////// create depth buffer (renderbuffer)
	////unsigned int render_buffer_obj_depth;
	////glGenRenderbuffers(1, &render_buffer_obj_depth);
	////glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_obj_depth);
	////glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, display_width, display_height);
	//// attach buffers
	////glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	////glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_buffer, 0);
	//////glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_buffer_obj_depth);
	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	//	std::cout << "Framebuffer not complete!" << std::endl;
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);


	// 4.3 shadow fbo
	// ---------------------------------------------------------
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	fbo_shadow.push_back(depthMapFBO);  // Store FBO ID


	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		shadowmap_resolution_x, shadowmap_resolution_y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float border_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

	tex_shadow_maps.push_back(depthMap);

	// Enable drawing to the back buffer
	//glDrawBuffer(GL_BACK);
	// Enable reading from the front buffer
	//glReadBuffer(GL_FRONT);

	// 4.4 point cubemap
	// ---------------------------------------------------------
	unsigned int shadow_cubemap_fbo;
	glGenFramebuffers(1, &shadow_cubemap_fbo);
	fbo_shadow_cube.push_back(shadow_cubemap_fbo);

	unsigned int shadow_depth_cubemap;
	glGenTextures(1, &shadow_depth_cubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadow_depth_cubemap);
	for (unsigned int i = 0; i < 6; ++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
			shadowmap_resolution_x, shadowmap_resolution_y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	tex_shadow_cubemaps.push_back(shadow_depth_cubemap);

	// texture for framebuffer
	// ---------------------------------------------------------
	glGenTextures(1, &fbo_backbuffer_color);
	glBindTexture(GL_TEXTURE_2D, fbo_backbuffer_color);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, k_scr_width, k_scr_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_backbuffer_color, 0);

	// deferred shading buffer
    // ----------------------------------------------------------
	glGenFramebuffers(1, &g_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, g_buffer);

	// - position color buffer
    glGenTextures(1, &g_position);
    glBindTexture(GL_TEXTURE_2D, g_position);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, display_width, display_height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_position, 0);

	// normal color buffer
    glGenTextures(1, &g_normal);
    glBindTexture(GL_TEXTURE_2D, g_normal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, display_width, display_height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, g_normal, 0);

	// - color + specular color buffer
    glGenTextures(1, &g_color_specular);
    glBindTexture(GL_TEXTURE_2D, g_color_specular);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, display_width, display_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, g_color_specular, 0);

	// - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    unsigned int attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3, attachments);

	// rbo
    // ----------------------------------------------------------
	glGenRenderbuffers(1, &rbo_backbuffer_depth);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_backbuffer_depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, k_scr_width, k_scr_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo_backbuffer_depth);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer error: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
	// unbind frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	input_speaker.addListener(this);

	// gamma background linear -> srgb
	clear_color.x = pow(clear_color.x, 2.2);
	clear_color.y = pow(clear_color.y, 2.2);
	clear_color.z = pow(clear_color.z, 2.2);

	return 0;
}

bool Application::load(const ConfigData& config)
{
	loadConfig(config);

	loadSceneData(config);

	loadShaders();

	// 3.8 generate uniform buffer object matrices
	// ----------------------------------------------------------------------------------------------
	// first. We get the relevant block indices
	std::vector<std::string> uniform_buffer_array;
	uniform_buffer_array.push_back("advglsl-red");
	uniform_buffer_array.push_back("advglsl-green");
	uniform_buffer_array.push_back("advglsl-blue");
	uniform_buffer_array.push_back("advglsl-yellow");


	for (int ii = 0; ii < uniform_buffer_array.size(); ii++)
	{
		std::string shaderName = uniform_buffer_array[ii]; // Replace this with the actual shader name

		auto shaderIter = shaders.find(shaderName);
		if (shaderIter != shaders.end()) {
			// The shader with the given name exists in the map
			// Access the id of the shader through the shared pointer
			GLuint shaderId = shaderIter->second->ID;
			unsigned int uniform_block_index1 = glGetUniformBlockIndex(shaderId, "Matrices");
			glUniformBlockBinding(shaderId, uniform_block_index1, 0);

			// Now you can use the shader id as needed
		}
		else {
			std::cout << "Uniform buffer objects are not loaded" << std::endl;
		}

	}

	// Now actually create the buffer
	int range = 5002;
	glGenBuffers(1, &ubo_matrices);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrices);
	glBufferData(GL_UNIFORM_BUFFER, range * sizeof(Mat4), NULL, GL_STATIC_DRAW); // allocate size of mat4 x2 byte of memory
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	// define the range of the buffer that links to a uniform binding point
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo_matrices, 0, range * sizeof(Mat4));

	loadTextures();

	loadMeshData();

	return 1;
}

void Application::loadConfig(const ConfigData& config)
{
	// load config states
	this->b_wireframe_mode = config.at("settings").at("is_wireframeMode") == "true";
}

void Application::loadSceneData(const ConfigData& config)
{

	int scene_number = std::stoi(config.at("scene").at("active_scene"));
	if (active_test_scene > 12) {
		create_test_scene_frames = false;
		save_frame = false;
	}
	if (create_test_scene_frames) {
		scene_number = active_test_scene;
		save_frame = true;
	}
	// select scene test scene
	if (scene_number == 0)			active_scene = new TestScene;
	else if (scene_number == 1)		active_scene = new MultipleLightsTestScene;
	else if (scene_number == 2)		active_scene = new ImportModelTestScene;
	else if (scene_number == 3)		active_scene = new OutlinerTestScene;
	else if (scene_number == 4)		active_scene = new BlendingTestScene;
	else if (scene_number == 5)		active_scene = new FaceCullingTestScene;
	else if (scene_number == 6)		active_scene = new FrameBufferTestScene;
	else if (scene_number == 7)		active_scene = new CubemapTestScene;
	else if (scene_number == 8)		active_scene = new AdvancedGLSLTestScene;
	else if (scene_number == 9)		active_scene = new GeoShaderTestScene;
	else if (scene_number == 10)	active_scene = new InstancingTestScene;
	else if (scene_number == 11)	active_scene = new AntiAliasingTestScene;
	else if (scene_number == 12)	active_scene = new BlinnPhongTestScene;
	else if (scene_number == 13)	active_scene = new GammaCorrectionTestScene;
	else if (scene_number == 14)	active_scene = new ShadowsTestScene;
	else if (scene_number == 15)	active_scene = new PointShadowsTestScene;
	else if (scene_number == 16)	active_scene = new NormalMapTestScene;
	else if (scene_number == 17)	active_scene = new ParallaxTestScene;
	else if (scene_number == 18)	active_scene = new HDRTestScene;
	else if (scene_number == 19)	active_scene = new BloomTestScene;
	else if (scene_number == 20)	active_scene = new DeferredShadingTestScene;


	// ----- set cubemap
	// --------------------------------------------------------------------------------------
	cubemap_texture = img_utils::loadCubemap(data_dir_path, PathAfterDirectory::cubemap_texture_paths["nebula-blue"]);


	// ----- camera
	// --------------------------------------------------------------------------------------
	active_scene->cameras.push_back(Camera());
	Camera& cam = active_scene->cameras.back();

	cam.near = std::stof(config.at("default_camera").at("near"));
	cam.far = std::stof(config.at("default_camera").at("far"));
	cam.fov = std::stof(config.at("default_camera").at("fov"));
	// cam.rotation_sensitivity = std::stof(config.at("default_camera").at("rotation_sensitivity"));
	resetCamera();
	active_scene->loadData();
	SceneState& scene_state = active_scene->scene_state;
	// register listeners
	input_speaker.addListener(active_scene);
	// ui
	scene_state.b_toggleui = false;

	// animation
	scene_state.last_frame_time = std::stof(config.at("default_animation")
		.at("last_frame_time"));

	// predefined_scene_element_transforms
	Transform transform;
	scene_state.transforms.push_back(transform);

	// ----- models
	// --------------------------------------------------------------------------------------
	std::vector<const char*> model_paths = loadModelPaths();

	for (int ii = 0; ii < model_paths.size(); ii++)
	{
		Model ourModel((data_dir_path + model_paths[ii]).c_str());
		active_scene->models.push_back(Model(ourModel));
	}

	//		ui bindings
	// --------------------------------------------------------------------------------------
	if (active_scene->predefined_scene_elements.size() > 0)
		ui_vector = active_scene->predefined_scene_elements.back().transform.position;
}

void Application::loadTextures()
{
	// texture
	setVerticalFlipMode(true);

	for (auto it = active_scene->texture_names.begin(); it != active_scene->texture_names.end(); ++it)
	{
		TextureSet	texture_set;
		std::string texture_name = *it;
		PathAfterDirectory::texture_paths[texture_name].color != "" ?
			texture_set.color = createTexture(data_dir_path, PathAfterDirectory::texture_paths[texture_name].color)
			: texture_set.color = 0;

		PathAfterDirectory::texture_paths[texture_name].roughness != "" ?
			texture_set.roughness = createTexture(data_dir_path, PathAfterDirectory::texture_paths[texture_name].roughness)
			: texture_set.roughness = 0;

		PathAfterDirectory::texture_paths[texture_name].normal != "" ?
			texture_set.normal = createTexture(data_dir_path, PathAfterDirectory::texture_paths[texture_name].normal)
			: texture_set.normal = 0;

		PathAfterDirectory::texture_paths[texture_name].specular != "" ?
			texture_set.specular = createTexture(data_dir_path, PathAfterDirectory::texture_paths[texture_name].specular)
			: texture_set.specular = 0;

		PathAfterDirectory::texture_paths[texture_name].emission != "" ?
			texture_set.emission = createTexture(data_dir_path, PathAfterDirectory::texture_paths[texture_name].emission)
			: texture_set.emission = 0;
		textures[texture_name] = texture_set;

		PathAfterDirectory::texture_paths[texture_name].displacement != "" ?
			texture_set.displacement = createTexture(data_dir_path, PathAfterDirectory::texture_paths[texture_name].displacement)
			: texture_set.displacement = 0;
		textures[texture_name] = texture_set;
	}

}

void Application::loadShaders()
{
    // Iterate over the shader paths map
    for (const auto& [shader_name, path_struct] : PathAfterDirectory::shader_paths)
    {

		const std::string rel_vrtx = std::string(path_struct.vrtx);
        const std::string rel_frag = std::string(path_struct.frag);
        const std::string rel_geom = std::string(path_struct.geom);


        // Convert std::string_view to std::string within the function calls
        const std::string vrtx = std::string(file_utils::getFileNameWithoutExtension(rel_vrtx));
        const std::string frag = std::string(file_utils::getFileNameWithoutExtension(rel_frag));
        const std::string geom =
            path_struct.geom.empty()
                ? ""
                : std::string(file_utils::getFileNameWithoutExtension(rel_geom));

        // Create the ShaderCompileDesc object
        ShaderCompileDesc shader_compile_description;
        shader_compile_description.name      = shader_name;
        shader_compile_description.vrtx_path = shader_dir_path + rel_vrtx;
        shader_compile_description.frag_path = shader_dir_path + rel_frag;
        shader_compile_description.geom_path = geom.empty() ? "" : shader_dir_path + rel_geom;

        // Store shader in the map using shader_name as the key
        shaders[shader_name] = std::make_shared<Shader>(shader_compile_description);

        // Optional: Set uniform block for matrices
        // unsigned int uniform_block_index = glGetUniformBlockIndex(shaders.at(shader_name)->ID, "Matrices");
        // glUniformBlockBinding(shaders.at(shader_name)->ID, uniform_block_index, 0);
    }
}



std::vector<const char*> Application::loadModelPaths()
{
	std::vector<const char*> model_paths;
	for (const std::string& path : active_scene->model_paths)
	{
		model_paths.push_back(path.c_str());
	}
	return model_paths;
}


void Application::loadMeshData()
{
	// create vertex array object and vertex buffer object
	glGenVertexArrays(buffer_count, vertex_arrays);
	glGenBuffers(buffer_count, vertex_buffers); // :: memory alani olusturuyor
	glGenBuffers(buffer_count, element_buffers); // :: ebo icin memory


	// binding buffers
	//glBindVertexArray(vertex_arrays[0]);
	//glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData::cube_vrts__pos_uv), VertexData::cube_vrts__pos_uv, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffers[0]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VertexData::square_inds), VertexData::square_inds, GL_STATIC_DRAW);

	// linking vertex attributes
	// --------------------------       
	// 1. parameter specifies which vertex attribute we want to configure  | location of position
	// 2. parameter specifies siez of vertex. 3vec3 so 3 value
	// 3. parameter specifies type of data gl_float
	// 4. parameter specifies if you want to data to be normalized
	// 5. known as stride space between consequtive vertex attributes
	// 6. void this is the !! offset where the position data begins in the buffer

	// stride
	// lit: coord, normal, texture
	//glGenVertexArrays(1, &lit_vao);
	//glGenBuffers(1, &lit_vbo); // :: memory alani olusturuyor
	//glBindBuffer(GL_ARRAY_BUFFER, lit_vbo);
	//// we only need to bind to the VBO, the container's VBO's data already contains the data.
	//glBindVertexArray(lit_vao);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData::cube_vrts__pos_norm_uv), VertexData::cube_vrts__pos_norm_uv, GL_STATIC_DRAW);
	//stride = 8;
	//// set the vertex attribute 
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// att: normals
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//// att: texture
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	//generateBuffer(lit_vao, lit_vbo, VertexData::cube_vrts__pos_uv, 5, 1, 0);

	glGenBuffers(1, &lit_ebo); // :: ebo icin memory
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lit_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(VertexData::cube_inds__pos_norm_uv), VertexData::cube_inds__pos_norm_uv, GL_STATIC_DRAW);

	// --working
	//PredefNameMaps::predef3d_namemap;
	//for (int ii = 0; ii < PredefNameMaps::predef3d_namemap.size(); ii++)
	unsigned int ii = 0;
	for (auto it = PredefNameMaps::predef3d_namemap.begin(); it != PredefNameMaps::predef3d_namemap.end(); ++it) {
		Predef3DNode it_obj = it->second;
		glGenVertexArrays(1, &vertex_arrays[ii]);
		glGenBuffers(1, &vertex_buffers[ii]);
		glBindVertexArray(vertex_arrays[ii]);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[ii]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * it_obj.num_elements, it_obj.p_data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, it_obj.att_num_elements[0], GL_FLOAT, GL_FALSE, it_obj.stride * sizeof(float), (void*)0);

		if (it_obj.att_num_elements.size() > 1) {
			glEnableVertexAttribArray(1);
			unsigned int att_size = it_obj.att_num_elements[0];
			glVertexAttribPointer(1, it_obj.att_num_elements[1], GL_FLOAT, GL_FALSE, it_obj.stride * sizeof(float), (void*)(att_size * sizeof(float)));
		}

		if (it_obj.att_num_elements.size() > 2) {
			glEnableVertexAttribArray(2);
			unsigned int att_size = it_obj.att_num_elements[0] + it_obj.att_num_elements[1];
			glVertexAttribPointer(2, it_obj.att_num_elements[2], GL_FLOAT, GL_FALSE, it_obj.stride * sizeof(float), (void*)(att_size * sizeof(float)));
		}

		// application specific name mapping
		named_arrays[it->first] = vertex_arrays[ii];
		ii++;
	}


	//glGenBuffers(1, &instanced_buffer);
	////glBindBuffer(GL_ARRAY_BUFFER, instanced_buffer);
	////glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * 100, &active_scene->computed_data.translations2d[0], GL_STATIC_DRAW);
	////glBindBuffer(GL_ARRAY_BUFFER, 0);

	////glEnableVertexAttribArray(2);
	////glBindBuffer(GL_ARRAY_BUFFER, instanced_buffer);
	////glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	////glBindBuffer(GL_ARRAY_BUFFER, 0);
	////glVertexAttribDivisor(2, 1);

	//glBindBuffer(GL_ARRAY_BUFFER, instanced_buffer);
	//glBufferData(GL_ARRAY_BUFFER, active_scene->scene_state.instance_count * sizeof(Mat4),
	//	&active_scene->computed_data.mat4[0], GL_STATIC_DRAW);
	//for (unsigned int i = 0; i < active_scene->models.size(); i++)
	//{
	//	unsigned int VAO = active_scene->models[i].meshes.VAO;
	//	glBindVertexArray(VAO);
	//	// vertex attributes
	//// vertex attributes
	//	std::size_t vec4Size = sizeof(Vec4);
	//	glEnableVertexAttribArray(3);
	//	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
	//	glEnableVertexAttribArray(4);
	//	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
	//	glEnableVertexAttribArray(5);
	//	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
	//	glEnableVertexAttribArray(6);
	//	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

	//	glVertexAttribDivisor(3, 1);
	//	glVertexAttribDivisor(4, 1);
	//	glVertexAttribDivisor(5, 1);
	//	glVertexAttribDivisor(6, 1);

	//	glBindVertexArray(0);
	//}


	// Instancing vbo test 
	if (active_scene->scene_state.using_computed_data)
	{
		unsigned int amount = active_scene->scene_state.instance_count;
		glGenBuffers(1, &instanced_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, instanced_buffer);
		glBufferData(GL_ARRAY_BUFFER, amount * sizeof(Mat4), &active_scene->computed_data.mat4[0], GL_STATIC_DRAW);

		Model rock = active_scene->models[0];
		for (unsigned int i = 0; i < rock.meshes.size(); i++)
		{
			unsigned int VAO = rock.meshes[i].vao;
			glBindVertexArray(VAO);
			// vertex attributes
			GLsizei vec4Size = sizeof(Vec4);
			size_t vec4stride = vec4Size;
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4stride));
			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4stride));
			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4stride));

			glVertexAttribDivisor(3, 1);
			glVertexAttribDivisor(4, 1);
			glVertexAttribDivisor(5, 1);
			glVertexAttribDivisor(6, 1);

			glBindVertexArray(0);
		}
	}


	// clean new_up
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Application::generateBuffer(uint vrtx_arr, uint vrtx_buffer, const float obj_vrts[], const uint& stride, bool vrtx, bool tex)
{
	// light
	glGenVertexArrays(1, &vrtx_arr);
	glGenBuffers(1, &vrtx_buffer); // :: memory alani olusturuyor
	glBindBuffer(GL_ARRAY_BUFFER, vrtx_buffer);
	// we only need to bind to the VBO, the container's VBO's data already contains the data.
	// todo: vertexbuffer class olustur
	glBindVertexArray(vrtx_arr);
	glBufferData(GL_ARRAY_BUFFER, sizeof(obj_vrts), obj_vrts, GL_STATIC_DRAW);
	// att: vrtx 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
	if (vrtx)
		glEnableVertexAttribArray(0);
	// att: texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(3 * sizeof(float)));
	if (tex)
		glEnableVertexAttribArray(2);
}

void Application::generateShadowFBO()
{
}

void Application::mainLoop(ConfigData& config)
{
	// uniform variables according to update frequency
	Uniforms uni;
	UniformsPerObject& uni_obj = uni.upo;
	UniformsPerView& uni_view = uni.upv;
	UniformsPerFrame& uni_frame = uni.upf;

	// initial values for the uniforms
	uni_obj.world_matrix = mat_utils::identity4();
	uni_view.view_matrix = mat_utils::identity4();
	uni_view.projection_matrix = mat_utils::identity4();
	uni_obj.mix_value = 0.2f;

	// ----- render loop 
	// --------------------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window) && reload == false)
	{
		processInput(window, uni_obj);
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		Camera& cam = active_scene->cameras[0];
		camera_aspect_ratio = float(w) / float(h);
		cam.aspect_ratio = camera_aspect_ratio;

		// Start the Dear ImGui frame
		updateUI();

		updateScene();

		drawScene(uni);

		drawUI();
		
		glfwSwapBuffers(window);
		glfwPollEvents();


		if (!ui_events.is_empty())
		{
			for (const auto& pair : ui_events.peek()) {
				if (pair.first == UIEvent::SelectScene)
				{
					config["scene"]["active_scene"] = std::to_string(pair.second[0]);
					ui_events.remove();
					reload = true;
				}
				ui_events.remove();
				break;
			}
		}
		else if (create_test_scene_frames)
		{
			reload = true;
			save_frame = true;
			active_test_scene += 1;
			break;
		}

	}
}

int Application::initWindowSystem(const unsigned int& width, const unsigned int& height, const char*& window_name)
{
	// :: GLFW
	glfwInit();
	// first param what option we want to configure; second option is value we set.
	// 3 means we are explicitly using core profile. version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_SAMPLES, 4);
	//
	// if apple

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	//glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
	this->window = glfwCreateWindow(width, height, window_name, NULL, NULL);
	// first two parameters x,y in size; 3. name; 4-5 necessary but ignore
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// resize handle
	glfwSetFramebufferSizeCallback(window, callbackFrameBufferSize);
	glfwSetCursorPosCallback(window, callbackMouse);
	glfwSetScrollCallback(window, callbackScroll);
	return 0;
}


void Application::unload()
{
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	input_speaker.removeListener(active_scene);
	delete active_scene;
	//glDeleteVertexArrays(1, &lit_vao);
	//glDeleteBuffers(1, &lit_vbo);
	if (!reload)
	{
		glDeleteFramebuffers(1, &fbo_backbuffer);
		glDeleteRenderbuffers(1, &rbo_backbuffer_depth);
		glDeleteVertexArrays(buffer_count, vertex_arrays);
		glDeleteBuffers(buffer_count, vertex_buffers);
	}
}

int Application::exit()
{
	// glfw: purge allocated memory
	// ------------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void Application::compute_QuadVrtxTangents()
{
	if (computed_vertex_array_obj == 0)
	{
		// positions
		Vec3 pos1(-1.0f, +1.0f, 0.0f);
		Vec3 pos2(-1.0f, -1.0f, 0.0f);
		Vec3 pos3(+1.0f, -1.0f, 0.0f);
		Vec3 pos4(+1.0f, +1.0f, 0.0f);
		// texture coordinates
		Vec2 uv1(0.0f, 1.0f);
		Vec2 uv2(0.0f, 0.0f);
		Vec2 uv3(1.0f, 0.0f);
		Vec2 uv4(1.0f, 1.0f);
		// normal vector
		Vec3 nm(0.0f, 0.0f, 1.0f);

		// calculate tangent/bitangent vectors of both triangles
		Vec3 tangent1, bitangent1;
		Vec3 tangent2, bitangent2;
		// triangle 1
		// ----------
		Vec3 edge1 = pos2 - pos1;
		Vec3 edge2 = pos3 - pos1;
		Vec2 deltaUV1 = uv2 - uv1;
		Vec2 deltaUV2 = uv3 - uv1;

		float det = deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y;
		if (abs(det) < 1e-6) {
			det = 1e-6; // Prevent division by zero
		}
		float f = 1.0f / det;

		tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		tangent1.normalize();

		bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		bitangent1.normalize();

		// triangle 2
		// ----------
		edge1 = pos3 - pos1;
		edge2 = pos4 - pos1;
		deltaUV1 = uv3 - uv1;
		deltaUV2 = uv4 - uv1;


		//f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		tangent2.normalize();

		bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		bitangent2.normalize();

		float handedness = (math_utils::dot3d(
			math_utils::cross3d(tangent1, bitangent1), nm) > 0.0f) ? 1.0f : -1.0f;

		float quadVertices[] = {
			// positions               // normal            // texcoords   // tangent                               // bitangent
			pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, handedness, //bitangent1.x, bitangent1.y, bitangent1.z,
			pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, handedness, //bitangent1.x, bitangent1.y, bitangent1.z,
			pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, handedness, //bitangent1.x, bitangent1.y, bitangent1.z,
																										
			pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, handedness, //bitangent2.x, bitangent2.y, bitangent2.z,
			pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, handedness, //bitangent2.x, bitangent2.y, bitangent2.z,
			pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, handedness //bitangent2.x, bitangent2.y, bitangent2.z
		};
		// configure plane VAO
		glGenVertexArrays(1, &computed_vertex_array_obj);
		glGenBuffers(1, &computed_vertex_buffer);
		glBindVertexArray(computed_vertex_array_obj);
		glBindBuffer(GL_ARRAY_BUFFER, computed_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		const unsigned int vertex_stride = 12;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_stride * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_stride * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_stride * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, vertex_stride * sizeof(float), (void*)(8 * sizeof(float)));
		//glEnableVertexAttribArray(4);
		//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
	}
	glBindVertexArray(computed_vertex_array_obj);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void assignBuffer(const float* objToDraw, const int sizeofObjToDraw, const unsigned int& inptLayout, const unsigned int& vrtxBuffer)
{
	glBindVertexArray(inptLayout);	// VAO note that we bind to a different VAO now
	glBindBuffer(GL_ARRAY_BUFFER, vrtxBuffer);	// and a different VBO
	glBufferData(GL_ARRAY_BUFFER, sizeofObjToDraw, objToDraw, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Application::setPointLightParameters(Uniforms& uni)
{
	// point light
	const std::vector<PointLight>& point_lights = active_scene->point_lights;
	if (point_lights.empty()) { return; }
	float multiplier = 4.0f;
	for (int ii = 0; ii < point_lights.size(); ii++)
	{
		std::string name = "point_lights[" + std::to_string(ii) + "].";
		active_shader->setVec3(name + "position", point_lights[ii].position);
		active_shader->setVec3(name + "ambient", point_lights[ii].ambient);
		active_shader->setVec3(name + "diffuse", point_lights[ii].diffuse);
		active_shader->setVec3(name + "specular", point_lights[ii].specular);
		active_shader->setFloat(name + "constant", point_lights[ii].constant);
		active_shader->setFloat(name + "linear", point_lights[ii].linear);
		active_shader->setFloat(name + "quadratic", point_lights[ii].quadratic);
		active_shader->setFloat(name + "brightness", point_lights[ii].brightness);
	}
}

void Application::setDirectionalLightParameters(Uniforms& uni)
{
	const std::vector<DirectionalLight>& directional_lights = active_scene->directional_lights;
	if (directional_lights.empty()) { return; }
	active_shader->setVec3("directional_light.direction", directional_lights[0].direction.normalized());
	active_shader->setVec3("directional_light.diffuse", directional_lights[0].diffuse); // darken diffuse light a bit
	active_shader->setVec3("directional_light.ambient", directional_lights[0].ambient);
	active_shader->setVec3("directional_light.specular", directional_lights[0].specular);
	active_shader->setFloat("directional_light.brightness", directional_lights[0].brightness);
}

void Application::setSpotLightParameters(Uniforms& uni)
{
	const std::vector<SpotLight>& spot_lights = active_scene->spot_lights;
	if (spot_lights.empty()) { return; }
	active_shader->setVec3("spot_light.position", spot_lights[0].position);
	active_shader->setVec3("spot_light.direction", spot_lights[0].direction);
	active_shader->setVec3("spot_light.ambient", spot_lights[0].ambient);
	active_shader->setVec3("spot_light.diffuse", spot_lights[0].diffuse);
	active_shader->setVec3("spot_light.specular", spot_lights[0].specular);
	active_shader->setFloat("spot_light.constant", spot_lights[0].constant);
	active_shader->setFloat("spot_light.linear", spot_lights[0].linear);
	active_shader->setFloat("spot_light.quadratic", spot_lights[0].quadratic);
	active_shader->setFloat("spot_light.cutoff", spot_lights[0].cutoff);
	active_shader->setFloat("spot_light.outer_cutoff", spot_lights[0].outer_cutoff);
	active_shader->setFloat("spot_light.brightness", spot_lights[0].brightness);
}

void Application::drawScene(Uniforms& uni)
{



	active_scene->scene_state.stats_vrts = 0;
	active_scene->scene_state.stats_tris = 0;

	const SceneState& scene_state = active_scene->scene_state;
	const Camera& cam = active_scene->cameras[0];

	// setting uniform names
	UniformsPerObject& upo = uni.upo;
	UniformsPerView& upv = uni.upv;
	UniformsPerFrame& upf = uni.upf;
	// create transformations
	//upo.world_matrix = mat_utils::rotationX(toRadian(-45.0f))
	//	* mat_utils::rotationXYZ(scene_state.time, Vec3(1.0f, 1.0f, 1.0f).normalized())
	//	;
	// calculate matrices
	upv.projection_matrix
		= mat_utils::projectPerspective(toRadian(cam.fov), cam.aspect_ratio, cam.near, cam.far);

	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);


	if (active_scene->scene_state.display_shadows)
	{
		if (!active_scene->directional_lights.empty()) drawShadowMap();
		if (!active_scene->point_lights.empty()) drawShadowCubemap();
	}


	glDrawBuffer(GL_BACK);  // Enable drawing to the back buffer
	glReadBuffer(GL_FRONT);  // Enable reading from the front buffer

	display_width = display_w;
	//upv.projection_matrix
	//	= mat_utils::projectOrthographic(display_width / 50.0f, cam.aspect_ratio, cam.near, cam.far);
	//upv.projection_matrix
	//	= mat_utils::projectOrthographic(cam.near, cam.far, -10.0f, 10.0f, 10.0f, -10.0f);
	upv.view_matrix = cam.calcViewMatrix(world_up);
	upv.view_proj_matrix = upv.projection_matrix * upv.view_matrix;

	// 3.8 uniform buffer object set
	glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Mat4), &upv.projection_matrix.transposed().m[0][0]); // const void *
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrices);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Mat4), sizeof(Mat4), &upv.view_matrix.transposed().m[0][0]);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);



	// draw wireframe or not
	if (b_wireframe_mode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	// 3.4. framebuffer
	// bind to framebuffer and draw scene as we normally would to color texture 
	//glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_illumination_msaa);


	// enable this to avoid awkward whatever front rendering
	glEnable(GL_DEPTH_TEST);

	// enable stencil test
	glEnable(GL_STENCIL_TEST);

	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// anti aliasing
	glEnable(GL_MULTISAMPLE);

	// https://learnopengl.com/Advanced-OpenGL/Stencil-testing
	// both the depth and stencil test pass, we will use the reference value
	glStencilOp(
		GL_KEEP,		// stencil action if stencil test fails 
		GL_KEEP,		// stencil action if stencil test passes but depth test fails
		GL_REPLACE		// stencil action if both pass
	);

	// render clear screen
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// get width and height
	glViewport(0, 0, display_w, display_h);

	// draw scene
	disableStencil();

	upv.view_matrix = cam.calcViewMatrix(world_up);
	upv.projection_matrix
		= mat_utils::projectPerspective(toRadian(cam.fov), cam.aspect_ratio, cam.near, cam.far);
	//upv.projection_matrix
	//	= mat_utils::projectOrthographic(cam.near, cam.far, -10.0f, 10.0f, 10.0f, -10.0f);
	upv.view_proj_matrix = upv.projection_matrix * upv.view_matrix;

	drawHelper_lightPlaceholders(uni);

	drawSceneNodes_primitive(uni);

	drawSceneNodes_models(uni);

	drawScene_skybox(uni);

	drawBackbuffer(display_w, display_h);


}

void Application::drawHelper_lightPlaceholders(Uniforms& uni)
{
	// draw light placeholders
	// --------------------------------------------------------------------------
	std::vector<PointLight>& point_lights = active_scene->point_lights;
	for (int ii = 0; ii < point_lights.size(); ii++)
	{
		this->active_shader = shaders.at("3d");
		(*active_shader).use();

		// assign uniforms
		active_shader->setVec3("light_color", active_scene->point_lights[ii].diffuse); // light_coloru degistirme
		active_shader->setFloat("light_brightness", active_scene->point_lights[ii].brightness); 
		active_shader->setMat4("view_matrix", uni.upv.view_matrix);
		active_shader->setMat4("projection_matrix", uni.upv.projection_matrix);
		active_shader->setMat4("view_proj_matrix", uni.upv.view_proj_matrix);

		glBindVertexArray(named_arrays.at("icosphere02"));
		active_shader->setVec3("light_color", point_lights[ii].diffuse);

		Mat4 model = mat_utils::translation(point_lights[ii].position)
			* mat_utils::scale(PrimitiveSceneNodes::light_placeholder.transform.scale)
			;
		active_shader->setMat4("world_matrix", model);

		glDrawArrays(GL_TRIANGLES, 0, 240);

	}

	std::vector<SpotLight>& spot_lights = active_scene->spot_lights;
	for (int ii = 0; ii < spot_lights.size(); ii++)
	{
		this->active_shader = shaders.at("3d");
		(*active_shader).use();

		// assign uniforms
		active_shader->setVec3("light_color", active_scene->spot_lights[ii].diffuse); // light_coloru degistirme
		active_shader->setMat4("view_matrix", uni.upv.view_matrix);
		active_shader->setMat4("projection_matrix", uni.upv.projection_matrix);
		active_shader->setMat4("view_proj_matrix", uni.upv.view_proj_matrix);

		glBindVertexArray(named_arrays.at("cube"));
		active_shader->setVec3("light_color", spot_lights[ii].diffuse);

		Mat4 model = mat_utils::translation(spot_lights[ii].position)
			* mat_utils::scale(PrimitiveSceneNodes::light_placeholder.transform.scale)
			;
		active_shader->setMat4("world_matrix", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
}


void Application::drawHelper_axes(Uniforms& uni)
{
	// ----- draw 0: draw axes
	// -------------------------------------------------------------------------------------
	if (active_scene->scene_state.display_axes)
	{
		this->active_shader = shaders.at("axes");
		(*active_shader).use();
		active_shader->setMat4("world_mat", mat_utils::identity4());
		active_shader->setMat4("view_mat", uni.upv.view_matrix);
		active_shader->setMat4("projection_mat", uni.upv.projection_matrix);
		glBindVertexArray(named_arrays.at("origin"));
		glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(4));
	}
}

void Application::drawShadowCubemap()
{
	float near = 0.1f, far = 20.1f;

	shadow_far_plane = far;

	Mat4 shadow_proj = mat_utils::projectPerspective(math_utils::toRadian(90.0f), shadowmap_aspect_ratio, near, far);

	Vec3 light_pos = active_scene->point_lights[0].position;

	// Right (+X face)
	mat_light_space_cubemaps[0] = shadow_proj *
		mat_utils::lookAtDirection(light_pos, Vec3(+1.0, 0.0, 0.0), Vec3(0.0f, -1.0f, 0.0f)); // Up is -Y

	// Left (-X face)
	mat_light_space_cubemaps[1] = shadow_proj *
		mat_utils::lookAtDirection(light_pos, Vec3(-1.0, 0.0, 0.0), Vec3(0.0f, -1.0f, 0.0f)); // Up is -Y

	// Top (+Y face)
	mat_light_space_cubemaps[2] = shadow_proj *
		mat_utils::lookAtDirection(light_pos, Vec3(0.0, +1.0, 0.0), Vec3(0.0f, 0.0f, -1.0f)); // Up is +Z

	// Bottom (-Y face)
	mat_light_space_cubemaps[3] = shadow_proj *
		mat_utils::lookAtDirection(light_pos, Vec3(0.0, -1.0, 0.0), Vec3(0.0f, 0.0f, +1.0f)); // Up is -Z

	// Front (+Z face)
	mat_light_space_cubemaps[4] = shadow_proj *
		mat_utils::lookAtDirection(light_pos, Vec3(0.0, 0.0, -1.0), Vec3(0.0f, -1.0f, 0.0f)); // Up is -Y

	// Back (-Z face)
	mat_light_space_cubemaps[5] = shadow_proj *
		mat_utils::lookAtDirection(light_pos, Vec3(0.0, 0.0, +1.0), Vec3(0.0f, -1.0f, 0.0f)); // Up is -Y


	this->active_shader = shaders.at("shadowmap-pl");

	// Bind the framebuffer and set up for depth rendering
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_shadow_cube[0]);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, tex_shadow_cubemaps[0], 0);

	// Enable depth testing and prepare the framebuffer for rendering
	glEnable(GL_DEPTH_TEST);

	// Ensure no color buffer is drawn to
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glViewport(0, 0, shadowmap_resolution_x, shadowmap_resolution_y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// ... send uniforms to shader (including light's far_plane value)
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_shadow_cubemaps.back());
	// ... bind other textures
	drawSceneNode_primitive_shadows_pl(far);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Application::drawShadowMap()
{
	float near_plane = 0.1f, far_plane = 100.0f;
	float dim = dimension;
	Mat4 light_projection = mat_utils::projectOrthographic(near_plane, far_plane, -dim, dim, dim, -dim);
	//light_projection = mat_utils::projectPerspective(toRadian(cam.fov), cam.aspect_ratio, cam.near, cam.far);

	const Vec3& p = active_scene->directional_lights[0].position;
	const Vec3& d = active_scene->directional_lights[0].direction;

	//Mat4 light_view = mat_utils::lookAtTarget(
	//	Vec3(p.x, p.y, p.z),						// position
	//	//Vec3(-1.0f, -0.8f, -0.2f),				// direction
	//	Vec3(0.0f, 0.0f, 0.0f),					// target
	//	world_up									// world up
	//);

	Mat4 light_view = mat_utils::lookAtDirection(
		p,											// position
		d,											// direction
		world_up									// world up
	);


	Mat4 light_space_matrix = light_projection * light_view;

	if (this->mat_light_space.size() == 0)
	{
		this->mat_light_space.push_back(light_space_matrix);
	}
	else
	{
		this->mat_light_space[0] = light_space_matrix;
	}


	this->active_shader = shaders.at("shadowmap");

	// Bind the framebuffer and set up for depth rendering
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_shadow[0]);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex_shadow_maps[0], 0);

	// Enable depth testing and prepare the framebuffer for rendering
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);  // Optional: setting cull face to render only front faces for shadow mapping

	// Ensure no color buffer is drawn to
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Set viewport and clear depth buffer
	glViewport(0, 0, shadowmap_resolution_x, shadowmap_resolution_y);
	glClear(GL_DEPTH_BUFFER_BIT);

	// Set the uniform for the light space matrix
	GLuint lightSpaceMatrixLocation = glGetUniformLocation(this->active_shader->ID, "lightSpaceMatrix");
	GLfloat* ptr_light_space_mat = reinterpret_cast<GLfloat*>(&light_space_matrix._11);
	glUniformMatrix4fv(lightSpaceMatrixLocation, 1, GL_FALSE, ptr_light_space_mat);
	ptr_mat_light_space.push_back(ptr_light_space_mat);

	// Render the scene
	drawSceneNode_primitive_shadows_dl(light_space_matrix);

	// Unbind the framebuffer to reset rendering to the default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glCullFace(GL_BACK);  // Reset culling to default if needed

}

void Application::drawBackbuffer(int display_w, int display_h)
{
	// 3.4. framebuffer
	// --------------------------------------------------------------------------------------
	glDisable(GL_CULL_FACE);

	// ---------------------- extract bloom bright color end


	// intermediate buffer to attach bloom
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_illumination_msaa);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_illumination_hdr);
	
	// Resolve the multisampled color buffer into tex_hdr_color[0] (first render target of HDR)
	glReadBuffer(GL_COLOR_ATTACHMENT0); // From MSAA framebuffer's single color target
	glDrawBuffer(GL_COLOR_ATTACHMENT0); // To HDR framebuffer's first render target

	glBlitFramebuffer(0, 0, display_width, display_height, 0, 0, display_w, display_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	// bind frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_illumination_hdr);	

	// Set the viewport to match your screen size
	glViewport(0, 0, display_width, display_height);
	
	// select shader
	this->active_shader = shaders.at("bloom");
	(*active_shader).use();

	// bind vertex array
	glBindVertexArray(named_arrays.at("frame"));

	// Bind the resolved texture (tex_hdr_color[0]) as input
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_illumination_hdr[0]); // Texture written by glBlitFramebuffer
	//glUniform1i(glGetUniformLocation(hdrShader.ID, "input_texture"), 0);

	// Configure multiple render targets (if needed)
	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(1, &attachments[1]);
	// Render a full-screen quad
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Unbind framebuffers to reset state
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// ---------------------- extract bloom bright color end
	
	
	/// ---------------------- gaussian blur
			// 2. blur bright fragments with two-pass Gaussian Blur 
		// --------------------------------------------------
	bool horizontal = true, first_iteration = true;
	unsigned int amount = 10;
	this->active_shader = shaders.at("gaussian-blur");
	(*active_shader).use();

	for (unsigned int i = 0; i < amount; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo_bloom[horizontal]);
		active_shader->setInt("horizontal", horizontal);
		glBindTexture(GL_TEXTURE_2D, first_iteration ? tex_illumination_hdr[1] : tex_bloom[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
		// bind vertex array
		glBindVertexArray(named_arrays.at("frame"));

		// Render a full-screen quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		horizontal = !horizontal;
		if (first_iteration)
			first_iteration = false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	/// ---------------------- gaussian blur end


	// 3.11 anti aliasing
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_illumination_hdr);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_backbuffer);
	glBlitFramebuffer(0, 0, display_width, display_height, 0, 0, display_w, display_h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


#define CHECK_BACKBUFFER_ENCODING 0
#if CHECK_BUFFER_ENCODING
	// check back buffer encoding
	GLint encoding;
	glGetFramebufferAttachmentParameteriv(
		GL_FRAMEBUFFER, 
		GL_BACK_LEFT, 
		GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING,
		&encoding
	);
	std::cout << (encoding == GL_SRGB ? "srgb" : "linear");
#endif

	glDisable(GL_DEPTH_TEST); 
	// disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	glClear(GL_COLOR_BUFFER_BIT);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	this->active_shader = shaders.at("framebuffer");
	(*active_shader).use();

	glBindVertexArray(named_arrays.at("frame"));

	glActiveTexture(GL_TEXTURE0);
	active_shader->setInt("screen_texture", 0);
	glBindTexture(GL_TEXTURE_2D, fbo_backbuffer_color);

	glActiveTexture(GL_TEXTURE1);
	active_shader->setInt("screen_bloom", 1);
	glBindTexture(GL_TEXTURE_2D, tex_bloom[!horizontal]);

	active_shader->setFloat("exposure", active_scene->scene_state.exposure);
	active_shader->setBool  ("bloom", active_scene->scene_state.bloom);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Unbind textures to release texture slots
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture from slot 0
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture from slot 1
	// Reset active texture slot to default (GL_TEXTURE0)
	glActiveTexture(GL_TEXTURE0);

	if (save_frame)
	{
		std::string result = std::format("{}{}{}", config_dir_path, "test_scene_frames/scene", active_test_scene, "_test.png");
		img_utils::saveFrameBufferAsPNG(display_w, display_h, result.c_str());
		save_frame = false;
	}

}

void Application::drawSceneNode_primitive_shadows_dl(const Mat4& model_mat)
{
	const int element_count = static_cast<int>(active_scene->predefined_scene_elements.size());
	(*active_shader).use();
	for (int i = 0; i < element_count; i++)
	{
		glBindVertexArray(0);
		active_shader->setMat4("lightSpaceMatrix", model_mat);
		const std::string& name = active_scene->predefined_scene_elements[i].vertex_array_name;
		glBindVertexArray(named_arrays.at(name));
		const Transform& transform = active_scene->predefined_scene_elements[i].transform;
		const Mat4 model =
			mat_utils::translation(Vec3(transform.position.x, transform.position.y, transform.position.z))  // 0, 3, 10 * cos(ss.time)
			* mat_utils::rotateX(toRadian(transform.rotation.x))
			* mat_utils::rotateY(toRadian(transform.rotation.y))
			* mat_utils::rotateZ(toRadian(transform.rotation.z))
			* mat_utils::scale(transform.scale.x, transform.scale.y, transform.scale.z)
			;
		active_shader->setMat4("model", model);
		//if (active_scene->predefined_scene_elements[i].element_bools.indexed)
		//{
		//	// Bind the index buffer
		//	// fix: exception error scene
		//	glBindBuffer(named_arrays.at(name), lit_ebo);
		//	glDrawElements(GL_TRIANGLES, sizeof(float) * PredefNameMaps::predef3d_namemap.at(name).num_elements, GL_UNSIGNED_INT, 0);
		//}
		//else if (active_scene->predefined_scene_elements[i].element_bools.partial_render)
		//{
		//	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(36 / active_scene->scene_state.vertex_divider));
		//}
		//else
		//{
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
	}
}

void Application::drawSceneNode_primitive_shadows_pl(const float far_plane)
{
	const int element_count = static_cast<int>(active_scene->predefined_scene_elements.size());
	(*active_shader).use();
	active_shader->setVec3("light_position", active_scene->point_lights[0].position);
	active_shader->setFloat("far_plane", far_plane);

	for (int ii = 0; ii < 6; ii++)
	{
		std::string name = "shadow_transform_matrices[" + std::to_string(ii) + "]";
		active_shader->setMat4(name, mat_light_space_cubemaps[ii]);
	}

	for (int i = 0; i < element_count; i++)
	{
		/*active_shader->setMat4Vector("shadow_transform_matrcies", shadow_transform_matrices);*/

		const std::string& name = active_scene->predefined_scene_elements[i].vertex_array_name;
		glBindVertexArray(named_arrays.at(name));
		const Transform& transform = active_scene->predefined_scene_elements[i].transform;
		const Mat4 model =
			mat_utils::translation(Vec3(transform.position.x, transform.position.y, transform.position.z))  // 0, 3, 10 * cos(ss.time)
			* mat_utils::rotateX(toRadian(transform.rotation.x))
			* mat_utils::rotateY(toRadian(transform.rotation.y))
			* mat_utils::rotateZ(toRadian(transform.rotation.z))
			* mat_utils::scale(transform.scale.x, transform.scale.y, transform.scale.z)
			;
		active_shader->setMat4("model", model);
		//if (active_scene->predefined_scene_elements[i].element_bools.indexed)
		//{
		//	// Bind the index buffer
		//	glBindBuffer(named_arrays.at(name), lit_ebo);
		//	glDrawElements(GL_TRIANGLES, sizeof(float) * PredefNameMaps::predef3d_namemap.at(name).num_elements, GL_UNSIGNED_INT, 0);
		//}
		//else if (active_scene->predefined_scene_elements[i].element_bools.partial_render)
		//{
		//	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(36 / active_scene->scene_state.vertex_divider));
		//}
		//else
		//{
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
	}
}

void Application::setUniforms(Uniforms& uni)
{
	// draw scene objects
	// --------------------------------------------------------------------------
	Camera cam = active_scene->cameras[0];
	UniformsPerObject& upo = uni.upo;
	UniformsPerView& upv = uni.upv;
	UniformsPerFrame& upf = uni.upf;
	// assign uniforms
	active_shader->setVec3("view_pos", cam.position);
	active_shader->setMat4("view_mat", upv.view_matrix);
	active_shader->setMat4("projection_mat", upv.projection_matrix);
	active_shader->setFloat("mix_val", upo.mix_value);
	active_shader->setFloat("time", active_scene->scene_state.time);
	active_shader->setFloat("tiling_factor", 1.0f);
	active_shader->setBool("gamma", active_scene->scene_state.gamma);
	active_shader->setInt("num_point_lights", active_scene->point_lights.size());
	active_shader->setFloat("prlx_height_scale", 0.2f);
	active_shader->setFloat("far_plane", shadow_far_plane);
	active_shader->setFloat("anim_tant", active_scene->scene_state.tant);

	// assign shadow
	if (mat_light_space.size() > 0)
		active_shader->setMat4("light_space_matrix", mat_light_space[0]);

	// textures
	active_shader->setInt("material.diffuse_map1", 0);
	active_shader->setInt("material.specular_map1", 1);
	active_shader->setInt("material.normal_map1", 2);
	active_shader->setInt("material.emission_map1", 3);
	active_shader->setInt("shadow_map", 4);
	active_shader->setInt("shadow_cubemap", 5);
	active_shader->setInt("material.depth_map1", 6);

	// factors
	active_shader->setFloat("material.emission_factor", active_scene->scene_state.emission_factor); // material emission factor
	active_shader->setFloat("material.shininess", active_scene->scene_state.shininess);
}

void Application::drawSceneNodes_primitive(Uniforms& uni)
{
	// draw scene objects
	// --------------------------------------------------------------------------
	Camera cam = active_scene->cameras[0];
	UniformsPerObject& upo = uni.upo;
	UniformsPerView& upv = uni.upv;
	UniformsPerFrame& upf = uni.upf;
	int element_count = static_cast<int>(active_scene->predefined_scene_elements.size());
	for (int i = 0; i < element_count; i++)
	{
		if (active_scene->predefined_scene_elements[i].element_bools.indexed)
		{
			// enable face culling 
			glEnable(GL_CULL_FACE);
			//glCullFace(GL_FRONT
			glFrontFace(GL_CW);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
		this->active_shader = shaders.at(active_scene->predefined_scene_elements[i].shader_name);
		// activate shader
		(*active_shader).use();

		if (active_scene->scene_state.using_computed_data)
		{
			for (unsigned int i = 0; i < 100; i++)
			{
				std::string name = "offsets[" + std::to_string(i) + "]";
				Vec2 translation = active_scene->computed_data.translations2d[i];
				active_shader->setVec2(name, translation);
			}
		}

		setUniforms(uni);
		// directional light
		setDirectionalLightParameters(uni);
		// point light
		setPointLightParameters(uni);
		//// spotLight
		setSpotLightParameters(uni);

		Mat4 model = mat_utils::identity4();
		active_shader->setMat4("world_mat", model);

		// material

		// default values
		active_shader->setVec3("material.diffuse", 0.5f, 0.5f, 0.5f);
		active_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);

		float maxObjectScale = (std::max(model._11, std::max(model._22, model._33)));
		//active_shader->setFloat("outline_scale", maxObjectScale);


		// assign texture
		std::string texture_name = active_scene->predefined_scene_elements[i].texture_name;

		glActiveTexture(GL_TEXTURE0);
		textures[texture_name].color != 0 ?
			glBindTexture(GL_TEXTURE_2D, textures[texture_name].color)
			: glBindTexture(GL_TEXTURE_2D, 0);

		if (active_scene->predefined_scene_elements[i].shader_name == "cubemaplit")
		{
			active_shader->setInt("skybox", 0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
		}


		glActiveTexture(GL_TEXTURE1);
		textures[texture_name].specular != 0 ?
			glBindTexture(GL_TEXTURE_2D, textures[texture_name].specular)
			: glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTexture(GL_TEXTURE2);
		textures[texture_name].color != 0 ?
			glBindTexture(GL_TEXTURE_2D, textures[texture_name].normal)
			: glBindTexture(GL_TEXTURE_2D, 0);


		glActiveTexture(GL_TEXTURE3);
		textures[texture_name].color != 0 ?
			glBindTexture(GL_TEXTURE_2D, textures[texture_name].emission)
			: glBindTexture(GL_TEXTURE_2D, 0);


		glActiveTexture(GL_TEXTURE4);
		tex_shadow_maps.size() > 0 ?
			glBindTexture(GL_TEXTURE_2D, tex_shadow_maps[0])
			: glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTexture(GL_TEXTURE5);
		tex_shadow_cubemaps.size() > 0 ?
			glBindTexture(GL_TEXTURE_CUBE_MAP, tex_shadow_cubemaps[0])
			: glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		glActiveTexture(GL_TEXTURE6);
		textures.at(texture_name).displacement != 0 ?
			glBindTexture(GL_TEXTURE_2D, textures.at(texture_name).displacement)
			: glBindTexture(GL_TEXTURE_2D, 0);


		// ----- draw 1: draw element
		// -------------------------------------------------------------------------------------
		std::string name = active_scene->predefined_scene_elements[i].vertex_array_name;
		glBindVertexArray(named_arrays.at(name));
		Transform transform = active_scene->predefined_scene_elements[i].transform;
		model =
			mat_utils::translation(Vec3(transform.position.x, transform.position.y, transform.position.z))  // 0, 3, 10 * cos(ss.time)
			* mat_utils::rotateX(toRadian(transform.rotation.x))
			* mat_utils::rotateY(toRadian(transform.rotation.y))
			* mat_utils::rotateZ(toRadian(transform.rotation.z))
			* mat_utils::scale(transform.scale.x, transform.scale.y, transform.scale.z)
			;
		active_shader->setMat4("world_matrix", model);
		active_shader->setMat4("world_mat", model);

		if (active_scene->predefined_scene_elements[i].element_bools.stencil_testing) { disableStencil(); }

		if (active_scene->predefined_scene_elements[i].element_bools.is_using_tan_space)
		{
			compute_QuadVrtxTangents();
		}
		else if (!active_scene->predefined_scene_elements[i].element_bools.is_triangle)
		{
			glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(36 / active_scene->scene_state.vertex_divider));
		}
		else if (active_scene->predefined_scene_elements[i].element_bools.indexed) // face culling
		{
			// Bind the index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lit_ebo);
			int count = PredefNameMaps::predef3d_namemap.at(name).num_elements / PredefNameMaps::predef3d_namemap.at(name).stride;
			glDrawElements(GL_TRIANGLES, sizeof(VertexData::cube_inds__pos_norm_uv), GL_UNSIGNED_INT, 0);
		}
		else if (active_scene->predefined_scene_elements[i].element_bools.partial_render)
		{
			glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(36 / active_scene->scene_state.vertex_divider));
		}
		else if (active_scene->scene_state.draw_instanced)
		{
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, active_scene->scene_state.instance_count);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		if (active_scene->predefined_scene_elements[i].element_bools.stencil_testing) {
			enableStencil();
			this->active_shader = shaders.at("stenciltesting");
			(*active_shader).use();
			// light uniforms
			const SceneState& ss = active_scene->scene_state;
			UniformsPerObject& upo = uni.upo;
			UniformsPerView& upv = uni.upv;
			UniformsPerFrame& upf = uni.upf;

			// assign textures and uniforms
			active_shader->setVec3("view_pos", active_scene->cameras[0].position);
			active_shader->setMat4("view_proj_matrix", upv.view_proj_matrix);

			active_shader->setInt("material.texture_diffuse1", 0);
			active_shader->setInt("material.texture_specular1", 1);
			active_shader->setInt("material.texture_emissive1", 2);
			
			active_shader->setInt("shadow_map", 3);
			active_shader->setInt("shadow_cubemap", 4);

			active_shader->setFloat("material.emission_factor", ss.emission_factor);
			active_shader->setFloat("material.shininess", active_scene->scene_state.shininess);

			// set ligt parameters
			setDirectionalLightParameters(uni);
			setPointLightParameters(uni);
			setSpotLightParameters(uni);

			Mat4 world = model;
			active_shader->setMat4("world_matrix", world);

			float maxObjectScale = (std::max(world._11, std::max(world._22, world._33)));
			active_shader->setFloat("outline_scale", maxObjectScale);
			if (active_scene->predefined_scene_elements[i].element_bools.indexed)
			{
				// Bind the index buffer
				glBindBuffer(named_arrays.at(name), lit_ebo);
				std::string name = active_scene->predefined_scene_elements[i].vertex_array_name;
				glDrawElements(GL_TRIANGLES, sizeof(float) * PredefNameMaps::predef3d_namemap.at(name).num_elements, GL_UNSIGNED_INT, 0);
			}
			else if (active_scene->predefined_scene_elements[i].element_bools.partial_render)
			{
				glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(36 / active_scene->scene_state.vertex_divider));
			}
			else
			{
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			clearStencil();
			glClear(GL_STENCIL_BUFFER_BIT);
		}

	}
}

void Application::drawSceneNodes_models(Uniforms& uni)
{
	// ---- draw 2: models
// -------------------------------------------------------------------------------------
	for (int i = 0; i < active_scene->models.size(); i++)
	{

		// face culling
		if (active_scene->scene_state.model_element_bools[i].indexed)
		{
			// enable face culling 
			glEnable(GL_CULL_FACE);
			//glCullFace(GL_FRONT);
			glFrontFace(GL_CW);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

		active_scene->scene_state.b_model_refraction 
			? active_scene->scene_state.model_shader_name = "cubemaplit" 
			: active_scene->scene_state.model_shader_name = active_scene->scene_state.model_shader_name;
		
		this->active_shader = shaders.at(active_scene->scene_state.model_shader_name);
		// activate shader
		(*active_shader).use();
		// light uniforms
		const SceneState& ss = active_scene->scene_state;
		UniformsPerObject& upo = uni.upo;
		UniformsPerView& upv = uni.upv;
		UniformsPerFrame& upf = uni.upf;


		setUniforms(uni);


		if (active_scene->scene_state.b_model_refraction)
		{
			active_shader->setInt("skybox", 0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
		}

		// set ligt parameters
		setDirectionalLightParameters(uni);
		setPointLightParameters(uni);
		setSpotLightParameters(uni);

		Mat4 world = mat_utils::identity4();
		active_scene->scene_nodes.size() > 0
			? world *= mat_utils::scale(active_scene->scene_nodes[i].transform.scale)
			: world *= mat_utils::scale(1.0f, 1.0f, 1.0f);
		
		active_shader->setMat4("world_mat", world);

		float maxObjectScale = (std::max(world._11, std::max(world._22, world._33)));
		active_shader->setFloat("outline_scale", maxObjectScale);

		std::vector<ElementBools> bools = active_scene->scene_state.model_element_bools;
		if (bools[i].stencil_testing) { disableStencil(); }
		active_scene->models[i].draw(*active_shader);

		// then draw model with normal visualizing geometry shader

		if (active_scene->scene_state.display_normals)
		{
			this->active_shader = shaders.at("normal");
			(*active_shader).use();
			active_shader->setMat4("projection_mat", upv.projection_matrix);
			active_shader->setMat4("view_mat", upv.view_matrix);
			active_shader->setMat4("world_mat", world);
			active_scene->models[i].draw(*active_shader);
		}


		if (bools[i].stencil_testing) {
			enableStencil();
			this->active_shader = shaders.at("stenciltesting02");
			(*active_shader).use();
			// light uniforms
			const SceneState& ss = active_scene->scene_state;
			UniformsPerObject& upo = uni.upo;
			UniformsPerView& upv = uni.upv;
			UniformsPerFrame& upf = uni.upf;

			// assign textures and uniforms
			active_shader->setVec3("view_pos", active_scene->cameras[0].position);
			active_shader->setMat4("view_mat", upv.view_matrix);
			active_shader->setMat4("projection_mat", upv.projection_matrix);

			active_shader->setFloat("material.emission_factor", ss.emission_factor);

			// set ligt parameters
			setDirectionalLightParameters(uni);
			setPointLightParameters(uni);
			setSpotLightParameters(uni);

			Mat4 world = mat_utils::identity4();
			active_shader->setMat4("world_mat", world);

			float maxObjectScale = (std::max(world._11, std::max(world._22, world._33)));
			active_shader->setFloat("outline_scale", maxObjectScale);
			active_scene->models[i].draw(*active_shader);
			clearStencil();
			glClear(GL_STENCIL_BUFFER_BIT);
		}

		if (active_scene->scene_state.draw_instanced)
		{
			std::string shader = "instance02";
			this->active_shader = shaders.at(shader);
			(*active_shader).use();
			active_shader->setMat4("view_mat", upv.view_matrix);
			active_shader->setMat4("projection_mat", upv.projection_matrix);
			//active_shader->setMat4("world_mat", world);

			// method 1: without instance
			//for (int ii = 0; ii < active_scene->scene_state.instance_count; ii++)
			//{
			//	std::string name = "world_mat";
			//	active_shader->setMat4(name, active_scene->computed_data.mat4[ii]);
			//	active_scene->models[i].draw(*active_shader);
			//}

			// method 2: split instancing with for loop
			//if (active_scene->scene_state.instance_count > 1000)
			//{
			//	int loop_count = active_scene->scene_state.instance_count / 1000;
			//	int remainder = active_scene->scene_state.instance_count % 1000;
			//	if (remainder > 0) loop_count += 1;
			//	for (int ii = 0; ii < loop_count; ii++)
			//	{
			//		for (int iii = 0; iii < 1000; iii++)
			//		{
			//			std::string name = "transformation_mat[" + std::to_string(iii) + "]";
			//			active_shader->setMat4(name, active_scene->computed_data.mat4[iii+ii^1000]);
			//		}
			//		active_scene->models[i].drawInstanced(*active_shader, 1000);
			//	}
			//}
			//else
			//{
			//	for (int ii = 0; ii < active_scene->scene_state.instance_count; ii++)
			//	{
			//		std::string name = "transformation_mat[" + std::to_string(ii) + "]";
			//		active_shader->setMat4(name, active_scene->computed_data.mat4[ii]);
			//	}
			//	active_scene->models[i].drawInstanced(*active_shader, active_scene->scene_state.instance_count);
			//}

			// method 3: split instancing with ubo
			//int size = 5000;
			//if (active_scene->scene_state.instance_count > size)
			//{
			//	int loop_count = active_scene->scene_state.instance_count / size;
			//	int remainder = active_scene->scene_state.instance_count % size;
			//	if (remainder > 0) loop_count += 1;
			//	for (int ii = 0; ii < loop_count; ii++)
			//	{
			//		glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrices);
			//		glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(Mat4), size*sizeof(Mat4), &active_scene->computed_data.mat4[ii*size].m[0][0]);
			//		glBindBuffer(GL_UNIFORM_BUFFER, 0);
			//		active_scene->models[i].drawInstanced(*active_shader, size);
			//	}
			//}
			//else
			//{
			//	for (int ii = 0; ii < active_scene->scene_state.instance_count; ii++)
			//	{
			//		std::string name = "transformation_mat[" + std::to_string(ii) + "]";
			//		active_shader->setMat4(name, active_scene->computed_data.mat4[ii]);
			//	}
			//	active_scene->models[i].drawInstanced(*active_shader, active_scene->scene_state.instance_count);
			//}

			// method 4: brute force ubo
			//glBindBuffer(GL_UNIFORM_BUFFER, ubo_matrices);
			//glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(Mat4), 5000*sizeof(Mat4), &active_scene->computed_data.mat4[0].m[0][0]);
			//glBindBuffer(GL_UNIFORM_BUFFER, 0);
			//		active_scene->models[i].drawInstanced(*active_shader, active_scene->scene_state.instance_count);

			// method 5: brute force vbo
			for (unsigned int i = 0; i < active_scene->models[0].meshes.size(); i++)
			{

				glBindVertexArray(active_scene->models[0].meshes[i].vao);
				glDrawElementsInstanced(
					GL_TRIANGLES, static_cast<GLsizei>(active_scene->models[0].meshes[i].indices.size()),
					GL_UNSIGNED_INT, 0,
					static_cast<GLsizei>(active_scene->scene_state.instance_count)
				);
				active_scene->scene_state.stats_vrts += 3 * active_scene->scene_state.instance_count;
				active_scene->scene_state.stats_tris += 1 * active_scene->scene_state.instance_count;
			}

		}
	}
}

void Application::drawScene_skybox(Uniforms& uni)
{
	// 3.5 skybox 
	// --------------------------------------------------------------------------------------
	Camera cam = active_scene->cameras[0];
	UniformsPerObject& upo = uni.upo;
	UniformsPerView& upv = uni.upv;
	UniformsPerFrame& upf = uni.upf;
	if (active_scene->scene_state.display_skybox) {
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		this->active_shader = shaders.at("cubemap");
		(*active_shader).use();
		glBindVertexArray(named_arrays.at("skybox"));
		upv.view_matrix = cam.calcViewMatrix(world_up);
		upv.view_matrix._14 = 0.0f;
		upv.view_matrix._24 = 0.0f;
		upv.view_matrix._34 = 0.0f;
		upv.projection_matrix
			= mat_utils::projectPerspective(toRadian(cam.fov), cam.aspect_ratio, cam.near, cam.far);
		//upv.projection_matrix
			//= mat_utils::projectOrthographic(display_width, cam.aspect_ratio, cam.near, cam.far);
		upv.view_proj_matrix = upv.projection_matrix * upv.view_matrix;
		active_shader->setMat4("view_proj_matrix", uni.upv.view_proj_matrix);
		active_shader->setInt("skybox", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default
	}
}


void Application::setPresetMaterial(const Material& material)
{
	active_shader->setVec3("material.specular", material.specular);
	active_shader->setVec3("material.diffuse", material.diffuse);
	active_shader->setFloat("material.shininess", material.shininess * 128.0f);
	//active_shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	//active_shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	//active_shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	//active_shader->setFloat("material.shininess", 32.0f);
}

void Application::setMaterial(const Material& material)
{
	active_shader->setVec3("material.specular", material.specular);
	active_shader->setInt("material.diffuse_map", 0);
	active_shader->setFloat("material.shininess", material.shininess);
}

void Application::updateScene()
{
	SceneState& scene_state = active_scene->scene_state;
	scene_state.time = (float)glfwGetTime();
	scene_state.delta_time = scene_state.time - scene_state.last_frame_time;
	scene_state.last_frame_time = scene_state.time;
	// animate?
	if (!scene_state.animate)
		return;
	if (save_frame)
		scene_state.time = 0.0f;
	active_scene->update();
}

void Application::resetCamera()
{
	Camera& camera = active_scene->cameras[0];
	//camera.position = Vec3(0.0f, 0.0f, 5.0f);
	camera.position = Vec3(-12.0f, 10.0f, 12.0f);
	const Vec3 k_camera_target_point = Vec3(0.0f, 0.0f, 0.0f);
	camera.lookAtTarget(k_camera_target_point);
}

void Application::setPathType(std::string in_path_mode)
{
	if (in_path_mode == "full") path_mode = Application::PathMode::FULL;
	if (path_mode == Application::PathMode::FULL)
	{
		data_dir_path = DATA_DIR_FULL;
		config_dir_path = CONFIG_DIR_FULL;
		shader_dir_path = SHADER_DIR_FULL;
	}
	else
	{
		data_dir_path = file_utils::getExecutableDir() + "\\data\\";
		config_dir_path = file_utils::getExecutableDir() + "\\config\\";
		shader_dir_path = file_utils::getExecutableDir() + "\\shaders\\";
	}
}

unsigned int fourStageAnimation(const unsigned int& stage)
{
	return stage == 4 ? 1 : stage + 1;
}

void setTriangleLightColorShiftByTime(Vec3& light_color, Vec3& light_specular, const float& time)
{
	float color_state = ((sin(time * 0.5f) + 1.0f) * 0.5f) * 6.0f;
	float r, g, b;

	if (color_state < 1.0f)
	{
		r = 1.0f;
		g = color_state;
		b = 0.0f;
	}
	else if (color_state < 2.0f)
	{
		r = 2.0f - color_state;
		g = 1.0f;
		b = 0.0f;
	}
	else if (color_state < 3.0f)
	{
		r = 0.0f;
		g = 1.0f;
		b = color_state - 2.0f;
	}
	else if (color_state < 4.0f)
	{
		r = 0.0f;
		g = 4.0f - color_state;
		b = 1.0f;
	}
	else if (color_state < 5.0f)
	{
		r = color_state - 4.0f;
		g = 0.0f;
		b = 1.0f;
	}
	else
	{
		r = 1.0f;
		g = 0.0f;
		b = 6.0f - color_state;
	}
	light_color = Vec3(r, g, b);
	light_specular = light_color * 0.5f;
}

void drawObjToScr(const unsigned int& shader, const unsigned int& vao)
{
	glUseProgram(shader);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}



#endif