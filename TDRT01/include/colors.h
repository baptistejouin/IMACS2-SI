typedef struct col3f
{
    float r, g, b;
} ColorRGB;

// Construit la couleur (r, g, b)
ColorRGB createColor(float r, float g, float b);

// Addition, soustraction et multiplication des couleurs C1 et C2
ColorRGB addColors(ColorRGB c1, ColorRGB c2);
ColorRGB subColors(ColorRGB c1, ColorRGB c2);
ColorRGB multColors(ColorRGB c1, ColorRGB c2);

// Multiplication et division d une couleur C par un scalaire a
ColorRGB multColor(ColorRGB c, float a);
ColorRGB divColor(ColorRGB c, float a);