/*
 * File:   binary_database_reader.cpp
 * Author: quangpham
 *
 * Created on June 14, 2013, 9:18 PM
 */

#include "binary_database_reader.h"

BinaryDatabaseReader::BinaryDatabaseReader() {
    all_sentences.clear();
    reader.open(kBinaryRecordedDatabasePath);
}

BinaryDatabaseReader::~BinaryDatabaseReader() {
    reader.close();
}

vector<RecordedSentence>& BinaryDatabaseReader::get_all_sentences() {
    return all_sentences;
}

RecordedSentence& BinaryDatabaseReader::get_sentence_at(int index) {
    return all_sentences[index];
}

bool BinaryDatabaseReader::load_data() {
    if (!reader.is_opened()) {
        cerr << "Error loading recorded database description (binary) file" << endl;
        return false;
    }

    cout << "Loading recorded database description (binary) file ..." << endl;
    int n_sentences = reader.read_omega() - 1;

    for (int i = 0; i < n_sentences; ++i) {
        RecordedSentence sentence;
        sentence.set_sentence_id(reader.read_omega() - 1);
        sentence.set_file_name(reader.read_string());

        int n_phrases = reader.read_omega() - 1;

        for (int j = 0; j < n_phrases; ++j) {
            RecordedPhrase phrase;
            phrase.set_phrase_id(reader.read_omega() - 1);

            int n_syllables = reader.read_omega() - 1;
            phrase.set_phrase_length(n_syllables);

            for (int k = 0; k < n_syllables; ++k) {
                RecordedSyllable syllable;

                syllable.set_syllable_id(reader.read_omega() - 1);
                syllable.set_syllable_name(reader.read_string());
                syllable.set_syllable_tone(reader.read_omega() - 1);
                syllable.set_start_index(reader.read_omega() - 1);
                syllable.set_finish_index(reader.read_omega() - 1);

                syllable.set_initial_phoneme_type(reader.read_string());
                syllable.set_initial_phoneme(reader.read_string());
                syllable.set_middle_phoneme_type(reader.read_string());
                syllable.set_middle_phoneme(reader.read_string());
                syllable.set_nucleus_phoneme_type(reader.read_string());
                syllable.set_nucleus_phoneme(reader.read_string());
                syllable.set_final_phoneme_type(reader.read_string());
                syllable.set_final_phoneme(reader.read_string());

                syllable.set_left_syllable_name(reader.read_string());
                syllable.set_left_syllable_tone(reader.read_omega() - 1);
                syllable.set_left_syllable_phoneme_type(reader.read_string());
                syllable.set_left_syllable_final_phoneme(reader.read_string());

                syllable.set_right_syllable_name(reader.read_string());
                syllable.set_right_syllable_tone(reader.read_omega() - 1);
                syllable.set_right_syllable_phoneme_type(reader.read_string());
                syllable.set_right_syllable_initial_phoneme(reader.read_string());

                phrase.add_syllable(syllable);
            }

            sentence.add_phrase(phrase);
        }

        all_sentences.push_back(sentence);
    }

    cout << "Recorded database description (binary) loaded successfully: " << all_sentences.size() << " sentences" << endl << endl;
    return true;
}