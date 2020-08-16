#ifndef __DFTU_H__
#define __DFTU_H__

#pragma once

#include "Export.hpp"

//! Namespace to isolate definitions.
namespace dftu
{
//! Base/fundamental dimensions
enum BaseDimension
{
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
    //! The symbol for this dimension.
    const char * symbol;
    //! The product of powers of each base dimension.
    int power[BASEDIM_MAX];
};

extern bool DFTU_API dimensionless(const Dimension & dim);

//! Determine whether a given dimension is a base dimension.
//! @retval true if dim is a base dimension.
//! @retval false otherwise.
extern bool DFTU_API base( const Dimension & dim );

extern const DFTU_API Dimension DIM_SPACE;
extern const DFTU_API Dimension DIM_TIME;
extern const DFTU_API Dimension DIM_MASS;
extern const DFTU_API Dimension DIM_CHARGE;
extern const DFTU_API Dimension DIM_TEMPERATURE;
extern const DFTU_API Dimension DIM_AMOUNT;

//! Pre-defined derived dimension for velocity.
extern const DFTU_API Dimension DIM_VELOCITY;
//! Pre-defined derived dimension for density.
extern const DFTU_API Dimension DIM_DENSITY;

//! Enumeration of base units.
//! These index an array of structures.
enum BaseUnitType
{
    //! Dimensionless.
    BASEUNIT_ONE,
    //! Metre (L).
    BASEUNIT_METRE,
    //! Second (T).
    BASEUNIT_SECOND,
    //! Kilogram (M).
    BASEUNIT_KILOGRAM,
    //! Coulomb (Q).
    BASEUNIT_COULOMB,
    //! Kelvin (theta).
    BASEUNIT_KELVIN,
    //! Amount of matter (N).
    BASEUNIT_MOLE,
    //! Limit.
    BASEUNIT_MAX
};
/*
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
*/

//! The base 10 power of a unit.
//! This defines some useful presets without restricting the value.
enum Scale
{
    SCALE_PICO=-12,
    SCALE_NANO=-9,
    SCALE_MICRO=-6,
    SCALE_MILLI=-3,
    SCALE_CENTI=-2,
    SCALE_DECI=-1,
    SCALE_ONE=1,
    SCALE_KILO=3,
    SCALE_MEGA=6,
    SCALE_GIGA=9,
    SCALE_TERA=12
};

//! A combination of base units.
struct DFTU_API Unit
{
    //! The name of the unit e.g. millemetre.
    const char * name;
    //! The ASCII symbol of the unit e.g. 'mm'.
    const char * symbol;
    //! The product of powers of base units.
    //! This corresponds to powers of base dimensions.
    int power[BASEUNIT_MAX];
    //! A conversion factor to SI units.
    //! 1.0 if this is an SI unit.
    double factorSI;
    //! The base 10 power of the unit.
    //! This turns e.g. m into mm.
    Scale scale;
};

extern const DFTU_API Unit UNIT_METRE;
extern const DFTU_API Unit UNIT_SECOND;
extern const DFTU_API Unit UNIT_KILOGRAM;
extern const DFTU_API Unit UNIT_COULOMB;
extern const DFTU_API Unit UNIT_KELVIN;
extern const DFTU_API Unit UNIT_MOLE;

//! A physical quantity.
struct DFTU_API Quantity
{
    //! The name of the quantity.
    const char * name;
    //! The symbol as a byte array terminated by a null.
    const char * symbol;
    //! The SI unit of this quantity.
    const Unit * unitSI;
};

//! Length (L, m)
extern const DFTU_API Quantity QUANTITY_LENGTH;
//! Width (L, m)
extern const DFTU_API Quantity QUANTITY_WIDTH;
//! Height (L, m)
extern const DFTU_API Quantity QUANTITY_HEIGHT;
//! Mass (M, kg)
extern const DFTU_API Quantity QUANTITY_MASS;
//! Time (T, s)
extern const DFTU_API Quantity QUANTITY_TIME;
//! Velocity (LT^-1, ms^-1)
extern const DFTU_API Quantity QUANTITY_VELOCITY;
//! Acceleration (LT^-2, ms^-2)
extern const DFTU_API Quantity QUANTITY_ACCELERATION;
//! Jerk, rate of acceleration (LT^-3, ms^-3)
extern const DFTU_API Quantity QUANTITY_JERK;
//! Frequency (T^-1, Hz)
extern const DFTU_API Quantity QUANTITY_FREQUENCY;
//! Spatial frequency (L^-1, m^-1)
extern const DFTU_API Quantity QUANTITY_SPATIAL_FREQUENCY;

//! Determine whether a given quantity is a base quantity.
extern bool DFTU_API base( const Quantity & q );

//! Determine whether unit is dimensionless.
//! @retval true if all the powers of the base dimensions are zero.
extern bool DFTU_API dimensionless( const Unit & unit );

//! Determine whether a given quantity is dimensionless.
//! @retval true if its SI unit is dimensionless.
extern bool DFTU_API dimensionless( const Quantity & q );

//! A reading of a physical quantity.
struct DFTU_API Reading
{
    double value;
    const Unit * unit;
};

//! The result of a conversion.
enum DFTU_API ConversionResult
{
    //! The conversion was successful.
    CONVERT_SUCCESS,
    //! The target unit is equal to the original unit.
    CONVERT_NOCHANGE,
    //! The two units were incommensurable so no conversion is possible.
    //! This means that the products of powers of dimensions were not the same.
    CONVERT_INCOMMENSURABLE
};

//! Determine whether two units are commensurate.
//! This means that they can be used in expressions involving
//! addition and subtraction.
//! It is not a necessary condition for expressions involving multiplication
//! and division of quantities.
//! @param[in] unit1 The first unit to test.
//! @param[in] unit2 The second unit to test.
//! @note Order of units is not significant.
extern bool DFTU_API commensurable( const Unit & unit1, const Unit & unit2 );

//! Convert a reading in one unit to another.
//! This is only possible if the units
//! @param[in] inputReading The original reading to be converted.
//! @param[in] targetUnit The target unit - must be commensurable with the original unit of inputReading.
//! @param[out] outputReading The target converted reading.
//! @retval CONVERT_SUCCESS if a conversion was made.
//! @retval CONVERT_NOCHANGE if the source and target units are exactly the same, conpared by pointer.
//! @retval CONVERT_INCOMMENSURABLE if the source and target units incommensurable and and the conversion is impossible.
//! @note The output is unmodified on failure.
extern ConversionResult DFTU_API convert( const Reading & inputReading, const Unit & targetUnit, Reading * outputReading );

//! The result of a call to parse().
enum DFTU_API ParseResult
{
    //! Parse successful.
    PARSE_SUCCESS,
    //! The value could not be determined.
    PARSE_BAD_VALUE,
    //! The unit could not be determined or was not in the input system.
    PARSE_BAD_UNIT
};

//! A system of units available for parsing.
struct UnitSystem
{
    int numUnits;
    const Unit units[];
};

extern const DFTU_API UnitSystem SI;

//! Parse a C staring into a Reading object.
//! @retval PARSE_SUCCESS if successful.
//! @retval PARSE_BAD_VALUE if the value could not be determined.
//! @retval PARSE_BAD_UNIT if the unit could not be determined or is not in system.
extern ParseResult DFTU_API parse( const char * value, const UnitSystem * system, Reading * outputReading );

}

#endif // !__DFTU_H__
