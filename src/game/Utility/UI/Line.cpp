//
// Created by e22-watson on 29/01/2020.
//

#include <cmath>

#include "Line.h"

Line::Line(ASGE::Renderer* renderer, int height, ASGE::Colour colour)
{
  sprite = renderer->createRawSprite();
  sprite->loadTexture(texture_path);
  sprite->height(height);
  sprite->colour(colour);
}

void Line::drawLine(ASGE::Renderer* renderer,
                    Vector2 start_pos,
                    Vector2 end_pos)
{
  // Get the vector representing the difference between end_pod and start_pos
  Vector2 angular_vector = end_pos - start_pos;

  // The magnitude of this is the length - in this case width - of the line
  sprite->width(angular_vector.getMagnitude());

  // The rotation in radians will be the inverse tangent of the same vector
  // (tan^-1(O/A))
  sprite->rotationInRadians(
    std::atan(angular_vector.getY() / angular_vector.getX()));

  // Since sprites draw from the top left we need to draw either from the target
  // XPos or start XPos depending on whether the line is pointing left or right
  // from its start position
  sprite->xPos(angular_vector.getX() > 0 ? start_pos.getX() : end_pos.getX());

  // Because it's rotated from the center we need to correct the line's xPos (it
  // being drawn from the top left) by 1-Cos(angle)
  sprite->xPos(sprite->xPos() -
               std::abs((sprite->width() / 2) *
                        (1 - std::cos(sprite->rotationInRadians()))));

  // YPos needs to be corrected by the average of the two positions
  sprite->yPos((start_pos.getY() + end_pos.getY()) / 2);

  renderer->renderSprite(*sprite);
}