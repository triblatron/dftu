#include "dftu.hpp"

namespace dftu
{
	bool dimensionless(const Dimension & dim)
	{
		// True if all powers of the base dimensions are 0.
		bool result = true;

		for (int i = BASEDIM_ONE; result && i < BASEDIM_MAX; ++i)
		{
			if (dim.power[i] != 0)
			{
				result = false;
			}
		}
		return result;
	}

	bool base(const Dimension & dim)
	{
		// True if there is only one dimension with non-zero power and its power is one
		int sumOfPowers = 0;

		for (int i = BASEDIM_ONE; i < BASEDIM_MAX; ++i)
		{
			if (dim.power[i] != 1 && dim.power[i] != 0 )
			{
				return false;
			}
			sumOfPowers+=dim.power[i];
		}
		return sumOfPowers==1;
	}

	bool base(const Quantity & q)
	{
		int sumOfPowers = 0;

		for (int i = BASEUNIT_ONE; i < BASEUNIT_MAX; ++i)
		{
			if (q.unitSI->power[i] != 1 && q.unitSI->power[i] != 0)
			{
				return false;
			}
			sumOfPowers += q.unitSI->power[i];
		}

		return sumOfPowers==1;
	}

	bool dimensionless(const Unit & unit)
	{
		bool result = true;

		for (int i = BASEUNIT_ONE; result && i < BASEUNIT_MAX; ++i)
		{
			if (unit.power[i] != 0)
			{
				result = false;
			}
		}

		return result;
	}

	bool dimensionless(const Quantity & q)
	{
		return dimensionless(*q.unitSI);
	}
}
