#pragma once

class Matrix3x3
{
public:
	static Matrix3x3 RotationMatrix(float angle);
	static Matrix3x3 TranslationMatrix(const Vector2D& translation);
	static Matrix3x3 UniformScaleMatrix(float scaleFactor);
	static Matrix3x3 NonUniformScaleMatrix(float scaleX, float scaleY);

	Matrix3x3();
	Matrix3x3(std::array<std::array<float, 3>, 3> matrixArray) : m_matrix(std::move(matrixArray)) {}
	void Transpose();
	Matrix3x3 operator+(const Matrix3x3& matrix) const;
	Matrix3x3 operator-(const Matrix3x3& matrix) const;
	Matrix3x3 operator*(const Matrix3x3& matrix) const;
	Vector2D operator*(const Vector2D& vector) const;
	Matrix3x3& operator+=(const Matrix3x3& right);
	Matrix3x3& operator-=(const Matrix3x3& right);
	Matrix3x3& operator*=(const Matrix3x3& matrix);
private:
	std::array<std::array<float, 3>, 3> m_matrix;
};
