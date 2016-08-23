/*
==============================================================================

This file is part of the JUCE library.
Copyright (c) 2015 - ROLI Ltd.

Permission is granted to use this software under the terms of either:
a) the GPL v2 (or any later version)
b) the Affero GPL v3

Details of these licenses can be found at: www.gnu.org/licenses

JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

------------------------------------------------------------------------------

To release a closed-source product which uses JUCE, commercial licenses are
available: visit www.juce.com for more information.

==============================================================================
*/

#include "IIRFilterDouble.h"

#if JUCE_INTEL
#define JUCE_SNAP_TO_ZERO(n)    if (! (n < -1.0e-8f || n > 1.0e-8f)) n = 0;
#else
#define JUCE_SNAP_TO_ZERO(n)
#endif

//==============================================================================
IIRCoefficientsDouble::IIRCoefficientsDouble() noexcept
{
	zeromem(coefficients, sizeof(coefficients));
}

IIRCoefficientsDouble::~IIRCoefficientsDouble() noexcept {}

IIRCoefficientsDouble::IIRCoefficientsDouble(const IIRCoefficientsDouble& other) noexcept
{
	memcpy(coefficients, other.coefficients, sizeof(coefficients));
}

IIRCoefficientsDouble& IIRCoefficientsDouble::operator= (const IIRCoefficientsDouble& other) noexcept
{
	memcpy(coefficients, other.coefficients, sizeof(coefficients));
	return *this;
}

IIRCoefficientsDouble::IIRCoefficientsDouble(double c1, double c2, double c3,
	double c4, double c5, double c6) noexcept
{
	const double a = 1.0 / c4;

	coefficients[0] = (float)(c1 * a);
	coefficients[1] = (float)(c2 * a);
	coefficients[2] = (float)(c3 * a);
	coefficients[3] = (float)(c5 * a);
	coefficients[4] = (float)(c6 * a);
}

IIRCoefficientsDouble IIRCoefficientsDouble::makeLowPass(const double sampleRate,
	const double frequency) noexcept
{
	jassert(sampleRate > 0);

	const double n = 1.0 / std::tan(double_Pi * frequency / sampleRate);
	const double nSquared = n * n;
	const double c1 = 1.0 / (1.0 + std::sqrt(2.0) * n + nSquared);

	return IIRCoefficientsDouble(c1,
		c1 * 2.0,
		c1,
		1.0,
		c1 * 2.0 * (1.0 - nSquared),
		c1 * (1.0 - std::sqrt(2.0) * n + nSquared));
}

IIRCoefficientsDouble IIRCoefficientsDouble::makeHighPass(const double sampleRate,
	const double frequency) noexcept
{
	const double n = std::tan(double_Pi * frequency / sampleRate);
	const double nSquared = n * n;
	const double c1 = 1.0 / (1.0 + std::sqrt(2.0) * n + nSquared);

	return IIRCoefficientsDouble(c1,
		c1 * -2.0,
		c1,
		1.0,
		c1 * 2.0 * (nSquared - 1.0),
		c1 * (1.0 - std::sqrt(2.0) * n + nSquared));
}

IIRCoefficientsDouble IIRCoefficientsDouble::makeLowShelf(const double sampleRate,
	const double cutOffFrequency,
	const double Q,
	const float gainFactor) noexcept
{
	jassert(sampleRate > 0);
	jassert(Q > 0);

	const double A = jmax(0.0f, std::sqrt(gainFactor));
	const double aminus1 = A - 1.0;
	const double aplus1 = A + 1.0;
	const double omega = (double_Pi * 2.0 * jmax(cutOffFrequency, 2.0)) / sampleRate;
	const double coso = std::cos(omega);
	const double beta = std::sin(omega) * std::sqrt(A) / Q;
	const double aminus1TimesCoso = aminus1 * coso;

	return IIRCoefficientsDouble(A * (aplus1 - aminus1TimesCoso + beta),
		A * 2.0 * (aminus1 - aplus1 * coso),
		A * (aplus1 - aminus1TimesCoso - beta),
		aplus1 + aminus1TimesCoso + beta,
		-2.0 * (aminus1 + aplus1 * coso),
		aplus1 + aminus1TimesCoso - beta);
}

