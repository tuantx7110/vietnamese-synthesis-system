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

    public static boolean isSilence(String s) {
        s = s.trim();
        return ("NUL".equals(s) || "SIL".equals(s) || "SILS".equals(s));
    }

    public static String getInitial(String s) {
        s = s.trim();
        if ((s.length() == 0) || isEndPhrase(s) || isEndSentence(s) || isSilence(s)) {
            return "NUL";
        }

        if (s.length() >= 2) {
            String start = s.substring(0, 2).trim();
            String[] a = new String[]{"gi", "gh", "tr", "ch", "ph", "th", "kh", "ng", "nh"};
            for (int i = 0; i < a.length; ++i) {
                if (a[i].equals(start)) {
                    return start;
                }
            }
        }

        String start = s.substring(0, 1).trim();
        if ("c".equals(start) || "k".equals(start) || "q".equals(start)) {
            return "c";
        }

        return start;
    }

    public static String getFinal(String s) {
        s = s.trim();
        if ((s.length() == 0) || isEndPhrase(s) || isEndSentence(s) || isSilence(s)) {
            return "NUL";
        }

        if (s.length() >= 2) {
            String finish = s.substring(s.length() - 2).trim();
            String[] a = new String[]{"ch", "ng", "nh"};
            for (int i = 0; i < a.length; ++i) {
                if (a[i].equals(finish)) {
                    return finish;
                }
            }
        }

        return s.substring(s.length() - 1).trim();
    }

    private void writePhrase(int phraseId, int start, int finish) throws Exception {
        eventWriter.add(eventFactory.createStartElement("", "", "phrase"));
        eventWriter.add(eventFactory.createAttribute("id_phrase", Integer.toString(phraseId)));
        eventWriter.add(eventFactory.createAttribute("length", Integer.toString(finish - start + 1)));
        endline();

        for (int i = start; i <= finish; ++i) {
            PhraseInfo phrase = allPhrases.get(i);
            eventWriter.add(eventFactory.createStartElement("", "", "syllable"));
            eventWriter.add(eventFactory.createAttribute("id_syl", Integer.toString(i - start)));
            eventWriter.add(eventFactory.createAttribute("name", phrase.getPhraseContent()));
            eventWriter.add(eventFactory.createAttribute("start_index", Integer.toString(phrase.getStartFrame())));
            eventWriter.add(eventFactory.createAttribute("end_index", Integer.toString(phrase.getFinishFrame())));
            endline();

            eventWriter.add(eventFactory.createStartElement("", "", "initial"));
            eventWriter.add(eventFactory.createCharacters(getInitial(phrase.getPhraseContent())));
            eventWriter.add(eventFactory.createEndElement("", "", "initial"));
            endline();

            eventWriter.add(eventFactory.createStartElement("", "", "final"));
            eventWriter.add(eventFactory.createCharacters(getFinal(phrase.getPhraseContent())));
            eventWriter.add(eventFactory.createEndElement("", "", "final"));
            endline();

            eventWriter.add(eventFactory.createStartElement("", "", "leftSyl"));
            String leftSyllable = (i <= 0 ? "NUL" : allPhrases.get(i - 1).getPhraseContent());
            eventWriter.add(eventFactory.createAttribute("finalPhnm", getFinal(leftSyllable)));
            eventWriter.add(eventFactory.createCharacters(leftSyllable));
            eventWriter.add(eventFactory.createEndElement("", "", "leftSyl"));
            endline();

            eventWriter.add(eventFactory.createStartElement("", "", "rightSyl"));
            String rightSyllable = (i >= allPhrases.size() - 1 ? "NUL" : allPhrases.get(i + 1).getPhraseContent());
            eventWriter.add(eventFactory.createAttribute("initialPhnm", getInitial(rightSyllable)));
            eventWriter.add(eventFactory.createCharacters(rightSyllable));
            eventWriter.add(eventFactory.createEndElement("", "", "rightSyl"));
            endline();

            eventWriter.add(eventFactory.createEndElement("", "", "syllable"));
            endline();
        }

        eventWriter.add(eventFactory.createEndElement("", "", "phrase"));
        endline();
    }

    private void writeSentence(int sentenceId, int start, int finish) throws Exception {
        eventWriter.add(eventFactory.createStartElement("", "", "sentence"));
        eventWriter.add(eventFactory.createAttribute("id_sen", Integer.toString(sentenceId)));
        endline();

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
        endline();
    }

    private void endline() throws Exception {
        eventWriter.add(eventFactory.createDTD("\n"));
    }

    public void writeToXmlFile(File xmlFile) throws Exception {
        XMLOutputFactory outputFactory = XMLOutputFactory.newInstance();
        eventWriter = outputFactory.createXMLEventWriter(new FileOutputStream(xmlFile), "UTF-8");
        eventFactory = XMLEventFactory.newInstance();

        eventWriter.add(eventFactory.createStartDocument());
        endline();
        eventWriter.add(eventFactory.createStartElement("", "", "root"));
        endline();

        eventWriter.add(eventFactory.createStartElement("", "", "file"));
        eventWriter.add(eventFactory.createAttribute("file_name", getFilename()));
        endline();

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
        endline();

        eventWriter.add(eventFactory.createEndElement("", "", "root"));
        endline();

        eventWriter.add(eventFactory.createEndDocument());
        endline();

        eventWriter.close();
    }
}
