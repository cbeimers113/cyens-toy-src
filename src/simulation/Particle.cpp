#include <cstddef>
#include "Particle.h"

std::vector<StructProperty> Particle::GetProperties()
{
	std::vector<StructProperty> properties;
	properties.push_back(StructProperty("type", StructProperty::ParticleType, offsetof(Particle, type)));
	properties.push_back(StructProperty("life/carbons", StructProperty::ParticleType, offsetof(Particle, life)));
	properties.push_back(StructProperty("ctype/hydroxyl location", StructProperty::ParticleType, offsetof(Particle, ctype)));
	properties.push_back(StructProperty("x-position", StructProperty::Float, offsetof(Particle, x)));
	properties.push_back(StructProperty("y-position", StructProperty::Float, offsetof(Particle, y)));
	properties.push_back(StructProperty("x-velocity", StructProperty::Float, offsetof(Particle, vx)));
	properties.push_back(StructProperty("y-velocity", StructProperty::Float, offsetof(Particle, vy)));
	properties.push_back(StructProperty("temperature", StructProperty::Float, offsetof(Particle, temp)));
	properties.push_back(StructProperty("flags", StructProperty::UInteger, offsetof(Particle, flags)));
	properties.push_back(StructProperty("tmp/hydrogens", StructProperty::Integer, offsetof(Particle, tmp)));
	properties.push_back(StructProperty("tmp2/bond location", StructProperty::Integer, offsetof(Particle, tmp2)));
	properties.push_back(StructProperty("deco colour", StructProperty::UInteger, offsetof(Particle, dcolour)));
	properties.push_back(StructProperty("pavg0", StructProperty::Float, offsetof(Particle, pavg[0])));
	properties.push_back(StructProperty("pavg1", StructProperty::Float, offsetof(Particle, pavg[1])));
	properties.push_back(StructProperty("compression (gas)", StructProperty::UInteger, offsetof(Particle, gasCompression)));
	return properties;
}
