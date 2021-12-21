#include "graphic.hpp"

#include <iostream>
#include <fstream>
using namespace std;
Color::Color()
    : r(0), g(0), b(0)
{

}

Color::Color(float r, float g, float b)
    :r(r), g(g), b(b)
{

}

Color::~Color()
{

}

Graphic::Graphic(int width, int height)
    :m_width(width), m_height(height), m_colors(vector<Color>(width * height))
{

}

Graphic::~Graphic()
{

}

Color Graphic::get_color(int x, int y) const
{
    return m_colors[y * m_width + x];
}

void Graphic::set_color(const Color& color, int x, int y)
{
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

void Graphic::Export(const char* path) const
{
    ofstream my_file;
    my_file.open(path, ios::out | ios::binary);

    if(!my_file.is_open())
    {
        cout << "File could not be opened" << endl;
        return;
    }

    unsigned char bmpPad[3] = {0, 0, 0};
    const int padding_amount = ((4 - (m_width * 3) % 4) % 4);

    const int file_header_size = 14;
    const int information_header_size = 40;
    const int file_size = file_header_size + information_header_size + m_width * m_height * 3 + padding_amount * m_height;

    unsigned char file_header[file_header_size];
    //File type
    file_header[0] = 'B';
    file_header[1] = 'M';
    //File size
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;
    //Reserved 1 (not used)
    file_header[6] = 0;
    file_header[7] = 0;
    //Reserved 2 (not used)
    file_header[8] = 0;
    file_header[9] = 0;
    //pixel data offset
    file_header[10] = file_header_size + information_header_size;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;

    unsigned char information_header[information_header_size];

    //Header size
    information_header[0] = information_header_size;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;

    information_header[4] = m_width;
    information_header[5] = m_width >> 8;
    information_header[6] = m_width >> 16;
    information_header[7] = m_width >> 24;

    information_header[8] = m_height;
    information_header[9] = m_height >> 8; 
    information_header[10] = m_height >> 16;
    information_header[11] = m_height >> 24;

    information_header[12] = 1;
    information_header[13] = 0;

    information_header[14] = 24;
    information_header[15] = 0;

    information_header[16] = 0;
    information_header[17] = 0;
    information_header[18] = 0;
    information_header[19] = 0;

    information_header[20] = 0;
    information_header[21] = 0;
    information_header[22] = 0;
    information_header[23] = 0;

    information_header[24] = 0;
    information_header[25] = 0;
    information_header[26] = 0;
    information_header[27] = 0;

    information_header[28] = 0;
    information_header[29] = 0;
    information_header[30] = 0;
    information_header[31] = 0;

    information_header[32] = 0;
    information_header[33] = 0;
    information_header[34] = 0;
    information_header[35] = 0;

    information_header[36] = 0;
    information_header[37] = 0;
    information_header[38] = 0;
    information_header[39] = 0;

    my_file.write(reinterpret_cast<char*> (file_header), file_header_size);
    my_file.write(reinterpret_cast<char*> ( information_header), information_header_size);

    for(int y = 0; y < m_height; y++)
    {
        for(int x = 0; x < m_width; x++)
        {
            unsigned char r = static_cast<unsigned char> (get_color(x, y).r * 255.0f);
            unsigned char g = static_cast<unsigned char> (get_color(x, y).g * 255.0f);
            unsigned char b = static_cast<unsigned char> (get_color(x, y).b * 255.0f);

            unsigned char color[] = {b, g, r};

            my_file.write(reinterpret_cast<char*>(color), 3);
        }

        my_file.write(reinterpret_cast<char*>(bmpPad), padding_amount);
    }

    my_file.close();

    cout << "File created" << endl;


}