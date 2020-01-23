//
// Created by Joshua on 23/01/2020.
//

#pragma once
struct rect
{
  float x = 0;
  float y = 0;
  float length = 0;
  float height = 0;
  bool isInside(float x, float y) const;
  bool isInside(const rect& rhs) const;
  bool isBetween(float value, float min, float max) const;
};