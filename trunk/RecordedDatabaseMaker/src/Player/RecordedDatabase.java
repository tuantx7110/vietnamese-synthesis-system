package Player;

import java.util.ArrayList;
import java.util.List;

public class RecordedDatabase {

    private List<PhraseInfo> allPhrases;

    public RecordedDatabase() {
        allPhrases = new ArrayList<PhraseInfo>();
    }

    public void addPhrase(PhraseInfo phrase) {
        allPhrases.add(phrase);
    }
}
