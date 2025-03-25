// ---------------------------------------------------------------------------------------
// ----- notes
// ---------------------------------------------------------------------------------------


// ---------------------------------------------------------------------------------------
// ----- libraries
// ---------------------------------------------------------------------------------------
#include "application.h"				
#include "scene.h"				
#include "events.h"	
#include "opengl.h"			

//Application::toggle_mouselock = !Application::toggle_mouselock;


// ---------------------------------------------------------------------------------------
// ----- function definitions
// ---------------------------------------------------------------------------------------
void Scene::onMultipleKeyPress(std::vector<int> keys) {

	Camera& cam = cameras[0];
	float cam_speed = 2.5f * scene_state.delta_time;
	const Vec3& cam_dir = cam.getDirection();
	const Vec3& cam_up = cam.getUp(Application::world_up);
	const Vec3& cam_right = cam.getRight(Application::world_up);

	for (const int& key : keys) {
		auto it = keyboard.find(key);
		InputEvent event = (it != keyboard.end()) ? it->second : InputEvent::Undefined;
		active_input_events.insert(event);
	}


	for (const auto& event : active_input_events) {
		// ----- camera transform speed
		if (event == InputEvent::MoveSpeedIncrease)
		{
			cam_speed *= 8.0f;
		}
		// ---- camera movement
		if (event == InputEvent::MoveForward)
			cam.position += +cam_speed * cam_dir;
		else if (event == InputEvent::MoveBackward)
			cam.position -= +cam_speed * cam_dir;


		if (event == InputEvent::MoveRight)
			cam.position += +cam_speed * cam_right;
		else if (event == InputEvent::MoveLeft)
			cam.position += -cam_speed * cam_right;

		if (event == InputEvent::MoveUp)
			cam.position += +cam_speed * cam_up;
		else if (event == InputEvent::MoveDown)
			cam.position += -cam_speed * cam_up;

		// ----- camera rotation
		if (event == InputEvent::RotateRight)
			cam.rotate(-cam.rotation_sensitivity, 0.0f);
		else if (event == InputEvent::RotateLeft)
			cam.rotate(+cam.rotation_sensitivity, 0.0f);

		if (event == InputEvent::RotateUp)
			cam.rotate(0.0f, -cam.rotation_sensitivity);
		if (event == InputEvent::RotateDown)
			cam.rotate(0.0f, +cam.rotation_sensitivity);

		//// ----- 
		if (event == InputEvent::ToggleUI)
			// todo toggleui applicationa ait
			scene_state.toggle_ui = !scene_state.toggle_ui;


	}
	//std::cout << "cam_dir: " << cam_dir.x << " " << cam_dir.y << " " << cam_dir.z << std::endl;
	//std::cout << "cam_speed: " << cam_speed << std::endl;
	active_input_events.clear();
}
