#pragma once

#include <random>

class Utilities
{
public:
	static int Random(int min, int max);
	static bool CircleOverlap(const Vector2D & position1, float radius1, const Vector2D & position2, float radius2);
	static float ToRadians(float degrees);
	static float ToDegrees(float degrees);
	static float MapValue(float value, float start1, float end1, float start2, float end2);

    static inline float Random(float min, float max) {
        thread_local static std::mt19937 gen{std::random_device{}()};
        thread_local static std::uniform_real_distribution<float> pick{min, max};
        return pick(gen);
    }

    static inline float RandomFrom0To1() {
        thread_local static std::mt19937 gen{std::random_device{}()};
        thread_local static std::uniform_real_distribution<float> pick{0.0f, 1.0f};
        return pick(gen);
    }

private:
	Utilities() {}
};