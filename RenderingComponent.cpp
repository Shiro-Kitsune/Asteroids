#include "stdafx.h"

RenderingComponent::RenderingComponent(const Color& color, bool visible) : m_color(color)
{
	m_visible = visible;
}


RenderingComponent::RenderingComponent(const Color & color, std::vector<LineSegment> lines, bool visible) : m_color(color), m_lines(std::move(lines))
{
	m_visible = visible;
}

void RenderingComponent::AddLineSegment(const LineSegment& line)
{
	m_lines.push_back(line);
}

void RenderingComponent::DeleteGeometry()
{
	m_lines.clear();
}

const std::vector<LineSegment>& RenderingComponent::GetGeometry() const
{
	return m_lines;
}

const Color& RenderingComponent::GetColor() const
{
	return m_color;
}

void RenderingComponent::SetColor(const Color& color)
{
	m_color = color;
}

void RenderingComponent::SetVisibility(bool visible)
{
	m_visible = visible;
}

bool RenderingComponent::IsVisible() const
{
	return m_visible;
}