//
// Created by dell on 2018/11/2.
//

#ifndef CPP_CODE_SCREEN_H
#define CPP_CODE_SCREEN_H

class Screen {
private:
    int m_width;
    int m_height;
public:
    Screen();
    Screen(int x, int y);
    int GetWidth();
    int GetHeight();
    void SetWidth(int x);
    void SetHeight(int y);
    int GetNumberPixels();
};


#endif //CPP_CODE_SCREEN_H
