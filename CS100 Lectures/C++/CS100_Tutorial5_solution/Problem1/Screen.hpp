#include <stdlib.h>

class Screen {
public:
  Screen( int width, int height );

  int GetWidth();
  int GetHeight();
  void SetWidth( int width );
  void SetHeight( int height );
  
  int GetNumberPixels();

private:
  int m_width;
  int m_height;
};