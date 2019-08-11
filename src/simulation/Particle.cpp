#include <cstddef>
#include "Particle.h"

std::vector<StructProperty> const &Particle::GetProperties()
{
	static std::vector<StructProperty> properties = {
		{ "type"   , StructProperty::ParticleType, offsetof(Particle, type   ) },
		{ "life"   , StructProperty::ParticleType, offsetof(Particle, life   ) },
		{ "ctype"  , StructProperty::ParticleType, offsetof(Particle, ctype  ) },
		{ "x-pos"  , StructProperty::Float       , offsetof(Particle, x      ) },
		{ "y-pos"  , StructProperty::Float       , offsetof(Particle, y      ) },
		{ "x-vel"  , StructProperty::Float       , offsetof(Particle, vx     ) },
		{ "y-vel"  , StructProperty::Float       , offsetof(Particle, vy     ) },
		{ "temp"   , StructProperty::Float       , offsetof(Particle, temp   ) },
		{ "compr"  , StructProperty::UInteger    , offsetof(Particle, gasCompression)},
		{ "tmp"    , StructProperty::Integer     , offsetof(Particle, tmp    ) },
		{ "tmp2"   , StructProperty::Integer     , offsetof(Particle, tmp2   ) },
		{ "dcolour", StructProperty::UInteger    , offsetof(Particle, dcolour) },
		{ "pavg0"  , StructProperty::Float       , offsetof(Particle, pavg[0]) },
		{ "pavg1"  , StructProperty::Float       , offsetof(Particle, pavg[1]) },
	};
	return properties;
}
