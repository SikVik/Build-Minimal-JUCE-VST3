
#pragma once
#include <JuceHeader.h>

class JUCE_Minimal_VST3AudioProcessor : public juce::AudioProcessor
{
public:
    JUCE_Minimal_VST3AudioProcessor();
    ~JUCE_Minimal_VST3AudioProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return "JUCE_Minimal_VST3"; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram (int) override {}
    const juce::String getProgramName (int) override { return {}; }
    void changeProgramName (int, const juce::String&) override {}
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
    juce::AudioProcessorValueTreeState apvts { *this, nullptr, "PARAMS", createLayout() };

private:
    juce::dsp::Oscillator<float> osc { [] (float x) { return std::sin (x); } };
    juce::dsp::Gain<float> gain;
    juce::dsp::ProcessSpec spec{};
};
