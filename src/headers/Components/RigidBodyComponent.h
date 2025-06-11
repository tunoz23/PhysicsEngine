#pragma once

// These must be defined before any Jolt includes

// Must include Core.h first
#include "Jolt/Jolt.h"
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

// STL includes

// Optional: wrap inside your namespace
struct RigidBodyComponent
{
    JPH::BodyID bodyID = static_cast<JPH::BodyID>(JPH::BodyID::cInvalidBodyID);

};
