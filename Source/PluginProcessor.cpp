
#include "PluginProcessor.h"
#include "PluginEditor.h"

JUCE_Minimal_VST3AudioProcessor::JUCE_Minimal_VST3AudioProcessor()
: AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{}

bool JUCE_Minimal_VST3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void JUCE_Minimal_VST3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = (juce::uint32)samplesPerBlock;
    spec.numChannels = 2;

    osc.prepare (spec);
    gain.prepare (spec);
    osc.setFrequency (220.0f);
    gain.setGainLinear (0.2f);
}

void JUCE_Minimal_VST3AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    for (const auto metadata : midi)
    {
        const auto msg = metadata.getMessage();
        if (msg.isNoteOn())
            osc.setFrequency (juce::MidiMessage::getMidiNoteInHertz (msg.getNoteNumber()));
    }

    juce::dsp::AudioBlock<float> block (buffer);
    osc.process (juce::dsp::ProcessContextReplacing<float> (block));
    gain.setGainLinear (apvts.getRawParameterValue("gain")->load());
    gain.process (juce::dsp::ProcessContextReplacing<float> (block));
}

void JUCE_Minimal_VST3AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto state = apvts.copyState(); auto xml = state.createXml())
        copyXmlToBinary (*xml, destData);
}

void JUCE_Minimal_VST3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
        apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

juce::AudioProcessorEditor* JUCE_Minimal_VST3AudioProcessor::createEditor()
{
    return new JUCE_Minimal_VST3AudioProcessorEditor (*this);
}

juce::AudioProcessorValueTreeState::ParameterLayout JUCE_Minimal_VST3AudioProcessor::createLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back (std::make_unique<juce::AudioParameterFloat>("gain", "Gain",
                      juce::NormalisableRange<float>(0.0f, 1.0f, 0.0001f, 1.0f), 0.2f));
    return { params.begin(), params.end() };
}

extern "C" __attribute__((visibility("default"))) JUCE_API juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter();
juce::AudioProcessor* createPluginFilter() { return new JUCE_Minimal_VST3AudioProcessor(); }
