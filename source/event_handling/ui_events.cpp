// ----- Libraries
// ---------------------------------------------------------------------------------------
#include "renderer.h"			// shader objesi olusturmaya dair veritipi


// ----- variables
// ---------------------------------------------------------------------------------------


// ----- Functions
// ---------------------------------------------------------------------------------------
void Renderer::onUIEvent(const UIEvent& event, const std::vector<int>& params)
{
	std::map<UIEvent, std::vector<int>> event_map;
	event_map[event] = params;
	ui_events.add(event_map);
}
