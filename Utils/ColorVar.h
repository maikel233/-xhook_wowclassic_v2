#pragma once
#include <imgui.h>
#include "Utils.h" // Assuming Utils.h contains the necessary utility functions

class ColorVar {
public:
    ImColor color;
    bool rainbow;
    float rainbowSpeed;

    // Constructor with default parameters and member initializer list
    ColorVar(const ImColor& color = ImColor(255, 255, 255, 255), bool rainbow = false, float rainbowSpeed = 0.5f)
        : color(color), rainbow(rainbow), rainbowSpeed(rainbowSpeed) {
    }

    // Function to retrieve the current color, considering rainbow effect
    ImColor getColor() const {
        if (rainbow) {
            ImColor result = Utils::GetRainbowColor(rainbowSpeed);
            result.Value.w = color.Value.w; // Preserve the original alpha
            return result;
        }
        return color;
    }
};

class HealthColorVar : public ColorVar {
public:

    // Declare Print if it's meant to be a member
    // SomeType Print;

    HealthColorVar(const ImColor& color = ImColor(255, 255, 255, 255), bool rainbow = false, float rainbowSpeed = 0.5f, bool hp = false)
        : ColorVar(color, rainbow, rainbowSpeed) {
        // Constructor body
    }
    // Function to retrieve the color based on health status
    ImColor getColor(const WObject* player) const {
        if (rainbow) {
            ImColor result = Utils::GetRainbowColor(rainbowSpeed);
            result.Value.w = color.Value.w; // Preserve the original alpha
            return result;
        }
       /* if (hp) {
            return Color::ToImColor(Utils::GetHealthColor(player));
        }*/
        return color;
    }
};
