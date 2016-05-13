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
		tailOff(0.0)
	{
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
		frequency = cyclesPerSecond;
		period = 1 / frequency;

		angleDelta = 1 / getSampleRate();
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
					if (currentAngle < midPoint)
					{
						currentSample = static_cast<FloatType> (level * tailOff);
					}
					else
					{
						currentSample = static_cast<FloatType> (-level * tailOff);
					}

					for (int i = outputBuffer.getNumChannels(); --i >= 0;)
						outputBuffer.addSample(i, startSample, currentSample);

					currentAngle += angleDelta;
					if (currentAngle >= period)
					{
						currentAngle -= period;
					}
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
					if (currentAngle < midPoint)
					{
						currentSample = static_cast<FloatType> (level);
					}
					else
					{
						currentSample = static_cast<FloatType> (-level);
					}

					for (int i = outputBuffer.getNumChannels(); --i >= 0;)
						outputBuffer.addSample(i, startSample, currentSample);

					currentAngle += angleDelta;
					if (currentAngle >= period)
					{
						currentAngle -= period;
					}
					++startSample;
				}
			}
		}
	}

	double currentAngle, angleDelta, level, tailOff, frequency, period;
};


#endif  // SQUAREWAVESOUND_H_INCLUDED
