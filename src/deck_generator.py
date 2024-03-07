import jsonlines
import os, shutil
from datetime import datetime

def MIDIToPitch(midi_note: int) -> str:
    # get the letter 
    letters = ["A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"]
    letter_index = (midi_note - 21) % 12
    letter = letters[letter_index]
    
    # get the octave
    octaves = [0, 1, 2, 3, 4, 5, 6, 7, 8]
    octave_index = int((midi_note - 12) / 12)
    octave = octaves[octave_index]
    
    
    return str(letter) + str(octave)

def SemitonesToInterval(semitones: int) -> str:
    intervals = ["Unison", "Minor 2nd", "Major 2nd", "Minor 3rd", "Major 3rd", "Perfect 4th", "Dim 5th", "Perfect 5th", "Minor 6th", "Major 6th", "Minor 7th", "Major 7th", "Octave", "Minor 9th", "Major 9th", "Minor 10th", "Major 10th", "Perfect 11th", "Dim 12th", "Perfect 12th", "Minor 13th", "Major 13th", "Minor 14th", "Major 14th", "Two Octaves"]
    return intervals[semitones]

if __name__=="__main__":
    # configure the interval identification deck space
    group = 1
    instruments = ["piano"] #, "guitar", "synth"]
    # lower_bound = 21    # A0
    # upper_bound = 108   # C8
    lower_bound = 48    # A0
    upper_bound = 49   # C8
    midi_notes = range(lower_bound, upper_bound+1, 1)
    directions = [1, -1, 0]
    intervals = range(0, 25)
    current_time = datetime.now()
    print(current_time)
    
    
    # write the interval identification deck
    interval_filename = "../resources/deck_intervals.jsonl"
    card_id = 1000001
    with jsonlines.open(interval_filename, mode='w') as writer:
        # write the first line with deck params
        first_line = {"factor": 0.2345679012345679, "decay": -0.5, "params": [0.4, 0.6, 2.4, 5.8, 4.93, 0.94, 0.86, 0.01, 1.49, 0.14, 0.94, 2.18, 0.05, 0.34, 1.26, 0.29, 2.61]}
        writer.write(first_line)
        
        # write all of the instrument lines
        for instrument in instruments:
            for midi_note in midi_notes:
                for direction in directions:
                    for interval in intervals:
                        if direction == -1: # descending
                            if (midi_note + (interval * direction)) < lower_bound or interval==0:
                                continue
                        elif(direction == 1):   # ascending
                            if (midi_note + (interval * direction)) > upper_bound or interval == 0:
                                continue
                        else:   # harmonic
                            if (midi_note + (interval)) > upper_bound or interval == 0:
                                continue
                        card_dict = {"cardID": card_id, "due": str(current_time), "initialized": 0, "difficulty": -1, "stability": -1, "instrument": instrument, "intervalSemitones": interval, "intervalName": SemitonesToInterval(interval), "startingMIDINote": midi_note, "startingNoteName": MIDIToPitch(midi_note), "direction": direction}
                        writer.write(card_dict)
                        card_id += 1
    
    
    
    
    
    
