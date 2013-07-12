package Player;

import Player.unit.FileUnit;
import Player.unit.PhraseUnit;
import Player.unit.SentenceUnit;
import Player.unit.SyllableUnit;
import java.io.File;
import java.io.FileOutputStream;
import java.util.List;
import javax.xml.stream.XMLEventFactory;
import javax.xml.stream.XMLEventWriter;
import javax.xml.stream.XMLOutputFactory;

public class XmlDatabaseWriter {

    public final String END_INDEX_ATTRIBUTE = "end_index";
    public final String FILE_ELEMENT = "file";
    public final String FILE_NAME_ATTRIBUTE = "file_name";
    public final String FINAL_PHONEME_ATTRIBUTE = "finalPhnm";
    public final String FINAL_PHONEME_ELEMENT = "final";
    public final String ID_PHRASE_ATTRIBUTE = "id_phrase";
    public final String ID_SENTENCE_ATTRIBUTE = "id_sen";
    public final String ID_SYLLABLE_ATTRIBUTE = "id_syl";
    public final String INITIAL_PHONEME_ATTRIBUTE = "initialPhnm";
    public final String INITIAL_PHONEME_ELEMENT = "initial";
    public final String LEFT_SYLLABLE_ELEMENT = "leftSyl";
    public final String PHRASE_ELEMENT = "phrase";
    public final String PHRASE_LENGTH_ATTRIBUTE = "length";
    public final String RIGHT_SYLLABLE_ELEMENT = "rightSyl";
    public final String ROOT_ELEMENT = "root";
    public final String SENTENCE_ELEMENT = "sentence";
    public final String START_INDEX_ATTRIBUTE = "start_index";
    public final String SYLLABLE_ELEMENT = "syllable";
    public final String SYLLABLE_NAME_ATTRIBUTE = "name";
    private File xmlFile;
    private XMLEventWriter eventWriter;
    private XMLEventFactory eventFactory;

    public XmlDatabaseWriter(File xmlFile) {
        this.xmlFile = xmlFile;
    }

    public void open() throws Exception {
        XMLOutputFactory outputFactory = XMLOutputFactory.newInstance();
        eventWriter = outputFactory.createXMLEventWriter(new FileOutputStream(xmlFile), "UTF-8");
        eventFactory = XMLEventFactory.newInstance();

        eventWriter.add(eventFactory.createStartDocument());
        writeEndline();

        eventWriter.add(eventFactory.createStartElement("", "", ROOT_ELEMENT));
        writeEndline();
    }

    public void close() throws Exception {
        eventWriter.add(eventFactory.createEndElement("", "", ROOT_ELEMENT));
        writeEndline();

        eventWriter.add(eventFactory.createEndDocument());
        writeEndline();

        eventWriter.close();
    }

    private void writeEndline() throws Exception {
        eventWriter.add(eventFactory.createDTD("\n"));
    }

    private void writeSyllableUnit(SyllableUnit syllableUnit) throws Exception {
        eventWriter.add(eventFactory.createStartElement("", "", SYLLABLE_ELEMENT));
        eventWriter.add(eventFactory.createAttribute(ID_SYLLABLE_ATTRIBUTE, Integer.toString(syllableUnit.getId())));
        eventWriter.add(eventFactory.createAttribute(SYLLABLE_NAME_ATTRIBUTE, syllableUnit.getName()));
        eventWriter.add(eventFactory.createAttribute(START_INDEX_ATTRIBUTE, Integer.toString(syllableUnit.getStartIndex())));
        eventWriter.add(eventFactory.createAttribute(END_INDEX_ATTRIBUTE, Integer.toString(syllableUnit.getEndIndex())));
        writeEndline();

        eventWriter.add(eventFactory.createStartElement("", "", INITIAL_PHONEME_ELEMENT));
        eventWriter.add(eventFactory.createCharacters(syllableUnit.getInitialPhoneme()));
        eventWriter.add(eventFactory.createEndElement("", "", INITIAL_PHONEME_ELEMENT));
        writeEndline();

        eventWriter.add(eventFactory.createStartElement("", "", FINAL_PHONEME_ELEMENT));
        eventWriter.add(eventFactory.createCharacters(syllableUnit.getFinalPhoneme()));
        eventWriter.add(eventFactory.createEndElement("", "", FINAL_PHONEME_ELEMENT));
        writeEndline();

        eventWriter.add(eventFactory.createStartElement("", "", LEFT_SYLLABLE_ELEMENT));
        eventWriter.add(eventFactory.createAttribute(FINAL_PHONEME_ATTRIBUTE, syllableUnit.getLeftSyllable().getFinalPhoneme()));
        eventWriter.add(eventFactory.createCharacters(syllableUnit.getLeftSyllable().getName()));
        eventWriter.add(eventFactory.createEndElement("", "", LEFT_SYLLABLE_ELEMENT));
        writeEndline();

        eventWriter.add(eventFactory.createStartElement("", "", RIGHT_SYLLABLE_ELEMENT));
        eventWriter.add(eventFactory.createAttribute(INITIAL_PHONEME_ATTRIBUTE, syllableUnit.getRightSyllable().getInitialPhoneme()));
        eventWriter.add(eventFactory.createCharacters(syllableUnit.getRightSyllable().getName()));
        eventWriter.add(eventFactory.createEndElement("", "", RIGHT_SYLLABLE_ELEMENT));
        writeEndline();

        eventWriter.add(eventFactory.createEndElement("", "", SYLLABLE_ELEMENT));
        writeEndline();
    }

    private void writePhraseUnit(PhraseUnit phraseUnit) throws Exception {
        eventWriter.add(eventFactory.createStartElement("", "", PHRASE_ELEMENT));
        eventWriter.add(eventFactory.createAttribute(ID_PHRASE_ATTRIBUTE, Integer.toString(phraseUnit.getId())));
        eventWriter.add(eventFactory.createAttribute(PHRASE_LENGTH_ATTRIBUTE, Integer.toString(phraseUnit.getLength())));
        writeEndline();

        List<SyllableUnit> syllables = phraseUnit.getSyllables();
        for (int i = 0; i < syllables.size(); ++i) {
            writeSyllableUnit(syllables.get(i));
        }

        eventWriter.add(eventFactory.createEndElement("", "", PHRASE_ELEMENT));
        writeEndline();
    }

    private void writeSentenceUnit(SentenceUnit sentenceUnit) throws Exception {
        eventWriter.add(eventFactory.createStartElement("", "", SENTENCE_ELEMENT));
        eventWriter.add(eventFactory.createAttribute(ID_SENTENCE_ATTRIBUTE, Integer.toString(sentenceUnit.getId())));
        writeEndline();

        List<PhraseUnit> phrases = sentenceUnit.getPhrases();
        for (int i = 0; i < phrases.size(); ++i) {
            writePhraseUnit(phrases.get(i));
        }

        eventWriter.add(eventFactory.createEndElement("", "", SENTENCE_ELEMENT));
        writeEndline();
    }

    public void writeFileUnit(FileUnit fileUnit) throws Exception {
        eventWriter.add(eventFactory.createStartElement("", "", FILE_ELEMENT));
        eventWriter.add(eventFactory.createAttribute(FILE_NAME_ATTRIBUTE, fileUnit.getFilename()));
        writeEndline();

        List<SentenceUnit> sentences = fileUnit.getSentences();
        for (int i = 0; i < sentences.size(); ++i) {
            writeSentenceUnit(sentences.get(i));
        }

        eventWriter.add(eventFactory.createEndElement("", "", FILE_ELEMENT));
        writeEndline();
    }
}
