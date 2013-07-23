/*
 * File:   binary_database_converter.cpp
 * Author: quangpham
 *
 * Created on June 13, 2013, 9:05 PM
 */

#include "binary_database_converter.h"

BinaryDatabaseConverter::BinaryDatabaseConverter() {
    database_reader.load_data();
    database_writer.open(kBinaryRecordedDatabasePath);
}

BinaryDatabaseConverter::~BinaryDatabaseConverter() {
    database_writer.close();
}

void BinaryDatabaseConverter::convert_to_binary() {
    if (!database_writer.is_opened()) {
        cerr << "Database writer is not opened" << endl;
        return;
    }

    cout << "Converting XML to binary database ..." << endl;
    vector<RecordedSentence>& all_sentences = database_reader.get_all_sentences();

    int n_sentences = all_sentences.size();
    database_writer.write_omega(n_sentences + 1); // Make sure value is positive

    set<string> distinct_syllables;

    for (int i = 0; i < n_sentences; ++i) {
        RecordedSentence& sentence = all_sentences[i];
        database_writer.write_omega(sentence.get_sentence_id() + 1);
        database_writer.write_string(sentence.get_file_name());

        vector<RecordedPhrase>& phrases = sentence.get_all_phrases();
        int n_phrases = phrases.size();
        database_writer.write_omega(n_phrases + 1);

        for (int j = 0; j < n_phrases; ++j) {
            RecordedPhrase& phrase = phrases[j];
            database_writer.write_omega(phrase.get_phrase_id() + 1);

            vector<RecordedSyllable>& syllables = phrase.get_all_syllables();
            int n_syllables = syllables.size();
            database_writer.write_omega(n_syllables + 1);

            for (int k = 0; k < n_syllables; ++k) {
                RecordedSyllable& syllable = syllables[k];
                distinct_syllables.insert(syllable.get_left_syllable_name());

                database_writer.write_omega(syllable.get_syllable_id() + 1);
                database_writer.write_string(syllable.get_syllable_name());
                database_writer.write_omega(syllable.get_syllable_tone() + 1);
                database_writer.write_omega(syllable.get_start_index() + 1);
                database_writer.write_omega(syllable.get_finish_index() + 1);

                database_writer.write_string(syllable.get_initial_phoneme_type());
                database_writer.write_string(syllable.get_initial_phoneme());
                database_writer.write_string(syllable.get_middle_phoneme_type());
                database_writer.write_string(syllable.get_middle_phoneme());
                database_writer.write_string(syllable.get_nucleus_phoneme_type());
                database_writer.write_string(syllable.get_nucleus_phoneme());
                database_writer.write_string(syllable.get_final_phoneme_type());
                database_writer.write_string(syllable.get_final_phoneme());

                database_writer.write_string(syllable.get_left_syllable_name());
                database_writer.write_omega(syllable.get_left_syllable_tone() + 1);
                database_writer.write_string(syllable.get_left_syllable_phoneme_type());
                database_writer.write_string(syllable.get_left_syllable_final_phoneme());

                database_writer.write_string(syllable.get_right_syllable_name());
                database_writer.write_omega(syllable.get_right_syllable_tone() + 1);
                database_writer.write_string(syllable.get_right_syllable_phoneme_type());
                database_writer.write_string(syllable.get_right_syllable_initial_phoneme());
            }
        }
    }

    cout << "Converted successfully. #Number distinct syllables = " << distinct_syllables.size() << endl;
    save_distinct_syllables(distinct_syllables, kDatabaseStatisticPath);
}

void BinaryDatabaseConverter::save_distinct_syllables(set<string> syllables, string filename) {
    string raw_text = "Number distinct syllables: " + to_string(syllables.size()) + "\n\n";
    for (set<string>::iterator it = syllables.begin(); it != syllables.end(); ++it) {
        raw_text = raw_text + (*it) + "\n";
    }
    write_text_file(filename, raw_text);
}
