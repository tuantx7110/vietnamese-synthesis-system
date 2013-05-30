/*
 * File:   recorded_database_reader.cpp
 * Author: quangpham
 *
 * Created on May 28, 2013, 9:19 AM
 */

#include <iostream>
#include <fstream>
using namespace std;

#include "recorded_database_reader.h"
#include "../utils/string_utils.h"

const string RecordedDatabaseReader::kRecordedDatabasePath = "searcher/recorded_database/";
const string RecordedDatabaseReader::kRecordedDatabaseDescriptionPath = kRecordedDatabasePath + "Text_DB_Creator.xml"; //"recorded_database_description.xml";

RecordedDatabaseReader::RecordedDatabaseReader() {
    init();
}

RecordedDatabaseReader::~RecordedDatabaseReader() {
}

void RecordedDatabaseReader::init() {
    current_file_id = -1;
    current_file_name = "";
    all_sentences.clear();
    current_sentence.init();
    current_phrase.init();
    current_syllable.init();
}

vector<RecordedSentence>& RecordedDatabaseReader::get_all_sentences() {
    return all_sentences;
}

bool RecordedDatabaseReader::load_data() {
    ifstream ifs(kRecordedDatabaseDescriptionPath.c_str());

    if (!ifs.is_open()) {
        cerr << "Error loading recorded database description file" << endl;
        return false;
    }

    cout << "Loading recorded database description file ..." << endl;

    string line;
    vector<string> tokens;

    while (getline(ifs, line)) {
        trim_string(line);

        if (line.length() == 0) continue;
        tokens = split_string(line);
        string element = tokens[0];

        if (start_with_string(element, "<root")) continue;
        if (start_with_string(element, "</root")) break;

        if (start_with_string(element, "<file")) {
            if (!read_file_details(tokens)) {
                cerr << "Cannot read file details" << endl;
                return false;
            }
            continue;
        }
        if (start_with_string(element, "</file")) {
            continue;
        }

        if (start_with_string(element, "<sentence")) {
            current_sentence.init();
            if (!read_sentence_details(tokens)) {
                cerr << "Cannot read sentence details" << endl;
                return false;
            }
            continue;
        }
        if (start_with_string(element, "</sentence")) {
            current_sentence.set_file_id(current_file_id);
            current_sentence.set_file_name(current_file_name);
            all_sentences.push_back(current_sentence);
            continue;
        }

        if (start_with_string(element, "<phrase")) {
            current_phrase.init();
            if (!read_phrase_details(tokens)) {
                cerr << "Cannot read phrase details" << endl;
                return false;
            }
            continue;
        }
        if (start_with_string(element, "</phrase")) {
            current_sentence.add_phrase(current_phrase);
            continue;
        }

        if (start_with_string(element, "<syllable")) {
            current_syllable.init();
            if (!read_syllable_details(tokens)) {
                cerr << "Cannot read syllable details" << endl;
                return false;
            }
            continue;
        }
        if (start_with_string(element, "</syllable")) {
            current_phrase.add_syllable(current_syllable);
            if (debug_recorded_database_reader) cout << endl;
            continue;
        }

        if (start_with_string(element, "<initial") || start_with_string(element, "<middle")
                || start_with_string(element, "<nucleus") || start_with_string(element, "<final")) {
            if (!read_phoneme_details(tokens, element.substr(1))) {
                cerr << "Cannot read " + element.substr(1) + " phoneme details" << endl;
                return false;
            }
            continue;
        }

        if (start_with_string(element, "<leftSyl") || start_with_string(element, "<rightSyl")) {
            if (!read_neighbor_syllable_details(tokens, element == "<leftSyl")) {
                cerr << "Cannot read neighbor syllable details" << endl;
                return false;
            }
            continue;
        }

        if (start_with_string(element, "<tone")) {
            string value = "";
            int syllable_tone = -1;
            if (!read_content_value(element, value)) {
                cerr << "Cannot read syllable tone" << endl;
                return false;
            }
            if (!parse_int(value, syllable_tone)) {
                cerr << "Error parsing syllable tone" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << "     Syllable tone = " << syllable_tone << endl;
            current_syllable.set_syllable_tone(syllable_tone);
            continue;
        }
    }

    cout << "Recorded database description loaded successfully: " << all_sentences.size() << " sentences" << endl << endl;
    ifs.close();

    return true;
}

bool RecordedDatabaseReader::read_attribute_value(string s, string& value) {
    int from = first_index_of(s, "\"");
    int to = last_index_of(s, "\"");

    if (from == -1 || to == -1 || from > to) {
        cerr << "Attribute value not found." << endl;
        return false;
    }

    value = s.substr(from + 1, to - from - 1);
    return true;
}

bool RecordedDatabaseReader::read_content_value(string s, string& value) {
    int from = first_index_of(s, ">");
    int to = first_index_of(s, "</");

    if (from == -1 || to == -1 || from > to) {
        cerr << "Content value not found." << endl;
        return false;
    }

    value = s.substr(from + 1, to - from - 1);
    return true;
}

bool RecordedDatabaseReader::read_file_details(vector<string> tokens) {
    for (int i = 1; i < (int) tokens.size(); ++i) {
        string s = tokens[i];
        string value = "";

        if (start_with_string(s, "id_file")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading file id" << endl;
                return false;
            }
            if (!parse_int(value, current_file_id)) {
                cerr << "Error parsing file id" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << current_file_id << endl;
        } else if (start_with_string(tokens[i], "file_name")) {
            if (!read_attribute_value(s, current_file_name)) {
                cerr << "Error reading file name" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << current_file_name << endl;
        }
    }
    return true;
}

bool RecordedDatabaseReader::read_sentence_details(vector<string> tokens) {
    for (int i = 1; i < (int) tokens.size(); ++i) {
        string s = tokens[i];
        string value = "";
        int sentence_id = -1;

        if (start_with_string(s, "id_sen")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading sentence id" << endl;
                return false;
            }
            if (!parse_int(value, sentence_id)) {
                cerr << "Error parsing sentence id" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << "Sentence ID = " << sentence_id << endl;
            current_sentence.set_sentence_id(sentence_id);
        }
    }
    return true;
}

bool RecordedDatabaseReader::read_phrase_details(vector<string> tokens) {
    for (int i = 1; i < (int) tokens.size(); ++i) {
        string s = tokens[i];
        string value = "";
        int phrase_id = -1;
        int phrase_length = -1;

        if (start_with_string(s, "id_phrase")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading phrase id" << endl;
                return false;
            }
            if (!parse_int(value, phrase_id)) {
                cerr << "Error parsing phrase id" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << "  Phrase ID = " << phrase_id << endl;
            current_phrase.set_phrase_id(phrase_id);
        } else if (start_with_string(s, "length")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading phrase length" << endl;
                return false;
            }
            if (!parse_int(value, phrase_length)) {
                cerr << "Error parsing phrase length" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << "  Phrase length = " << phrase_length << endl;
            current_phrase.set_phrase_length(phrase_length);
        }
    }
    return true;
}

bool RecordedDatabaseReader::read_syllable_details(vector<string> tokens) {
    for (int i = 1; i < (int) tokens.size(); ++i) {
        string s = tokens[i];
        string value = "";
        int syllable_id = -1;
        int start_index = -1;
        int finish_index = -1;
        int number_phonemes = -1;
        double energy = -1.0;

        if (start_with_string(s, "id_syl")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading syllable id" << endl;
                return false;
            }
            if (!parse_int(value, syllable_id)) {
                cerr << "Error parsing syllable id" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << "     Syllable ID = " << syllable_id << endl;
            current_syllable.set_syllable_id(syllable_id);
        } else if (start_with_string(s, "name")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading syllable name" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << "     Syllable name = " << value << endl;
            current_syllable.set_syllable_name(value);
        } else if (start_with_string(s, "start_index")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading start index" << endl;
                return false;
            }
            if (!parse_int(value, start_index)) {
                cerr << "Error parsing start index" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << "     Start index  = " << start_index << endl;
            current_syllable.set_start_index(start_index);
        } else if (start_with_string(s, "end_index")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading finish index" << endl;
                return false;
            }
            if (!parse_int(value, finish_index)) {
                cerr << "Error parsing finish index" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << "     Finish index = " << finish_index << endl;
            current_syllable.set_finish_index(finish_index);
        } else if (start_with_string(s, "numOfPhone")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading number phonemes" << endl;
                return false;
            }
            if (!parse_int(value, number_phonemes)) {
                cerr << "Error parsing number phonemes" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << "     Number phonemes = " << number_phonemes << endl;
            current_syllable.set_number_phonemes(number_phonemes);
        } else if (start_with_string(s, "energy")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading energy" << endl;
                return false;
            }
            if (!parse_double(value, energy)) {
                cerr << "Error parsing energy" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << "     Energy = " << energy << endl;
            current_syllable.set_energy(energy);
        }
    }
    return true;
}

bool RecordedDatabaseReader::read_phoneme_details(vector<string> tokens, string which_phoneme) {
    for (int i = 1; i < (int) tokens.size(); ++i) {
        string s = tokens[i];
        string value = "";

        if (start_with_string(s, "type")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading " << which_phoneme << " phoneme type" << endl;
                return false;
            }
            if (debug_recorded_database_reader) cout << "     " << which_phoneme << " phoneme type = " << value << endl;
            if (which_phoneme == "initial") {
                current_syllable.set_initial_phoneme_type(value);
            } else if (which_phoneme == "middle") {
                current_syllable.set_middle_phoneme_type(value);
            } else if (which_phoneme == "nucleus") {
                current_syllable.set_nucleus_phoneme_type(value);
            } else if (which_phoneme == "final") {
                current_syllable.set_final_phoneme_type(value);
            } else {
                cerr << "Unknown phoneme" << endl;
                return false;
            }
        }
    }

    string phoneme = "";
    if (!read_content_value(tokens[(int) tokens.size() - 1], phoneme)) {
        cerr << "Error reading " << which_phoneme << " phoneme content" << endl;
        return false;
    }
    if (debug_recorded_database_reader) cout << "     " << which_phoneme << " phoneme content = " << phoneme << endl;
    if (which_phoneme == "initial") {
        current_syllable.set_initial_phoneme(phoneme);
    } else if (which_phoneme == "middle") {
        current_syllable.set_middle_phoneme(phoneme);
    } else if (which_phoneme == "nucleus") {
        current_syllable.set_nucleus_phoneme(phoneme);
    } else if (which_phoneme == "final") {
        current_syllable.set_final_phoneme(phoneme);
    } else {
        cerr << "Unknown phoneme" << endl;
        return false;
    }
    return true;
}

bool RecordedDatabaseReader::read_neighbor_syllable_details(vector<string> tokens, bool is_left_neighbor) {
    for (int i = 0; i < (int) tokens.size(); ++i) {
        string s = tokens[i];
        string value = "";
        int neighbor_tone;

        if (start_with_string(s, "tone")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading neighbor tone" << endl;
                return false;
            }
            if (!parse_int(value, neighbor_tone)) {
                cerr << "Error parsing neighbor tone" << endl;
                return false;
            }
            if (is_left_neighbor) {
                if (debug_recorded_database_reader) cout << "     Left neighbor tone = " << neighbor_tone << endl;
                current_syllable.set_left_syllable_tone(neighbor_tone);
            } else {
                if (debug_recorded_database_reader) cout << "     Right neighbor tone = " << neighbor_tone << endl;
                current_syllable.set_right_syllable_tone(neighbor_tone);
            }
        } else if (start_with_string(s, "finalPhnm") || start_with_string(s, "initialPhnm")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading neighbor final/initial phoneme" << endl;
                return false;
            }
            if (is_left_neighbor) {
                if (debug_recorded_database_reader) cout << "     Left neighbor final phoneme = " << value << endl;
                current_syllable.set_left_syllable_final_phoneme(value);
            } else {
                if (debug_recorded_database_reader) cout << "     Right neighbor initial phoneme = " << value << endl;
                current_syllable.set_right_syllable_initial_phoneme(value);
            }
        } else if (start_with_string(s, "leftPhnmType") || start_with_string(s, "rightPhnmType")) {
            if (!read_attribute_value(s, value)) {
                cerr << "Error reading neighbor left/right phoneme type" << endl;
                return false;
            }
            if (is_left_neighbor) {
                if (debug_recorded_database_reader) cout << "     Left neighbor phoneme type = " << value << endl;
                current_syllable.set_left_syllable_phoneme_type(value);
            } else {
                if (debug_recorded_database_reader) cout << "     Right neighbor phoneme type = " << value << endl;
                current_syllable.set_right_syllable_phoneme_type(value);
            }
        }
    }
    return true;
}
