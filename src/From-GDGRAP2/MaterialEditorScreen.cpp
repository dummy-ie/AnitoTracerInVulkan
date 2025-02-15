#include "MaterialEditorScreen.h"

#include <algorithm>

#include "UIManager.h"

using namespace gdeng03;

MaterialEditorScreen::MaterialEditorScreen() : AUIScreen("MaterialEditorScreen")
{
	//loadDefaultTextures();
}

bool MaterialEditorScreen::canSelectMaterial() const
{
	return selectedMaterial == nullptr;
}

void MaterialEditorScreen::setSelectedMaterial(Material* mat)
{
	//loadDefaultTextures();
	color = { mat->Diffuse.x, mat->Diffuse.y, mat->Diffuse.z, mat->Diffuse.w };

	// if (!mat->albedoTexture)
	// 	albedoTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/default_square.png");
	// else
	// {
	// 	this->albedoTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(mat->albedoTexture->fullPath.c_str());
	// 	//LogUtils::log(this, "AlbedoTexture is not null");
	// }
	//
	// if (!mat->metallicTexture)
	// 	metallicTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/default_square.png");
	// else
	// 	this->metallicTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(mat->metallicTexture->fullPath.c_str());
	//
	// if (!mat->smoothnessTexture)
	// 	smoothnessTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/default_square.png");
	// else
	// 	this->smoothnessTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(mat->smoothnessTexture->fullPath.c_str());
	//
	// if (!mat->normalTexture)
	// 	normalTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/default_square.png");
	// else
	// 	this->normalTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(mat->normalTexture->fullPath.c_str());

	// this->metallic = mat->metallic;
	// this->smoothness = mat->smoothness;
	// this->flatness = mat->flatness;
	//
	// this->tiling = mat->tiling;
	// this->offset = mat->offset;

	selectedMaterial = mat;
}

void MaterialEditorScreen::unselectMaterial()
{
	selectedMaterial = nullptr;
	//loadDefaultTextures();
}

// bool* MaterialEditorScreen::getMaterialEditorOpen()
// {
// 	return &isMaterialEditorOpen;
// }

void MaterialEditorScreen::drawUI()
{
	if (isColorPickerOpen && !enabled)
		isColorPickerOpen = false;

	if (isColorPickerOpen)
		showColorPickerWindow();

	ImGui::Begin("Material Editor", &enabled);

	if (selectedMaterial != nullptr)
	{
		showMaterialEditorWindow();
		updateSelectedMaterial();
	}

	ImGui::End();

}

void MaterialEditorScreen::showColorPickerWindow()
{
	if (ImGui::Begin("Color Picker", &isColorPickerOpen))
	{
		ImGui::SameLine();
		ImGui::ColorPicker4("Albedo Color##4", reinterpret_cast<float*>(&color), 0);
	}
	ImGui::End();
}

// idk what the fuck goin on anymore tbh
void MaterialEditorScreen::updateMaterial(Material* mat)
{
	setSelectedMaterial(mat);
	updateSelectedMaterial();
	unselectMaterial();
}

void MaterialEditorScreen::updateSelectedMaterial()
{
	if (!selectedMaterial)
	{
		//loadDefaultTextures();
		return;
	}

	selectedMaterial->Diffuse = { this->color.x, this->color.y, this->color.z, this->color.w };

	// selectedMaterial->albedoTexture = this->albedoTexture;
	// selectedMaterial->metallicTexture = this->metallicTexture;
	// selectedMaterial->smoothnessTexture = this->smoothnessTexture;
	// selectedMaterial->normalTexture = this->normalTexture;
	//
	// selectedMaterial->metallic = this->metallic;
	// selectedMaterial->smoothness = this->smoothness;
	// selectedMaterial->flatness = this->flatness;
	//
	// selectedMaterial->tiling = this->tiling;
	// selectedMaterial->offset = this->offset;
}

