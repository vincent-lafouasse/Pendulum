#pragma once

struct Mass {
    float grams;

    [[nodiscard]] Mass from_kilos(float k) { return {1000.0f * k}; }
    [[nodiscard]] Mass from_grams(float g) { return {g}; }

    [[nodiscard]] float as_kilos() const { return grams / 1000.0f; }
    [[nodiscard]] float as_grams() const { return grams; }
    [[nodiscard]] float si() const { return as_grams(); }
};


struct Length {
    float millis;

    [[nodiscard]] Length from_meters(float m) { return {1000.0f * m}; }
    [[nodiscard]] Length from_millis(float m) { return {m}; }

    [[nodiscard]] float as_meters() const { return millis / 1000.0f; }
    [[nodiscard]] float as_millis() const { return millis; }
    [[nodiscard]] float si() const { return as_millis(); }
};
