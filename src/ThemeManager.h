#pragma once

class QString;

class ThemeManager
{
public:
    enum class Theme
    {
        Light,
        Dark
    };

    static void apply(Theme theme);

private:
    static QString lightTheme();
    static QString darkTheme();
};