void MaterialEditorScreen::showMaterialEditorWindow()
{
	ImGui::Text("Main Maps");
	constexpr ImVec2 imageSize = { 100, 100 };
	//albedo
	ImGui::Text("Albedo Map");
	// if (ImGui::ImageButton("Albedo Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(albedoTexture->getShaderResourceView())), imageSize))
	// {
	// 	loadTextureFile(albedoTexture);
	// }
	ImGui::SameLine();
	if (ImGui::ColorButton("Color", color, 0, ImVec2(50, 30)))
	{
		isColorPickerOpen = !isColorPickerOpen;
	}
	if (ImGui::Button("Clear Albedo"))
	{
		//GraphicsEngine::get()->getTextureManager()->loadBlankTexture(albedoTexture);
	}

	ImGui::NewLine();

	//slider size
	ImGui::PushItemWidth(250);

	//metallic
	ImGui::Text("Metallic Map");
	// if (ImGui::ImageButton("Metallic Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(metallicTexture->getShaderResourceView())), imageSize))
	// {
	// 	loadTextureFile(metallicTexture);
	// }
	ImGui::SameLine();
	ImGui::SliderFloat("Metallic", &metallic, 0, 1);
	if (ImGui::Button("Clear Metallic"))
	{
		//GraphicsEngine::get()->getTextureManager()->loadBlankTexture(metallicTexture);
	}

	ImGui::NewLine();

	//smoothness
	ImGui::Text("Smoothness Map");
	// if (ImGui::ImageButton("Smoothness Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(smoothnessTexture->getShaderResourceView())), imageSize))
	// {
	// 	loadTextureFile(smoothnessTexture);
	// }
	ImGui::SameLine();
	ImGui::SliderFloat("Smoothness", &smoothness, 0, 1);
	if (ImGui::Button("Clear Smoothness"))
	{
		//GraphicsEngine::get()->getTextureManager()->loadBlankTexture(smoothnessTexture);
	}

	ImGui::NewLine();

	//albedo
	ImGui::Text("Normal Map");
	// if (ImGui::ImageButton("Normal Map", static_cast<ImTextureID>(reinterpret_cast<intptr_t>(normalTexture->getShaderResourceView())), imageSize))
	// {
	// 	loadTextureFile(normalTexture);
	// 	// if (!isNormalImage(normalTexture))
	// 	// {
	// 	// 	GraphicsEngine::get()->getTextureManager()->loadBlankTexture(normalTexture);
	// 	// }
	// }
	ImGui::SameLine();
	ImGui::SliderFloat("Flatness", &flatness, 0, 1);
	if (ImGui::Button("Clear Normal"))
	{
		//GraphicsEngine::get()->getTextureManager()->loadBlankTexture(normalTexture);
	}

	ImGui::NewLine();

	//input field size
	ImGui::PushItemWidth(125);

	//tiling
	ImGui::Text("Tiling");
	//x
	ImGui::Text("X"); ImGui::SameLine(40);
	ImGui::PushItemWidth(225);
	ImGui::SliderFloat("##TilingXSlider", &tiling.x, -20, 20); ImGui::SameLine();
	ImGui::PushItemWidth(125);
	ImGui::InputFloat("##Tiling X", &tiling.x);
	//y
	ImGui::Text("Y"); ImGui::SameLine(40);
	ImGui::PushItemWidth(225);
	ImGui::SliderFloat("##TilingYSlider", &tiling.y, -20, 20); ImGui::SameLine();
	ImGui::PushItemWidth(125);
	ImGui::InputFloat("##Tiling Y", &tiling.y);

	ImGui::NewLine();

	//offset
	ImGui::Text("Offset");
	//x
	ImGui::Text("X"); ImGui::SameLine(40);
	ImGui::PushItemWidth(225);
	ImGui::SliderFloat("##OffsetXSlider", &offset.x, -20, 20); ImGui::SameLine();
	ImGui::PushItemWidth(125);
	ImGui::InputFloat("##Offset X", &offset.x);
	//y
	ImGui::Text("Y"); ImGui::SameLine(40);
	ImGui::PushItemWidth(225);
	ImGui::SliderFloat("##OffsetYSlider", &offset.y, -20, 20); ImGui::SameLine();
	ImGui::PushItemWidth(125);
	ImGui::InputFloat("##Offset Y", &offset.y);

	ImGui::PopItemWidth();
}

// std::vector<unsigned char> MaterialEditorScreen::getPixelData(const TexturePtr& texture)
// {
// 	std::vector<unsigned char> pixelData;
//
// 	if (!texture) return pixelData;
//
// 	//get the texture resource from the shader resource view
// 	const Microsoft::WRL::ComPtr<ID3D11Resource> resource = texture->getResource();
//
// 	//get the texture description
// 	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
// 	if (FAILED(resource.As(&texture2D))) return pixelData;
//
// 	D3D11_TEXTURE2D_DESC textureDesc;
// 	texture2D->GetDesc(&textureDesc);
//
// 	//create a staging texture for cpu access
// 	textureDesc.Usage = D3D11_USAGE_STAGING;
// 	textureDesc.BindFlags = 0;
// 	textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
// 	textureDesc.MiscFlags = 0;
//
// 	Microsoft::WRL::ComPtr<ID3D11Texture2D> stagingTexture;
// 	if (const HRESULT hr = GraphicsEngine::get()->getRenderSystem()->getDevice()->CreateTexture2D(&textureDesc, nullptr, &stagingTexture); FAILED(hr))
// 		return pixelData;
//
// 	//copy the original texture to the staging texture
// 	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->copyResource(stagingTexture.Get(), resource.Get());
//
// 	//map the staging texture for reading
// 	D3D11_MAPPED_SUBRESOURCE mappedData;
// 	if (!GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->mapResource(stagingTexture.Get(), mappedData, 0, D3D11_MAP_READ, 0)) {
// 		return pixelData;
// 	}
//
// 	//calculate pixel data size and copy it
// 	const size_t rowPitch = mappedData.RowPitch;
// 	const size_t dataSize = rowPitch * textureDesc.Height;
// 	pixelData.resize(dataSize);
// 	memcpy(pixelData.data(), mappedData.pData, dataSize);
//
// 	//unmap the resource
// 	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->unmapResource(stagingTexture.Get(), 0);
//
// 	return pixelData;
// }

