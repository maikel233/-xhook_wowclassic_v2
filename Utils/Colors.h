#pragma once
#include <windows.h>
#include <algorithm>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

struct Color {
    int r;
    int g;
    int b;
    int a;

    // Default constructor
    Color() : r(0), g(0), b(0), a(255) {}

    // Constructor with RGB, default alpha
    Color(int red, int green, int blue, int alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {
    }

    // Operator overloading for division
    Color operator/(float div) const {
        return Color(
            static_cast<int>(r / div),
            static_cast<int>(g / div),
            static_cast<int>(b / div),
            a
        );
    }

    // Operator overloading for division assignment
    Color& operator/=(float div) {
        r = static_cast<int>(r / div);
        g = static_cast<int>(g / div);
        b = static_cast<int>(b / div);
        return *this;
    }

    // Operator overloading for multiplication assignment
    Color& operator*=(float coeff) {
        r = static_cast<int>(r * coeff);
        g = static_cast<int>(g * coeff);
        b = static_cast<int>(b * coeff);
        return *this;
    }

    // Static function to create a Color from HSB values
    static Color FromHSB(float hue, float saturation, float brightness) {
        float h = (hue == 1.0f) ? 0.0f : (hue * 6.0f);
        float f = h - static_cast<int>(h);
        float p = brightness * (1.0f - saturation);
        float q = brightness * (1.0f - saturation * f);
        float t = brightness * (1.0f - (saturation * (1.0f - f)));

        if (h < 1)
            return Color(static_cast<int>(brightness * 255), static_cast<int>(t * 255), static_cast<int>(p * 255));
        else if (h < 2)
            return Color(static_cast<int>(q * 255), static_cast<int>(brightness * 255), static_cast<int>(p * 255));
        else if (h < 3)
            return Color(static_cast<int>(p * 255), static_cast<int>(brightness * 255), static_cast<int>(t * 255));
        else if (h < 4)
            return Color(static_cast<int>(p * 255), static_cast<int>(q * 255), static_cast<int>(brightness * 255));
        else if (h < 5)
            return Color(static_cast<int>(t * 255), static_cast<int>(p * 255), static_cast<int>(brightness * 255));
        else
            return Color(static_cast<int>(brightness * 255), static_cast<int>(p * 255), static_cast<int>(q * 255));
    }

    // Static function to convert ImColor to Color
    static Color FromImColor(const ImColor& color) {
        return Color(
            static_cast<int>(color.Value.x * 255),
            static_cast<int>(color.Value.y * 255),
            static_cast<int>(color.Value.z * 255),
            static_cast<int>(color.Value.w * 255)
        );
    }

    // Static function to convert Color to ImColor
    static ImColor ToImColor(const Color& color) {
        return ImColor(
            color.r / 255.0f,
            color.g / 255.0f,
            color.b / 255.0f,
            color.a / 255.0f
        );
    }
};
