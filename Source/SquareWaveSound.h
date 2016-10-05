/*
  ==============================================================================

    SquareWaveSound.h
    Created: 10 May 2016 9:37:47am
    Author:  Alex

  ==============================================================================
*/

#ifndef SQUAREWAVESOUND_H_INCLUDED
#define SQUAREWAVESOUND_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class SquareWaveSound : public SynthesiserSound
{
public:
	SquareWaveSound() {}

	bool appliesToNote(int /*midiNoteNumber*/) override { return true; }
	bool appliesToChannel(int /*midiChannel*/) override { return true; }
};

//==============================================================================
/** A simple demo synth voice that just plays a sine wave.. */
class SquareWaveVoice : public SynthesiserVoice
{
public:
	SquareWaveVoice()
		: angleDelta(0.0),
		tailOff(0.0),
		numPartials(10)
	{
		partialMultiples.resize(numPartials, 0);
		partialAmplitudes.resize(numPartials, 0.0);
		phases.resize(numPartials, 0.0);
		phaseIncrements.resize(numPartials, 0.0);
	}

	bool canPlaySound(SynthesiserSound* sound) override
	{
		return dynamic_cast<SquareWaveSound*> (sound) != nullptr;
	}

	void startNote(int midiNoteNumber, float velocity,
		SynthesiserSound* /*sound*/,
		int /*currentPitchWheelPosition*/) override
	{
		currentAngle = 0.0;
		level = velocity * 0.15;
		tailOff = 0.0;

		double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		double cyclesPerSample = cyclesPerSecond / getSampleRate();
		double samplesPerCycle = getSampleRate() / cyclesPerSecond;
		frequency = cyclesPerSecond;
		frqRad = twoPi / getSampleRate();
		period = 1 / frequency;

		angleDelta = 1 / getSampleRate();

		phaseIncrements[0] = frqRad * frequency;
		phases[0] = 0.0;
		partialMultiples[0] = 1.0;
		partialAmplitudes[0] = 1.0;
		for (int partialIdx = 1; partialIdx < numPartials; partialIdx++)
		{
			partialMultiples[partialIdx] = (2 * partialIdx) - 1;
			partialAmplitudes[partialIdx] = 1.0 / partialMultiples[partialIdx];
		}

		for (int partialIdx = 1; partialIdx < numPartials; partialIdx++)
		{
			phaseIncrements[partialIdx] = phaseIncrements[0] * partialMultiples[partialIdx];
		}
		// Calculate scale to normalize amplitudes
		for (int n = 0; n < samplesPerCycle; n++)
		{
			double value = 0.0;
			for (int partialIdx = 0; partialIdx < numPartials; partialIdx++)
			{
				value += std::sin(phases[partialIdx]) * partialAmplitudes[partialIdx];
				if ((phases[partialIdx] += phaseIncrements[partialIdx]) >= twoPi)
				{
					phases[partialIdx] -= twoPi;
				}
			}
			scale = value > scale ? value : scale;
		}
	}

	void stopNote(float /*velocity*/, bool allowTailOff) override
	{
		if (allowTailOff)
		{
			// start a tail-off by setting this flag. The render callback will pick up on
			// this and do a fade out, calling clearCurrentNote() when it's finished.

			if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
								// stopNote method could be called more than once.
				tailOff = 1.0;
		}
		else
		{
			// we're being told to stop playing immediately, so reset everything..

			clearCurrentNote();
			angleDelta = 0.0;
		}
	}

	void pitchWheelMoved(int /*newValue*/) override
	{
		// can't be bothered implementing this for the demo!
	}

	void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override
	{
		// not interested in controllers in this case.
	}

	void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override
	{
		processBlock(outputBuffer, startSample, numSamples);
	}

	void renderNextBlock(AudioBuffer<double>& outputBuffer, int startSample, int numSamples) override
	{
		processBlock(outputBuffer, startSample, numSamples);
	}

private:

	template <typename FloatType>
	void processBlock(AudioBuffer<FloatType>& outputBuffer, int startSample, int numSamples)
	{
		if (angleDelta != 0.0)
		{
			double midPoint = period / 2.0;
			if (tailOff > 0)
			{
				while (--numSamples >= 0)
				{
					FloatType currentSample;
					/*
					if (currentAngle < midPoint)
					{
						currentSample = static_cast<FloatType> (level * tailOff);
					}
					else
					{
						currentSample = static_cast<FloatType> (-level * tailOff);
					}
					*/

					double value = 0.0;
					for (int partialIdx = 0; partialIdx < numPartials; partialIdx++)
					{
						value += std::sin(phases[partialIdx]) * partialAmplitudes[partialIdx];
						if ((phases[partialIdx] += phaseIncrements[partialIdx]) >= twoPi)
						{
							phases[partialIdx] -= twoPi;
						}
					}
					currentSample = level * tailOff * (value / scale);

					for (int i = outputBuffer.getNumChannels(); --i >= 0;)
						outputBuffer.addSample(i, startSample, currentSample);

					/*
					currentAngle += angleDelta;
					if (currentAngle >= period)
					{
						currentAngle -= period;
					}
					*/
					++startSample;

					tailOff *= 0.99;

					if (tailOff <= 0.005)
					{
						clearCurrentNote();

						angleDelta = 0.0;
						break;
					}
				}
			}
			else
			{
				while (--numSamples >= 0)
				{
					FloatType currentSample;
					/*
					if (currentAngle < midPoint)
					{
						currentSample = static_cast<FloatType> (level);
					}
					else
					{
						currentSample = static_cast<FloatType> (-level);
					}
					*/
					double value = 0.0;
					for (int partialIdx = 0; partialIdx < numPartials; partialIdx++)
					{
						value += std::sin(phases[partialIdx]) * partialAmplitudes[partialIdx];
						if ((phases[partialIdx] += phaseIncrements[partialIdx]) >= twoPi)
						{
							phases[partialIdx] -= twoPi;
						}
					}
					currentSample = level * (value / scale);

					for (int i = outputBuffer.getNumChannels(); --i >= 0;)
						outputBuffer.addSample(i, startSample, currentSample);

					/*
					currentAngle += angleDelta;
					if (currentAngle >= period)
					{
						currentAngle -= period;
					}
					*/
					++startSample;
				}
			}
		}
	}

	double currentAngle, angleDelta, level, tailOff, frequency, period;
	double frqRad;
	double twoPi = 2.0 * double_Pi;

	int numPartials;
	std::vector<int> partialMultiples;
	std::vector<double> partialAmplitudes;
	/* The current phase of each partial */
	std::vector<double> phases;
	/* The phase increments of each partial */
	std::vector<double> phaseIncrements;
	/* Scale to normalize amplitude */
	double scale;
	std::vector<double> sigma;
};


#endif  // SQUAREWAVESOUND_H_INCLUDED
