package Player;

import Player.unit.FileUnit;
import Player.unit.LeftSyllableUnit;
import Player.unit.PhraseUnit;
import Player.unit.RightSyllableUnit;
import Player.unit.SentenceUnit;
import Player.unit.SyllableUnit;
import java.io.File;
import java.io.FileInputStream;
import java.util.Iterator;
import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

public class XmlDatabaseReader {

    public final String END_INDEX_ATTRIBUTE = "end_index";
    public final String FILE_NAME_ATTRIBUTE = "file_name";
    public final String FILE_ELEMENT = "file";
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
    public final String SENTENCE_ELEMENT = "sentence";
    public final String START_INDEX_ATTRIBUTE = "start_index";
    public final String SYLLABLE_ELEMENT = "syllable";
    public final String SYLLABLE_NAME_ATTRIBUTE = "name";
    private File xmlFile;
    private XMLEventReader eventReader;

    public XmlDatabaseReader(File xmlFile) {
        this.xmlFile = xmlFile;
    }

    public FileUnit loadData() throws Exception {
        FileUnit fileUnit = null;
        SentenceUnit sentenceUnit = null;
        PhraseUnit phraseUnit = null;
        SyllableUnit syllableUnit = null;
        LeftSyllableUnit leftSyllableUnit = null;
        RightSyllableUnit rightSyllableUnit = null;

        XMLInputFactory inputFactory = XMLInputFactory.newInstance();
        eventReader = inputFactory.createXMLEventReader(new FileInputStream(xmlFile), "UTF-8");

        while (eventReader.hasNext()) {
            XMLEvent event = eventReader.nextEvent();
            if (event.isStartElement()) {
                StartElement element = event.asStartElement();
                String name = element.getName().getLocalPart();

                if (name.equals(FILE_ELEMENT)) {
                    fileUnit = new FileUnit();
                    Iterator<Attribute> attributes = element.getAttributes();
                    while (attributes.hasNext()) {
                        Attribute attribute = attributes.next();
                        if (attribute.getName().toString().equals(FILE_NAME_ATTRIBUTE)) {
                            fileUnit.setFilename(attribute.getValue());
                        }
                    }
                } else if (name.equals(SENTENCE_ELEMENT)) {
                    sentenceUnit = new SentenceUnit();
                    Iterator<Attribute> attributes = element.getAttributes();
                    while (attributes.hasNext()) {
                        Attribute attribute = attributes.next();
                        if (attribute.getName().toString().equals(ID_SENTENCE_ATTRIBUTE)) {
                            sentenceUnit.setId(Integer.parseInt(attribute.getValue()));
                        }
                    }
                } else if (name.equals(PHRASE_ELEMENT)) {
                    phraseUnit = new PhraseUnit();
                    Iterator<Attribute> attributes = element.getAttributes();
                    while (attributes.hasNext()) {
                        Attribute attribute = attributes.next();
                        final String attributeName = attribute.getName().toString();
                        if (attributeName.equals(ID_PHRASE_ATTRIBUTE)) {
                            phraseUnit.setId(Integer.parseInt(attribute.getValue()));
                        } else if (attributeName.equals(PHRASE_LENGTH_ATTRIBUTE)) {
                            phraseUnit.setLength(Integer.parseInt(attribute.getValue()));
                        }
                    }
                } else if (name.equals(SYLLABLE_ELEMENT)) {
                    syllableUnit = new SyllableUnit();
                    Iterator<Attribute> attributes = element.getAttributes();
                    while (attributes.hasNext()) {
                        Attribute attribute = attributes.next();
                        final String attributeName = attribute.getName().toString();
                        if (attributeName.equals(ID_SYLLABLE_ATTRIBUTE)) {
                            syllableUnit.setId(Integer.parseInt(attribute.getValue()));
                        } else if (attributeName.equals(SYLLABLE_NAME_ATTRIBUTE)) {
                            syllableUnit.setName(attribute.getValue());
                        } else if (attributeName.equals(START_INDEX_ATTRIBUTE)) {
                            syllableUnit.setStartIndex(Integer.parseInt(attribute.getValue()));
                        } else if (attributeName.equals(END_INDEX_ATTRIBUTE)) {
                            syllableUnit.setEndIndex(Integer.parseInt(attribute.getValue()));
                        }
                    }
                } else if (name.equals(INITIAL_PHONEME_ELEMENT)) {
                    event = eventReader.nextEvent();
                    syllableUnit.setInitialPhoneme(event.asCharacters().getData());
                } else if (name.equals(FINAL_PHONEME_ELEMENT)) {
                    event = eventReader.nextEvent();
                    syllableUnit.setFinalPhoneme(event.asCharacters().getData());
                } else if (name.equals(LEFT_SYLLABLE_ELEMENT)) {
                    leftSyllableUnit = new LeftSyllableUnit();
                    Iterator<Attribute> attributes = element.getAttributes();
                    while (attributes.hasNext()) {
                        Attribute attribute = attributes.next();
                        final String attributeName = attribute.getName().toString();
                        if (attributeName.equals(FINAL_PHONEME_ATTRIBUTE)) {
                            leftSyllableUnit.setFinalPhoneme(attribute.getValue());
                        }
                    }
                    event = eventReader.nextEvent();
                    leftSyllableUnit.setName(event.asCharacters().getData());
                } else if (name.equals(RIGHT_SYLLABLE_ELEMENT)) {
                    rightSyllableUnit = new RightSyllableUnit();
                    Iterator<Attribute> attributes = element.getAttributes();
                    while (attributes.hasNext()) {
                        Attribute attribute = attributes.next();
                        final String attributeName = attribute.getName().toString();
                        if (attributeName.equals(INITIAL_PHONEME_ATTRIBUTE)) {
                            rightSyllableUnit.setInitialPhoneme(attribute.getValue());
                        }
                    }
                    event = eventReader.nextEvent();
                    rightSyllableUnit.setName(event.asCharacters().getData());
                }
            } else if (event.isEndElement()) {
                EndElement element = event.asEndElement();
                final String name = element.getName().getLocalPart();

                if (name.equals(FILE_ELEMENT)) {
                    return fileUnit;
                } else if (name.equals(SENTENCE_ELEMENT)) {
                    fileUnit.addSentence(sentenceUnit);
                    sentenceUnit = null;
                } else if (name.equals(PHRASE_ELEMENT)) {
                    sentenceUnit.addPhrase(phraseUnit);
                    phraseUnit = null;
                } else if (name.equals(SYLLABLE_ELEMENT)) {
                    phraseUnit.addSyllable(syllableUnit);
                    syllableUnit = null;
                } else if (name.equals(LEFT_SYLLABLE_ELEMENT)) {
                    syllableUnit.setLeftSyllable(leftSyllableUnit);
                    leftSyllableUnit = null;
                } else if (name.equals(RIGHT_SYLLABLE_ELEMENT)) {
                    syllableUnit.setRightSyllable(rightSyllableUnit);
                    rightSyllableUnit = null;
                }
            }
        }

        return fileUnit;
    }
}
