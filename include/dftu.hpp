#ifndef __DFTU_H__
#define __DFTU_H__

#pragma once

#include "config/config.h"

//! Namespace to isolate definitions.
namespace dftu
{
//! Base/fundamental dimensions
enum BaseDimension
{
	//! Dimensionless, a pure quantity.
	BASEDIM_NONE,
	//! Pseudo-dimension to use as a denominator in a derived dimension.
	BASEDIM_ONE,
	//! Length dimension (m).
	BASEDIM_LENGTH,
	//! Time dimension (s).
	BASEDIM_TIME,
	//! Mass dimension (kg).
	BASEDIM_MASS,
	//! Dummy last dimension, use as a limit.
	BASEDIM_MAX
};

//! Derived dimensions.
//! A polynomial of base dimensions.
struct DFTU_API DerivedDimension
{
	int power[BASEDIM_MAX]
};

//! Pre-defined derived dimensions for velocity.
extern const DFTU_API DerivedDimension DIM_VELOCITY;
//! Pre-defined derived dimensions for density.
extern const DFTU_API DerivedDimension DIM_DENSITY;

struct BaseUnit
{
	//! Name of the unit e.g. 'metre'
	const char * name;
	//! Symbol for the unit e.g. 'm'
	const char * symbol;
	//! The dimension of the unit.
	const BaseDimension dimension;
};

extern const DFTU_API BaseUnit UNIT_METRE;
extern const DFTU_API BaseUnit UNIT_FOOT;
extern const DFTU_API BaseUnit UNIT_SECOND;
extern const DFTU_API BaseUnit UNIT_KILOGRAM;

//! The base 10 power of a unit.
enum Scale
{
	SCALE_MICRO=-6,
	SCALE_MILLE=-3,
	SCALE_CENTI=-2
	SCALE_DECI=-1,
	SCALE_KILO=3,
	SCALE_MEGA=6
};

struct DerivedUnit
{
	//! The name of the unit e.g. millemetre.
	const char * name;
	//! The base unit we are modifying.
	const BaseUnit baseUnit;
	//! This turns e.g. m into mm.
	Scale scale;
};

}

#endif // !__DFTU_H__
