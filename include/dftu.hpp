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
	//! Spatial dimension (L).
	BASEDIM_LENGTH,
	//! Time dimension (T).
	BASEDIM_TIME,
	//! Mass dimension (M).
	BASEDIM_MASS,
	//! Electric charge (Q).
	BASEDIM_CHARGE,
	//! Absolute Temperature (Theta).
	BASEDIM_TEMPERATURE,
	//! Amount of a substance (N).
	BASEDIM_AMOUNT,
	//! Dummy last dimension, use as a limit.
	BASEDIM_MAX
};

//! Derived dimensions.
//! A arary of powers of base dimensions.
//! A base dimension is one where only one element 
//! is non-zero and is equal to one.
struct DFTU_API Dimension
{
	int power[BASEDIM_MAX];
};

//! Determine whether a given dimension is a base dimension.
//! @retval true if dim is a base dimension.
//! @retval false otherwise.
extern bool DFTU_API base( const Dimension & dim );

//! Pre-defined derived dimensions for velocity.
extern const DFTU_API Dimension DIM_VELOCITY;
//! Pre-defined derived dimensions for density.
extern const DFTU_API Dimension DIM_DENSITY;

//! A base unit, defined for one of the base quantities.
struct BaseUnit
{
	//! Name of the unit e.g. 'metre'
	const char * name;
	//! Symbol for the unit e.g. 'm'
	const char * symbol;
	//! The dimension of the unit.
	BaseDimension dimension;
};

extern const DFTU_API BaseUnit UNIT_METRE;
extern const DFTU_API BaseUnit UNIT_FOOT;
extern const DFTU_API BaseUnit UNIT_SECOND;
extern const DFTU_API BaseUnit UNIT_KILOGRAM;
extern const DFTU_API BaseUnit UNIT_RADIAN;

//! The base 10 power of a unit.
//! This defines some useful presets without restricting the value.
enum Scale
{
	SCALE_MICRO=-6,
	SCALE_MILLE=-3,
	SCALE_CENTI=-2
	SCALE_DECI=-1,
	SCALE_KILO=3,
	SCALE_MEGA=6,
	SCALE_TERA=9
};

//! A combination of base units.
struct DFTU_API DerivedUnit
{
	//! The name of the unit e.g. millemetre.
	const char * name;
	//! The ASCII symbol of the unit e.g. 'mm'.
	const char * symbol;
	//! The base unit we are modifying.
	const BaseUnitPower * combination;
	//! The base 10 power of the unit.
	//! This turns e.g. m into mm.
	unsigned char scale;
};

struct DFTU_API Quantity
{
	//! The name of the quantity.
	const char * name;
	const DerivedUnit * unit;
};

}

#endif // !__DFTU_H__
