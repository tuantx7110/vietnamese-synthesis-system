/*
 * File:   binary_database_converter.cpp
 * Author: quangpham
 *
 * Created on June 13, 2013, 9:05 PM
 */

#include "binary_database_converter.h"

BinaryDatabaseConverter::BinaryDatabaseConverter() {
    database_writer.open(kBinaryRecordedDatabasePath);
}

BinaryDatabaseConverter::BinaryDatabaseConverter(string output_binary_file) {
    database_writer.open(output_binary_file);
}

BinaryDatabaseConverter::~BinaryDatabaseConverter() {
    database_writer.close();
}

bool BinaryDatabaseConverter::convertXmlDatabase(XmlDatabaseReader database_reader) {
    database_reader.load_data();
    return convertXmlDatabase(database_reader.get_all_sentences());
}

bool BinaryDatabaseConverter::convertXmlDatabase(vector<RecordedSentence>& all_sentences) {
    if (!database_writer.is_opened()) {
        cerr << "Database writer is not opened" << endl;
        return false;
    }

    cout << "Converting XML to binary database ..." << endl;

    int n_sentences = all_sentences.size();
    if (!database_writer.write_omega(n_sentences + 1)) {
    	cerr << "Error write n_sentences " << n_sentences << endl;
    	return false;
    }

    for (int i = 0; i < n_sentences; ++i) {
        RecordedSentence& sentence = all_sentences[i];
        if (!database_writer.write_omega(sentence.get_sentence_id() + 1)) {
        	cerr << "Error write sentence id " << sentence.get_sentence_id() << endl;
        	return false;
        }

        if (!database_writer.write_string(sentence.get_file_name())) {
        	cerr << "Error write file name " << sentence.get_file_name() << endl;
        	return false;
        }

        vector<RecordedPhrase>& phrases = sentence.get_all_phrases();
        int n_phrases = phrases.size();

        if (!database_writer.write_omega(n_phrases + 1)) {
        	cerr << "Error write n_phrase " << n_phrases << endl;
        	return false;
        }

        for (int j = 0; j < n_phrases; ++j) {
            RecordedPhrase& phrase = phrases[j];

            if (!database_writer.write_omega(phrase.get_phrase_id() + 1)) {
            	cerr << "Error write phrase id " << phrase.get_phrase_id() << endl;
            	return false;
            }

            vector<RecordedSyllable>& syllables = phrase.get_all_syllables();
            int n_syllables = syllables.size();

            if (!database_writer.write_omega(n_syllables + 1)) {
            	cerr << "Error write n_syllables " << n_syllables << endl;
            	return false;
            }

            for (int k = 0; k < n_syllables; ++k) {
                RecordedSyllable& syllable = syllables[k];

                if (!database_writer.write_omega(syllable.get_syllable_id() + 1)) {
                	cerr << "Error write syllable id " << syllable.get_syllable_id() << endl;
                	return false;
                }

                if (!database_writer.write_string(syllable.get_syllable_name())) {
                	cerr << "Error write syllable name " << syllable.get_syllable_name() << endl;
                	return false;
                }

                if (!database_writer.write_omega(syllable.get_start_index() + 1)) {
                	cerr << "Error write start index " << syllable.get_start_index() << endl;
                	return false;
                }

                if (!database_writer.write_omega(syllable.get_finish_index() + 1)) {
                	cerr << "Error write finish index " << syllable.get_finish_index() << endl;
                	return false;
                }

                if (!database_writer.write_string(syllable.get_initial_phoneme())) {
                	cerr << "Error write initial phoneme " << syllable.get_initial_phoneme() << endl;
                	return false;
                }

                if (!database_writer.write_string(syllable.get_final_phoneme())) {
                	cerr << "Error write final phoneme " << syllable.get_final_phoneme() << endl;
                	return false;
                }

                if (!database_writer.write_string(syllable.get_left_syllable_name())) {
                	cerr << "Error write left syllable name " << syllable.get_left_syllable_name() << endl;
                	return false;
                }

                if (!database_writer.write_string(syllable.get_left_syllable_final_phoneme())) {
                	cerr << "Error write left syllable final phoneme " << syllable.get_left_syllable_final_phoneme() << endl;
                	return false;
                }

                if (!database_writer.write_string(syllable.get_right_syllable_name())) {
                	cerr << "Error write right syllable name " << syllable.get_syllable_name() << endl;
                	return false;
                }

                if (!database_writer.write_string(syllable.get_right_syllable_initial_phoneme())) {
                	cerr << "Error write right syllable initial phoneme " << syllable.get_right_syllable_initial_phoneme() << endl;
                	return false;
                }
            }
        }
    }

    cout << "Converted successfully." << endl;
    return true;
}
