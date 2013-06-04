/*
 * input_text_reader.cpp
 *
 *  Created on: May 29, 2013
 *      Author: quangpham
 */

#include "input_text_reader.h"

InputTextReader::InputTextReader() {
    // TODO Auto-generated constructor stub

}

InputTextReader::~InputTextReader() {
    // TODO Auto-generated destructor stub
}

vector<SearchingSentence>& InputTextReader::get_all_sentences() {
    return all_searching_sentences;
}

bool InputTextReader::init() {
    if (!tokenizer.load_configure()) {
        cerr << "Cannot load tokenizer" << endl;
        return false;
    }

    raw_input_text = "";
    tokens.clear();
    all_searching_sentences.clear();

    return true;
}

bool InputTextReader::read_input_text_file(string file_name) {
    if (!read_text_file(file_name, raw_input_text)) {
        cerr << "Cannot read input text file" << endl;
        return false;
    }

    if (debug_input_text_reader) cout << "Raw input text = " + raw_input_text << endl;

    if (!parse_input_text()) {
        cerr << "Error parsing input text" << endl;
        return false;
    }

    return true;

}

bool InputTextReader::parse_input_text() {
    tokens = tokenizer.segment(raw_input_text);

    if (debug_input_text_reader) {
        cout << "Segmented text = ";
        for (int i = 0; i < (int) tokens.size(); ++i) {
            cout << tokens[i] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < (int) tokens.size(); ++i) {
        replace_all(tokens[i], '_', ' ');
        trim_string(tokens[i]);
    }

    all_searching_sentences.clear();

    SearchingSentence searching_sentence;
    SearchingPhrase searching_phrase;
    SearchingPhrase sub_phrase;

    searching_sentence.init();
    bool sentence_empty = true;

    int number_tokens = (int) tokens.size();
    for (int i = 0; i <= number_tokens; ++i) {
        if ((i == number_tokens) || (is_punctuation(tokens[i]))) {
            if (!sentence_empty) {
                searching_phrase.init();
                searching_phrase.set_phrase_level(1);
                searching_phrase.set_phrase_content((i == number_tokens || is_long_silence(tokens[i])) ? "SILS" : "SIL");
                searching_sentence.add_searching_phrase(searching_phrase);

                all_searching_sentences.push_back(searching_sentence);
                searching_sentence.init();
                sentence_empty = true;
            }
            continue;
        }

        searching_phrase.init();
        searching_phrase.set_phrase_content(tokens[i]);
        searching_phrase.set_phrase_level(1);

        vector<string> words = split_string(tokens[i]);
        if (words.size() > 1) {
            for (int i = 0; i < (int) words.size(); ++i) {
                sub_phrase.init();
                sub_phrase.set_phrase_content(words[i]);
                sub_phrase.set_phrase_level(2);
                searching_phrase.add_sub_phrase(sub_phrase);
            }
        }

        searching_sentence.add_searching_phrase(searching_phrase);
        sentence_empty = false;
    }

    if (debug_input_text_reader) {
        cout << endl << "Total sentence = " << all_searching_sentences.size() << endl;
        for (int i = 0; i < (int) all_searching_sentences.size(); ++i) {
            searching_sentence = all_searching_sentences[i];
            cout << "Sentence " << (i + 1) << " = " << searching_sentence.get_sentence_content() << endl;

            vector<SearchingPhrase>& searching_phrases = searching_sentence.get_searching_phrases();
            for (int j = 0; j < (int) searching_phrases.size(); ++j) {
                searching_phrase = searching_phrases[j];
                cout << "  Phrase " << (j + 1) << " = " << searching_phrase.get_phrase_content() << " " << searching_phrase.get_phrase_level() << endl;

                if (searching_phrase.has_sub_phrase()) {
                    vector<SearchingPhrase>& sub_phrases = searching_phrase.get_sub_phrases();
                    for (int k = 0; k < (int) sub_phrases.size(); ++k) {
                        sub_phrase = sub_phrases[k];
                        cout << "    Sub-phrase " << (k + 1) << " = " << sub_phrase.get_phrase_content() << " " << sub_phrase.get_phrase_level() << endl;
                    }
                }
            }
        }
        cout << endl;
    }

    return true;
}
