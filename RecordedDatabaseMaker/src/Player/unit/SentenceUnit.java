package Player.unit;

import java.util.ArrayList;
import java.util.List;

public class SentenceUnit {

    private int id;
    private List<PhraseUnit> phrases;

    public SentenceUnit() {
        id = -1;
        phrases = new ArrayList<PhraseUnit>();
    }

    public void addPhrase(PhraseUnit phrase) {
        phrases.add(phrase);
    }

    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

    /**
     * @param id the id to set
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * @return the phrases
     */
    public List<PhraseUnit> getPhrases() {
        return phrases;
    }

    /**
     * @param phrases the phrases to set
     */
    public void setPhrases(List<PhraseUnit> phrases) {
        this.phrases = phrases;
    }
}
