#ifndef _TEXTUREBASE_H
#define _TEXTUREBASE_H

enum TextureLoadStatus {
	Error,
	Error_Reading_File,
	Invalid_Format,
	OK
};

enum TextureFormat {
	RGB,
	RGBA,
	DEPTH
};

class TextureBase {
public:
	TextureBase( int textureType );
	virtual ~TextureBase();

	virtual TextureLoadStatus Load() = 0;
	virtual void Create( int width, int height, TextureFormat textureFormat ) = 0;
	void Bind();
	void Unbind();
	void Unload();
	void SetName( const char * name ) { this->name = name; }
	const char * GetName() { return name; }
	int GetTextureId() { return textureId; }
	int GetTextureType() { return textureType; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
protected:
	int textureType;
	unsigned int textureId;
	bool mipMapping;
	const char * name;
	int width;
	int height;
private:
	// Disallows copy constructor
	TextureBase( const TextureBase& orig );
	// Disallows the copy constructor
	TextureBase& operator = ( const TextureBase& other );
};

#endif // !_TEXTUREBASE_H