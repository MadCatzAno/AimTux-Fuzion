#include "panel.h"


Panel::Panel ()
{
}


Panel::Panel (Vector2D position) : Panel ()
{
	this->position = position;
}

Panel::Panel (Vector2D position, Vector2D size) : Panel (position)
{
	this->size = size;
}


Panel::Panel (Vector2D position, Vector2D size, Color backgroundColor) : Panel (position, size)
{
	this->backGroundColor = backgroundColor;
}


void Panel::AddComponent (Component* component)
{
	childComponents.push_back (component);
}

void Panel::RemoveComponent (Component* component)
{
	childComponents.erase (std::remove(childComponents.begin(), childComponents.end(), component));
}

void Panel::Draw ()
{
	this->Clear (backGroundColor);
	
	
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		
		// Update the childs context
		childComponent->context = this->context + childComponent->position;
		
		// Draw the component
		childComponent->Draw ();
	}
}

void Panel::MouseMove (PositionContext mouseContext)
{
	for (int i = 0; i < childComponents.size(); i++)
	{
		Component* childComponent = childComponents[i];
		
		int x = mouseContext.x;
		int y = mouseContext.y;
		
		if	(
				x >= childComponent->position.x && x <= childComponent->position.x + childComponent->size.x &&
				y >= childComponent->position.y && y <= childComponent->position.y + childComponent->size.y
			)
		{
			if (!childComponent->isHovered)
			{
				if (childComponent->onMouseEnterEvent != NULL)
				{
					childComponent->onMouseEnterEvent();
				}
				childComponent->isHovered = true;
			}
			childComponent->MouseMove (mouseContext - childComponent->position);
		}
		else
		{
			if (childComponent->isHovered)
			{
				if (childComponent->onMouseLeaveEvent != NULL)
				{
					childComponent->onMouseLeaveEvent();
				}
				childComponent->isHovered = false;
			}
		}
	}
}



