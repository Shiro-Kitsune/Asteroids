#pragma once

class RenderingComponent : public Component
{
public:
	RenderingComponent(const Color& color, bool visible = true);
	RenderingComponent(const Color& color, std::vector<LineSegment> lines, bool visible = true);

	void AddLineSegment(const LineSegment& line);
	void DeleteGeometry();
	const std::vector<LineSegment>& GetGeometry() const;
	const Color& GetColor() const;
	void SetColor(const Color& color);
	void SetVisibility(bool visible);
	bool IsVisible() const;
private:
	Color m_color;
	bool m_visible;
	std::vector<LineSegment> m_lines;
};