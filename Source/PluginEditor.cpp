
#include "PluginEditor.h"

JUCE_Minimal_VST3AudioProcessorEditor::JUCE_Minimal_VST3AudioProcessorEditor (JUCE_Minimal_VST3AudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    setResizable (false, false);
    setSize (420, 220);

    gainSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 60, 18);
    addAndMakeVisible (gainSlider);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.apvts, "gain", gainSlider);
}

void JUCE_Minimal_VST3AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (juce::Font (18.0f, juce::Font::bold));
    g.drawText ("JUCE Minimal VST3", getLocalBounds().removeFromTop(30), juce::Justification::centred);
}

void JUCE_Minimal_VST3AudioProcessorEditor::resized()
{
    gainSlider.setBounds (getLocalBounds().withSizeKeepingCentre (160, 160));
}
