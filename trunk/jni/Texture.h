
#ifndef TEXTURE_H
#define TEXTURE_H 

class Texture
{

  /// ID number given to texture (OpenGL or PSP GU, etc)
  int texture_id;

  public:
    static int loadTexture(const char* filename);
    static Texture* createTexture(const char* filename);

};

#endif /* TEXTURE_H */
