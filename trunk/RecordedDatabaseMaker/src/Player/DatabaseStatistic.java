package Player;

import Player.unit.FileUnit;
import Player.unit.PhraseUnit;
import Player.unit.SentenceUnit;
import Player.unit.SyllableUnit;
import java.io.File;
import java.io.PrintStream;
import java.util.Iterator;
import java.util.List;
import java.util.TreeSet;

public class DatabaseStatistic {

    private int numberFiles;
    private int numberSentences;
    private int numberPhrases;
    private int numberSyllables;
    private TreeSet<String> syllableSet;
    private TreeSet<String> singleWordSet;

    public DatabaseStatistic() {
        numberFiles = 0;
        numberSentences = 0;
        numberPhrases = 0;
        numberSyllables = 0;
        syllableSet = new TreeSet<String>();
        singleWordSet = new TreeSet<String>();
    }

    public void writeStatisticFile(File statisticFile) throws Exception {
        PrintStream out = new PrintStream(statisticFile);
        display(out, true);
    }

    public void display(PrintStream out, boolean showSyllables) {
        out.println("Number files: " + numberFiles);
        out.println("Number sentences: " + numberSentences);
        out.println("Number phrases: " + numberPhrases);
        out.println("Number syllables: " + numberSyllables);
        out.println("Number distinct syllables: " + syllableSet.size());
        out.println("Number distinct single word: " + singleWordSet.size());
        if (showSyllables) {
            out.println("======================== SYLLABLE LIST ========================");
            Iterator<String> iterator = syllableSet.iterator();
            while (iterator.hasNext()) {
                out.println(iterator.next());
            }
            out.println("======================== SINGLE WORD LIST ========================");
            iterator = singleWordSet.iterator();
            while (iterator.hasNext()) {
                out.println(iterator.next());
            }
        }
    }

    public void addFileUnit(FileUnit fileUnit) {
        ++numberFiles;
        List<SentenceUnit> sentences = fileUnit.getSentences();
        for (int i = 0; i < sentences.size(); ++i) {
            addSentenceUnit(sentences.get(i));
        }
    }

    private void addSentenceUnit(SentenceUnit sentenceUnit) {
        ++numberSentences;
        List<PhraseUnit> phrases = sentenceUnit.getPhrases();
        for (int i = 0; i < phrases.size(); ++i) {
            addPhraseUnit(phrases.get(i));
        }
    }

    private void addPhraseUnit(PhraseUnit phraseUnit) {
        ++numberPhrases;
        List<SyllableUnit> syllables = phraseUnit.getSyllables();
        for (int i = 0; i < syllables.size(); ++i) {
            addSyllableUnit(syllables.get(i));
        }
    }

    boolean isWord(String s) {
        if (s.equals("SIL")) {
            return false;
        }
        for (int i = 0; i < s.length(); ++i) {
            final char c = s.charAt(i);
            if (!Character.isLetter(c) && (c != '_') && (c != ' ')) {
                return false;
            }
        }
        return true;
    }

    private void addSyllableUnit(SyllableUnit syllableUnit) {
        final String syllableName = syllableUnit.getName();
        if (!isWord(syllableName)) {
            return;
        }
        ++numberSyllables;
        syllableSet.add(syllableName);
        if (syllableName.indexOf("_") < 0) {
            singleWordSet.add(syllableName);
        }
    }
}
