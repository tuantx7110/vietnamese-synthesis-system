package Player;

import java.io.File;
import java.io.FileOutputStream;
import java.util.ArrayList;
import java.util.List;
import javax.xml.stream.XMLEventFactory;
import javax.xml.stream.XMLEventWriter;
import javax.xml.stream.XMLOutputFactory;

public class RecordedDatabase {

    private List<PhraseInfo> allPhrases;
    private XMLEventWriter eventWriter;
    private XMLEventFactory eventFactory;

    public RecordedDatabase() {
        allPhrases = new ArrayList<PhraseInfo>();
    }

    public void clear() {
        allPhrases.clear();
    }

    public void addPhrase(PhraseInfo phrase) {
        allPhrases.add(phrase);
    }

    public boolean isEmpty() {
        return allPhrases.isEmpty();
    }

    public PhraseInfo removeLastPhrase() {
        if (allPhrases.isEmpty()) {
            return null;
        }
        PhraseInfo info = allPhrases.get(allPhrases.size() - 1);
        allPhrases.remove(allPhrases.size() - 1);
        return info;
    }

    private String getFilename() {
        return allPhrases.get(0).getAudioFilename();
    }

    public static boolean isEndSentence(String s) {
        s = s.trim();
        return (".".equals(s) || "?".equals(s) || "!".equals(s));
    }

    public static boolean isEndPhrase(String s) {
        s = s.trim();
        return (",".equals(s) || "-".equals(s));
    }

    private void writePhrase(int phraseId, int start, int finish) throws Exception {
        eventWriter.add(eventFactory.createStartElement("", "", "phrase"));
        eventWriter.add(eventFactory.createAttribute("id_phrase", Integer.toString(phraseId)));
        eventWriter.add(eventFactory.createAttribute("length", Integer.toString(finish - start + 1)));

        for (int i = start; i <= finish; ++i) {
            PhraseInfo phrase = allPhrases.get(i);
            eventWriter.add(eventFactory.createStartElement("", "", "syllable"));
            eventWriter.add(eventFactory.createAttribute("id_syl", Integer.toString(i - start)));
            eventWriter.add(eventFactory.createAttribute("name", phrase.getPhraseContent()));
            eventWriter.add(eventFactory.createAttribute("start_index", Integer.toString(phrase.getStartFrame())));
            eventWriter.add(eventFactory.createAttribute("end_index", Integer.toString(phrase.getFinishFrame())));

            eventWriter.add(eventFactory.createStartElement("", "", "leftSyl"));
            String leftSyllable = (i <= 1 ? "NUL" : allPhrases.get(i - 1).getPhraseContent());
            eventWriter.add(eventFactory.createCharacters(leftSyllable));
            eventWriter.add(eventFactory.createEndElement("", "", "leftSyl"));

            eventWriter.add(eventFactory.createStartElement("", "", "rightSyl"));
            String rightSyllable = (i >= allPhrases.size() - 1 ? "NUL" : allPhrases.get(i + 1).getPhraseContent());
            eventWriter.add(eventFactory.createCharacters(rightSyllable));
            eventWriter.add(eventFactory.createEndElement("", "", "rightSyl"));

            eventWriter.add(eventFactory.createEndElement("", "", "syllable"));
        }

        eventWriter.add(eventFactory.createEndElement("", "", "phrase"));
    }

    private void writeSentence(int sentenceId, int start, int finish) throws Exception {
        eventWriter.add(eventFactory.createStartElement("", "", "sentence"));
        eventWriter.add(eventFactory.createAttribute("id_sen", Integer.toString(sentenceId)));

        int begin = start;
        int phraseId = 0;

        for (int i = start; i <= finish; ++i) {
            if (i == finish || isEndPhrase(allPhrases.get(i).getPhraseContent())) {
                int end = i;
                writePhrase(phraseId, begin, end);
                ++phraseId;
                begin = i + 1;
            }
        }

        eventWriter.add(eventFactory.createEndElement("", "", "sentence"));
    }

    public void writeToXmlFile(File xmlFile) throws Exception {
        XMLOutputFactory outputFactory = XMLOutputFactory.newInstance();
        eventWriter = outputFactory.createXMLEventWriter(new FileOutputStream(xmlFile), "UTF-8");
        eventFactory = XMLEventFactory.newInstance();

        eventWriter.add(eventFactory.createStartDocument());
        eventWriter.add(eventFactory.createStartElement("", "", "root"));

        eventWriter.add(eventFactory.createStartElement("", "", "file"));
        eventWriter.add(eventFactory.createAttribute("file_name", getFilename()));

        int n = allPhrases.size();
        int start = 0;
        int sentenceId = 0;

        for (int i = 0; i < n; ++i) {
            if (i == n - 1 || isEndSentence(allPhrases.get(i).getPhraseContent())) {
                int finish = i;
                writeSentence(sentenceId, start, finish);
                ++sentenceId;
                start = i + 1;
            }
        }

        eventWriter.add(eventFactory.createEndElement("", "", "file"));

        eventWriter.add(eventFactory.createEndElement("", "", "root"));
        eventWriter.add(eventFactory.createEndDocument());
        eventWriter.close();
    }
}
