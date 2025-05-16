#pragma once
#include <string>
#include <vector>
#include <map>
// ----------------------------------------------------------------------------
//				forward declarations
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
//				abstract
// ----------------------------------------------------------------------------

struct ModelPath {
	std::string model_file;
};


struct ShaderPaths
{
    std::string_view vrtx{};
    std::string_view frag{};
    std::string_view geom{};
};


struct TexturePaths {
	std::string color;
	std::string roughness;
	std::string normal;
	std::string specular;
	std::string emission;
	std::string displacement;
};


class PathAfterDirectory
{
   public:
    //static const std::unordered_map<std::string, ShaderPaths> shader_paths;
    static const std::vector<ModelPath>                       model_paths;
    static std::map<std::string, TexturePaths>                texture_paths;
    static std::map<std::string, std::vector<std::string>>    cubemap_texture_paths;
};