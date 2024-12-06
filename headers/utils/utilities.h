#pragma once

#include "../../headers/abstract/matrix4.h"
#include <string>
#include <vector>
#include<unordered_map>

struct Vec3;


namespace str_utils
{
	std::vector<std::string> split(const std::string& str, const std::string& delimiter);
}

namespace file_utils
{
	std::string getExecutableDir();
	std::string getFileNameWithoutExtension(const std::string& filePath);
	std::string getDirectoryName(const std::string& filePath);
	std::string getDirectoryPath(const std::string& filePath);
	std::string getExtension(const std::string& filePath);

	std::string readFileContents(const std::string& path);
	std::vector<std::string> parseFileToRowArray(const std::string& path);
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> parseSimple(const std::string& path);
}

namespace math_utils
{ 
	constexpr float PI = 3.14159265359f;
	// scaling
	float scaleByteToZeroOne(unsigned int byte);	
	float scaleByteToZeroOne(float byte);
	Vec3 scaleByteToZeroOne(float a, float b, float c);
	Vec3 scaleByteToZeroOne(unsigned int a, unsigned int b, unsigned int c);
	// trigonometri
	float toRadian(float degree);
	float toDegree(float radian);
	// float
	bool compareApprox(const float& a, const float& b);
	// vector
	std::vector<float> scaleByteToZeroOneVec3(const unsigned int x, const unsigned int y, const unsigned int z);
	std::vector<float> scaleByteToZeroOneVec3(const float x, const float y, const float z);
	float dot3d(const Vec3& v1, const Vec3& v2);
	Vec3 cross3d(const Vec3& v1, const Vec3& v2);

}

namespace mat_utils
{
	Mat4 debugMat();
	Mat4 identity4();
	Mat4 transpose(const Mat4& mat);
	Mat4 inverse(const Mat4& mat);
	float determinant(const Mat4& mat);
	Mat4 cofactor(const Mat4& mat);
	Mat4 scale(const float& x, const float& y, const float& z);
	Mat4 scale(const Vec3& vec);
	Mat4 scale(const float& x);
	Mat4 translation(const float& x, const float& y, const float& z);
	Mat4 translation(const float& x);
	Mat4 translation(const Vec3& vec);
	Mat4 translate(const float& x, const float& y, const float& z);
	Mat4 translate(const float& x);
	Mat4 translate(const Vec3& vec);
	Mat4 rotationX(const float& angleInRadians);
	Mat4 rotationY(const float& angleInRadians);
	Mat4 rotationZ(const float& angleInRadians);
	Mat4 rotationXYZ(const float& angleInRadians, const Vec3& axis);
	Mat4 rotateX(const float& angleInRadians);
	Mat4 rotateY(const float& angleInRadians);
	Mat4 rotateZ(const float& angleInRadians);
	Mat4 rotateXYZ(const float& angleInRadians, const Vec3& axis);
	Mat4 projectPerspective(float fov_inRadians, float aspect_ratio, float near, float far);
	Mat4 projectPerspective(float near, float far, float left, float right, float top, float bottom);

	Mat4 lookAtTarget(const Vec3& position, const Vec3& target, const Vec3& world_up);
	Mat4 lookAtDirection(const Vec3& position, const Vec3& direction, const Vec3& world_up);


	Mat4 projectOrthographic(const float& vertical_size, const float& aspect_ratio, const float& near, const float& far);
	Mat4 projectOrthographic(const float& near, const float& far, const float& left, const float& right, const float& top, const float& bottom);
}

namespace vec_utils
{
	float length(const Vec3& vec);
	float distance(const Vec3& vec1, const Vec3& vec2);
	Vec3  normalize(const Vec3& vec);
}

namespace img_utils
{
	unsigned int textureFromFile(const char* path, const std::string& directory, bool gamma = false);
	unsigned int createTexture(const std::string& data_dir, const std::string& path, const int& wrapping = 0);
	void setVerticalFlipMode(bool flipMode);
	unsigned int loadCubemap(const std::string& data_dir, const std::vector<std::string>& faces);
	void saveFrameBufferAsPNG(int width, int height, const char* filename);
}

namespace color_utils
{
	unsigned int hexToUInt(const std::string& hex);
	std::vector<unsigned int> hexToRGB(const std::string& hexColor);
}