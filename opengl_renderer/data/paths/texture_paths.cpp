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
		.color		= "data/textures/2k_test_diffuse_mid.jpg"
		,.specular  = "data/textures/2k_test_specular.jpg"
		,.emission  = "data/textures/2k_test_emission.jpg"
		}
	},
	{"checker_800",
		{
		.color = "data/textures/800_blackchecker.png"
		,.specular = "data/textures/800_checker_specular_regions.png"
		,.emission = "data/textures/800_checker_emission.png"
		}
	},
	{"out_container2",
		{
		.color = "data/textures/out_container2_diffuse.png"
		,.specular = "data/textures/out_container2_specular.png"
		,.emission = "data/textures/out_container2_emission.png"
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