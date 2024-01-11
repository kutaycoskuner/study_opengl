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
		,.emission = "data/textures/800_checker_emission_regions.png"
		}
	}
};