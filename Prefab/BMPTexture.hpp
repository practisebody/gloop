#pragma once

_GL_BEGIN
_PREFAB_BEGIN
class BMPTexture : public Texture2D
{
public:
	BMPTexture()
	{
		m_dataFormat = GL_BGR;
	}

	BMPTexture* Data(const char* name)
	{
		std::unique_ptr<BITMAPFILEHEADER> bmpHeader = std::make_unique<BITMAPFILEHEADER>();
		std::unique_ptr<BITMAPINFOHEADER> bmpInfo = std::make_unique<BITMAPINFOHEADER>();

		std::ifstream file(name, std::ios::binary);
		assert(file);

		file.read(reinterpret_cast<char*>(bmpHeader.get()), sizeof(BITMAPFILEHEADER));
		file.read(reinterpret_cast<char*>(bmpInfo.get()), sizeof(BITMAPINFOHEADER));
		assert(bmpHeader->bfType == 0x4D42);

		m_nWidth = bmpInfo->biWidth;
		m_nHeight = bmpInfo->biHeight;
		m_dataType = static_cast<GLenum>(GL::DATA_TYPE::UNSIGNED_BYTE);
		std::unique_ptr<char[]> image = std::make_unique<char[]>(bmpInfo->biSizeImage * 3);
		file.seekg(bmpHeader->bfOffBits);
		file.read(image.get(), bmpInfo->biSizeImage);
		file.close();

		Texture2D::Data(image.get());

		EL_PSY_CONGROO;
	}
};
_PREFAB_END
_GL_END