
cmake_minimum_required(VERSION 3.21)
project(JUCE_Minimal_VST3 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  JUCE
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG        7.0.12
)
FetchContent_MakeAvailable(JUCE)

juce_add_plugin(JUCE_Minimal_VST3
    COMPANY_NAME "You"
    PLUGIN_NAME "JUCE_Minimal_VST3"
    BUNDLE_ID com.you.minimalvst3
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    FORMATS VST3
    PRODUCT_NAME "JUCE_Minimal_VST3"
)

juce_generate_juce_header(JUCE_Minimal_VST3)

target_sources(JUCE_Minimal_VST3 PRIVATE
    ${PROJECT_SOURCE_DIR}/Source/PluginProcessor.cpp
    ${PROJECT_SOURCE_DIR}/Source/PluginEditor.cpp
)

target_compile_definitions(JUCE_Minimal_VST3 PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
)

target_link_libraries(JUCE_Minimal_VST3 PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
)

target_include_directories(JUCE_Minimal_VST3 PRIVATE
    ${PROJECT_SOURCE_DIR}/Source
)