IIRCoefficientsDouble IIRCoefficientsDouble::makeHighShelf(const double sampleRate,
	const double cutOffFrequency,
	const double Q,
	const float gainFactor) noexcept
{
	jassert(sampleRate > 0);
	jassert(Q > 0);

	const double A = jmax(0.0f, std::sqrt(gainFactor));
	const double aminus1 = A - 1.0;
	const double aplus1 = A + 1.0;
	const double omega = (double_Pi * 2.0 * jmax(cutOffFrequency, 2.0)) / sampleRate;
	const double coso = std::cos(omega);
	const double beta = std::sin(omega) * std::sqrt(A) / Q;
	const double aminus1TimesCoso = aminus1 * coso;

	return IIRCoefficientsDouble(A * (aplus1 + aminus1TimesCoso + beta),
		A * -2.0 * (aminus1 + aplus1 * coso),
		A * (aplus1 + aminus1TimesCoso - beta),
		aplus1 - aminus1TimesCoso + beta,
		2.0 * (aminus1 - aplus1 * coso),
		aplus1 - aminus1TimesCoso - beta);
}

IIRCoefficientsDouble IIRCoefficientsDouble::makePeakFilter(const double sampleRate,
	const double centreFrequency,
	const double Q,
	const float gainFactor) noexcept
{
	jassert(sampleRate > 0);
	jassert(Q > 0);

	const double A = jmax(0.0f, std::sqrt(gainFactor));
	const double omega = (double_Pi * 2.0 * jmax(centreFrequency, 2.0)) / sampleRate;
	const double alpha = 0.5 * std::sin(omega) / Q;
	const double c2 = -2.0 * std::cos(omega);
	const double alphaTimesA = alpha * A;
	const double alphaOverA = alpha / A;

	return IIRCoefficientsDouble(1.0 + alphaTimesA,
		c2,
		1.0 - alphaTimesA,
		1.0 + alphaOverA,
		c2,
		1.0 - alphaOverA);
}

//==============================================================================
IIRFilterDouble::IIRFilterDouble() noexcept
	: v1(0), v2(0), active(false)
{
}

IIRFilterDouble::IIRFilterDouble(const IIRFilterDouble& other) noexcept
	: v1(0), v2(0), active(other.active)
{
	const SpinLock::ScopedLockType sl(other.processLock);
	coefficients = other.coefficients;
}

IIRFilterDouble::~IIRFilterDouble() noexcept
{
}

//==============================================================================
void IIRFilterDouble::makeInactive() noexcept
{
	const SpinLock::ScopedLockType sl(processLock);
	active = false;
}

void IIRFilterDouble::setCoefficients(const IIRCoefficientsDouble& newCoefficients) noexcept
{
	const SpinLock::ScopedLockType sl(processLock);

	coefficients = newCoefficients;
	active = true;
}

//==============================================================================
void IIRFilterDouble::reset() noexcept
{
	const SpinLock::ScopedLockType sl(processLock);
	v1 = v2 = 0;
}

float IIRFilterDouble::processSingleSampleRaw(const float in) noexcept
{
	float out = coefficients.coefficients[0] * in + v1;

	JUCE_SNAP_TO_ZERO(out);

	v1 = coefficients.coefficients[1] * in - coefficients.coefficients[3] * out + v2;
	v2 = coefficients.coefficients[2] * in - coefficients.coefficients[4] * out;

	return out;
}

void IIRFilterDouble::processSamples(float* const samples, const int numSamples) noexcept
{
	const SpinLock::ScopedLockType sl(processLock);

	if (active)
	{
		const float c0 = coefficients.coefficients[0];
		const float c1 = coefficients.coefficients[1];
		const float c2 = coefficients.coefficients[2];
		const float c3 = coefficients.coefficients[3];
		const float c4 = coefficients.coefficients[4];
		float lv1 = v1, lv2 = v2;

		for (int i = 0; i < numSamples; ++i)
		{
			const float in = samples[i];
			const float out = c0 * in + lv1;
			samples[i] = out;

			lv1 = c1 * in - c3 * out + lv2;
			lv2 = c2 * in - c4 * out;
		}

		JUCE_SNAP_TO_ZERO(lv1);  v1 = lv1;
		JUCE_SNAP_TO_ZERO(lv2);  v2 = lv2;
	}
}

void IIRFilterDouble::processSamples(double* const samples, const int numSamples) noexcept
{
	const SpinLock::ScopedLockType sl(processLock);

	if (active)
	{
		const double c0 = coefficients.coefficients[0];
		const double c1 = coefficients.coefficients[1];
		const double c2 = coefficients.coefficients[2];
		const double c3 = coefficients.coefficients[3];
		const double c4 = coefficients.coefficients[4];
		float lv1 = v1, lv2 = v2;

		for (int i = 0; i < numSamples; ++i)
		{
			const double in = samples[i];
			const double out = c0 * in + lv1;
			samples[i] = out;

			lv1 = c1 * in - c3 * out + lv2;
			lv2 = c2 * in - c4 * out;
		}

		JUCE_SNAP_TO_ZERO(lv1);  v1 = lv1;
		JUCE_SNAP_TO_ZERO(lv2);  v2 = lv2;
	}
}

#undef JUCE_SNAP_TO_ZERO
