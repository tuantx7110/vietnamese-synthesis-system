#include "test_database_reader.h"

void test_xml_database_reader() {
    XmlDatabaseReader reader;
    reader.load_data();
}

void test_binary_database_reader() {
    BinaryDatabaseReader reader;
    reader.load_data();

    vector<RecordedSentence>& sentences = reader.get_all_sentences();
    for (int i = 0; i < (int) sentences.size(); ++i) {
        RecordedSentence sentence = sentences[i];
        cout << sentence.get_sentence_id() << " " << sentence.get_file_name() << endl;

        vector<RecordedPhrase>& phrases = sentence.get_all_phrases();
        for (int j = 0; j < (int) phrases.size(); ++j) {
            RecordedPhrase phrase = phrases[j];
            cout << " - " << phrase.get_phrase_id() << " " << phrase.get_phrase_length() << endl;

            vector<RecordedSyllable>& syllables = phrase.get_all_syllables();
            for (int k = 0; k < (int) syllables.size(); ++k) {
                RecordedSyllable syllable = syllables[k];
                cout << "    + " << syllable.get_syllable_id() << " " << syllable.get_syllable_name() << " "
                        << syllable.get_syllable_tone() << " " << syllable.get_start_index() << " " << syllable.get_finish_index();
                cout << " " << syllable.get_initial_phoneme() << " " << syllable.get_middle_phoneme() << " " << syllable.get_nucleus_phoneme() << " " << syllable.get_final_phoneme();
                cout << " " << syllable.get_left_syllable_name() << " " << syllable.get_right_syllable_name() << endl;
            }
        }
    }
}
