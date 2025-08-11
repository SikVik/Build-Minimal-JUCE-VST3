
#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class JUCE_Minimal_VST3AudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    JUCE_Minimal_VST3AudioProcessorEditor (JUCE_Minimal_VST3AudioProcessor&);
    ~JUCE_Minimal_VST3AudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_Minimal_VST3AudioProcessor& processor;
    juce::Slider gainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
};
