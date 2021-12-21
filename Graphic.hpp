#include <vector>

struct Color
{
    float r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};


class Graphic
{
public:
    Graphic(int width, int height);
    ~Graphic();

    Color get_color(int x, int y) const;
    void set_color(const Color& color, int x, int y);

    void Export(const char* path) const;

private:
    int64_t m_width;
    int64_t m_height;
    std::vector<Color> m_colors;
};