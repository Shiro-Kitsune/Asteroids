#pragma once

class RenderingComponent;
class UITextComponent;
class ParticleEmmiter;

class Renderer
{
public:
	void Render(const EntityManager& manager) const;
private:
	void RenderEntity(const RenderingComponent& renderingComponent, const Vector2D& position, float angle) const;
	void RenderUIText(const UITextComponent& uiTextComponent, const Vector2D& position) const;
	void RenderParticles(const ParticleEmmiter& particleEmmiter, const Vector2D& position, float angle) const;
};