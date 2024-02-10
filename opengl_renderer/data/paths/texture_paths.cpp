// ---------------------------------------------------------------------------------------
// libraries
// ---------------------------------------------------------------------------------------
#include "../headers/data/data.h"     

// ---------------------------------------------------------------------------------------
// data
// ---------------------------------------------------------------------------------------

// ! const olamiyor
std::map<std::string, TexturePaths> RelativePaths::texture_paths =
{
	{"test_2k",
		{
		.color		= "data/textures/test_2k_mid_color.jpg"
		,.specular  = "data/textures/test_2k_specular.jpg"
		,.emission  = "data/textures/test_2k_emission.jpg"
		}
	},
	{"grid_2k_white",
		{
		.color = "data/textures/grid_2k_16d_white_color.png"
		,.specular = "data/textures/test_2k_specular.jpg"
		//,.emission = "data/textures/grid02_16d_emission_2k.png"
		}
	},
	{"linegrid_2k_darkgray",
		{
		.color = "data/textures/linegrid_2k_16d_darkgray_color.png"
		,.specular = "data/textures/kraftpaper01_2k_roughness.jpg"
		,.emission = "data/textures/test_2k_emission.jpg"
		}
	},
	{"out_container2",
		{
		.color = "data/textures/out_container2_diffuse.png"
		,.specular = "data/textures/out_container2_specular.png"
		,.emission = "data/textures/out_container2_emission.jpg"
		}
	},
	{"out_grass",
		{
		.color = "data/textures/out_blending_grass.png"
		}
	},
	{"out_blending_window_blue",
		{
		.color = "data/textures/out_blending_transparent_window_blue_256.png"
		}
	}
};