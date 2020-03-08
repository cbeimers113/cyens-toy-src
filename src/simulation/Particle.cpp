#include <cstddef>
#include "Particle.h"

std::vector<StructProperty> const& Particle::GetProperties()
{
	static std::vector<StructProperty> properties = {
		{ "type",		   StructProperty::ParticleType, offsetof(Particle, type) },
		{ "life/C#",	   StructProperty::ParticleType, offsetof(Particle, life) },
		{ "ctype/OH-pos",  StructProperty::ParticleType, offsetof(Particle, ctype) },
		{ "x-pos",		   StructProperty::Float,		 offsetof(Particle, x) },
		{ "y-pos",		   StructProperty::Float,		 offsetof(Particle, y) },
		{ "x-vel",		   StructProperty::Float,		 offsetof(Particle, vx) },
		{ "y-vel",		   StructProperty::Float,		 offsetof(Particle, vy) },
		{ "temp",   	   StructProperty::Float,		 offsetof(Particle, temp) },
		{ "isotope",	   StructProperty::UInteger,	 offsetof(Particle, isotope) },
		{ "compression",   StructProperty::UInteger,	 offsetof(Particle, gasCompression) },
		{ "flags"  ,	   StructProperty::UInteger,	 offsetof(Particle, flags) },
		{ "tmp/H#"    ,	   StructProperty::Integer,		 offsetof(Particle, tmp) },
		{ "tmp2/bond-pos", StructProperty::Integer,		 offsetof(Particle, tmp2) },
		{ "deco-colour",   StructProperty::UInteger,	 offsetof(Particle, dcolour) },
		{ "pavg0",		   StructProperty::Float,		 offsetof(Particle, pavg[0]) },
		{ "pavg1",		   StructProperty::Float,		 offsetof(Particle, pavg[1]) },
	};
	return properties;
}
