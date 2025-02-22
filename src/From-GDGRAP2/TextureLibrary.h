#pragma once

#include <memory>
#include <unordered_map>
#include <string>

namespace Vulkan
{
	struct SamplerConfig;
}

namespace Assets
{
	class Texture;
}

class TextureLibrary
{
private:
	typedef std::unordered_map <std::string, Assets::Texture> TextureMap;

	TextureMap textureMap;

public:
	void addTexture(const std::string& textureName, const std::string& fileName);
	void deleteTexture(std::string textureName);
	Assets::Texture getTexture(std::string textureName);
	std::vector<Assets::Texture> getTextureLibraryList();

private:
	static TextureLibrary* sharedInstance;

private:
	TextureLibrary();
	~TextureLibrary();
	TextureLibrary(TextureLibrary const&);
	TextureLibrary& operator= (TextureLibrary const&);

public:
	static TextureLibrary* getInstance();
	static void initialize();
	static void destroy();
};