// bool MaterialEditorScreen::isNormalImage(const TexturePtr& texture)
// {
// 	const std::vector<unsigned char> pixelData = getPixelData(texture);
//
// 	//calculate average blue dominance.
// 	const int totalPixels = pixelData.size() / 4;
// 	int blueDominantCount = 0;
//
// 	for (int i = 0; i < totalPixels; ++i)
// 	{
// 		const int r = pixelData[i * 4];
// 		const int g = pixelData[i * 4 + 1];
// 		const int b = pixelData[i * 4 + 2];
//
// 		//check if blue is the highest component.
// 		if (b > r && b > g)
// 		{
// 			blueDominantCount++;
// 		}
// 	}
//
// 	//threshold
// 	return (blueDominantCount / static_cast<float>(totalPixels)) >= 0.9f;
// }

// void MaterialEditorScreen::loadTextureFile(TexturePtr& texture)
// {
// 	//create file object instance
// 	if (!LogUtils::logHResult(this, CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
// 	{
// 		return;
// 	}
//
// 	//create fileopnedialogue object
// 	IFileOpenDialog* f_FileSystem;
// 	if (!LogUtils::logHResult(this, CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&f_FileSystem))))
// 	{
// 		CoUninitialize();
// 		return;
// 	}
//
// 	COMDLG_FILTERSPEC fileTypes[] = {
// 		{ L"Image Files", L"*.jpg;*.jpeg;*.png" }
// 	};
//
// 	f_FileSystem->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
// 	f_FileSystem->SetFileTypeIndex(1);
// 	f_FileSystem->SetDefaultExtension(L"jpg");
//
// 	//this part does NOT like LogUtils::logHResult at all
// 	//open file dialogue window
// 	if (const HRESULT fileSelect = f_FileSystem->Show(nullptr); FAILED(fileSelect))
// 	{
// 		LogUtils::log(this, "Texture load cancelled");
// 		f_FileSystem->Release();
// 		CoUninitialize();
// 		return;
// 	}
//
// 	//retrieve file name from selected item
// 	IShellItem* fFiles;
// 	if (!LogUtils::logHResult(this, f_FileSystem->GetResult(&fFiles)))
// 	{
// 		f_FileSystem->Release();
// 		CoUninitialize();
// 		return;
// 	}
//
// 	//store and convert file name
// 	PWSTR fPath;
// 	if (!LogUtils::logHResult(this, fFiles->GetDisplayName(SIGDN_FILESYSPATH, &fPath)))
// 	{
// 		fFiles->Release();
// 		f_FileSystem->Release();
// 		CoUninitialize();
// 		return;
// 	}
//
// 	//format and store file path
// 	std::wstring path(fPath);
// 	std::replace(path.begin(), path.end(), L'\\', L'/');
// 	const wchar_t* wPath = path.c_str();
//
// 	//create texture from file
// 	texture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(wPath);
//
// 	// if (!LogUtils::logHResult(
// 	// 	this,
// 	// 	DirectX::CreateWICTextureFromFile(
// 	// 		GraphicsEngine::get()->getRenderSystem()->getDevice(),
// 	// 		w_path,
// 	// 		nullptr,
// 	// 		texture)))
// 	// {
// 	// 	LogUtils::log(this, "Texture load failed");
// 	// 	LogUtils::log(this, std::string(path.begin(), path.end()));
// 	// }
// 	// else
// 	// {
// 	// 	LogUtils::log(this, "Texture load success");
// 	// 	LogUtils::log(this, std::string(path.begin(), path.end()));
// 	// }
//
//
// 	CoTaskMemFree(fPath);
// 	fFiles->Release();
// 	f_FileSystem->Release();
// 	CoUninitialize();
// }

// void MaterialEditorScreen::loadDefaultTextures()
// {
// 	albedoTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/default_square.png");
// 	metallicTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/default_square.png");
// 	smoothnessTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/default_square.png");
// 	normalTexture = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"assets/images/default_square.png");
//
// 	color = ImVec4(1, 1, 1, 1);
// }
