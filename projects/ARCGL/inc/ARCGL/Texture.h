/*-----------------------------------------------------------------------------
Author: Aaron Cox
Description:	Basic Texture class...
does nothing special except wrap up basic texture information like width,
height and the handle provided by openGL

Usage:
-------------------------------------------------------------------------------

// creating a texture
Texture *pTexture = new Texture( "image.png" )

pTexture->GetWidth();
pTexture->GetHeight();
pTexture->GetTextureHandle();

// rendering can be preformed via the SpriteBatch!
// or the texture can be used in standard opengl calls
// such as:
glBindTexure(GL_TEXTURE_2D, pTexture->GetTextureHandle());

// when done, make sure to delete the texture
delete pTexture;

-----------------------------------------------------------------------------*/


#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:

	// overloaded constructor
	// loads a texture given the filename...
	// program will crash if texture was unable to be found.
	Texture(const char *filename);

	// overloaded constructor
	// builds a texture given the width, height and pointer to an array of pixels
	Texture(unsigned int width, unsigned int height, unsigned int *pixels = 0);

	// destructor
	// frees the texture from video memory
	virtual ~Texture();

	// Return the textures size
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;

	// returns the texture handle genorated by openGL
	unsigned int GetTextureHandle()	const;


protected:

	unsigned int	m_width;
	unsigned int	m_height;
	unsigned int	m_glTextureHandle;

private:

	// Returns an OpenGL texture ID
	// out_width and out_height are pointers, the function will return the textures width and height
	// through these paramaters if not NULL
	static unsigned int LoadTexture(const char *filename, unsigned int *out_width = 0, unsigned int *out_height = 0);

	// unloads the texture from graphics memory
	// expects a valid openGL texture ID, as returned from the LoadTexture function
	static void DeleteTexture(unsigned int textureID);

};

#endif