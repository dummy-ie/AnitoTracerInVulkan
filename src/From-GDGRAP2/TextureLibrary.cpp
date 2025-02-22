#include "TextureLibrary.h"

#include <stb_image.h>

#include "Assets/Texture.hpp"
#include "Utilities/Exception.hpp"
#include "Utilities/FileUtils.h"

TextureLibrary* TextureLibrary::sharedInstance = nullptr;
void TextureLibrary::addTexture(const std::string& textureName, const std::string& fileName)
{
	//this->textureMap[textureName] = std::make_shared<Assets::Texture>(Assets::Texture::LoadTexture(fileName, Vulkan::SamplerConfig()));
	this->textureMap.insert(std::make_pair(textureName, Assets::Texture::LoadTexture(fileName, Vulkan::SamplerConfig())));
}

void TextureLibrary::deleteTexture(std::string textureName)
{
	this->textureMap.erase(textureName);
}

Assets::Texture TextureLibrary::getTexture(std::string textureName)
{
	return this->textureMap[textureName];
}

std::vector<Assets::Texture> TextureLibrary::getTextureLibraryList()
{
	std::vector<Assets::Texture> textures;
	for (auto& texture : this->textureMap)
	{
		textures.push_back(texture.second);
	}
	return textures;
}

void TextureLibrary::initialize()
{
	sharedInstance = new TextureLibrary();
}

void TextureLibrary::destroy()
{
	delete sharedInstance;
}

TextureLibrary::TextureLibrary()
{
	this->addTexture("white", FileUtils::getAssetsFolderPath().generic_string() + "/textures/white.png");
	this->addTexture("2k_mars", FileUtils::getAssetsFolderPath().generic_string() + "/textures/2k_mars.jpg");
	this->addTexture("2k_moon", FileUtils::getAssetsFolderPath().generic_string() + "/textures/2k_moon.jpg");
	this->addTexture("land_ocean_ice_cloud_2048", FileUtils::getAssetsFolderPath().generic_string() + "/textures/land_ocean_ice_cloud_2048.png");
	this->addTexture("checker", FileUtils::getAssetsFolderPath().generic_string() + "/textures/checker.jpg");
	this->addTexture("earthmap", FileUtils::getAssetsFolderPath().generic_string() + "/textures/earthmap.jpg");
}

TextureLibrary::~TextureLibrary()
{
}

TextureLibrary* TextureLibrary::getInstance()
{
	return sharedInstance;
}
