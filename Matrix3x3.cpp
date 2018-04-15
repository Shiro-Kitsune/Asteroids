#include "stdafx.h"

Matrix3x3::Matrix3x3() : m_matrix{ {{1.0f, 0.0f, 0.0f}, {0.0, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}} }
{
}

Matrix3x3 Matrix3x3::RotationMatrix(float angle)
{
	Matrix3x3 matrix;
	matrix.m_matrix[0][0] = cos(angle);
	matrix.m_matrix[0][1] = sin(angle);
	matrix.m_matrix[1][0] = -sin(angle);
	matrix.m_matrix[1][1] = cos(angle);
	return matrix;
}

Matrix3x3 Matrix3x3::TranslationMatrix(const Vector2D& translation)
{
	Matrix3x3 matrix;
	matrix.m_matrix[2][0] = translation.x;
	matrix.m_matrix[2][1] = translation.y;
	return matrix;
}

Matrix3x3 Matrix3x3::UniformScaleMatrix(float scaleFactor)
{
	Matrix3x3 matrix;
	matrix.m_matrix[0][0] = scaleFactor;
	matrix.m_matrix[1][1] = scaleFactor;
	return matrix;
}

Matrix3x3 Matrix3x3::NonUniformScaleMatrix(float scaleX, float scaleY)
{
	Matrix3x3 matrix;
	matrix.m_matrix[0][0] = scaleX;
	matrix.m_matrix[1][1] = scaleY;
	return matrix;
}

void Matrix3x3::Transpose()
{
	std::array<std::array<float, 3>, 3> newMatrix;
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			newMatrix[row][col] = m_matrix[col][row];
		}
	}

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			m_matrix[row][col] = newMatrix[row][col];
		}
	}
}

Matrix3x3 Matrix3x3::operator+(const Matrix3x3& matrix) const
{
	std::array<std::array<float, 3>, 3> newMatrix;
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			newMatrix[row][col] = (m_matrix[row][col] + matrix.m_matrix[row][col]);
		}
	}
	return Matrix3x3(newMatrix);
}

Matrix3x3 Matrix3x3::operator-(const Matrix3x3& matrix) const
{
	std::array<std::array<float, 3>, 3> newMatrix;
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			newMatrix[row][col] = (m_matrix[row][col] - matrix.m_matrix[row][col]);
		}
	}
	return Matrix3x3(newMatrix);
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& right) const
{
	std::array<std::array<float, 3>, 3> newMatrix;
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			newMatrix[row][col] = (m_matrix[row][0] * right.m_matrix[0][col]) + (m_matrix[row][1] * right.m_matrix[1][col]) + (m_matrix[row][2] * right.m_matrix[2][col]);
		}
	}
	return Matrix3x3(newMatrix);
}

Vector2D Matrix3x3::operator*(const Vector2D& vector) const
{
	float x = m_matrix[0][0] * vector.x + m_matrix[1][0] * vector.y + m_matrix[2][0];
	float y = m_matrix[0][1] * vector.x + m_matrix[1][1] * vector.y + m_matrix[2][1];
	return Vector2D(x, y);
}

Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& right)
{
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			m_matrix[row][col] += right.m_matrix[row][col];
		}
	}
	return *this;
}

Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& right)
{
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			m_matrix[row][col] -= right.m_matrix[row][col];
		}
	}
	return *this;
}

Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& matrix)
{
	std::array<std::array<float, 3>, 3> newMatrix;
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			newMatrix[row][col] = (m_matrix[row][0] * matrix.m_matrix[0][col]) + (m_matrix[row][1] * matrix.m_matrix[1][col]) + (m_matrix[row][2] * matrix.m_matrix[2][col]);
		}
	}

	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			m_matrix[row][col] = newMatrix[row][col];
		}
	}
	return *this;
}