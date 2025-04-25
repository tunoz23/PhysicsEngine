#pragma once

struct CircleColliderComponent
{
	float radius;
	CircleColliderComponent(float radius) : radius(radius) {}
	CircleColliderComponent(CircleColliderComponent const& other) : radius(other.radius) {}
	CircleColliderComponent(CircleColliderComponent const&& other) noexcept : radius(other.radius) {};
};