#include "stdafx.h"

void Renderer::Render(const EntityManager& manager) const
{
	for (auto& entity : manager.GetEntities())
	{				
		Vector2D position = entity->GetPosition();
		float angle = entity->GetAngle();

		//If entity has a parent component its position is relative to parent's position, not world's position
		ParentComponent* parentComponent = entity->GetComponent<ParentComponent>();
		if (parentComponent != nullptr)
		{
			position += parentComponent->GetParentEntity()->GetPosition();
			angle += parentComponent->GetParentEntity()->GetAngle();
		}

		RenderingComponent* renderingComponent = entity->GetComponent<RenderingComponent>();
		if (renderingComponent != nullptr && renderingComponent->IsVisible())
		{
			RenderEntity(*renderingComponent, position, angle);
		}

		UITextComponent* uiTextComponent = entity->GetComponent<UITextComponent>();
		if (uiTextComponent != nullptr && uiTextComponent->IsVisible())
		{
			RenderUIText(*uiTextComponent, position);
		}

		ParticleEmmiter* particleEmmiter = entity->GetComponent<ParticleEmmiter>();
		if (particleEmmiter != nullptr)
		{
			RenderParticles(*particleEmmiter, position, angle);
		}
	}
}

void Renderer::RenderEntity(const RenderingComponent& renderingComponent, const Vector2D& position, const float angle) const
{
	Color color = renderingComponent.GetColor();
	std::vector<LineSegment> lines = renderingComponent.GetGeometry();

	if (lines.empty())
	{
		return;
	}

	float angleInRadians = Utilities::ToRadians(angle);
	Matrix3x3 transformationMatrix = Matrix3x3::RotationMatrix(angleInRadians) * Matrix3x3::TranslationMatrix(position);

	for (auto& line : lines)
	{
		Vector2D newStartPoint = line.m_startPoint * transformationMatrix;
		Vector2D newEndPoint = transformationMatrix * line.m_endPoint;
		App::DrawLine(newStartPoint.x, newStartPoint.y, newEndPoint.x, newEndPoint.y, color.red, color.green, color.blue);
	}
}

void Renderer::RenderUIText(const UITextComponent & uiTextComponent, const Vector2D& position) const
{
	Color color = uiTextComponent.GetColor();
	App::Print(position.x, position.y, uiTextComponent.GetText().c_str(), color.red, color.green, color.blue);
}

void Renderer::RenderParticles(const ParticleEmmiter & particleEmmiter, const Vector2D & position, float angle) const
{
	int size = particleEmmiter.GetParticles().size();
	for (auto& particle : particleEmmiter.GetParticles())
	{	
		Vector2D particlePosition = particle->GetPosition() + position;
		float particleAngle = particle->GetAngle() + angle;
		RenderingComponent* renderingComponent = particle->GetComponent<RenderingComponent>();
        RenderEntity(*renderingComponent, particlePosition, particleAngle);
	}
}
