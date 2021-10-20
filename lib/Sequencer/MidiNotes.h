#ifndef SEQUENCER_MIDI_NOTES_H
#define SEQUENCER_MIDI_NOTES_H

#include <Pitches.h>

#define BASE_NOTE 0
#define NOTE_UNDEFINED -1

#define NOTE_MIDI_C0 12
#define NOTE_MIDI_CS0 13
#define NOTE_MIDI_D0 14
#define NOTE_MIDI_DS0 15
#define NOTE_MIDI_E0 16
#define NOTE_MIDI_F0 17
#define NOTE_MIDI_FS0 18
#define NOTE_MIDI_G0 19
#define NOTE_MIDI_GS0 20
#define NOTE_MIDI_A0 21
#define NOTE_MIDI_AS0 22
#define NOTE_MIDI_B0 23
#define NOTE_MIDI_C1 24
#define NOTE_MIDI_CS1 25
#define NOTE_MIDI_D1 26
#define NOTE_MIDI_DS1 27
#define NOTE_MIDI_E1 28
#define NOTE_MIDI_F1 29
#define NOTE_MIDI_FS1 30
#define NOTE_MIDI_G1 31
#define NOTE_MIDI_GS1 32
#define NOTE_MIDI_A1 33
#define NOTE_MIDI_AS1 34
#define NOTE_MIDI_B1 35
#define NOTE_MIDI_C2 36
#define NOTE_MIDI_CS2 37
#define NOTE_MIDI_D2 38
#define NOTE_MIDI_DS2 39
#define NOTE_MIDI_E2 40
#define NOTE_MIDI_F2 41
#define NOTE_MIDI_FS2 42
#define NOTE_MIDI_G2 43
#define NOTE_MIDI_GS2 44
#define NOTE_MIDI_A2 45
#define NOTE_MIDI_AS2 46
#define NOTE_MIDI_B2 47
#define NOTE_MIDI_C3 48
#define NOTE_MIDI_CS3 49
#define NOTE_MIDI_D3 50
#define NOTE_MIDI_DS3 51
#define NOTE_MIDI_E3 52
#define NOTE_MIDI_F3 53
#define NOTE_MIDI_FS3 54
#define NOTE_MIDI_G3 55
#define NOTE_MIDI_GS3 56
#define NOTE_MIDI_A3 57
#define NOTE_MIDI_AS3 58
#define NOTE_MIDI_B3 59
#define NOTE_MIDI_C4 60
#define NOTE_MIDI_CS4 61
#define NOTE_MIDI_D4 62
#define NOTE_MIDI_DS4 63
#define NOTE_MIDI_E4 64
#define NOTE_MIDI_F4 65
#define NOTE_MIDI_FS4 66
#define NOTE_MIDI_G4 67
#define NOTE_MIDI_GS4 68
#define NOTE_MIDI_A4 69
#define NOTE_MIDI_AS4 70
#define NOTE_MIDI_B4 71
#define NOTE_MIDI_C5 72
#define NOTE_MIDI_CS5 73
#define NOTE_MIDI_D5 74
#define NOTE_MIDI_DS5 75
#define NOTE_MIDI_E5 76
#define NOTE_MIDI_F5 77
#define NOTE_MIDI_FS5 78
#define NOTE_MIDI_G5 79
#define NOTE_MIDI_GS5 80
#define NOTE_MIDI_A5 81
#define NOTE_MIDI_AS5 82
#define NOTE_MIDI_B5 83
#define NOTE_MIDI_C6 84
#define NOTE_MIDI_CS6 85
#define NOTE_MIDI_D6 86
#define NOTE_MIDI_DS6 87
#define NOTE_MIDI_E6 88
#define NOTE_MIDI_F6 89
#define NOTE_MIDI_FS6 90
#define NOTE_MIDI_G6 91
#define NOTE_MIDI_GS6 92
#define NOTE_MIDI_A6 93
#define NOTE_MIDI_AS6 94
#define NOTE_MIDI_B6 95
#define NOTE_MIDI_C7 96
#define NOTE_MIDI_CS7 97
#define NOTE_MIDI_D7 98
#define NOTE_MIDI_DS7 99
#define NOTE_MIDI_E7 100
#define NOTE_MIDI_F7 101
#define NOTE_MIDI_FS7 102
#define NOTE_MIDI_G7 103
#define NOTE_MIDI_GS7 104
#define NOTE_MIDI_A7 105
#define NOTE_MIDI_AS7 106
#define NOTE_MIDI_B7 107
#define NOTE_MIDI_C8 108
#define NOTE_MIDI_CS8 109
#define NOTE_MIDI_D8 110
#define NOTE_MIDI_DS8 111
#define NOTE_MIDI_E8 112
#define NOTE_MIDI_F8 113
#define NOTE_MIDI_FS8 114
#define NOTE_MIDI_G8 115
#define NOTE_MIDI_GS8 116
#define NOTE_MIDI_A8 117
#define NOTE_MIDI_AS8 118
#define NOTE_MIDI_B8 119

#define C_MAJOR_SCALE_MIDI                                                                           \
  {                                                                                                  \
    NOTE_MIDI_C5, NOTE_MIDI_D5, NOTE_MIDI_E5, NOTE_MIDI_F5, NOTE_MIDI_G5, NOTE_MIDI_A5, NOTE_MIDI_B5 \
  }

#define F_MAJOR_SCALE_MIDI                                                                            \
  {                                                                                                   \
    NOTE_MIDI_F5, NOTE_MIDI_G5, NOTE_MIDI_A5, NOTE_MIDI_AS5, NOTE_MIDI_C6, NOTE_MIDI_D6, NOTE_MIDI_E6 \
  }

// D, E, F, G, A, B♭, and C

#define D_MINOR_SCALE_MIDI                                                                            \
  {                                                                                                   \
    NOTE_MIDI_D4, NOTE_MIDI_E4, NOTE_MIDI_F4, NOTE_MIDI_G4, NOTE_MIDI_A4, NOTE_MIDI_AS4, NOTE_MIDI_C5 \
  }
int frequencyToMidiNote(int frequency);
unsigned int midiNoteToVoltage(int midiNote);

#endif
