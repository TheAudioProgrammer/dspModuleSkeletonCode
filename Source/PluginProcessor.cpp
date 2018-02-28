/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
DspModuleSkeletonAudioProcessor::DspModuleSkeletonAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

DspModuleSkeletonAudioProcessor::~DspModuleSkeletonAudioProcessor()
{
}

//==============================================================================
const String DspModuleSkeletonAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DspModuleSkeletonAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DspModuleSkeletonAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DspModuleSkeletonAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DspModuleSkeletonAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DspModuleSkeletonAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DspModuleSkeletonAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DspModuleSkeletonAudioProcessor::setCurrentProgram (int index)
{
}

const String DspModuleSkeletonAudioProcessor::getProgramName (int index)
{
    return {};
}

void DspModuleSkeletonAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DspModuleSkeletonAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec;
    
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
}

void DspModuleSkeletonAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DspModuleSkeletonAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DspModuleSkeletonAudioProcessor::process (dsp::ProcessContextReplacing<float> context)
{
    //do your dsp processing and output here
}

void DspModuleSkeletonAudioProcessor::updateParameters()
{
    //be sure to update params for your dsp here
}


void DspModuleSkeletonAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //data structure that points to the buffer
    dsp::AudioBlock<float> block (buffer);
    
    //update any parameters for your processes
    updateParameters();
    
    //if you have more than one dsp process, put them in the process method
    //JUCE dsp processes each have their own process method
    process (dsp::ProcessContextReplacing<float> (block));
}

//==============================================================================
bool DspModuleSkeletonAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DspModuleSkeletonAudioProcessor::createEditor()
{
    return new DspModuleSkeletonAudioProcessorEditor (*this);
}

//==============================================================================
void DspModuleSkeletonAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DspModuleSkeletonAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DspModuleSkeletonAudioProcessor();
}
